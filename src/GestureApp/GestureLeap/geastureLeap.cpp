#include "geastureLeap.h"


void GestureLeap::processWindow() {
	std::pair<int, double> res = gesturePrediction.predict(window.getWindow());

	++num_predictions;
	++prediction_map[res.first];

	if (res.first < 0)
	{
		invalid_acc.push_back(res.second);
		return;
	}

	if (res.first > 6)
	{
		switch (res.first)
		{
		case 7:
			printf("predicted Gesture: %d RIGHT [%.3f]\n", res.first, res.second);
			window.flush();
			break;
		case 8:
			printf("predicted Gesture: %d LEFT [%.3f]\n", res.first, res.second);
			window.flush();
			break;
		default:
			break;
		}
	}

	else
		printf("predicted Gesture: %d [%.3f]\n", res.first, res.second);
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


void GestureLeap::getInvalidAcc() const{

	std::cout << "Number of predictions: " << num_predictions << std::endl;
	std::cout << "[";
	for (const auto& v : invalid_acc)
	{
		std::cout << std::setprecision(3) << v << ", ";
	}
	std::cout << std::endl;
}
