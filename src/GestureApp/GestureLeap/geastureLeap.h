#pragma once
#pragma once
#include <iostream>
#include <iomanip> 
#include <map>

#include "MultiLeap.h"
#include "SlidingWindow.h"
#include "DataProcessing/DataNormalizationr.h"
#include "DataProcessing/Model.h"
#include "DataProcessing/GesturePrediction.h"


class GestureLeap {
public:
	GestureLeap(const std::string& model_dir, const int &t, const int &f) :
		window(t), gesturePrediction(model_dir, t, f), num_predictions(0){}
	/** Callback for when a frame of tracking data is available. */
	void onFrame(const LEAP_TRACKING_EVENT* frame, const unsigned deviceId, void* context);
	/** Conclude success rate of prediction */
	void getSuccessRate() const;
private:
	HoppingWindow window;
	GesturePrediction gesturePrediction;
	long long int num_predictions;
	std::map<int, long long int> prediction_map = { {-1, 0}, {1, 0}, {2, 0},{3, 0}, {4, 0},{5, 0},{6, 0},{7, 0},{8, 0} };



	/*Forward data from window for prediction and flush if its dynamic gesture*/
	void processWindow();
};

