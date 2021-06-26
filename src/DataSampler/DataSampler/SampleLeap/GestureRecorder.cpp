#include "GestureRecorder.h"

GestureRecorder::GestureRecorder(const std::string gt): count(0), gestureType(gt), recording(false), continuous(false), dynamicRecording(false), dynamic_timestep(0) {

	dataNormalization = DataNormalizationSampling(
		configManager.getConfigValue("timestep").asInt(),
		configManager.getConfigValue("num_features").asInt()
	);
	timestep = configManager.getConfigValue("timestep").asInt();
	dynamic_timestep = configManager.getConfigValue("dynamic_timestep").asInt();

	timestepBackup = configManager.getConfigValue("timestep").asInt();
	num_features = configManager.getConfigValue("num_features").asInt();

	dataset_dir = configManager.getConfigValue("dataset_directory").asCString();

}

void GestureRecorder::startRecording() { recording = true; continuous = false; }
void GestureRecorder::startDynamicRecording() { recording = true; timestep = dynamic_timestep; dynamicRecording = true; }

void GestureRecorder::openRecording() {
	recording = true;
	continuous = true;
}

void GestureRecorder::pauseRecording() {
	recording = false;
	continuous = false;
	window.clear();
}

void GestureRecorder::reinitRecording(const std::string& gt, const int& i)
{
	if (recording)
	{
		std::cout << "---> Ongoing recording, pause your recording first using: p" << std::endl;
		return;
	}
	count = i;
	gestureType = gt;
}


void GestureRecorder::OnFrame(const LEAP_TRACKING_EVENT* frame, const unsigned deviceId, float deviation, void* context) {
	if (!recording)
	{
		window.clear();
		return;
	}


	if (frame->nHands > 1) {
		std::cout << "Multiple hands presented, sample is thrown away" << std::endl;
		if (!continuous)
			recording = false;
		window.clear();
	}

	if (frame->nHands == 0) {
		if (!window.empty())
			processData(true);
		window.clear();
		return;
	}

	window.push_back(frame->pHands[0]);

	if (window.size())
		std::cout << window.size() << std::endl;

	if (window.size() == timestep)
	{
		processData(false);
	}
}

void GestureRecorder::processData(bool notFull)
{
	if (dynamicRecording)
	{
		if (window.size() % 2)
			window.pop_back();
		window = dataNormalization.selectSignificantFrames(window, window.size());
	}

	timestep = timestepBackup;
	dynamicRecording = false;
	std::vector<std::vector<double>> dataFrame(timestepBackup, std::vector<double>(num_features, 0.0));
	dataNormalization.scale(window, dataFrame);
	writeDown(dataFrame, notFull);
}

void GestureRecorder::checkDirectories()
{
	std::string gesture_dir = dataset_dir + "/" + gestureType;


	std::wstring LPCWSTR_datasetDir(dataset_dir.begin(), dataset_dir.end());
	std::wstring LPCWSTR_gestureDir(gesture_dir.begin(), gesture_dir.end());


	if (CreateDirectory(LPCWSTR_datasetDir.c_str(), NULL))
		std::cout << "created directory \"" << dataset_dir << std::endl;

	if (CreateDirectory(LPCWSTR_gestureDir.c_str(), NULL))
		std::cout << "created directory:\"" << gesture_dir << std::endl;
}


void GestureRecorder::cleanUp()
{
	window.clear();
	++count;
	if (!continuous)
		recording = false;
}

void GestureRecorder::writeDown(const std::vector<std::vector<double>>& data, bool notFull)
{
	checkDirectories();
	std::string name = dataset_dir + "/" + gestureType + "/" + std::to_string(count) + ".txt";
	std::ofstream writer(name, std::ios::trunc);
	std::cout << "save file to: " << name << std::endl;
	if (!writer)
	{
		std::cout << "Error Opening File" << std::endl;
		cleanUp();
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
	cleanUp();

}