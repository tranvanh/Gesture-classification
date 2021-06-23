#include "geastureLeap.h"

GestureLeap::GestureLeap(): num_predictions(0), listen_bool(true), configManager() {

gesturePrediction = GesturePrediction(
		configManager.getConfigValue("model_directory").asCString(),
		configManager.getConfigValue("timestep").asInt(),
		configManager.getConfigValue("num_features").asInt(),
		configManager.getConfigVector("min_scales"),
		configManager.getConfigVector("max_scales")
	);
	window = SlidingWindow(configManager.getConfigValue("timestep").asInt(), configManager.getConfigValue("sliding_rate").asInt());
}

void GestureLeap::processWindow(const float & deviation) {
	std::pair<int, double> res = gesturePrediction.predict(window.getWindow());
	
	++num_predictions;

	++prediction_map[res.first];

	if (res.first < 0)
	{
		printf("invalid prediction [%.3f] <%lld> deviation: %f \n", res.second, num_predictions, deviation);
		invalid_acc.push_back(res.second);
		return;
	}

	if (res.first > 6)
	{
		switch (res.first)
		{
		case 7:
			printf("predicted Gesture: %d RIGHT [%.3f] <%lld> deviation: %f \n", res.first, res.second, num_predictions, deviation);
			window.flush();
			break;
		case 8:
			printf("predicted Gesture: %d LEFT [%.3f] <%lld> deviation: %f \n", res.first, res.second, num_predictions, deviation);
			window.flush();
			break;
		default:
			break;
		}
	}

	else
		printf("predicted Gesture: %d [%.3f] <%lld> deviation: %f \n", res.first, res.second, num_predictions, deviation);

}

void GestureLeap::onFrame(const LEAP_TRACKING_EVENT* frame, const unsigned deviceId, float deviation, void* context) {
	if (!listen_bool)
		return;

	if (frame->nHands == 0 || frame->nHands > 1) {
		if (frame->nHands > 1)
		{
			std::cout << "Invalid number of hands" << std::endl;
		/*	for (uint32_t h = 0; h < frame->nHands; h++) {
				LEAP_HAND* hand = &frame->pHands[h];
				printf("Hand id %i from device %i is a %s hand with position (%f, %f, %f) with confidence %f and deviation %f.\n",
					hand->id,
					deviceId,
					(hand->type == eLeapHandType_Left ? "left" : "right"),
					hand->palm.position.x,
					hand->palm.position.y,
					hand->palm.position.z,
					hand->confidence,
					deviation);
			}*/
		}
		if (!window.isEmpty())
			processWindow(deviation);
		window.flush();
		return;
	}

	if (num_predictions > PREDICTION_LIMIT){
		std::cout << "STOP LIMIT REACHED" << std::endl;
		window.flush();
		return;
	}

	LEAP_HAND hand = frame->pHands[0];

	window.AddFrame(hand);
	if (window.isFull())
	{
		processWindow(deviation);
		window.slide();
	}

}

void GestureLeap::getSuccessRate() const {

	std::cout << "Number of predictions: "  << num_predictions << std::endl;
	for (const auto& v : prediction_map)
	{
		std::cout << std::setprecision(3) << "[" << v.first << "] = " << (double)v.second / num_predictions << std::endl;
	}
}


void GestureLeap::getInvalidAcc() const{

	std::cout << "Number of predictions: " << num_predictions << std::endl;
	std::cout << "[";
	for (const auto& v : invalid_acc)
	{
		std::cout << std::setprecision(3) << v << ", ";
	}
	std::cout << "]"<< std::endl;
}
