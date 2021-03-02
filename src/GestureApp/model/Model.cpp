#include "Model.h"

int Model::predict(const std::vector<float> &input_data) {
    auto output = this->model(cppflow::tensor(input_data, { 1,this->num_timestep,this->num_features }));
    auto values = output.get_data<float>();
    float glob_max = -1;
    int res = 0;
    for (int i = 0; i < values.size(); ++i) {
        res = values[i] > glob_max ? i : res;
        glob_max = values[i] > glob_max ? values[i] : glob_max;
    }
    return res;
}