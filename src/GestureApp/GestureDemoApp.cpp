#include <iostream>
#include <functional>
#include <vector>

#include "MultiLeap.h"

#include "../includes/cppflow/ops.h"
#include "../includes/cppflow/model.h"
#include "GestureLeap/GeastureLeap.h"
#include "GestureLeap/ConfigManager.h"

/**Disclamer: Initialization is extended from MultiLeapCallbackTest file **/

constexpr unsigned int hash(const char* s, int off = 0) {
	return !s[off] ? 5381 : (hash(s, off + 1) * 33) ^ s[off];
}


void printHelp() {
	std::cout << "calibrate  => Calibrate devices" << std::endl;
	std::cout << "merge      => Merge hands" << std::endl;
	std::cout << "stopMerge  => Stop merging hands" << std::endl;
	std::cout << "help       => show available commands" << std::endl;
}

/** Callback for when the connection opens. */
static void OnConnect(void* context) {
	std::cout << "Connected." << std::endl;
}

/** Callback for when the connection breaks. */
static void OnConnectionLost(void* context) {
	std::cout << "ConnectionLost." << std::endl;
}

/** Callback for when a device is found. */
static void OnDevice(const LEAP_DEVICE_INFO* props, const int* handle, const unsigned id, void* context) {
	std::cout << "Found device with id " << id << " and serial number " << props->serial << std::endl;
}

/** Callback for when a device is lost. */
static void OnDeviceLost(const char* device, void* context)
{
	std::cout << "Lost device " << device << std::endl;
}

/** Callback for when a device fails. */
static void OnDeviceFailure(const LEAP_DEVICE_FAILURE_EVENT* deviceFailureEvent, void* context)
{
	std::cout << "Failed device " << deviceFailureEvent->status << std::endl;
}


/** Callback for when a sample loop is ran. */
static void OnSample(const int deviceCount, const uint32_t* ids, const int* completion, void* context)
{
	for (int i = 0; i < deviceCount; i++) {
		std::cout << "Calibration for device " << ids[i] << " has " << completion[i] << " percent completion." << std::endl;
	}
}

/** Callback for when a message is sent. */
static void OnLogMessage(const eLeapLogSeverity severity, const int64_t timestamp,
	const char* message, void* context) {
	const char* severity_str;
	switch (severity) {
	case eLeapLogSeverity_Critical:
		severity_str = "Critical";
		break;
	case eLeapLogSeverity_Warning:
		severity_str = "Warning";
		break;
	case eLeapLogSeverity_Information:
		severity_str = "Info";
		break;
	default:
		severity_str = "";
		break;
	}
	printf("[%s][%lli] %s\n", severity_str, (long long int)timestamp, message);
}


