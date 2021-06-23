#pragma once
#include <iostream>
#include <vector>
#include "../../includes/cppflow/ops.h"
#include "../../includes/cppflow/model.h"

class Model
{
public:
	Model() {};
	Model(const std::string& model_dir, const int& t, const int& f) : num_timestep(t), num_features(f) {
		model.loadModel(model_dir);
		auto output = model.get_operations();
		for (const auto& i : output)
		{
			std::cout << i << std::endl;
		}
	};
	/** Preform prediction **/
	std::pair<int, double> predict(const std::vector<double> &input_data);
	int getTimeStep() const { return this->num_timestep; }
	int getNumFeatures() const { return this->num_features; }

private:
	cppflow::model model;
	int num_timestep;
	int num_features;
};
