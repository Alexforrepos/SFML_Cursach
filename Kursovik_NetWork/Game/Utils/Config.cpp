#include "Config.h"

inline void Config::load(const std::string& filename) {
	if (!std::filesystem::exists(filename)) {
		throw std::runtime_error("Config file does not exist: " + filename);
	}

	try {
		std::ifstream file(filename);
		if (!file.is_open())
			throw "err open file";
		config = nlohmann::json::parse(file);
		currentFilePath = filename;
	}
	catch (const nlohmann::json::parse_error& e) {
		throw std::runtime_error("Failed to parse JSON config: " + std::string(e.what()));
	}
}

inline void Config::save(const std::string& filename) {
	std::string savePath = filename.empty() ? currentFilePath : filename;
	if (savePath.empty()) {
		throw std::runtime_error("No file path specified for saving");
	}

	try {
		std::ofstream file(savePath);
		file << config.dump(4);  // Красивое форматирование с отступами
	}
	catch (const std::exception& e) {
		throw std::runtime_error("Failed to save config: " + std::string(e.what()));
	}
}
