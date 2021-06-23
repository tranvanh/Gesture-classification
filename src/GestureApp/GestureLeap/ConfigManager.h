#pragma once
#include <filesystem>
#include <shlobj.h>
#include <windows.h>
#include <string>
#include <json/value.h>
#include <fstream>
#include <iostream>
#include <json/json.h>
#include <vector>


class ConfigManager
{
public:
	ConfigManager();
	ConfigManager(const ConfigManager& configManager);
	Json::Value getConfigValue(const char* key) const& { return root[key]; }
	std::vector<double> getConfigVector(const char* key) const&;
private:
	void defaultConfig();
	std::string path;
	Json::Value root;
};

