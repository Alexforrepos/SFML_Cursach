#pragma once
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
class Config_load
{
	nlohmann::json config;

public:
	Config_load()
	{
		try
		{
			std::ifstream file("./resources/config.json");
			if (!file.is_open())
			{
				throw "json file didnt open";
			}
			file >> config;
			file.close();
		}
		catch(const nlohmann::json::parse_error& e)
		{
			std::cerr << "parse err" << e.what() << std::endl;
		}
	}
	static Config_load& getconfig()
	{
		static Config_load d;
		return d;
	}

	nlohmann::json& get() { return config; };
};

