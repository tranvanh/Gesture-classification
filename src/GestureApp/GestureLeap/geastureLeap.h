#pragma once
#pragma once
#include <iostream>
#include <iomanip> 
#include <map>
#include <list>

#include "MultiLeap.h"
#include "SlidingWindow.h"
#include "DataProcessing/DataNormalizationr.h"
#include "DataProcessing/Model.h"
#include "DataProcessing/GesturePrediction.h"
#define PREDICTION_LIMIT 1000



class GestureLeap {

public:
	GestureLeap(const std::string& model_dir, const int &t, const int &f, const int &r) :
		window(t, r), gesturePrediction(model_dir, t, f), num_predictions(0), listen_bool(true){}
	void reinit() {
		num_predictions = 0;
		prediction_map = { {-1, 0}, {0, 0}, {1, 0}, {2, 0},{3, 0}, {4, 0},{5, 0},{6, 0},{7, 0},{8, 0} };
		invalid_acc.clear();
		listen_bool = true;
		window.flush();
	}
	/** Callback for when a frame of tracking data is available. */
	void onFrame(const LEAP_TRACKING_EVENT* frame, const unsigned deviceId, float deviation, void* context);
	void listen() { listen_bool = true; }
	void stop() { listen_bool = false; }

	/** Conclude success rate of prediction */
	void getSuccessRate() const;
	void getInvalidAcc() const;

private:
	SlidingWindow window;
	GesturePrediction gesturePrediction;
	long long int num_predictions;
	std::map<int, long long int> prediction_map = { {-1, 0}, {0, 0}, {1, 0}, {2, 0},{3, 0}, {4, 0},{5, 0},{6, 0},{7, 0},{8, 0} };
	std::list<double> invalid_acc;
	bool listen_bool;


	/** Forward data from window for prediction and flush if its dynamic gesture **/
	void processWindow(const float &deviation);
};

