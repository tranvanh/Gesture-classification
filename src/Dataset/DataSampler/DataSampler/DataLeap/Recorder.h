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
	Recorder(const int& t, const int& f, const int &c, const std::string gt) : dataNormalization(t, f), timestep(t), num_features(f),
		count(c), gestureType(gt), recording(false), continuous(false) {}
	/** Callback for when a frame of tracking data is available. */
	void OnFrame(const LEAP_TRACKING_EVENT* frame, const unsigned deviceId);
	
	void startRecording();
	void openRecording();
	void pauseRecording();

	void reinitRecording(const int &i, const std::string gt);

private:
	void writeDown(const std::vector<std::vector<double>>& data, bool notFull);
	void processData(bool notFull);

	DataNormalization dataNormalization;
	std::list<LEAP_HAND> window;
	int timestep;
	int num_features;
	int count;
	bool recording;

	bool continuous;

	std::string gestureType;
};

