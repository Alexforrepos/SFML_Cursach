#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <variant>
#include <string>
#include <map>

class Res_Manager
{
	static Res_Manager* RM;

	std::map<std::string, std::variant<sf::Texture*, sf::Music*, sf::Font*>> resources;
	Res_Manager() = default;
	~Res_Manager()
	{
		for (auto& [key, resource] : resources)
		{
			std::visit([](auto* ptr)
				{
					if (ptr)
					{
						delete ptr;
						std::cout << "Resource deleted." << std::endl;
					}
				}, resource);
		}
		resources.clear();
	}
public:
	int load_from_file(const std::string& filename);

#pragma region load<>
	template<typename T>
	void load(const std::string& filepath)
	{
		throw "have not such data type";
	};
	template<>
	void load<sf::Texture*>(const std::string& filepath)
	{
		if (!std::filesystem::exists(filepath))
		{
			throw "filename not existed";
		}
		std::string filename_ = std::filesystem::path(filepath).filename().string();
		sf::Texture* t = new sf::Texture;
		t->loadFromFile(filepath);
		resources.emplace(filename_, t);
	}

	template<>
	void load<sf::Music*>(const std::string& filepath)
	{
		if (!std::filesystem::exists(filepath))
			throw "filename not existed";
		std::string filename_ = std::filesystem::path(filepath).filename().string();
		sf::Music* m = new sf::Music;
		m->openFromFile(filepath);
		resources.emplace(filename_, m);
	}
	template<>
	void load<sf::Font*>(const std::string& filepath)
	{
		if (!std::filesystem::exists(filepath))
			throw "filename not existed";
		std::string filename = std::filesystem::path(filepath).filename().string();
		sf::Font* f = new sf::Font();
		f->loadFromFile(filepath);
		resources.emplace(filename, f);
	}
#pragma endregion

#pragma region access


	template<typename T>
	T get_access(const std::string& filename)
	{
		throw "type not define";
	};
	template<>
	sf::Texture* get_access<sf::Texture*>(const std::string& filename)
	{
		auto it = resources.find(filename);
		if (it == resources.end())
			throw "have not resourece with this name";
		return std::get<sf::Texture*>(it->second);
	}
	template<>
	sf::Music* get_access<sf::Music*>(const std::string& filename)
	{
		auto it = resources.find(filename);
		if (it == resources.end())
			throw "have not resourece with this name";
		return std::get<sf::Music*>(it->second);
	}
	template<>
	sf::Font* get_access<sf::Font*>(const std::string& filename)
	{
		auto it = resources.find(filename);
		if (it == resources.end())
			throw "have not resourece with this name";
		return std::get<sf::Font*>(it->second);
	}
#pragma endregion

	static Res_Manager* getmger() { return RM ? RM : RM = new Res_Manager; }
	static Res_Manager& get() { return RM ? *RM : *(RM = new Res_Manager); }
	static void del() { if (RM) delete RM; }
};