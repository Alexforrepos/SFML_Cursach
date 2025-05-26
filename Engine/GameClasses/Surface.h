#pragma once
#include "Engine/R_Manager.h"
#include "Utils/Config.h"
#include "Engine/Object.h"
#include "Engine/MSG_Manager.h"
#include "Hologram.h"
#include "GameClasses/Sun.h"
#include <random>
#include <vector>
#include "ScoreManager.h"
#define DEFAULT_LINE_QOUNT 5
#define DEFAULT_LINE_SIZE 9
#define START_SURFACE_POSITION_X 300
#define START_SURFACE_POSITION_Y 100
#define PLANT_DISTANCE 10
#define PLANT_SIZE_W 100
#define PLANT_SIZE_H 100
#define START_ZOMBIE_POSITION_X 1550
#define ZOMBIE_SPAWN_SIZE 100

class Place
{
public:
    using ull = unsigned long long;

    bool isplanted;
    ull plantid;
    sf::RectangleShape shape_rect;
    std::shared_ptr<Plant> plantobj;

    Place() = default;

    Place(sf::Vector2f pos, sf::Vector2f size)
        : shape_rect(size), isplanted(false), plantid(VOID_ID)
    {
        shape_rect.setPosition(pos);
        shape_rect.setTexture(&R_Manager::get().access<sf::Texture>("Drag.png"));
    }

    void plant(std::shared_ptr<Object> pl)
    {
        if (isplanted && plantobj)
            return;
        if (auto plant = std::dynamic_pointer_cast<Plant>(pl))
        {
            plantobj = plant;
            isplanted = true;
            plantid = pl->getId();
        }
    }

    void deletePLant()
    {
        if (!isplanted || !plantobj)
            return;
        MSG_Manager::get().addMSG(
            std::make_shared<Engine::MSG_TYPE_KILL>(plantobj, nullptr)
        );
        isplanted = false;
        plantobj.reset();
        plantid = VOID_ID;
    }

    bool isPlanted()
    {
        return isplanted;
    }

    void draw(sf::RenderWindow& win)
    {
        win.draw(shape_rect);
    }

    template<class Archive>
    void serialize(Archive& ar)
    {
        ar(shape_rect, isplanted, plantid);
        if constexpr (Archive::is_loading::value)
        {
            const auto& texture = R_Manager::get().access<sf::Texture>(!isplanted ? "Drag.png" : "IvtClub.png");
            shape_rect.setTexture(&texture);
        }
    }

    virtual ~Place() = default;
};

class Zombie_StartPosition
{
public:
    sf::RectangleShape shape_rect;
    bool isOccupied = false;

    Zombie_StartPosition() = default;

    Zombie_StartPosition(sf::Vector2f pos)
    {
        shape_rect.setSize({ ZOMBIE_SPAWN_SIZE, ZOMBIE_SPAWN_SIZE });
        shape_rect.setPosition(pos);
        shape_rect.setTexture(&R_Manager::get().access<sf::Texture>("bozhepomogi.jpg"));
    }

    template<class Archive>
    void serialize(Archive& ar)
    {
        ar(shape_rect, isOccupied);
    }

    virtual ~Zombie_StartPosition() = default;
};

class Surface : public Object
{
private:
    std::vector<std::vector<Place>> place_vector;
    std::vector<Zombie_StartPosition> zombie_places;
    int lines_qount, lines_size;
    Timer sunSpawnTimer{ 5000 }; // 5 sec

public:
    Surface() = default;

    Surface(const int& lines_qount, const int& lines_size = DEFAULT_LINE_SIZE)
        : lines_qount(lines_qount), lines_size(lines_size), Object(static_cast<int>(Types::Level))
    {
        for (int rows = 0; rows < lines_qount; rows++)
        {
            place_vector.push_back(std::vector<Place>());
            for (int cols = 0; cols < lines_size; cols++)
            {
                auto x = static_cast<float>(START_SURFACE_POSITION_X + cols * (PLANT_SIZE_W + PLANT_DISTANCE));
                auto y = static_cast<float>(START_SURFACE_POSITION_Y + rows * (PLANT_SIZE_H + PLANT_DISTANCE));
                place_vector[rows].push_back(Place(
                    { x, y },
                    { PLANT_SIZE_W, PLANT_SIZE_H }
                ));
            }
        }

        for (int row = 0; row < lines_qount; row++)
        {
            float y = static_cast<float>(START_SURFACE_POSITION_Y + row * (PLANT_SIZE_H + PLANT_DISTANCE));
            zombie_places.emplace_back(sf::Vector2f(START_ZOMBIE_POSITION_X, y));
        }
    }

    Surface(const Surface& other) = default;

    sf::Vector2f getPos() override;
    void changePos(const sf::Vector2f& other) override;
    void setPos(sf::Vector2f other) override;
    void update() override;
    void draw(sf::RenderWindow& win) override;
    void sendMsg(const std::shared_ptr<Engine::MSG>& msg) override;

    std::shared_ptr<Object> toPlant(std::string plantType, uint8_t line, uint8_t col);

    sf::RectangleShape line(std::vector<Place> places)
    {
        sf::RectangleShape line_;
        line_.setPosition(places[0].shape_rect.getPosition());
        line_.setSize({
            places[places.size() - 1].shape_rect.getPosition().x + places[places.size() - 1].shape_rect.getSize().x,
            places[0].shape_rect.getSize().y
            });
        if (static_cast<bool>(Config::getInstance()["Dev"]["OutLineDraw"]))
        {
            line_.setFillColor(sf::Color::Yellow);
            line_.setOutlineThickness(3.0f);
            line_.setOutlineColor(sf::Color::White);
        }
        return line_;
    }

    void SpawnZombie()
    {
        // Find unoccupied zombie start positions
        std::vector<size_t> available_indices;
        for (size_t i = 0; i < zombie_places.size(); ++i)
        {
            if (!zombie_places[i].isOccupied)
                available_indices.push_back(i);
        }

        if (available_indices.empty())
            return;

        // Randomly select an available position
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, available_indices.size() - 1);
        size_t selected_index = available_indices[dis(gen)];

        // Get line index and position
        int line_index = static_cast<int>(selected_index);
        sf::Vector2f start_pos = zombie_places[selected_index].shape_rect.getPosition();

        // Create zombie
        auto zombie = std::make_shared<Zombie>(line_index);
        zombie->setPos(start_pos);

        // Mark spawn point as occupied
        zombie_places[selected_index].isOccupied = true;

        // Add to O_Manager
        O_Manager::get().addObject(zombie);
    }

    template<class Archive>
    void serialize(Archive& ar)
    {
        ar(cereal::base_class<Object>(this));
        ar(lines_size, lines_qount);
        ar(zombie_places, place_vector);
    }
};

CEREAL_REGISTER_TYPE(Surface);
CEREAL_REGISTER_TYPE(Place);
CEREAL_REGISTER_TYPE(Zombie_StartPosition);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Object, Surface);