#include "R_Manager.h"

using namespace std;

int R_Manager::pushFromFile(std::string filepath)
{

    fstream file(filepath, ios::in | ios::out);
    if (!file.is_open())
        throw "file open err";
	string line;
    while (getline(file,line))
    {

		if (line.empty() || line[0] == '#')
			continue;
		istringstream iss(line);
		char mode;
		iss >> mode;
		try
		{

			
			switch (mode)
			{
			case 'd':	//для папок
			{
				char kind;
				string DirPath;
				iss >> kind >> DirPath;
				switch (kind)
				{
				case 't': //папки текстур
					for (auto files : filesystem::directory_iterator(DirPath))
						push<sf::Texture>(files.path().string());
					break;
				case 'm': //папки музыки
					for (auto files : filesystem::directory_iterator(DirPath))
						push<sf::Music>(files.path().string());
					break;
				case 'f': //папки шрифтов
					for (auto files : filesystem::directory_iterator(DirPath))
						push<sf::Font>(files.path().string());
					break;
				case 's'://для звука
					for (auto files : filesystem::directory_iterator(DirPath))
						push<sf::SoundBuffer>(files.path().string());
					break;
				}
				break;
			}
			case 't'://для текстуры
			{
				string respath;
				iss >> respath;
				push<sf::Texture>(respath);
				break;
			}
			case 'm'://для музыки
			{
				string respath;
				iss >> respath;
				push<sf::Music>(respath);
				break;
			}
			case 'f'://для шрифта
			{
				string respath;
				iss >> respath;
				push<sf::Font>(respath);
				break;
			}
			case 's':
			{
				string respath;
				iss >> respath;
				push<sf::SoundBuffer>(respath);
				break;
			}

			default :
				throw std::runtime_error("неизвестный мод чтения:" + string(1, mode));
			}
		}
		catch (const std::exception& e)
		{
			cerr << "not wrote ego ebat: " << line  << " - "  << e.what() << endl;
		}
		
    }

    return res.size();
}
