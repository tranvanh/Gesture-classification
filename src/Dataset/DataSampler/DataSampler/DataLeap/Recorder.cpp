#include "Recorder.h"

void Recorder::startRecording() { recording = true; }
void Recorder::startDynamicRecording(const int &t) { recording = true; timestep = t; dynamicRecording = true; }

void Recorder::openRecording() {
	recording = true;
	continuous = true;
}

void Recorder::pauseRecording(){
	recording = false;
	continuous = false;
	window.clear();
}

void Recorder::reinitRecording(const int& i, const std::string gt)
{
	if (recording)
	{
		std::cout << "---> Ongoing recording, pause your recording first: p" << std::endl;
		return;
	}
	count = i;
	gestureType = gt;
}

/** Callback for when a frame of tracking data is available. */
void Recorder::OnFrame(const LEAP_TRACKING_EVENT* frame, const unsigned deviceId) {
	if (!recording)
	{
		window.clear();
		return;
	}
	std::cout << window.size() << std::endl;
	if (frame->nHands == 0) {
		if (!window.empty())
			processData(true);
		window.clear();
		return;
	}

	window.push_back(frame->pHands[0]);
	if (window.size() == timestep)
	{
		processData(false);
	}
}

void Recorder::processData(bool notFull)
{
	if(dynamicRecording)
		window = dataNormalization.selectSignificantFrames(window, timestep);

	timestep = timestepBackup;
	std::vector<std::vector<double>> dataFrame(timestepBackup, std::vector<double>(num_features, 0));
	dataNormalization.scale(window, dataFrame);
	writeDown(dataFrame, notFull);
}

void Recorder::writeDown(const std::vector<std::vector<double>>& data, bool notFull)
{
	std::string name = "DataCollection/" + gestureType + "/" + std::to_string(count) + ".txt";
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
	if (notFull)
		std::cout << "WRITTEN " << count << " FILLED" << std::endl;
	else
		std::cout << "WRITTEN " << count << std::endl;
	window.clear();
	++count;
	if (!continuous)
		recording = false;
}