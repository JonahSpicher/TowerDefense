#ifndef ENEMY_H
#define ENEMY_H
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
    sf::RectangleShape enemyHealthBar;
    bool isAlive;
public:
    nEnemy(int posX, int posY);
    void move(); //adds velocity to position and sets position of the shape
    sf::RectangleShape getShape();
    sf::RectangleShape getHealthBarShape();
    sf::Vector2f getPosition();
    sf::Vector2f getVelocity();
    int getHealth();
    bool getAlive();
    void setPosition(sf::Vector2f newLoc);
    bool takeDamage(int damage);//takes in damage from tower and subtracts from health, calls die function if health is 0
    void die();


};
#endif
