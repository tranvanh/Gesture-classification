#pragma once
#include<list>
#include<vector>
#include <LeapC.h>
#include <math.h>
#include <iostream>

#define PI 3.14159265

/** Preprocess data **/
class DataNormalization {
public:
	DataNormalization(const int& t, const int& f) :timeStep(t), num_feature(f) {};

	/** Start processcing **/
	void scale(const std::list<LEAP_HAND>& window, std::vector<double>& normalized_data);
private:
	struct VECT {
		double x;
		double y;
		double z;
	};

	int timeStep;
	int num_feature;

	std::vector<double> min_scaler = { 0.    ,    0.    ,    0.    ,    0.    ,    0.    ,    0.    ,
	  0.    ,    0.    ,    0.    ,    0.    , -693.223 ,  -12.7777,
   -612.731 , -680.146 ,    0.    , -584.665 , -668.353 ,    0.    ,
   -569.33  , -649.613 ,    0.    , -597.032 , -675.481 ,    0.    ,
   -590.976 , -662.551 ,    0.    , -574.437 ,    0.    ,    0.    ,
	  0. };

	std::vector<double> max_scaler = { 180.   ,  180.   ,  180.   ,  179.999,  179.997,  180.   ,
		179.988,  180.   ,  179.985,  179.96 ,  539.053, 1036.65 ,
		720.07 ,  581.654, 1090.93 ,  709.384,  585.01 , 1068.79 ,
		705.543,  567.779, 1056.79 ,  702.861,  544.45 , 1061.02 ,
		693.173,  499.893, 1008.3  ,  707.228,  124.81 ,  161.082,
		137.709 };


	/** Perform MinMax scaling **/
	double min_max_scaler(const double& input, const int& k);

	/** Calculate hand features **/
	void calculate_features(std::vector<double>& output, const LEAP_HAND& hand, int& i);

	/** Compute vectors from given two points **/
	VECT lineFromPoint(const LEAP_VECTOR& a, const LEAP_VECTOR& b);

	/** Compute internal angle of given two vectors **/
	double internalAngle(const VECT& a, const VECT& b);

};