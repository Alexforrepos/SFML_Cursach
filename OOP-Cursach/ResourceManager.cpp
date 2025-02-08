#include "ResourceManager.h"
using namespace std; 
using namespace filesystem;

Res_Manager* Res_Manager::RM = nullptr;

int Res_Manager::load_from_file(const std::string& filename)
{
	fstream file(filename, ios::in | ios::out);
	if (!file.is_open())
		throw "resource file couldnt open\n";
	while (!file.eof())
	{
		char mode;
		file >> mode;
		string path;
		switch (mode)
		{
		case 'd':	//для папок
			char kind;
			file >> kind >> path;
			switch (kind)
			{
			case 't': //папки текстур
				for (auto files : filesystem::directory_iterator(path))
					load<sf::Texture*>(files.path().string());
				break;
			case 'm': //папки музыки
				for (auto files : filesystem::directory_iterator(path))
					load<sf::Music*>(files.path().string());
				break;
			case 'f': //папки шрифтов
				for (auto files : filesystem::directory_iterator(path))
					load<sf::Font*>(files.path().string());
				break;
			}
			break;
		case 't'://для текстуры
			file >> path;
			load<sf::Texture*>(path);
			break;
		case 'm'://для музыки
			file >> path;
			load<sf::Music*>(path);
			break;
		case 'f'://для шрифта
			load<sf::Font*>(path);
			file >> path;
			break;

		}
	}
	file.close();
	return 0;
}
