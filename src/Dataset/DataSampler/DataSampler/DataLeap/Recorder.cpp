#include "Recorder.h"


/** Callback for when a frame of tracking data is available. */
void Recorder::OnFrame(const LEAP_TRACKING_EVENT* frame, const unsigned deviceId) {
	if (frame->nHands == 0) {
		window.clear();
		return;
	}

	window.push_back(frame->pHands[0]);
	if (window.size() == timestep)
	{
		std::vector<std::vector<double>> dataFrame(timestep);
		dataNormalization.scale(window, dataFrame);
		writeDown(dataFrame);
	}
}

void Recorder::writeDown(const std::vector<std::vector<double>>& data)
{
	std::string name = "DataCollection/1_" + std::to_string(count)+ ".txt";
	std::ofstream writer(name, std::ios::app);
	if (!writer)
	{
		std::cout << "Error Opening File" << std::endl;
		return;
	}
	for (int i = 0; i < timestep; ++i) {
		for (int k = 0; k < num_features; ++k)
		{
			writer << data[i][k] << " ";
		}
		writer << std::endl;
	}
	writer.close();
	std::cout << "WRITTEN " << count << std::endl;
	window.clear();
	++count;
}