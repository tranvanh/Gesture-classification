#include "geastureLeap.h"


/** Callback for when a frame of tracking data is available. */
void GestureLeap::OnFrame(const LEAP_TRACKING_EVENT* frame, const unsigned deviceId) {
	if (frame->nHands == 0) {
		window.flush();
		return;
	}

	LEAP_HAND hand = frame->pHands[0];

	window.AddFrame(hand);
	if (window.isFull())
	{
		auto window_data = window.getWindow();
		std::vector<double> normalized_data(model.getNumFeatures() * model.getTimeStep());
		dataNormalization.scale(window.getWindow(), normalized_data);
		int res = model.predict(normalized_data);
		printf("predicted Gesture: %d\n", res);
	}
}