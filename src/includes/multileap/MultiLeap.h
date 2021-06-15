#ifndef MultiLeap_h
#define MultiLeap_h

#ifdef MULTILEAP_EXPORTS
#define MULTILEAP_API extern "C" __declspec(dllexport)
#else
#define MULTILEAP_API extern "C" __declspec(dllimport)
#endif

#include "MultiLeapDataTypes.h"
#include "MultiLeapCallbacks.h"

/// <summary>
/// Initialize the library and register all Leap Motion callbacks.
/// This version of init will start a thread that polls the Leap Motion Service and handles the callbacks invocation.
/// </summary>
/// <param name="onConnection">Leap Motion callback called on successful connection.</param>
/// <param name="onConnectionLost">Leap Motion callback called on connection lost.</param>
/// <param name="onDevice">Leap Motion callback called on device connection.</param>
/// <param name="onDeviceLost">Leap Motion callback called on device lost.</param>
/// <param name="onDeviceFailure">Leap Motion callback called on device failure.</param>
/// <param name="onFrame">Leap Motion callback called on frame.</param>
/// <param name="onLogMessage">Leap Motion callback called on sent log message.</param>
/// <param name="onSample">MultiLeap callback called when calibration sample loop is ran.</param>
/// <param name="context">Context of the connection (can be null).</param>
/// <returns>True if initializon was successful, false otherwise.</returns>
MULTILEAP_API bool MultiLeap_InitCallbacksConnection(connection_callback onConnection, connection_callback onConnectionLost,
	device_callback onDevice, device_lost_callback onDeviceLost, device_failure_callback onDeviceFailure,
	tracking_callback onFrame, log_callback onLogMessage, calibration_sample_callback onSample, void* context);

/// <summary>
/// Initialize the library.
/// This version does not start the underlying thread and the polling should be handled by the client
/// via the PollLeapMotionMessages function.
/// </summary>
/// <param name="onSample">MultiLeap callback called on calibration sampling thread run.</param>
/// <param name="context">Context of the connection (can be null).</param>
/// <returns>True if initializon was successful, false otherwise.</returns>
MULTILEAP_API bool MultiLeap_InitPollingConnection(calibration_sample_callback onSample, void* context);

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
MULTILEAP_API void MultiLeap_SetCallbacks(connection_callback onConnection, connection_callback onConnectionLost,
	device_callback onDevice, device_lost_callback onDeviceLost, device_failure_callback onDeviceFailure,
	tracking_callback onFrame, log_callback onLogMessage, calibration_sample_callback onSample,
	policy_callback onPolicy = nullptr, config_change_callback onConfigChange = nullptr,
	config_response_callback onConfigResponse = nullptr, image_callback onImage = nullptr,
	point_mapping_change_callback onPointMapping = nullptr);

/// <summary>
/// Close the connection and free all resources.
/// </summary>
MULTILEAP_API void MultiLeap_Deinit();

/// <summary>
/// Poll for a message from the Leap Motion Service. 
/// </summary>
/// <param name="message">The Leap Message struct to be filled.</param>
/// <param name="timeout">Timeout of the poll in milliseconds.</param>
/// <returns>Result of the internal poll.</returns>
MULTILEAP_API	eLeapRS MultiLeap_PollLeapMotionMessages(LEAP_CONNECTION_MESSAGE* message, unsigned int timeout);

/// <summary>
/// Calibrate the connected devices.
/// </summary>
/// <param name="sampleCount">The number of calibration samples to be taken.</param> 
MULTILEAP_API void MultiLeap_CalibrateDevices(const int sampleCount);

/// <summary>
/// Set the merge status the corresponding hands from the devices.
/// </summary>
/// <param name="merge">If the hands should be merged or not.</param>
MULTILEAP_API void MultiLeap_MergeHands(const bool merge);

/// <summary>
/// Set the device status.
/// </summary>
/// <param name="id">The ID of the device.</param>
/// <param name="enabled">If the device should be enabled or not.</param>
/// <returns>True on success, false otherwise (e.g. a device with provided id does not exist).</returns>
MULTILEAP_API bool MultiLeap_SetDeviceStatus(const unsigned id, const bool enabled);

/// <summary>
/// Set the device's translation, rotation and scale.
/// </summary>
/// <param name="id">The ID of the device.</param>
/// <param name="transformation">The transformation of the device.</param>
/// <returns>True on success, false otherwise (e.g. a device with provided id does not exist).</returns>
MULTILEAP_API bool MultiLeap_SetDeviceTransformation(const unsigned id, const char* transformation);

