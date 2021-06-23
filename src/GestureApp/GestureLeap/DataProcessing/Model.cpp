#include "Model.h"

std::pair<int, double> Model::predict(const std::vector<double> &input_data) {
    auto output = model(cppflow::tensor(input_data, { 1,this->num_timestep,this->num_features }));
    auto values = output.get_data<double>();
    
    double glob_max = 0.;
    int res = -1;
    for (int i = 0; i < values.size(); ++i) {
        res = values[i] > glob_max ? i : res;
        glob_max = values[i] > glob_max ? values[i] : glob_max;
    }

    res = glob_max >= 0.9 ? res : -1; // validating treshold
    return std::make_pair(res, glob_max);
}