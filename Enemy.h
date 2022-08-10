#include <iostream>
#include <SFML/Graphics.hpp>


class nEnemy
{
private:   //all variables that are characteristics of the towers
    int moveSpeed;

    sf::Vector2f position;
    sf::RectangleShape enemyShape;

public:
    nEnemy(int posX, int posY);
    sf::RectangleShape getShape();
    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f newLoc);
};
