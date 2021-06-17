#ifndef MultiLeap_h
#define MultiLeap_h

#ifdef MULTILEAP_EXPORTS
#define MULTILEAP_API extern "C" __declspec(dllexport)
#else
#define MULTILEAP_API extern "C" __declspec(dllimport)
#endif

#include "MultiLeapDataTypes.h"
#include "MultiLeapCallbacks.h"
#include "MultiLeapMessage.h"

/// <summary>
/// Initialize the library and register all Leap Motion callbacks.
/// This version of init will start a thread that polls the Leap Motion Service and handles the callbacks invocation.
/// </summary>
/// <param name="leapCallbacks">Struct of Leap Motion callbacks.</param>
/// <param name="multileapCallbacks">Struct of MultiLeap callbacks.</param>
/// <param name="context">Context of the connection (can be null).</param>
/// <returns>True if initializon was successful, false otherwise.</returns>
MULTILEAP_API bool MultiLeap_InitCallbacksConnection(LeapCallbacks leapCallbacks, MultiLeapCallbacks multileapCallbacks,
	void* context);

/// <summary>
/// Initialize the library.
/// This version does not start the underlying thread and the polling should be handled by the client
/// via the PollLeapMotionMessages function.
/// </summary>
/// <returns>True if initializon was successful, false otherwise.</returns>
MULTILEAP_API bool MultiLeap_InitPollingConnection();

/// <summary>
/// Set the library callbacks.
/// </summary>
/// <param name="leapCallbacks">Struct of Leap Motion callbacks.</param>
/// <param name="multileapCallbacks">Struct of MultiLeap callbacks.</param>
MULTILEAP_API void MultiLeap_SetCallbacks(LeapCallbacks leapCallbacks, MultiLeapCallbacks multileapCallbacks);

/// <summary>
/// Close the connection and free all resources.
/// </summary>
MULTILEAP_API void MultiLeap_Deinit();

/// <summary>
/// Poll for a message from the Leap Motion Service. 
/// </summary>
/// <param name="message">The MultiLeap Message struct to be filled.</param>
/// <param name="timeout">Timeout of the poll in milliseconds.</param>
/// <returns>Result of the internal poll.</returns>
MULTILEAP_API	eLeapRS MultiLeap_PollLeapMotionMessages(MultiLeap_Message* message, unsigned int timeout);

/// <summary>
/// Calibrate the connected devices.
/// </summary>
/// <param name="samplesCount">Count of samples to be taken.</param>
MULTILEAP_API void MultiLeap_CalibrateDevices(const int samplesCount = 100);

/// <summary>
/// Set the merge mode for the system.
/// </summary>
/// <param name="merge">The merge mode.</param>
MULTILEAP_API void MultiLeap_MergeHands(const MergeMode mode);

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
/// Set Leap Policy flags.
/// </summary>
/// <param name="set">The flags to set.</param>
/// <param name="clear">If previous flags should be cleared.</param>
/// <returns>Result of the call.</returns>
MULTILEAP_API eLeapRS MultiLeap_SetLeapPolicyFlags(uint64_t set, uint64_t clear);

/// <summary>
/// Set Leap Policy flags for specific device. NOT IMPLEMENTED YET.
/// </summary>
/// <param name="id">The ID of the device.</param>
/// <param name="set">The flags to set.</param>
/// <param name="clear">If previous flags should be cleared.</param>
/// <returns>Result of the call.</returns>
//MULTILEAP_API eLeapRS MultiLeap_SetLeapDevicePolicyFlags(const unsigned id, uint64_t set, uint64_t clear);

/// <summary>
/// If the device is calibrated.
/// </summary>
/// <param name="id">ID of the device.</param>
/// <returns>True if device transformation is persistent, false otherwise.</returns>
MULTILEAP_API bool MultiLeap_IsDeviceCalibrated(const uint32_t id);

/// <summary>
/// Mark if the device is calibrated.
/// </summary>
/// <param name="id">ID of the device.</param>
/// <param name="calibrated">True if device is calibrated, false otherwise.</param>
/// <returns>False when ID does not exist or when ID of virtual device was provided, true otherwise.</returns>
MULTILEAP_API bool MultiLeap_SetDeviceCalibrated(const uint32_t id, bool calibrated);

/// <summary>
/// Check if the calibration is currently running.
/// </summary>
/// <returns>True if the calibration is running, false otherwise.</returns>
MULTILEAP_API bool MultiLeap_IsCalibrationRunning();

/// <summary>
/// Stop the calibration. If it is not running, it does nothing.
/// </summary>
MULTILEAP_API void MultiLeap_StopCalibration();

/// <summary>
/// Resets calibration status for all devices.
/// </summary>
MULTILEAP_API void MultiLeap_ResetCalibration();

/// <summary>
/// Get the ID of the virtual device.
/// </summary>
/// <returns>The ID.</returns>
MULTILEAP_API const uint32_t MultiLeap_GetVirtualDeviceId();

/// <summary>
/// Saves transformations for all connected devices.
/// </summary>
/// <returns>True if the safe was successfull, false otherwise.</returns>
MULTILEAP_API bool MultiLeap_SaveConfiguration();

/// <summary>
/// Loads transformations for all connected devices.
/// </summary>
/// <returns>True if the safe was successfull, false otherwise.</returns>
MULTILEAP_API bool MultiLeap_LoadConfiguration();

MULTILEAP_API int MultiLeap_Test();
MULTILEAP_API int MultiLeap_TestAdd(int a, int b);

#endif /* MultiLeap_h */