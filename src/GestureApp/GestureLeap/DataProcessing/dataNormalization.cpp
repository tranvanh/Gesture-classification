#include "dataNormalizationr.h"

void DataNormalization::min_max_scaler(const std::vector<std::vector<double>> input, std::vector<float>& output)
{
	int ix = 0;
	for (int i = 0; i < this->timeStep; ++i)
	    for (int k = 0; k < this->num_feature; ++k, ++ix)
	        output[ix] = float(input[i][k] - min_scaler[k]) / (max_scaler[k] - min_scaler[k]);
}

double DataNormalization::internalAngle(const LEAP_VECTOR a, const LEAP_VECTOR b)
{
	double numerator = (double)a.x * b.x + (double)a.y * b.y + (double)a.z * b.z;
	double denominator = sqrt((double)a.x * a.x + (double)a.y * a.y + (double)a.z * a.z) * sqrt((double)b.x * b.x + (double)b.y * b.y + (double)b.z * b.z);
	return acos(numerator / denominator) * 180.0 / PI;
}

void DataNormalization::calculate_features(std::vector<double>& output, const LEAP_TRACKING_EVENT* frame)
{
	LEAP_HAND* hand = &frame->pHands[0];
	output = {
		internalAngle(hand->thumb.distal.next_joint, hand->thumb.proximal.prev_joint),
		internalAngle(hand->index.distal.next_joint, hand->index.intermediate.prev_joint),
		internalAngle(hand->middle.distal.next_joint, hand->middle.intermediate.prev_joint),
		internalAngle(hand->ring.distal.next_joint, hand->ring.intermediate.prev_joint),
		internalAngle(hand->pinky.distal.next_joint, hand->pinky.intermediate.prev_joint),

		internalAngle(hand->thumb.proximal.next_joint, hand->thumb.metacarpal.prev_joint),
		internalAngle(hand->index.intermediate.next_joint, hand->index.proximal.prev_joint),
		internalAngle(hand->middle.intermediate.next_joint, hand->middle.proximal.prev_joint),
		internalAngle(hand->ring.intermediate.next_joint, hand->ring.proximal.prev_joint),
		internalAngle(hand->pinky.intermediate.next_joint, hand->pinky.proximal.prev_joint),


		hand->thumb.distal.next_joint.x,
		hand->index.distal.next_joint.x,
		hand->middle.distal.next_joint.x,
		hand->ring.distal.next_joint.x,
		hand->pinky.distal.next_joint.x,
		hand->palm.position.x,

		hand->thumb.distal.next_joint.y,
		hand->index.distal.next_joint.y,
		hand->middle.distal.next_joint.y,
		hand->ring.distal.next_joint.y,
		hand->pinky.distal.next_joint.y,
		hand->palm.position.y,


		hand->thumb.distal.next_joint.z,
		hand->index.distal.next_joint.z,
		hand->middle.distal.next_joint.z,
		hand->ring.distal.next_joint.z,
		hand->pinky.distal.next_joint.z,
		hand->palm.position.z,

		internalAngle(hand->pinky.distal.next_joint, hand->ring.distal.next_joint),
		internalAngle(hand->ring.distal.next_joint, hand->middle.distal.next_joint),
		internalAngle(hand->middle.distal.next_joint, hand->index.distal.next_joint),
	};
}



void DataNormalization::scale(const std::list<const LEAP_TRACKING_EVENT*>& window, std::vector<float>& normalized_data)
{
	std::vector<std::vector<double>> dataFrame(this->timeStep);
	int i = 0;
	for (auto frame = window.cbegin(); frame != window.cend(); ++frame, ++i) {
		calculate_features(dataFrame[i], *frame);
	}

	min_max_scaler(dataFrame, normalized_data);
}