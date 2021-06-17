#include "geastureLeap.h"


void GestureLeap::processWindow() {
	int res = gesturePrediction.predict(window.getWindow());

	++num_predictions;
	++prediction_map[res];

	if (res < 0)
		return;

	if (res > 6)
	{
		switch (res)
		{
		case 7:
			printf("predicted Gesture: %d RIGHT\n", res);
			window.flush();
			break;
		case 8:
			printf("predicted Gesture: %d LEFT\n", res);
			window.flush();
			break;
		default:
			break;
		}
	}

	else
		printf("predicted Gesture: %d\n", res);
}

void GestureLeap::onFrame(const LEAP_TRACKING_EVENT* frame, const unsigned deviceId, float deviation, void* context) {
	if (frame->nHands == 0) {
		if (!window.isEmpty())
			processWindow();
		window.flush();
		return;
	}

	LEAP_HAND hand = frame->pHands[0];

	window.AddFrame(hand);
	if (window.isFull())
		processWindow();
}

void GestureLeap::getSuccessRate() const {

	std::cout << "Number of predictions: "  << num_predictions << std::endl;
	for (const auto& v : prediction_map)
	{
		std::cout << std::setprecision(3) << "[" << v.first << "] = " << (double)v.second / num_predictions << "%" << std::endl;
	}
}
