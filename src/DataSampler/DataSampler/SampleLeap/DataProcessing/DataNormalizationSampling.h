#pragma once
#include<list>
#include<vector>
#include <LeapC.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <set>

#define PI 3.14159265

class DataNormalizationSampling {
public:
	DataNormalizationSampling() :timeStep(0), num_feature(0) {};
	DataNormalizationSampling(const int& t, const int& f) :timeStep(t), num_feature(f) {};

	/** Filters significant frames **/
	std::list<LEAP_HAND> selectSignificantFrames(const std::list<LEAP_HAND>& window, const int &recordSize);

	/** Start processcing **/
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

	/** Compute distance between two given points **/
	double distancePoints(const LEAP_VECTOR& a, const LEAP_VECTOR& b);

	/** Compute average sum distance between fingers from each representative intervals **/
	double distanceFingerTips(const LEAP_HAND& a, const LEAP_HAND& b);

	/** Calculate hand features **/
	void calculate_features(std::vector<double>& output, const LEAP_HAND& hand);

	/** Compute distance between palm positions **/
	void calculate_palmDistance(const std::vector<LEAP_HAND>& input, std::vector<DISTANCE>& output);

	/** Desc sort on significance of frames **/
	void sortSignificant(std::vector<DISTANCE>& input);

	/** Compute vectors from given two points **/
	VECT lineFromPoint(const LEAP_VECTOR& a, const LEAP_VECTOR& b);
	/** Compute internal angle of given two vectors **/
	double internalAngle(const VECT& a, const VECT& b);

};