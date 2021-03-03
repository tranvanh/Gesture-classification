#include "dataNormalizationr.h"

void DataNormalization::min_max_scaler(const std::vector<std::vector<double>> input, std::vector<float>& output)
{
	int ix = 0;
	for (int i = 0; i < this->timeStep; ++i)
		for (int k = 0; k < this->num_feature; ++k, ++ix)
			output[ix] = float(input[i][k] - min_scaler[k]) / (max_scaler[k] - min_scaler[k]);

	//max_scaler = std::vector<double>(31, INT_MIN);
	//min_scaler = std::vector<double>(31, INT_MAX);
}


double DataNormalization::internalAngle(const VECT& a, const VECT& b)
{
	double numerator = (double)a.x * b.x + (double)a.y * b.y + (double)a.z * b.z;
	double denominator = sqrt((double)a.x * a.x + (double)a.y * a.y + (double)a.z * a.z) * sqrt((double)b.x * b.x + (double)b.y * b.y + (double)b.z * b.z);
	return acos(numerator / denominator) * 180.0 / PI;
}

DataNormalization::VECT DataNormalization::lineFromPoint(const LEAP_VECTOR &a, const LEAP_VECTOR &b)
{
	VECT res;
	res.x = b.x - a.x;
	res.y = b.y - a.y;
	res.z = b.z - a.z;
	return res;
}

void DataNormalization::fitScaler(const std::vector<double>& data)
{
	for (int i = 0; i < 31; ++i)
	{
		max_scaler[i] = max_scaler[i] > data[i] ? max_scaler[i] : data[i];
		min_scaler[i] = min_scaler[i] < data[i] ? min_scaler[i] : data[i];
	}
}

void DataNormalization::calculate_features(std::vector<double>& output, const LEAP_TRACKING_EVENT& frame)
{
	LEAP_HAND hand = frame.pHands[0];

	VECT CD_thumb = lineFromPoint(hand.thumb.distal.prev_joint, hand.thumb.distal.next_joint);
	VECT CD_index = lineFromPoint(hand.index.distal.prev_joint, hand.index.distal.next_joint);
	VECT CD_middle = lineFromPoint(hand.middle.distal.prev_joint, hand.middle.distal.next_joint);
	VECT CD_ring = lineFromPoint(hand.ring.distal.prev_joint, hand.ring.distal.next_joint);
	VECT CD_pinky = lineFromPoint(hand.pinky.distal.prev_joint, hand.pinky.distal.next_joint);

	VECT CB_thumb = lineFromPoint(hand.thumb.distal.prev_joint, hand.thumb.intermediate.prev_joint);
	VECT CB_index = lineFromPoint(hand.index.distal.prev_joint, hand.index.intermediate.prev_joint);
	VECT CB_middle = lineFromPoint(hand.middle.distal.prev_joint, hand.middle.intermediate.prev_joint);
	VECT CB_ring = lineFromPoint(hand.ring.distal.prev_joint, hand.ring.intermediate.prev_joint);
	VECT CB_pinky = lineFromPoint(hand.pinky.distal.prev_joint, hand.pinky.intermediate.prev_joint);

	VECT BC_thumb = lineFromPoint(hand.thumb.intermediate.prev_joint, hand.thumb.intermediate.next_joint);
	VECT BC_index = lineFromPoint(hand.index.intermediate.prev_joint, hand.index.intermediate.next_joint);
	VECT BC_middle = lineFromPoint(hand.middle.intermediate.prev_joint, hand.middle.intermediate.next_joint);
	VECT BC_ring = lineFromPoint(hand.ring.intermediate.prev_joint, hand.ring.intermediate.next_joint);
	VECT BC_pinky = lineFromPoint(hand.pinky.intermediate.prev_joint, hand.pinky.intermediate.next_joint);

	VECT BA_thumb = lineFromPoint(hand.thumb.intermediate.prev_joint, hand.thumb.proximal.prev_joint);
	VECT BA_index = lineFromPoint(hand.index.intermediate.prev_joint, hand.index.proximal.prev_joint);
	VECT BA_middle = lineFromPoint(hand.middle.intermediate.prev_joint, hand.middle.proximal.prev_joint);
	VECT BA_ring = lineFromPoint(hand.ring.intermediate.prev_joint, hand.ring.proximal.prev_joint);
	VECT BA_pinky = lineFromPoint(hand.pinky.intermediate.prev_joint, hand.pinky.proximal.prev_joint);

	VECT thumb = lineFromPoint(hand.thumb.proximal.prev_joint, hand.thumb.distal.next_joint);
	VECT index = lineFromPoint(hand.index.proximal.prev_joint, hand.index.distal.next_joint);
	VECT middle = lineFromPoint(hand.middle.proximal.prev_joint, hand.middle.distal.next_joint);
	VECT ring = lineFromPoint(hand.ring.proximal.prev_joint, hand.ring.distal.next_joint);
	VECT pinky = lineFromPoint(hand.pinky.proximal.prev_joint, hand.pinky.distal.next_joint);


	output = {

		internalAngle(CD_thumb, CB_thumb),
		internalAngle(CD_index, CB_index),
		internalAngle(CD_middle, CB_middle),
		internalAngle(CD_ring, CB_ring),
		internalAngle(CD_pinky, CB_pinky),

		internalAngle(BC_thumb, BA_thumb),
		internalAngle(BC_index, BA_index),
		internalAngle(BC_middle, BA_middle),
		internalAngle(BC_ring, BA_ring),
		internalAngle(BC_pinky, BA_pinky),

		hand.thumb.distal.next_joint.x,
		hand.index.distal.next_joint.x,
		hand.middle.distal.next_joint.x,
		hand.ring.distal.next_joint.x,
		hand.pinky.distal.next_joint.x,
		hand.palm.position.x,

		hand.thumb.distal.next_joint.y,
		hand.index.distal.next_joint.y,
		hand.middle.distal.next_joint.y,
		hand.ring.distal.next_joint.y,
		hand.pinky.distal.next_joint.y,
		hand.palm.position.y,


		hand.thumb.distal.next_joint.z,
		hand.index.distal.next_joint.z,
		hand.middle.distal.next_joint.z,
		hand.ring.distal.next_joint.z,
		hand.pinky.distal.next_joint.z,
		hand.palm.position.z,

		internalAngle(pinky, ring),
		internalAngle(ring, middle),
		internalAngle(middle, index)
	};
	//fitScaler(output);
}



void DataNormalization::scale(const std::list<LEAP_TRACKING_EVENT>& window, std::vector<float>& normalized_data)
{
	std::vector<std::vector<double>> dataFrame(this->timeStep);
	int i = 0;
	for (auto frame = window.cbegin(); frame != window.cend(); ++frame, ++i) {
		calculate_features(dataFrame[i], *frame);
	}

	min_max_scaler(dataFrame, normalized_data);
}