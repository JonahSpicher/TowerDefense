#include <iostream>
#include <SFML/Graphics.hpp>


class nEnemy
{
private:   //all variables that are characteristics of the enemy
    int moveSpeed;
    sf::Vector2f velocity;
    int health;
    sf::Vector2f position;
    sf::RectangleShape enemyShape;

public:
    nEnemy(int posX, int posY);
    void move(); //adds velocity to position and sets position of the shape
    sf::RectangleShape getShape();
    sf::Vector2f getPosition();
    sf::Vector2f getVelocity();
    int getHealth();
    void setPosition(sf::Vector2f newLoc);
    void takeDamage(int damage);//takes in damage from tower and subtracts from health, calls die function if health is 0
    void die();


};
