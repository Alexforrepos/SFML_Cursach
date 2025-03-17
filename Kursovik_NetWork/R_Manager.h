#pragma once
#include <memory>
#include <string>
#include <vector>
#include <variant>
#include <fstream>
#include <sstream> //string << int
#include <iostream>
#include <filesystem>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


class R_Manager
{
	std::vector<std::pair<std::string, std::variant<sf::Texture*,sf::Font*,sf::SoundBuffer*,sf::Music*>>> res;
	
	R_Manager() = default;

	/// <summary>
	/// служебная вставка данных ресурсов по пути 
	/// выдает эксепшн 
	/// </summary>
	/// <typeparam name="T">тип ресурса</typeparam>
	/// <param name="path">путь к ресурсу</param>
	/// <returns>удача или нет</returns>
	template<typename T>
	void push(std::string path)
	{
		throw "err type";
	}

#pragma region push

	template<>
	void push<sf::Texture>(std::string path)
	{
		if (!std::filesystem::exists(path))
			throw "filename not existed";
		std::string filename = std::filesystem::path(path).filename().string();
		sf::Texture* texture = new sf::Texture;
		if (!texture->loadFromFile(path))
			throw "failed to load texture";
		res.emplace_back(filename, texture);
	}

	template<>
	void push<sf::Font>(std::string path)
	{
		if (!std::filesystem::exists(path))
			throw "filename not existed";
		std::string filename = std::filesystem::path(path).filename().string();
		sf::Font* font = new sf::Font;
		if (!font->loadFromFile(path))
			throw "failed to load font";
		res.emplace_back(filename, font);
	}

	template<>
	void push<sf::SoundBuffer>(std::string path)
	{
		if (!std::filesystem::exists(path))
			throw "filename not existed";
		std::string filename = std::filesystem::path(path).filename().string();
		sf::SoundBuffer* buffer = new sf::SoundBuffer;
		if (!buffer->loadFromFile(path))
			throw "failed to load sound buffer";
		res.emplace_back(filename, buffer);
	}

	template<>
	void push<sf::Music>(std::string path)
	{
		if (!std::filesystem::exists(path))
			throw "filename not existed";
		std::string filename = std::filesystem::path(path).filename().string();
		sf::Music* music = new sf::Music;
		if (!music->openFromFile(path))
			throw "failed to load music";
		res.emplace_back(filename, music);
	}

#pragma endregion

public:

	~R_Manager()
	{
		for (auto& pair : res)
		{
			// Освобождаем память для каждого ресурса в зависимости от его типа
			std::visit([](auto&& arg) {
				using T = std::decay_t<decltype(arg)>;
				if constexpr (std::is_same_v<T, sf::Texture*>)
				{
					delete arg; // Удаляем текстуру
				}
				else if constexpr (std::is_same_v<T, sf::Font*>)
				{
					delete arg; // Удаляем шрифт
				}
				else if constexpr (std::is_same_v<T, sf::SoundBuffer*>)
				{
					delete arg; // Удаляем звуковой буфер
				}
				else if constexpr (std::is_same_v<T, sf::Music*>)
				{
					delete arg; // Удаляем музыку
				}
				}, pair.second);
		}

		// Очищаем вектор
		res.clear();
	}

	/// <summary>
	/// для реализации сингл тона 
	/// </summary>
	/// <returns>единственный экземпляр класса</returns>
	static R_Manager& get()
	{
		static R_Manager inst;	
		return inst;
	}


	/// <summary>
	/// считывает текстовый файл(с особым синтаксисом) и забирает от туда данные про местоположение папок с ресурсам и отдельных ресурсов
	/// </summary>
	/// <param name="path">путь к текстовому файлу</param>
	/// <returns>количество полученных ресурсов</returns>
	int pushFromFile(std::string path);



	/// <summary>
	/// это метод для доступа к ресурсам 
	/// он будет выдавать эксепешн если тип не перегружен
	/// </summary>
	/// <typeparam name="T">тип ресурса</typeparam>
	/// <param name="">путь к ресурсу</param>
	/// <returns>ресурс</returns>
	template<typename T>
	T& access(std::string)
	{
		throw "err type";
	};


#pragma region access

	template<>
	sf::Texture& access<sf::Texture>(std::string path)
	{
		for (auto& pair : res)
		{
			if (pair.first == path)
			{
				if (auto* texture = std::get_if<sf::Texture*>(&pair.second))
					return **texture;
			}
		}
		throw "texture not found";
	}

	template<>
	sf::Font& access<sf::Font>(std::string path)
	{
		for (auto& pair : res)
		{
			if (pair.first == path)
			{
				if (auto* font = std::get_if<sf::Font*>(&pair.second))
					return **font;
			}
		}
		throw "font not found";
	}

	template<>
	sf::SoundBuffer& access<sf::SoundBuffer>(std::string path)
	{
		for (auto& pair : res)
		{
			if (pair.first == path)
			{
				if (auto* buffer = std::get_if<sf::SoundBuffer*>(&pair.second))
					return **buffer;
			}
		}
		throw "sound buffer not found";
	}


	template<>
	sf::Music& access<sf::Music>(std::string path)
	{
		for (auto& pair : res)
		{
			if (pair.first == path)
			{
				if (auto* music = std::get_if<sf::Music*>(&pair.second))
					return **music;
			}
		}
		throw "music not found";
	}

#pragma endregion

};
//R_Manager::get().access<Texture>(name)
