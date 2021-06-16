#pragma once
#include<list>
#include<vector>
#include <LeapC.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <set>

#define PI 3.14159265

class DataNormalization {
public:
	DataNormalization(const int& t, const int& f) :timeStep(t), num_feature(f) {};

	std::list<LEAP_HAND> selectSignificantFrames(const std::list<LEAP_HAND>& window, const int &recordSize);
	void scale(const std::list<LEAP_HAND>& window, std::vector<std::vector<double>>& dataFrame);
private:
	struct VECT {
		double x;
		double y;
		double z;
	};

	struct DISTANCE {
		int id_left;
		int id_right;
		double dist;
	};

	int timeStep;
	int num_feature;

	double distancePoints(const LEAP_HAND &a, const LEAP_HAND &b);

	void calculate_features(std::vector<double>& output, const LEAP_HAND& hand);
	void calculate_palmDistance(const std::vector<LEAP_HAND>& input, std::vector<DISTANCE>& output);

	void sortSignificant(std::vector<DISTANCE>& input);

	VECT lineFromPoint(const LEAP_VECTOR& a, const LEAP_VECTOR& b);
	double internalAngle(const VECT& a, const VECT& b);

};