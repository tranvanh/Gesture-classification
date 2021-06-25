#pragma once
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <windows.h>
#include <stdio.h>

#include "MultiLeap.h"
#include "DataProcessing/DataNormalizationSampling.h"
#include "ConfigManager.h"


class GestureRecorder {
public:
	/** Callback for when the connection opens. */
	GestureRecorder(const std::string gt);
	/** Callback for when a frame of tracking data is available. */
	void OnFrame(const LEAP_TRACKING_EVENT* frame, const unsigned deviceId, float deviation, void* context);
	
	/** Single sample recording **/
	void startRecording();
	void startDynamicRecording();
	/** Open recording **/
	void openRecording();
	/** Recording siginificant frames**/
	void startDynamicRecording(const int& t);
	/** Pause recording **/
	void pauseRecording();


	/** Change Recorder's settings: gestureType and file index(default=0) **/
	void reinitRecording(const std::string& gt, const int &i);

private:
	/** Checks existence of save directories, creates them if necessary **/
	void checkDirectories();
	/** Saves sample **/
	void writeDown(const std::vector<std::vector<double>>& data, bool notFull);
	/** Forward data from window for prediction and flush if its dynamic gesture **/
	void processData(bool notFull);
	/** Set recording flags to default values and flush window**/
	void cleanUp();

	DataNormalization dataNormalization;
	ConfigManager configManager;

	std::string dataset_dir;
	std::list<LEAP_HAND> window;
	int timestep;
	int timestepBackup;
	int num_features;
	int count;
	bool recording;
	bool continuous;
	int dynamic_timestep;

	bool dynamicRecording;

	std::string gestureType;
};

