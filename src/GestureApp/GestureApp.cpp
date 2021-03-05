#include <iostream>
#include "MultiLeap.h"

#include "../includes/cppflow/ops.h"
#include "../includes/cppflow/model.h"
#include <vector>
#include "model/Model.h"
#include "GestureLeap/geastureLeap.h"

#include <functional>


/** Callback for when the connection opens. */
static void OnConnect() {
	std::cout << "Connected." << std::endl;
}

/** Callback for when the connection breaks. */
static void OnConnectionLost() {
	std::cout << "ConnectionLost." << std::endl;
}

/** Callback for when a device is found. */
static void OnDevice(const LEAP_DEVICE_INFO* props, const int* handle, const unsigned id) {
	std::cout << "Found device with id " << id << " and serial number " << props->serial << std::endl;
}

/** Callback for when a device is lost. */
static void OnDeviceLost(const char* device)
{
	std::cout << "Lost device " << device << std::endl;
}

/** Callback for when a device fails. */
static void OnDeviceFailure(const LEAP_DEVICE_FAILURE_EVENT* device_failure_event)
{
	std::cout << "Failed device " << device_failure_event->status << std::endl;
}

/** Callback for when a frame of tracking data is available. */
static void OnFrame(const LEAP_TRACKING_EVENT* frame, const unsigned deviceId) {
	for (uint32_t h = 0; h < frame->nHands; h++) {
		LEAP_HAND* hand = &frame->pHands[h];
		printf("    Hand id %i from device %i is a %s hand with position (%f, %f, %f) with confidence %f.\n",
			hand->id,
			deviceId,
			(hand->type == eLeapHandType_Left ? "left" : "right"),
			hand->palm.position.x,
			hand->palm.position.y,
			hand->palm.position.z,
			hand->confidence);
	}
}

/** Callback for when a sample loop is ran. */
static void OnSample(const bool status, const int count, const char* failedDevices)
{
	if (status) {
		std::cout << count << " samples taken." << std::endl;
	}
	else {
		std::cout << "Failed to take samples. Devices \"" << failedDevices << "\" do not see the hand." << std::endl;
	}
}

/** Callback for when a message is sent. */
static void OnLogMessage(const eLeapLogSeverity severity, const int64_t timestamp,
	const char* message) {
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

	std::cout << "Starting communication." << std::endl;


	static GestureLeap leap(200,31);
	tracking_callback onFrame = [](const LEAP_TRACKING_EVENT* frame, const unsigned deviceId) { leap.OnFrame(frame, deviceId); };

	if (!MultiLeap::Init(&OnConnect, &OnConnectionLost,
		&OnDevice, &OnDeviceLost, &OnDeviceFailure, onFrame, &OnLogMessage, &OnSample)) {
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
			MultiLeap::CalibrateDevices(200);
			break;
		case 'm':
			merge = !merge;
			MultiLeap::MergeHands(merge);
			break;
		case 'd':
			deviceEnabled = !deviceEnabled;
			MultiLeap::SetDeviceStatus(1, deviceEnabled);
			break;
		case 'g':
		{
			size_t size = 0;
			MultiLeap::GetDeviceTransformation(1, nullptr, size);
			char* result = new char[size];
			MultiLeap::GetDeviceTransformation(1, result, size);
			std::cout << result << std::endl;
			delete[] result;
			break;
		}
		case 's':
		{
			MultiLeap::SetDeviceTransformation(1, "{\"rotation\":{\"w\":1.0,\"x\":1.0,\"y\":0.0,\"z\":0.0},\"scale\":{\"x\":1.0,\"y\":1.0,\"z\":1.0},\"translation\":{\"x\":1.0,\"y\":1.0,\"z\":1.0}}");
			break;
		}
		case 'i':
		{
			size_t count = 0;
			MultiLeap::GetDevices(nullptr, nullptr, count);
			LEAP_DEVICE_INFO* info = new LEAP_DEVICE_INFO[count];
			for (size_t i = 0; i < count; i++) {
				info->serial = nullptr;
			}
			int* ids = new int[count];
			if (MultiLeap::GetDevices(info, ids, count)) {
				for (size_t i = 0; i < count; i++) {
					info->serial = new char[info->serial_length];
				}
				if (MultiLeap::GetDevices(info, ids, count)) {
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
			if (MultiLeap::GetDevice(id, info) && info) {
				std::cout << "Device with id " << id << " has serial number " << info->serial << "." << std::endl;
				delete[] info->serial;
			}
			delete info;
			break;
		}
		case 't':
		{
			std::cout << MultiLeap::GetInterpolatedFrameSize(1, MultiLeap::GetLeapNow()) << std::endl;
			break;
		}
		case 'f':
		{
			const LEAP_TRACKING_EVENT* frame = MultiLeap::GetInterpolatedFrame(1, MultiLeap::GetLeapNow());
			if (frame) {
				std::cout << frame->nHands << std::endl;
				delete frame;
			}
			break;
		}
		default:
			break;
		}
	} while (c != 'c');

	std::cout << "Stopping communication." << std::endl;

	MultiLeap::Deinit();

	return 0;

}