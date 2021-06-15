#include <iostream>
#include "MultiLeap.h"
#include "DataNormalizationr.h"
#include "Model.h"

/*Class serves as a crossroad for incoming data sent from sliding window*/
class GesturePrediction {
public:
	GesturePrediction(const std::string& model_dir, const int& t, const int& f) : model(model_dir, t, f), dataNormalization(t, f) {}
	/*Request prediction on incoming data*/
	int predict(const std::list<LEAP_HAND>& window_data);

private:
	Model model;
	DataNormalization dataNormalization;
};
