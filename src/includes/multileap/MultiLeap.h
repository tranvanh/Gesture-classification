#ifndef MultiLeap_h
#define MultiLeap_h

#ifdef MULTILEAP_EXPORTS
#define MULTILEAP_API __declspec(dllexport)
#else
#define MULTILEAP_API __declspec(dllimport)
#endif

#include "LeapCallbacks.h"

namespace MultiLeap
{

	/// <summary>
	/// Initialize the library and register all Leap Motion callbacks.
	/// </summary>
	/// <param name="onConnection">Leap Motion callback called on successful connection.</param>
	/// <param name="onConnectionLost">Leap Motion callback called on connection lost.</param>
	/// <param name="onDevice">Leap Motion callback called on device connection.</param>
	/// <param name="onDeviceLost">Leap Motion callback called on device lost.</param>
	/// <param name="onDeviceFailure">Leap Motion callback called on device failure.</param>
	/// <param name="onFrame">Leap Motion callback called on frame.</param>
	/// <param name="onLogMessage">Leap Motion callback called on sent log message.</param>
	/// <param name="onSample">MultiLeap callback called when calibration sample loop is ran.</param>
	extern "C" MULTILEAP_API bool Init(connection_callback onConnection, connection_callback onConnectionLost,
		device_callback onDevice, device_lost_callback onDeviceLost, device_failure_callback onDeviceFailure,
		tracking_callback onFrame, log_callback onLogMessage, calibration_sample_callback onSample);

	/// <summary>
	/// Set the library callbacks.
	/// </summary>
	/// <param name="onConnection">Leap Motion callback called on successful connection.</param>
	/// <param name="onConnectionLost">Leap Motion callback called on connection lost.</param>
	/// <param name="onDevice">Leap Motion callback called on device connection.</param>
	/// <param name="onDeviceLost">Leap Motion callback called on device lost.</param>
	/// <param name="onDeviceFailure">Leap Motion callback called on device failure.</param>
	/// <param name="onFrame">Leap Motion callback called on frame.</param>
	/// <param name="onLogMessage">Leap Motion callback called on sent log message.</param>
	/// <param name="onSample">MultiLeap callback called on calibration sampling thread run.</param>
	/// <param name="onPolicy">Leap Motion callback called on device policy.</param>
	/// <param name="onConfigChange">Leap Motion callback called on config change.</param>
	/// <param name="onConfigResponse">Leap Motion callback called on config change response.</param>
	/// <param name="onImage">Leap Motion callback called on sent image.</param>
	/// <param name="onPointMapping">Leap Motion callback called on point mapping change.</param>
	extern "C" MULTILEAP_API void SetCallbacks(connection_callback onConnection, connection_callback onConnectionLost,
		device_callback onDevice, device_lost_callback onDeviceLost, device_failure_callback onDeviceFailure,
		tracking_callback onFrame, log_callback onLogMessage, calibration_sample_callback onSample,
		policy_callback onPolicy = nullptr, config_change_callback onConfigChange = nullptr,
		config_response_callback onConfigResponse = nullptr, image_callback onImage = nullptr,
		point_mapping_change_callback onPointMapping = nullptr);

	/// <summary>
	/// Close the connection and free all resources.
	/// </summary>
	extern "C" MULTILEAP_API void Deinit();

	/// <summary>
	/// Calibrate the connected devices.
	/// </summary>
	/// <param name="sampleCount">The number of calibration samples to be taken.</param> 
	extern "C" MULTILEAP_API void CalibrateDevices(const int sampleCount);

	/// <summary>
	/// Set the merge status the corresponding hands from the devices.
	/// </summary>
	/// <param name="merge">If the hands should be merged or not.</param>
	extern "C" MULTILEAP_API void MergeHands(const bool merge);

