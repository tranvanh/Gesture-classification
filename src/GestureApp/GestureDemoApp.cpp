#include <iostream>
#include <functional>
#include <vector>

#include "MultiLeap.h"

#include "../includes/cppflow/ops.h"
#include "../includes/cppflow/model.h"
#include "GestureLeap/GeastureLeap.h"


#define MODEL_DIR "./LSTM_model"
#define TIMESTEP 60
#define NUM_FEATURES 31


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


	static GestureLeap gestureLeap(MODEL_DIR, TIMESTEP, NUM_FEATURES);
	tracking_callback onFrame = [](const LEAP_TRACKING_EVENT* frame, const unsigned deviceId, void* cxt) { gestureLeap.onFrame(frame, deviceId, cxt); };

	if (!MultiLeap_InitCallbacksConnection(&OnConnect, &OnConnectionLost,
		&OnDevice, &OnDeviceLost, &OnDeviceFailure, onFrame, &OnLogMessage, &OnSample, (void*)context)) {
		std::cout << "Failed to init MultiLeap." << std::endl;
		return 0;
	}
	char c = '\n';
	bool merge = true;
	bool deviceEnabled = true;
	do {
		std::cin >> c;

		switch (c)
		{
		case 'a':
			MultiLeap_CalibrateDevices(2500);
			break;
		case 'm':
			merge = !merge;
			MultiLeap_MergeHands(merge);
			break;
		case 'd':
			deviceEnabled = !deviceEnabled;
			MultiLeap_SetDeviceStatus(1, deviceEnabled);
			break;
		case 'g':
		{
			size_t size = 0;
			MultiLeap_GetDeviceTransformation(1, nullptr, size);
			char* result = new char[size];
			MultiLeap_GetDeviceTransformation(1, result, size);
			std::cout << result << std::endl;
			delete[] result;
			break;
		}
		case 's':
		{
			MultiLeap_SetDeviceTransformation(1, "{\"rotation\":{\"w\":1.0,\"x\":1.0,\"y\":0.0,\"z\":0.0},\"scale\":{\"x\":1.0,\"y\":1.0,\"z\":1.0},\"translation\":{\"x\":1.0,\"y\":1.0,\"z\":1.0}}");
			break;
		}
		case 'p':
		{
			MultiLeap_Vector3f* position = new MultiLeap_Vector3f();
			MultiLeap_Quaternionf* rotation = new MultiLeap_Quaternionf();
			MultiLeap_GetDeviceTransformationRaw(1, position, rotation);

			std::cout << "Pivot is:" << std::endl
				<< "position: " << position->x << ", " << position->y << ", " << position->z << std::endl
				<< "rotation: " << rotation->x << ", " << rotation->y << ", " << rotation->z << ", " << rotation->w << "." << std::endl;


			MultiLeap_SetDeviceTransformationRaw(1, MultiLeap_Vector3f{ 3,5,6 }, MultiLeap_Quaternionf{ 1,7,12,9 });

			MultiLeap_GetDeviceTransformationRaw(1, position, rotation);

			std::cout << "Pivot is:" << std::endl
				<< "position: " << position->x << ", " << position->y << ", " << position->z << std::endl
				<< "rotation: " << rotation->x << ", " << rotation->y << ", " << rotation->z << ", " << rotation->w << "." << std::endl;

			delete position;
			delete rotation;
			break;
		}
		case 'i':
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
						std::cout << "Device with id " << ids[i] << " has serial number " << info[i].serial << "." << std::endl;
						delete[] info[i].serial;
					}
				}
			}
			delete[] info;
			delete[] ids;
			break;
		}
		case 'j':
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
		case 't':
		{
			std::cout << MultiLeap_GetInterpolatedFrameSize(1, MultiLeap_GetLeapNow()) << std::endl;
			break;
		}
		case 'v':
		{
			std::cout << "ID of the virtual device is " << MultiLeap_GetVirtualDeviceId() << "." << std::endl;
			break;
		}
		case 'f':
		{
			const LEAP_TRACKING_EVENT* frame = MultiLeap_GetInterpolatedFrame(1, MultiLeap_GetLeapNow());
			if (frame) {
				std::cout << frame->nHands << std::endl;
				delete frame;
			}
			break;
		}
		case 'r':
		{
			std::cout << "Setting reference device to 8." << std::endl;
			if (!MultiLeap_SetPivotId(8)) {
				std::cout << "Setting reference device to 8 failed." << std::endl;
			}

			std::cout << "Setting reference device to 42." << std::endl;
			if (!MultiLeap_SetPivotId(42)) {
				std::cout << "Setting reference device to 42 failed." << std::endl;
			}

			std::cout << "Setting reference device to 2." << std::endl;
			if (MultiLeap_SetPivotId(2)) {
				std::cout << "Setting reference device to 2 succeeded." << std::endl;
			}
			std::cout << "Current reference device is " << MultiLeap_GetPivotId() << "." << std::endl;

			break;
		}
		default:
			break;
		}
	} while (c != 'c');

	std::cout << "Stopping communication." << std::endl;
	gestureLeap.getSuccessRate();

	MultiLeap_Deinit();
	delete context;
	return 0;
}