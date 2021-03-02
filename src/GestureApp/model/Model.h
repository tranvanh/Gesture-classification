#pragma once
#include <iostream>
#include <vector>
#include "../includes/cppflow/ops.h"
#include "../includes/cppflow/model.h"

class Model
{
public:
	Model(const std::string& model_dir, const int& t, const int& f) :model(model_dir), num_timestep(t), num_features(f) {};
	int predict(const std::vector<float> &input_data);
	int getTimeStep() const { return this->num_timestep; }
	int getNumFeatures() const { return this->num_features; }

private:
	cppflow::model model;
	int num_timestep;
	int num_features;
};
