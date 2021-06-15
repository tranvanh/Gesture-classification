#include "GesturePrediction.h"

int GesturePrediction::predict(const std::list<LEAP_HAND>& window_data) {
	std::vector<double> normalized_data(model.getNumFeatures() * model.getTimeStep(), 0);
	dataNormalization.scale(window_data, normalized_data);
	return model.predict(normalized_data);
}