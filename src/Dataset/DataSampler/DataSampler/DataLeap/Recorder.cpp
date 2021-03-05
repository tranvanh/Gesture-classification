#include "Recorder.h"


/** Callback for when a frame of tracking data is available. */
void Recorder::OnFrame(const LEAP_TRACKING_EVENT* frame, const unsigned deviceId) {
	if (frame->nHands == 0) {
		window.clear();
		return;
	}

	window.push_back(frame->pHands[0]);
	if (window.size() == timestep)
	{
		std::vector<double> normalized_data(num_features * timestep);
		dataNormalization.scale(window, normalized_data);
	}
	
}