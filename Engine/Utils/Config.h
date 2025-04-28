// Config.h
#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <filesystem>
#include <stdexcept>

class Config {
private:
	nlohmann::json config;
	std::string currentFilePath;

	// ��������� ����������� ��� ���������
	Config() = default;

public:
	// ������� ����������� � ������������
	// �� ���� ������ ������ ������ ���� ���� ������� ������
	Config(const Config&) = delete;
	Config& operator=(const Config&) = delete;

	static Config& getInstance() {
		static Config instance;
		return instance;
	}

	
	void load(const std::string& filename);

	
	void save(const std::string& filename = "");

	// ������ � ������ �������
	nlohmann::json& data() { return config; }
	const nlohmann::json& data() const { return config; }

	// �������� ������� �� �����
	nlohmann::json& operator[](const std::string& key) {
		return config[key];
	}
	const nlohmann::json& operator[](const std::string& key) const {
		return config.at(key);
	}

	// �������� ������������� �����
	bool contains(const std::string& key) const {
		return config.contains(key);
	}

#ifdef TEST
	void printConfig() const {
		if (config.empty()) {
			throw std::runtime_error("Config is empty");
		}
		std::cout << config.dump(4) << std::endl;
	}
#endif
	
};