	/// <summary>
	/// Set the device status.
	/// </summary>
	/// <param name="id">The ID of the device.</param>
	/// <param name="enabled">If the device should be enabled or not.</param>
	/// <returns>True on success, false otherwise (e.g. a device with provided serial number does not exist).</returns>
	extern "C" MULTILEAP_API bool SetDeviceStatus(const unsigned id, const bool enabled);

	/// <summary>
	/// Set the device's translation, rotation and scale.
	/// </summary>
	/// <param name="id">The ID of the device.</param>
	/// <param name="transformation">The transformation of the device.</param>
	/// <returns>True on success, false otherwise (e.g. a device with provided serial number does not work).</returns>
	extern "C" MULTILEAP_API bool SetDeviceTransformation(const unsigned id, const char* transformation);

	/// <summary>
	/// Get the device's translation, rotation and scale.
	/// Call this method first with empty result argument to determine the length of the result.
	/// </summary>
	/// <param name="id">The ID of the device.</param>
	/// <param name="result">The transformation of the device as a char array.</param>
	/// <param name="length">The length of the result in characters.</param>
	/// <returns>True on success, false otherwise (e.g. a device with provided serial number does not work).</returns>
	extern "C" MULTILEAP_API bool GetDeviceTransformation(const unsigned id, char* result, size_t & length);

	/// <summary>
	/// Get the info about the devices. Should be called three times:
	/// 1) First time with nullptr arays to get the count of devices.
	/// 2) Second time with allocated arrays to get the size of serial numbers. The serial number atributtes should be set to nullptr.
	/// 3) Third time with allocated serial number arrays.
	/// </summary>
	/// <param name="devicesArray">The array to store the device info.</param>
	/// <param name="idsArray">The array to store the device ids.</param>
	/// <param name="count">The count of the devices.</param>
	/// <returns>True on success, false otherwise (e.g. the array is not big enough).</returns>
	extern "C" MULTILEAP_API bool GetDevices(LEAP_DEVICE_INFO * devicesArray, int* idsArray, size_t & count);

	/// <summary>
	/// Get the info about a device with the specified serial number.
	/// </summary>
	/// <param name="id">The ID of the device.</param>
	/// <param name="device">The pointer store the device info.</param>
	/// <returns>True on success, false otherwise (e.g. the device with provided serial number not found or device not initialized).</returns>
	extern "C" MULTILEAP_API bool GetDevice(const unsigned id, LEAP_DEVICE_INFO * device);

	/// <summary>
	/// Get size for interpolated frame for set time.
	/// </summary>
	/// <param name="id">The ID of the device.</param>
	/// <param name="time">The time of the frame.</param>
	/// <returns>The interpolated frame.</returns>
	extern "C" MULTILEAP_API const uint64_t GetInterpolatedFrameSize(const unsigned id, const int64_t time);

	/// <summary>
	/// Get interpolated frame for set time.
	/// </summary>
	/// <param name="id">The ID of the device.</param>
	/// <param name="time">The time of the frame.</param>
	/// <returns>The interpolated frame.</returns>
	extern "C" MULTILEAP_API const LEAP_TRACKING_EVENT* GetInterpolatedFrame(const unsigned id, const int64_t time);

	/// <summary>
	/// Get interpolated frame for set time.
	/// </summary>
	/// <param name="id">The ID of the device.</param>
	/// <param name="time">The time of the frame.</param>
	/// <param name="sourceTime">The timestamp of the beginning frame from which to interpolate the frame data.</param>
	/// <returns>The interpolated frame.</returns>
	extern "C" MULTILEAP_API const LEAP_TRACKING_EVENT* GetInterpolatedFrameFromTime(const unsigned id, const int64_t time, const int64_t sourceTime);


	/// <summary>
	/// Get current Leap Timestamp;
	/// </summary>
	/// <returns>Current Leap time.</returns>
	extern "C" MULTILEAP_API const uint64_t GetLeapNow();

	extern "C" MULTILEAP_API int Test();
	extern "C" MULTILEAP_API int TestAdd(int a, int b);
}
#endif /* MultiLeap_h */