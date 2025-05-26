#include "Surface.h"
#include "Apex.h"
#include "PeaShooter.h"
#include "Skorostrel.h"
#include "FireLog.h"
#include "Pumpkin.h"
#include "Zombie.h"

using namespace std;

sf::Vector2f Surface::getPos()
{
    return sf::Vector2f(START_SURFACE_POSITION_X, START_SURFACE_POSITION_Y);
}

void Surface::changePos(const sf::Vector2f& other)
{
    // Static surface, no position change
}

void Surface::setPos(sf::Vector2f other)
{
    // Static surface, no position change
}

void Surface::update()
{
    if (sunSpawnTimer())
    {
        const int rows = static_cast<int>(place_vector.size());
        const int cols = rows > 0 ? static_cast<int>(place_vector[0].size()) : 0;
        if (rows > 0 && cols > 0)
        {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_int_distribution<> distRow(0, rows - 1);
            std::uniform_int_distribution<> distCol(0, cols - 1);

            int r = distRow(gen);
            int c = distCol(gen);
            auto& cell = place_vector[r][c];

            sf::Vector2f cellPos = cell.shape_rect.getPosition();
            sf::Vector2f cellSize = cell.shape_rect.getSize();
            sf::Vector2f sunPos{
                cellPos.x + cellSize.x / 2.f,
                cellPos.y + cellSize.y / 2.f
            };

            auto& tex = R_Manager::get().access<sf::Texture>("Sun.png");
            auto sun = std::make_shared<Sun>(sunPos, tex);
            MSG_Manager::get().addMSG(
                std::make_shared<Engine::MSG_TYPE_CREATE>(sun, this)
            );

            sunSpawnTimer.restart();
        }
    }
}

void Surface::draw(sf::RenderWindow& win)
{
    for (auto& line : place_vector)
    {
        win.draw(this->line(line));
        for (auto& place : line)
            place.draw(win);
    }
    for (auto& zp : zombie_places)
    {
        win.draw(zp.shape_rect);
    }
}

void Surface::sendMsg(const std::shared_ptr<Engine::MSG>& msg)
{
    if (msg->getIndex() == Engine::MSG_TYPE::MSG_TYPE_KILL)
    {
        auto killMsg = std::dynamic_pointer_cast<Engine::MSG_TYPE_KILL>(msg);
        if (!killMsg || !killMsg->victim)
            return;

        Object* obj = dynamic_cast<Object*>(killMsg->victim);
        if (!obj)
            return;

        int type = obj->type();
        if (type == static_cast<int>(Types::Hologram))
        {
            Hologram* holo = dynamic_cast<Hologram*>(killMsg->victim);
            if (!holo)
                return;

            sf::Vector2f pos = holo->getPos();
            for (size_t row = 0; row < place_vector.size(); ++row)
            {
                for (size_t col = 0; col < place_vector[row].size(); ++col)
                {
                    auto& place = place_vector[row][col];
                    auto place_rect = sf::FloatRect(
                        place.shape_rect.getPosition(),
                        place.shape_rect.getSize()
                    );
                    auto holorect = holo->getRect();
                    if (place_rect.intersects(holorect))
                    {
                        if (holo->getPlantType() == "Shovel" && place.isPlanted())
                        {
                            place.deletePLant();
                            place.shape_rect.setTexture(
                                &R_Manager::get().access<sf::Texture>("Drag.png"), true
                            );
                            return;
                        }

                        if (holo->getPlantType() == "Pumpkin" && place.isPlanted() && place.plantobj->getType() != "Pumpkin")
                        {
                            auto pumpkin = std::make_shared<Pumpkin>(static_cast<uint8_t>(row), static_cast<uint8_t>(col));
                            pumpkin->setPlant(place.plantobj);
                            place.plantobj = pumpkin;
                            pumpkin->setPos(place.shape_rect.getPosition());
                            place.shape_rect.setTexture(
                                &R_Manager::get().access<sf::Texture>("IvtClub.png"), true
                            );
                            return;
                        }

                        if (!place.isPlanted() && isInRange(holo->ObjectType, RANGE_PLANT))
                        {
                            auto plant = toPlant(
                                holo->getPlantType(),
                                static_cast<uint8_t>(row),
                                static_cast<uint8_t>(col)
                            );
                            if (plant)
                            {
                                plant->setPos(place.shape_rect.getPosition());
                                MSG_Manager::get().addMSG(
                                    std::make_shared<Engine::MSG_TYPE_CREATE>(plant, this)
                                );
                                place.plant(plant);
                                place.shape_rect.setTexture(
                                    &R_Manager::get().access<sf::Texture>("IvtClub.png"), true
                                );
                            }
                            return;
                        }
                    }
                }
            }
        }
        else if (type == static_cast<int>(Types::BasePlantType) && dynamic_cast<Plant*>(killMsg->victim)->getType() == "Pumpkin")
        {
            auto pumpkin = dynamic_cast<Pumpkin*>(killMsg->victim);
            auto& place = place_vector[pumpkin->line][pumpkin->col];
            if (auto original_plant = pumpkin->getOriginalPlant())
            {
                place.plantobj = original_plant;
                original_plant->setPos(place.shape_rect.getPosition());
            }
            else
            {
                place.plantobj.reset();
                place.isplanted = false;
                place.plantid = VOID_ID;
            }
            place.shape_rect.setTexture(
                &R_Manager::get().access<sf::Texture>(place.isplanted ? "IvtClub.png" : "Drag.png"), true
            );
        }
        else if (type == static_cast<int>(Types::BaseZombieType))
        {
            auto zombie = dynamic_cast<Zombie*>(killMsg->victim);
            if (zombie && zombie->getLine() < zombie_places.size())
            {
                zombie_places[zombie->getLine()].isOccupied = false;
            }
        }
    }
}

std::shared_ptr<Object> Surface::toPlant(std::string plantType, uint8_t line, uint8_t col)
{
    if (line >= place_vector.size() || col >= place_vector[line].size())
        return nullptr;

    if (plantType == "PeaShooter")
        return std::make_shared<PeaShooter>(line, col);
    else if (plantType == "Apex")
        return std::make_shared<Apex>(line, col);
    else if (plantType == "FireLog")
        return std::make_shared<FireLog>(line, col);
    else if (plantType == "Pumpkin")
        return std::make_shared<Pumpkin>(line, col);
    return nullptr;
}