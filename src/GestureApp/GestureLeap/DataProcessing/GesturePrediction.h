#include <iostream>
#include "MultiLeap.h"
#include "DataNormalizationr.h"
#include "Model.h"

/** Class serves as a crossroad for incoming data sent from sliding window **/
class GesturePrediction {
public:
	GesturePrediction() {};
	GesturePrediction(const std::string& model_dir, const std::string& serving, const int& t, const int& f, const std::vector<double>& min_scales, const std::vector<double>& max_scales) :
		dataNormalization(t, f, min_scales, max_scales) {
		model = Model(model_dir, serving, t, f);

	}
	/** Request prediction on incoming data **/
	std::pair<int, double> predict(const std::list<LEAP_HAND>& window_data);

private:
	Model model;
	DataNormalization dataNormalization;
};