int main(int argc, char** argv) {
	int* context = new int(256);

	std::cout << "Starting communication." << std::endl;
	static GestureLeap gestureLeap;

	LeapCallbacks leapCallbacks{};
	leapCallbacks.onConnection = OnConnect;
	leapCallbacks.onConnectionLost = OnConnectionLost;
	leapCallbacks.onDeviceFound = OnDevice;
	leapCallbacks.onDeviceLost = OnDeviceLost;
	leapCallbacks.onDeviceFailure = OnDeviceFailure;
	leapCallbacks.onFrame = [](const LEAP_TRACKING_EVENT* frame, const unsigned deviceId, float deviation, void* cxt) { gestureLeap.onFrame(frame, deviceId, deviation, cxt); };
	leapCallbacks.onLogMessage = OnLogMessage;

	MultiLeapCallbacks multileapCallbacks{};
	multileapCallbacks.onCalibrationSample = OnSample;

	if (!MultiLeap_InitCallbacksConnection(leapCallbacks, multileapCallbacks, (void*)context)) {
		std::cout << "Failed to init MultiLeap." << std::endl;
		return 0;
	}
	std::string command = "\n";
	bool deviceEnabled = true;
	do {
		std::cin >> command;

		switch (hash(command.c_str()))
		{
		case hash("calibrate"):
		{
			gestureLeap.stop();
			MultiLeap_CalibrateDevices(2500);
			break;
		}
		case hash("merge"):
			MultiLeap_MergeHands(MergeMode::COMBINATION);
			gestureLeap.listen();

			break;
		case hash("best"):
			MultiLeap_MergeHands(MergeMode::BEST);
			break;
		case hash("stopMerge"):
			MultiLeap_MergeHands(MergeMode::NONE);
			break;
		case hash("disable"):
			deviceEnabled = !deviceEnabled;
			MultiLeap_SetDeviceStatus(1, false);
			break;
		case hash("getTransformation"):
		{
			size_t size = 0;
			MultiLeap_GetDeviceTransformation(1, nullptr, size);
			char* result = new char[size];
			MultiLeap_GetDeviceTransformation(1, result, size);
			std::cout << result << std::endl;
			delete[] result;
			break;
		}
		case hash("setTransformation"):
		{
			MultiLeap_SetDeviceTransformation(1, "{\"rotation\":{\"w\":1.0,\"x\":1.0,\"y\":0.0,\"z\":0.0},\"scale\":{\"x\":1.0,\"y\":1.0,\"z\":1.0},\"translation\":{\"x\":1.0,\"y\":1.0,\"z\":1.0}}");
			break;
		}
		case hash("rawTransform"):
		{
			MultiLeap_Vector3f* position = new MultiLeap_Vector3f();
			MultiLeap_Quaternionf* rotation = new MultiLeap_Quaternionf();
			MultiLeap_GetDeviceTransformationRaw(1, position, rotation);

			std::cout << "Pivot has:" << std::endl
				<< "position: " << position->x << ", " << position->y << ", " << position->z << std::endl
				<< "rotation: " << rotation->x << ", " << rotation->y << ", " << rotation->z << ", " << rotation->w << "." << std::endl;


			MultiLeap_SetDeviceTransformationRaw(1, MultiLeap_Vector3f{ 3,5,6 }, MultiLeap_Quaternionf{ 1,7,12,9 });

			MultiLeap_GetDeviceTransformationRaw(1, position, rotation);

			std::cout << "Pivot has:" << std::endl
				<< "position: " << position->x << ", " << position->y << ", " << position->z << std::endl
				<< "rotation: " << rotation->x << ", " << rotation->y << ", " << rotation->z << ", " << rotation->w << "." << std::endl;

			delete position;
			delete rotation;
			break;
		}
		case hash("getDevices"):
		{
			size_t count = 0;
			MultiLeap_GetDevices(nullptr, nullptr, count);
			LEAP_DEVICE_INFO* info = new LEAP_DEVICE_INFO[count];
			for (size_t i = 0; i < count; i++) {
				info[i].serial = nullptr;
			}
			int* ids = new int[count];
			if (MultiLeap_GetDevices(info, ids, count)) {
				for (size_t i = 0; i < count; i++) {
					info[i].serial = new char[info->serial_length];
				}
				if (MultiLeap_GetDevices(info, ids, count)) {
					for (size_t i = 0; i < count; i++) {
						std::cout << "Device with id " << ids[i] << " has serial number " << info[i].serial << "." << " status [" << info[i].status << "]"<< std::endl;
						delete[] info[i].serial;
					}
				}
			}
			delete[] info;
			delete[] ids;
			break;
		}
		case hash("getDevice"):
		{
			LEAP_DEVICE_INFO* info = new LEAP_DEVICE_INFO;
			unsigned id = 1;
			if (MultiLeap_GetDevice(id, info) && info) {
				std::cout << "Device with id " << id << " has serial number " << info->serial << "." << std::endl;
				delete[] info->serial;
			}
			delete info;
			break;
		}
		case hash("interpolateSize"):
		{
			std::cout << MultiLeap_GetInterpolatedFrameSize(1, MultiLeap_GetLeapNow()) << std::endl;
			break;
		}
		case hash("interpolate"):
		{
			const LEAP_TRACKING_EVENT* frame = MultiLeap_GetInterpolatedFrame(1, MultiLeap_GetLeapNow());
			if (frame) {
				std::cout << frame->nHands << std::endl;
				delete frame;
			}
			break;
		}
		case hash("virtual"):
		{
			std::cout << "ID of the virtual device is " << MultiLeap_GetVirtualDeviceId() << "." << std::endl;
			break;
		}
		case hash("stopCalibration"):
		{
			if (!MultiLeap_IsCalibrationRunning()) {
				std::cout << "Calibration is not running." << std::endl;
				break;
			}
			MultiLeap_StopCalibration();
			std::cout << "Calibration stopped." << std::endl;
			gestureLeap.listen();
			break;
		}
		case hash("isCalibrated"):
		{
			std::cout << "The device with ID 2 is " << (MultiLeap_IsDeviceCalibrated(2) ? "" : "not ") << "calibrated." << std::endl;
			break;
		}
		case hash("setCalibrated"):
		{
			std::cout << "Setting calibrated for device with ID 2." << std::endl;
			MultiLeap_SetDeviceCalibrated(2, false);
			break;
		}
		case hash("policy"):
		{
			std::cout << "Setting Leap Policy to eLeapPolicyFlag_OptimizeHMD." << std::endl;
			std::cout << MultiLeap_SetLeapPolicyFlags(eLeapPolicyFlag_OptimizeHMD, 0) << std::endl;
			break;
		}
		case hash("save"):
		{

			std::cout << MultiLeap_SaveConfiguration() << std::endl;
			break;
		}
		case hash("load"):
		{

			std::cout << MultiLeap_LoadConfiguration() << std::endl;
			break;
		}
		case hash("reinit"):
		{
			gestureLeap.getSuccessRate();
			gestureLeap.getInvalidAcc();
			gestureLeap.reinit();
			std::cout << "DEMO APP REINIT" << std::endl;
			break;
		}
		case hash("help"):
		{
			printHelp();
		}
		default:
			break;
		}
	} while(hash("close") != hash(command.c_str()));

	std::cout << "Stopping communication." << std::endl;
	MultiLeap_Deinit();
	delete context;
	return 0;
}