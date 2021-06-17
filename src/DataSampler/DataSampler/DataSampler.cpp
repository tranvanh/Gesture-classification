#include <iostream>
#include <functional>
#include <vector>
#include "MultiLeap.h"

#include "SampleLeap/GestureRecorder.h"


#define DYNAMIC_TIMESTEP 120

#define TIMESTEP 90
#define NUM_FEATURES 31
#define COUNT 0
constexpr unsigned int hash(const char* s, int off = 0) {
	return !s[off] ? 5381 : (hash(s, off + 1) * 33) ^ s[off];
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

/** Callback for when a frame of tracking data is available. */
static void OnFrame(const LEAP_TRACKING_EVENT* frame, const unsigned deviceId, float deviation, void* context) {
	for (uint32_t h = 0; h < frame->nHands; h++) {
		LEAP_HAND* hand = &frame->pHands[h];
		printf("    Hand id %i from device %i is a %s hand with position (%f, %f, %f) with confidence %f and deviation %f.\n",
			hand->id,
			deviceId,
			(hand->type == eLeapHandType_Left ? "left" : "right"),
			hand->palm.position.x,
			hand->palm.position.y,
			hand->palm.position.z,
			hand->confidence,
			deviation);
	}
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
	std::string gestureType = "";
	std::cout << "Enter gesture Type" << std::endl;
	std::cin >> gestureType;

	static GestureRecorder gestureRecorder(TIMESTEP, NUM_FEATURES, COUNT, gestureType);

	std::cout << "Starting communication." << std::endl;
	LeapCallbacks leapCallbacks{};
	leapCallbacks.onConnection = OnConnect;
	leapCallbacks.onConnectionLost = OnConnectionLost;
	leapCallbacks.onDeviceFound = OnDevice;
	leapCallbacks.onDeviceLost = OnDeviceLost;
	leapCallbacks.onDeviceFailure = OnDeviceFailure;
	leapCallbacks.onFrame = OnFrame;
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
		case hash("record"):
		{
			std::cout << "start Recording" << std::endl;
			gestureRecorder.startRecording();
			break;
		}
		case  hash("pause"):
		{
			std::cout << "pause Recording" << std::endl;
			gestureRecorder.pauseRecording();
			break;
		}
		case hash("record --open"):
		{
			std::cout << "open Recording" << std::endl;
			gestureRecorder.openRecording();
			break;
		}
		case hash("record --dynamic"):
		{
			std::cout << "start dynamic Recording" << std::endl;
			gestureRecorder.startDynamicRecording(DYNAMIC_TIMESTEP);
			break;
		}
		case 'x':
		{
			int index = 0;
			std::string gestureType = "";
			std::cin >> gestureType >> index;
			std::cout << "reinit Recorder: gesture type[" << gestureType << "] file index[" << index << "]" << std::endl;
			gestureRecorder.reinitRecording(gestureType, index);
			break;
		}
		default:
			break;
		}
	} while (hash("close") != hash(command.c_str()));

	std::cout << "Stopping communication." << std::endl;

	MultiLeap_Deinit();
	delete context;
	return 0;
}