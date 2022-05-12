#include <iostream>
#include <SFML/Graphics.hpp>


class nTower
{
private:   //all variables that are characteristics of the towers
    int shootSpeed;

    sf::Vector2f position;
    sf::CircleShape towerShape;

public:
    nTower(int posX, int posY);
    sf::CircleShape getShape();
    sf::Vector2f getPosition();
};