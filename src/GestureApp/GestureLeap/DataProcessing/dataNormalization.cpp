#include "DataNormalizationr.h"

double DataNormalization::min_max_scaler(const double& input, const int& k)
{
	return double(input - min_scaler[k]) / (max_scaler[k] - min_scaler[k]);
}

double DataNormalization::internalAngle(const VECT& a, const VECT& b)
{
	double numerator = (double)a.x * b.x + (double)a.y * b.y + (double)a.z * b.z;
	double denominator = sqrt((double)a.x * a.x + (double)a.y * a.y + (double)a.z * a.z) * sqrt((double)b.x * b.x + (double)b.y * b.y + (double)b.z * b.z);
	return acos(numerator / denominator) * 180.0 / PI;
}

DataNormalization::VECT DataNormalization::lineFromPoint(const LEAP_VECTOR& a, const LEAP_VECTOR& b)
{
	VECT res;
	res.x = (double)b.x - a.x;
	res.y = (double)b.y - a.y;
	res.z = (double)b.z - a.z;
	return res;
}

void DataNormalization::calculate_features(std::vector<double>& output, const LEAP_HAND& hand, int& i)
{
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

	output[i++] = min_max_scaler(internalAngle(CD_thumb, CB_thumb), 0);
	output[i++] = min_max_scaler(internalAngle(CD_index, CB_index), 1);
	output[i++] = min_max_scaler(internalAngle(CD_middle, CB_middle), 2);
	output[i++] = min_max_scaler(internalAngle(CD_ring, CB_ring), 3);
	output[i++] = min_max_scaler(internalAngle(CD_pinky, CB_pinky), 4);

	output[i++] = min_max_scaler(internalAngle(BC_thumb, BA_thumb), 5);
	output[i++] = min_max_scaler(internalAngle(BC_index, BA_index), 6);
	output[i++] = min_max_scaler(internalAngle(BC_middle, BA_middle), 7);
	output[i++] = min_max_scaler(internalAngle(BC_ring, BA_ring), 8);
	output[i++] = min_max_scaler(internalAngle(BC_pinky, BA_pinky), 9);

	output[i++] = min_max_scaler(hand.thumb.distal.next_joint.x, 10);
	output[i++] = min_max_scaler(hand.thumb.distal.next_joint.y, 11);
	output[i++] = min_max_scaler(hand.thumb.distal.next_joint.z, 12);

	output[i++] = min_max_scaler(hand.index.distal.next_joint.x, 13);
	output[i++] = min_max_scaler(hand.index.distal.next_joint.y, 14);
	output[i++] = min_max_scaler(hand.index.distal.next_joint.z, 15);

	output[i++] = min_max_scaler(hand.middle.distal.next_joint.x, 16);
	output[i++] = min_max_scaler(hand.middle.distal.next_joint.y, 17);
	output[i++] = min_max_scaler(hand.middle.distal.next_joint.z, 18);

	output[i++] = min_max_scaler(hand.ring.distal.next_joint.x, 19);
	output[i++] = min_max_scaler(hand.ring.distal.next_joint.y, 20);
	output[i++] = min_max_scaler(hand.ring.distal.next_joint.z, 21);

	output[i++] = min_max_scaler(hand.pinky.distal.next_joint.x, 22);
	output[i++] = min_max_scaler(hand.pinky.distal.next_joint.y, 23);
	output[i++] = min_max_scaler(hand.pinky.distal.next_joint.z, 24);

	output[i++] = min_max_scaler(hand.palm.position.x, 25);
	output[i++] = min_max_scaler(hand.palm.position.y, 26);
	output[i++] = min_max_scaler(hand.palm.position.z, 27);

	output[i++] = min_max_scaler(internalAngle(pinky, ring), 28);
	output[i++] = min_max_scaler(internalAngle(ring, middle), 29);
	output[i++] = min_max_scaler(internalAngle(middle, index), 30);

}


void DataNormalization::scale(const std::list<LEAP_HAND>& window, std::vector<double>& normalized_data)
{
	int i = 0;
	for (auto hand = window.cbegin(); hand != window.cend(); ++hand) {
		calculate_features(normalized_data, *hand, i);
	}

}