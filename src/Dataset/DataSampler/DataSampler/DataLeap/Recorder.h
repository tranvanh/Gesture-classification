#pragma once
#pragma once
#include <iostream>
#include "MultiLeap.h"
#include "DataProcessing/dataNormalizationr.h"

#include <list>

class Recorder {
public:
	/** Callback for when the connection opens. */
	Recorder(const int &t, const int &f) : dataNormalization(t,f), timestep(t), num_features(f){}
	/** Callback for when a frame of tracking data is available. */
	void OnFrame(const LEAP_TRACKING_EVENT* frame, const unsigned deviceId);

private:
	DataNormalization dataNormalization;
	std::list<LEAP_HAND> window;
	int timestep;
	int num_features;


};

