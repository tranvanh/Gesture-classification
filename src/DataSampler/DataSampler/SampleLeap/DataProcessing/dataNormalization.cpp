#include "DataNormalizationr.h"

double DataNormalization::internalAngle(const VECT& a, const VECT& b)
{
	double numerator = (double)a.x * b.x + (double)a.y * b.y + (double)a.z * b.z;
	double denominator = sqrt((double)a.x * a.x + (double)a.y * a.y + (double)a.z * a.z) * sqrt((double)b.x * b.x + (double)b.y * b.y + (double)b.z * b.z);
	return acos(numerator / denominator) * 180.0 / PI;
}

DataNormalization::VECT DataNormalization::lineFromPoint(const LEAP_VECTOR& a, const LEAP_VECTOR& b)
{
	VECT res;
	res.x = b.x - a.x;
	res.y = b.y - a.y;
	res.z = b.z - a.z;
	return res;
}

void DataNormalization::calculate_features(std::vector<double>& output, const LEAP_HAND& hand)
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
		hand.thumb.distal.next_joint.y,
		hand.thumb.distal.next_joint.z,

		hand.index.distal.next_joint.x,
		hand.index.distal.next_joint.y,
		hand.index.distal.next_joint.z,

		hand.middle.distal.next_joint.x,
		hand.middle.distal.next_joint.y,
		hand.middle.distal.next_joint.z,

		hand.ring.distal.next_joint.x,
		hand.ring.distal.next_joint.y,
		hand.ring.distal.next_joint.z,

		hand.pinky.distal.next_joint.x,
		hand.pinky.distal.next_joint.y,
		hand.pinky.distal.next_joint.z,

		hand.palm.position.x,
		hand.palm.position.y,
		hand.palm.position.z,

		internalAngle(pinky, ring),
		internalAngle(ring, middle),
		internalAngle(middle, index)
	};
}
double DataNormalization::distancePoints(const LEAP_HAND& a, const LEAP_HAND& b)
{
	double x = (double)b.palm.position.x - a.palm.position.x;
	double y = (double)b.palm.position.y - a.palm.position.y;
	double z = (double)b.palm.position.z - a.palm.position.z;
	return sqrt(x * x + y * y + z * z);
}
void DataNormalization::calculate_palmDistance(const std::vector<LEAP_HAND>& input, std::vector<DISTANCE>& output)
{
	for (int i = 0; i < input.size() - 1; ++i)
	{
		output[i].id_left = i;
		output[i].id_right = i + 1;

		output[i].dist = distancePoints(input[i], input[i + 1]);
	}
}

void DataNormalization::sortSignificant(std::vector<DISTANCE>& input)
{
	struct compare
	{
		bool operator ()(const DISTANCE& left, const DISTANCE& right)const
		{
			return left.dist > right.dist;
		}
	};
	std::sort(input.begin(), input.end(), compare());
}
std::list<LEAP_HAND>  DataNormalization::selectSignificantFrames(const std::list<LEAP_HAND>& window, const int& recordSize)
{
	std::vector<LEAP_HAND> workingWindow(recordSize);
	std::vector<DISTANCE> distances(recordSize - 1);
	std::set<int> saved;
	std::list<LEAP_HAND> output;


	int ix = 0;
	for (const auto& i : window) {
		workingWindow[ix++] = i;
	}

	calculate_palmDistance(workingWindow, distances);
	sortSignificant(distances);

	for (int i = 0; i < distances.size(); ++i)
	{
		if (saved.size() == timeStep)
			break;

		if (saved.size() > timeStep)
			throw "result window size bigger than timeStep";


		if (saved.find(distances[i].id_left) == saved.end() && saved.find(distances[i].id_right) == saved.end()
			&& saved.size() < timeStep - 1) // left right not included and enough space for both
		{
			saved.insert(distances[i].id_left);

			saved.insert(distances[i].id_right);
		}
		else if (saved.find(distances[i].id_left) == saved.end() && saved.find(distances[i].id_right) == saved.end()
			&& saved.size() < timeStep) // left right not included and enough space for only one
		{
			if (distances[i].id_right == recordSize - 1)
			{// right edge
				saved.insert(distances[i].id_left);
			}
			else if (distances[i].id_left == 0)
			{// left edge
				saved.insert(distances[i].id_right);
			}
			else
			{
				double dist_left = distancePoints(workingWindow[distances[i].id_left - 1], workingWindow[distances[i].id_left]);
				double dist_right = distancePoints(workingWindow[distances[i].id_right], workingWindow[distances[i].id_right + 1]);
				if (dist_left > dist_right)
				{
					saved.insert(distances[i].id_left);
				}
				else
				{
					saved.insert(distances[i].id_right);
				}
			}
		}
		else if (saved.find(distances[i].id_left) != saved.end() && saved.find(distances[i].id_right) == saved.end()
			&& saved.size() < timeStep) // left not included and enough space
		{
			saved.insert(distances[i].id_left);
		}
		else if (saved.find(distances[i].id_left) == saved.end() && saved.find(distances[i].id_right) != saved.end()
			&& saved.size() < timeStep) // right not included and enough space
		{
			saved.insert(distances[i].id_right);
		}
	}

	for (const auto& i : saved)
		output.push_back(workingWindow[i]);


	return output;
}
void DataNormalization::scale(const std::list<LEAP_HAND>& window, std::vector<std::vector<double>>& dataFrame)
{
	int i = 0;
	for (auto hand = window.cbegin(); hand != window.cend(); ++hand, ++i) {
		calculate_features(dataFrame[i], *hand);
	}
}