#pragma once
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <windows.h>
#include <stdio.h>

#include "MultiLeap.h"
#include "DataProcessing/dataNormalizationr.h"


#define SAVE_DIR "DataCollection/"
#define DATASET_DIR "../../Dataset/"

class GestureRecorder {
public:
	/** Callback for when the connection opens. */
	GestureRecorder(const int& t, const int& f, const int &c, const std::string gt) : dataNormalization(t, f), timestep(t), timestepBackup(t), num_features(f),
		count(c), gestureType(gt), recording(false), continuous(false), dynamicRecording(false) {}
	/** Callback for when a frame of tracking data is available. */
	void OnFrame(const LEAP_TRACKING_EVENT* frame, const unsigned deviceId, float deviation, void* context);
	
	/** Single sample recording **/
	void startRecording();
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

