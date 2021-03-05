#ifndef LeapCallbacks_h
#define LeapCallbacks_h
#include "LeapC.h"

/* Leap Callback function pointers */
typedef void (*connection_callback)           ();
typedef void (*device_callback)               (const LEAP_DEVICE_INFO* device, const int * handle, const unsigned id);
typedef void (*device_lost_callback)          (const char * device);
typedef void (*device_failure_callback)       (const LEAP_DEVICE_FAILURE_EVENT* device_failure_event);
typedef void (*policy_callback)               (const uint32_t current_policies);
typedef void (*tracking_callback)             (const LEAP_TRACKING_EVENT* tracking_event, const unsigned deviceId);
typedef void (*log_callback)                  (const eLeapLogSeverity severity, const int64_t timestamp, const char* message);
typedef void (*config_change_callback)        (const uint32_t requestID, const bool success);
typedef void (*config_response_callback)      (const uint32_t requestID, LEAP_VARIANT value);
typedef void (*image_callback)                (const LEAP_IMAGE_EVENT* image_event);
typedef void (*point_mapping_change_callback) (const LEAP_POINT_MAPPING_CHANGE_EVENT* point_mapping_change_event);

// MultiLeap callbacks
typedef void (*calibration_sample_callback) (const bool status, const int sampleCount, const char* failedDevices);

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

#endif /* LeapCallbacks_h */