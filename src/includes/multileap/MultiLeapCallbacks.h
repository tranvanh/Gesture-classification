#ifndef MultiLeapCallbacks_h
#define MultiLeapCallbacks_h
#include "LeapC.h"

/* Leap Callback function pointers */

/// <summary>
/// Callback when a device is connected.
/// </summary>
/// <param name="context">The context of the callback.</param>
typedef void (*connection_callback)           (void* context);

/// <summary>
/// Callback when a device is connected.
/// </summary>
/// <param name="device">The connected device info.</param>
/// <param name="handle">The handle of the connected device.</param>
/// <param name="deviceId">The ID of the device.</param>
/// <param name="context">The context of the connection.</param>
typedef void (*device_callback)               (const LEAP_DEVICE_INFO* device, const int * handle, const unsigned id, void * context);

/// <summary>
/// Callback when a device is lost.
/// </summary>
/// <param name="device">Serial number of the device.</param>
/// <param name="context">The context of the connection.</param>
typedef void (*device_lost_callback)          (const char * device, void* context);

/// <summary>
/// Callback when a device fails.
/// </summary>
/// <param name="device_failure_event">Argument of the failure.</param>
/// <param name="context">The context of the connection.</param>
typedef void (*device_failure_callback)       (const LEAP_DEVICE_FAILURE_EVENT* device_failure_event, void* context);

/// <summary>
/// Callback when policy message is sent.
/// </summary>
/// <param name="current_policies">The current policies info.</param>
/// <param name="context">The context of the connection.</param>
typedef void (*policy_callback)               (const uint32_t current_policies, void* context);

/// <summary>
/// Callback when tracking event is sent.
/// </summary>
/// <param name="tracking_event">The tracking event data.</param>
/// <param name="deviceId">The ID of the device that sent the data.</param>
/// <param name="context">The context of the connection.</param>
typedef void (*tracking_callback)             (const LEAP_TRACKING_EVENT* tracking_event, const unsigned deviceId, void* context);

/// <summary>
/// Callback when log message is sent.
/// </summary>
/// <param name="severity">The severity of the log event.</param>
/// <param name="timestamp">The timestamp of the log event.</param>
/// <param name="message">The log message.</param>
/// <param name="context">The context of the connection.</param>
typedef void (*log_callback)                  (const eLeapLogSeverity severity, const int64_t timestamp, const char* message, void* context);

/// <summary>
/// Callback when config changes.
/// </summary>
/// <param name="requestID">ID of the request</param>
/// <param name="success">The status of the change.</param>
/// <param name="context">The context of the connection.</param>
typedef void (*config_change_callback)        (const uint32_t requestID, const bool success, void* context);

/// <summary>
/// Callback when config change result is sent.
/// </summary>
/// <param name="requestID">ID of the request</param>
/// <param name="value">The value of the variant.</param>
/// <param name="context">The context of the connection.</param>
typedef void (*config_response_callback)      (const uint32_t requestID, LEAP_VARIANT value, void* context);

/// <summary>
/// Callback when image is sent.
/// </summary>
/// <param name="image_event">The sent image information.</param>
/// <param name="context">The context of the connection.</param>
typedef void (*image_callback)                (const LEAP_IMAGE_EVENT* image_event, void* context);

/// <summary>
/// Callback when point mapping changes is sent.
/// </summary>
/// <param name="point_mapping_change_event">The point mapping change information.</param>
/// <param name="context">The context of the connection.</param>
typedef void (*point_mapping_change_callback) (const LEAP_POINT_MAPPING_CHANGE_EVENT* point_mapping_change_event, void* context);

// MultiLeap callbacks


/// <summary>
/// Callback when calibration sample loop is ran.
/// </summary>
/// <param name="device_count">Number of devices that are being calibrated.</param>
/// <param name="ids">IDs of devices that are being calibrated.</param>
/// <param name="completion">Array of completion of the calibration. The indexes correspond to the indexes in ids array.</param>
/// <param name="context">The context of the connection.</param>
typedef void (*calibration_sample_callback) (const int device_count, const uint32_t* ids, const int * completion, void* context);

/// <summary>
/// All possible Leap Motion callbacks.
/// </summary>
struct LeapCallbacks {
    /// <summary>
    /// Callback called when the Leap Motion service is connected.
    /// </summary>
    connection_callback      on_connection;

    /// <summary>
    /// Callback called when the Leap Motion service is disconnected.
    /// </summary>
    connection_callback      on_connection_lost;

    /// <summary>
    /// Callback called when a device is connected.
    /// </summary>
    device_callback          on_device_found;

    /// <summary>
    /// Callback called when a device is disconnected.
    /// </summary>
    device_lost_callback     on_device_lost;

    /// <summary>
    /// Callback called when a device fails.
    /// </summary>
    device_failure_callback  on_device_failure;

    /// <summary>
    /// Callback called when a policy is set.
    /// </summary>
    policy_callback          on_policy;

    /// <summary>
    /// Callback called when a frame is sent.
    /// </summary>
    tracking_callback        on_frame;

    /// <summary>
    /// Callback called when log message is sent.
    /// </summary>
    log_callback             on_log_message;

    /// <summary>
    /// Callback called when a config changes.
    /// </summary>
    config_change_callback   on_config_change;

    /// <summary>
    /// Callback called representing a result of a config change.
    /// </summary>
    config_response_callback on_config_response;

    /// <summary>
    /// Callback called when an image is sent.
    /// </summary>
    image_callback           on_image;

    /// <summary>
    /// Callback called when point mapping changes.
    /// </summary>
    point_mapping_change_callback on_point_mapping_change;
};

#endif /* MultiLeapCallbacks_h */