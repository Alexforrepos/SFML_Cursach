#pragma once
#include "I_Object.h"
#include "PlaceToPlant.h"
class Line :
    public I_Object
{
    sf::Shape* s;

    std::vector<PlaceToPlant*> places;

public:
    Line() = default;
    
    Line(sf::Shape* s, const std::vector<PlaceToPlant*>& places)
        : s(s), places(places)
    {
    }

    // Унаследовано через I_Object
    void Update() override;

    void SendMSG(MSG* msg) override;

    void Draw(sf::RenderWindow& win) override;

};