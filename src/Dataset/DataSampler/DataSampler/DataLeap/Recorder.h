#pragma once
#pragma once
#include <iostream>
#include "MultiLeap.h"
#include "DataProcessing/dataNormalizationr.h"
#include <fstream>
#include <list>
#include <string>

class Recorder {
public:
	/** Callback for when the connection opens. */
	Recorder(const int& t, const int& f) : dataNormalization(t, f), timestep(t), num_features(f), count(30), gestureType("6") {}
	/** Callback for when a frame of tracking data is available. */
	void OnFrame(const LEAP_TRACKING_EVENT* frame, const unsigned deviceId);

private:
	void writeDown(const std::vector<std::vector<double>>& data);
	DataNormalization dataNormalization;
	std::list<LEAP_HAND> window;
	int timestep;
	int num_features;
	int count;
	std::string gestureType;
};

