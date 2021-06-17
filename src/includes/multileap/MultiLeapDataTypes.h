#ifndef MultiLeapDataTypes_h
#define MultiLeapDataTypes_h

/// <summary>
/// Struct representing vector of three floats.
/// </summary>
struct MultiLeap_Vector3f {
	/// <summary>
	/// X component of the vector.
	/// </summary>
	float x;

	/// <summary>
	/// Y component of the vector.
	/// </summary>
	float y;

	/// <summary>
	/// Z component of the vector.
	/// </summary>
	float z;
};

/// <summary>
/// Struc representing quaternion of four floats.
/// </summary>
struct MultiLeap_Quaternionf {
	/// <summary>
	/// X component of the vector.
	/// </summary>
	float x;

	/// <summary>
	/// Y component of the vector.
	/// </summary>
	float y;

	/// <summary>
	/// Z component of the vector.
	/// </summary>
	float z;

	/// <summary>
	/// W component of the vector.
	/// </summary>
	float w;
};

/// <summary>
/// Merge mode of the data fusion.
/// </summary>
typedef enum {
	/// <summary>
	/// Tracking data will not be merged. All enabled sensors will send their data through API.
	/// </summary>
	NONE,

	/// <summary>
	/// Tracking data from all enabled sensors will be sent.
	/// </summary>
	COMBINATION,

	/// <summary>
	/// Only the hands with the highest confidence will be sent.
	/// </summary>
	BEST,
} MergeMode;

#endif /* MultiLeapDataTypes_h */