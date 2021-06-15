#pragma once
#pragma once
#include <iostream>
#include "MultiLeap.h"
#include "SlidingWindow.h"
#include "DataProcessing/DataNormalizationr.h"
#include "DataProcessing/Model.h"
#include "DataProcessing/GesturePrediction.h"


class GestureLeap {
public:
	GestureLeap(const int &t, const int &f, const std::string &model_dir) : window(t), gesturePrediction(model_dir, t, f){}
	/** Callback for when a frame of tracking data is available. */
	void OnFrame(const LEAP_TRACKING_EVENT* frame, const unsigned deviceId, void* context);

private:
	HoppingWindow window;
	GesturePrediction gesturePrediction;
	
	/*Forward data from window for prediction and flush if its dynamic gesture*/
	void processWindow();
};

