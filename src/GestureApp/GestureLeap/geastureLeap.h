#pragma once
#pragma once
#include <iostream>
#include "MultiLeap.h"
#include "../model/Model.h"
#include "DataProcessing/hoppingWindow.h"
#include "DataProcessing/dataNormalizationr.h"


class GestureLeap {
public:
	/** Callback for when the connection opens. */
	GestureLeap(const int &t, const int &f) : window(t), model("./LSTM_model", t, f), dataNormalization(t,f), dynamicGesture(false){}
	/** Callback for when a frame of tracking data is available. */
	void OnFrame(const LEAP_TRACKING_EVENT* frame, const unsigned deviceId);

private:
	HoppingWindow window;
	Model model;
	DataNormalization dataNormalization;
	
	bool dynamicGesture;


	void processWindow();
};