/// <summary>
/// Get the device's translation, rotation and scale.
/// Call this method first with empty result argument to determine the length of the result.
/// </summary>
/// <param name="id">The ID of the device.</param>
/// <param name="result">The transformation of the device as a char array.</param>
/// <param name="length">The length of the result in characters.</param>
/// <returns>True on success, false otherwise (e.g. a device with provided id does not exist).</returns>
MULTILEAP_API bool MultiLeap_GetDeviceTransformation(const unsigned id, char* result, size_t& length);

/// <summary>
/// Set the device's translation and rotation.
/// </summary>
/// <param name="id">The ID of the device.</param>
/// <param name="position">Vector representing the position of the device.</param>
/// <param name="rotation">Quaternion representing the rotation of the device.</param>
/// <returns>True on success, false otherwise (e.g. a device with provided id does not exist).</returns>
MULTILEAP_API bool MultiLeap_SetDeviceTransformationRaw(const unsigned id, MultiLeap_Vector3f position, MultiLeap_Quaternionf rotation);


/// <summary>
/// Get the device's translation, rotation.
/// </summary>
/// <param name="id">The ID of the device.</param>
/// <param name="position">Vector representing the position of the device.</param>
/// <param name="rotation">Quaternion representing the rotation of the device.</param>
/// <returns>True on success, false otherwise (e.g. a device with provided id does not exist or data structures are not initialized).</returns>
MULTILEAP_API bool MultiLeap_GetDeviceTransformationRaw(const unsigned id, MultiLeap_Vector3f* position, MultiLeap_Quaternionf* rotation);

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
MULTILEAP_API bool MultiLeap_GetDevices(LEAP_DEVICE_INFO* devicesArray, int* idsArray, size_t& count);

/// <summary>
/// Get the info about a device with the specified serial number.
/// </summary>
/// <param name="id">The ID of the device.</param>
/// <param name="device">The pointer store the device info.</param>
/// <returns>True on success, false otherwise (e.g. the device with provided serial number not found or device not initialized).</returns>
MULTILEAP_API bool MultiLeap_GetDevice(const unsigned id, LEAP_DEVICE_INFO* device);

/// <summary>
/// Get size for interpolated frame for set time.
/// </summary>
/// <param name="id">The ID of the device.</param>
/// <param name="time">The time of the frame.</param>
/// <returns>The interpolated frame.</returns>
MULTILEAP_API const uint64_t MultiLeap_GetInterpolatedFrameSize(const unsigned id, const int64_t time);

/// <summary>
/// Get interpolated frame for set time.
/// </summary>
/// <param name="id">The ID of the device.</param>
/// <param name="time">The time of the frame.</param>
/// <returns>The interpolated frame.</returns>
MULTILEAP_API const LEAP_TRACKING_EVENT* MultiLeap_GetInterpolatedFrame(const unsigned id, const int64_t time);

/// <summary>
/// Get interpolated frame for set time.
/// </summary>
/// <param name="id">The ID of the device.</param>
/// <param name="time">The time of the frame.</param>
/// <param name="sourceTime">The timestamp of the beginning frame from which to interpolate the frame data.</param>
/// <returns>The interpolated frame.</returns>
MULTILEAP_API const LEAP_TRACKING_EVENT* MultiLeap_GetInterpolatedFrameFromTime(const unsigned id, const int64_t time, const int64_t sourceTime);

/// <summary>
/// Get current Leap Timestamp;
/// </summary>
/// <returns>Current Leap time.</returns>
MULTILEAP_API const uint64_t MultiLeap_GetLeapNow();

/// <summary>
/// Get the ID of the reference device.
/// </summary>
/// <returns>The ID.</returns>
MULTILEAP_API const uint32_t MultiLeap_GetPivotId();

/// <summary>
/// Set the ID of the reference device.
/// </summary>
/// <param name="id">The ID of the device.</param>
/// <returns>False when ID does not exist or when ID of virtual device was provided, true otherwise.</returns>
MULTILEAP_API bool MultiLeap_SetPivotId(const uint32_t id);

/// <summary>
/// Get the ID of the virtual device.
/// </summary>
/// <returns>The ID.</returns>
MULTILEAP_API const uint32_t MultiLeap_GetVirtualDeviceId();

MULTILEAP_API int MultiLeap_Test();
MULTILEAP_API int MultiLeap_TestAdd(int a, int b);

#endif /* MultiLeap_h */