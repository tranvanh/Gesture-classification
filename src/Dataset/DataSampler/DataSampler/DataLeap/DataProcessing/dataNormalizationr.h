#pragma once
#include<list>
#include<vector>
#include <LeapC.h>
#include <math.h>
#include <iostream>

#define PI 3.14159265

class DataNormalization {
public:
	DataNormalization(const int& t, const int& f) :timeStep(t), num_feature(f) {};
	void scale(const std::list<LEAP_HAND>& window, std::vector<std::vector<double>>& dataFrame);
private:
	struct VECT {
		double x;
		double y;
		double z;
	};

	int timeStep;
	int num_feature;

	void calculate_features(std::vector<double>& output, const LEAP_HAND& hand);

	VECT lineFromPoint(const LEAP_VECTOR& a, const LEAP_VECTOR& b);
	double internalAngle(const VECT& a, const VECT& b);

};