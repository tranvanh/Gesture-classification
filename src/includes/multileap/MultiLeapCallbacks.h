#ifndef MultiLeapCallbacks_h
#define MultiLeapCallbacks_h
#include "MultiLeapC.h"

/* Leap Callback function pointers */

/// <summary>
/// Callback when a device is connected.
/// </summary>
/// <param name="context">The context of the callback.</param>
typedef void (*connectionCallback)(void *context);

/// <summary>
/// Callback when a device is connected.
/// </summary>
/// <param name="device">The connected device info.</param>
/// <param name="handle">The handle of the connected device.</param>
/// <param name="deviceId">The ID of the device.</param>
/// <param name="context">The context of the connection.</param>
typedef void (*deviceCallback)(const LEAP_DEVICE_INFO *device,
                               const int *handle, const unsigned deviceId,
                               void *context);

/// <summary>
/// Callback when a device is lost.
/// </summary>
/// <param name="device">Serial number of the device.</param>
/// <param name="context">The context of the connection.</param>
typedef void (*deviceLostCallback)(const char *device, void *context);

/// <summary>
/// Callback when a device fails.
/// </summary>
/// <param name="device_failure_event">Argument of the failure.</param>
/// <param name="context">The context of the connection.</param>
typedef void (*deviceFailureCallback)(
    const LEAP_DEVICE_FAILURE_EVENT *device_failure_event, void *context);

/// <summary>
/// Callback when policy message is sent.
/// </summary>
/// <param name="current_policies">The current policies info.</param>
/// <param name="context">The context of the connection.</param>
typedef void (*policyCallback)(const uint32_t current_policies, void *context);

/// <summary>
/// Callback when tracking event is sent.
/// </summary>
/// <param name="tracking_event">The tracking event data.</param>
/// <param name="deviceId">The ID of the device that sent the data.</param>
/// <param name="deviation">The deviation of the current tracking frame from the
/// merged data.</param> <param name="context">The context of the
/// connection.</param>
typedef void (*trackingCallback)(const LEAP_TRACKING_EVENT *tracking_event,
                                 const unsigned deviceId, float deviation,
                                 void *context);

/// <summary>
/// Callback when log message is sent.
/// </summary>
/// <param name="severity">The severity of the log event.</param>
/// <param name="timestamp">The timestamp of the log event.</param>
/// <param name="message">The log message.</param>
/// <param name="context">The context of the connection.</param>
typedef void (*logCallback)(const eLeapLogSeverity severity,
                            const int64_t timestamp, const char *message,
                            void *context);

/// <summary>
/// Callback when config changes.
/// </summary>
/// <param name="requestID">ID of the request</param>
/// <param name="success">The status of the change.</param>
/// <param name="context">The context of the connection.</param>
typedef void (*configChangeCallback)(const uint32_t requestID,
                                     const bool success, void *context);

/// <summary>
/// Callback when config change result is sent.
/// </summary>
/// <param name="requestID">ID of the request</param>
/// <param name="value">The value of the variant.</param>
/// <param name="context">The context of the connection.</param>
typedef void (*configResponseCallback)(const uint32_t requestID,
                                       LEAP_VARIANT value, void *context);

/// <summary>
/// Callback when image is sent.
/// </summary>
/// <param name="image_event">The sent image information.</param>
/// <param name="context">The context of the connection.</param>
typedef void (*imageCallback)(const LEAP_IMAGE_EVENT *image_event,
                              void *context);

/// <summary>
/// Callback when point mapping changes is sent.
/// </summary>
/// <param name="point_mapping_change_event">The point mapping change
/// information.</param> <param name="context">The context of the
/// connection.</param>
typedef void (*pointMappingChangeCallback)(
    const LEAP_POINT_MAPPING_CHANGE_EVENT *point_mapping_change_event,
    void *context);

/// <summary>
/// All possible Leap Motion callbacks.
/// </summary>
struct LeapCallbacks {
  /// <summary>
  /// Callback called when the Leap Motion service is connected.
  /// </summary>
  connectionCallback onConnection;

  /// <summary>
  /// Callback called when the Leap Motion service is disconnected.
  /// </summary>
  connectionCallback onConnectionLost;

  /// <summary>
  /// Callback called when a device is connected.
  /// </summary>
  deviceCallback onDeviceFound;

  /// <summary>
  /// Callback called when a device is disconnected.
  /// </summary>
  deviceLostCallback onDeviceLost;

  /// <summary>
  /// Callback called when a device fails.
  /// </summary>
  deviceFailureCallback onDeviceFailure;

  /// <summary>
  /// Callback called when a frame is sent.
  /// </summary>
  trackingCallback onFrame;

  /// <summary>
  /// Callback called when log message is sent.
  /// </summary>
  logCallback onLogMessage;

  /// <summary>
  /// Callback called when a policy is set.
  /// </summary>
  policyCallback onPolicy;

  /// <summary>
  /// Callback called when a config changes.
  /// </summary>
  configChangeCallback onConfigChange;

  /// <summary>
  /// Callback called representing a result of a config change.
  /// </summary>
  configResponseCallback onConfigResponse;

  /// <summary>
  /// Callback called when an image is sent.
  /// </summary>
  imageCallback onImage;

  /// <summary>
  /// Callback called when point mapping changes.
  /// </summary>
  pointMappingChangeCallback onPointMappingChange;
};

// MultiLeap callbacks
/// <summary>
/// Callback when calibration sample loop is ran.
/// </summary>
/// <param name="deviceCount">Number of devices that are being
/// calibrated.</param> <param name="ids">IDs of devices that are being
/// calibrated.</param> <param name="completion">Array of completion of the
/// calibration. The indexes correspond to the indexes in ids array.</param>
/// <param name="context">The context of the connection.</param>
typedef void (*calibrationSampleCallback)(const int deviceCount,
                                          const uint32_t *ids,
                                          const int *completion, void *context);

/// <summary>
/// All possible MultiLeap callbacks.
/// </summary>
struct MultiLeapCallbacks {
  /// <summary>
  /// Callback when calibration sample loop is ran.
  /// </summary>
  calibrationSampleCallback onCalibrationSample;
};

#endif /* MultiLeapCallbacks_h */