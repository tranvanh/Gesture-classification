#pragma once
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <windows.h>
#include <stdio.h>

#include "MultiLeap.h"
#include "DataProcessing/dataNormalizationr.h"


#define LPCWSTR_SAVE_DIR L"../../Dataset/DataCollection/"
#define SAVE_DIR "DataCollection/"
#define DATASET_DIR "../../Dataset/"

class GestureRecorder {
public:
	/** Callback for when the connection opens. */
	GestureRecorder(const int& t, const int& f, const int &c, const std::string gt) : dataNormalization(t, f), timestep(t), timestepBackup(t), num_features(f),
		count(c), gestureType(gt), recording(false), continuous(false), dynamicRecording(false) {}
	/** Callback for when a frame of tracking data is available. */
	void OnFrame(const LEAP_TRACKING_EVENT* frame, const unsigned deviceId, void* context);
	
	void startRecording();
	void openRecording();
	void startDynamicRecording(const int& t);
	void pauseRecording();



	void reinitRecording(const int &i, const std::string gt);

private:
	void checkDirectories();
	void writeDown(const std::vector<std::vector<double>>& data, bool notFull);
	void processData(bool notFull);
	void cleanUp();

	DataNormalization dataNormalization;

	std::list<LEAP_HAND> window;
	int timestep;
	int timestepBackup;
	int num_features;
	int count;
	bool recording;
	bool continuous;

	bool dynamicRecording;

	std::string gestureType;
};

