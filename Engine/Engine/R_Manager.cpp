#include "R_Manager.h"

using namespace std;

int R_Manager::pushFromFile(sf::RenderWindow& win, const std::string& filepath)
{
    fstream file(filepath, ios::in | ios::out);
    if (!file.is_open())
        throw "file open err";
    ProgressBar *progressBar = nullptr;
    // Сначала подсчитаем общее количество ресурсов для загрузки
    size_t totalResources = 0;
    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        istringstream iss(line);
        char mode;
        iss >> mode;

        if (mode == 'd') {
            char kind;
            string DirPath;
            iss >> kind >> DirPath;
            for (auto files : filesystem::directory_iterator(DirPath)) {
                totalResources++;
            }
        }
        else {
            totalResources++;
        }
    }

    // Вернемся в начало файла
    file.clear();
    file.seekg(0);

    // Создаем прогресс-бар, если не передан извне
    std::unique_ptr<ProgressBar> localProgressBar;
    if (!progressBar) {
        localProgressBar = std::make_unique<ProgressBar>(
            totalResources,
            sf::Vector2f(win.getSize().x * 0.8f, 30.f),
            sf::Vector2f(win.getSize().x * 0.1f, win.getSize().y * 0.9f)
        );
        progressBar = localProgressBar.get();
    }
    else {
        progressBar->setProgress(0.f);  // Сброс прогресса, если бар передан извне
    }

    size_t loadedResources = 0;

    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        // Обновляем прогресс-бар
        if (progressBar) {
            progressBar->increment();
            win.clear();
            progressBar->draw(win);
            win.display();
        }

        istringstream iss(line);
        char mode;
        iss >> mode;

        try {
            switch (mode) {
            case 'd': {
                char kind;
                string DirPath;
                iss >> kind >> DirPath;
                switch (kind) {
                case 't':
                    for (auto files : filesystem::directory_iterator(DirPath)) {
                        push<sf::Texture>(files.path().string());
                        loadedResources++;
                        if (progressBar) {
                            progressBar->setProgress(static_cast<float>(loadedResources) / totalResources);
                            win.clear();
                            progressBar->draw(win);
                            win.display();
                        }
                    }
                    break;
                case 'm':
                    for (auto files : filesystem::directory_iterator(DirPath))
                        push<sf::Music>(files.path().string());
                    break;
                case 'f':
                    for (auto files : filesystem::directory_iterator(DirPath))
                        push<sf::Font>(files.path().string());
                    break;
                case 's':
                    for (auto files : filesystem::directory_iterator(DirPath))
                        push<sf::SoundBuffer>(files.path().string());
                    break;
                }
                break;
            }
            case 't': {
                string respath;
                iss >> respath;
                push<sf::Texture>(respath);
                break;
            }
            case 'm': {
                string respath;
                iss >> respath;
                push<sf::Music>(respath);
                break;
            }
            case 'f': {
                string respath;
                iss >> respath;
                push<sf::Font>(respath);
                break;
            }
            case 's': {
                string respath;
                iss >> respath;
                push<sf::SoundBuffer>(respath);
                break;
            }
            default:
                throw std::runtime_error("МЕХГБЕЯРМШИ ЛНД ВРЕМХЪ:" + string(1, mode));
            }

            loadedResources++;
            if (progressBar) {
                progressBar->setProgress(static_cast<float>(loadedResources) / totalResources);
                win.clear();
                progressBar->draw(win);
                win.display();
            }
        }
        catch (const std::exception& e) {
            cerr << "Error loading resource: " << line << " - " << e.what() << endl;
        }
    }

    return res.size();
}
