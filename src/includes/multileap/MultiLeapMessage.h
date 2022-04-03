#ifndef MultiLeapMessage_h
#define MultiLeapMessage_h

#include "MultiLeapC.h"

/// <summary>
/// Metadata about tracking.
/// </summary>
struct MultiLeap_TrackingMessageMeta {
  /// <summary>
  /// The deviation of the tracking data.
  /// </summary>
  float deviation;

  /// <summary>
  /// Id of the real device that sent the tracking message from Leap Motion.
  /// </summary>
  uint32_t realDeviceId;

  /// <summary>
  /// Optional data about calibration.
  /// </summary>
  int calibrationPercentage = 0;
};

/// <summary>
/// Type of meta message part of MultiLeap message.
/// </summary>
enum class MultiLeap_MessageMetaType {
  /// <summary>
  /// No additional metadata.
  /// </summary>
  EMPTY,

  /// <summary>
  /// Additional information about tracking.
  /// </summary>
  TRACKING,
};

/// <summary>
/// Struct representing MultiLeap message with its metadata
/// </summary>
struct MultiLeap_Message {
  /// <summary>
  /// The basic Leap Motion Message.
  /// </summary>
  LEAP_CONNECTION_MESSAGE leapMessage;

  /// <summary>
  /// The type of meta message.
  /// </summary>
  MultiLeap_MessageMetaType type;

  /// <summary>
  /// Meta information about MultiLeap Message.
  /// </summary>
  union {
    /// <summary>
    /// Metainformation about the tracking data.
    /// </summary>
    MultiLeap_TrackingMessageMeta *trackingMessageMeta = nullptr;
  };

private:
};

/// <summary>
/// Cleans all metadata values.
/// </summary>
void cleanMultiLeapMessageMetadata(MultiLeap_Message *message);

#endif /* MultiLeapMessage_h */