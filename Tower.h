#include <iostream>
#include <SFML/Graphics.hpp>


class nTower
{
private:   //all variables that are characteristics of the towers
    int shootSpeed;
    int reloadTime; //in frames
    int damage;
    sf::Vector2f position; //position for tower
    sf::Vector2f bulletPos; //position for bullet

    sf::CircleShape towerShape;
    bool shooting; //checks if a bullet is currently moving
    sf::CircleShape bullet;
public:
    nTower(int posX, int posY); //constructor
    //getter functions for shape, speed and position
    sf::CircleShape getShape();
    sf::CircleShape getBulletShape();
    sf::Vector2f getBulletPosition();
    sf::Vector2f getPosition();
    int getShootSpeed();
    int getReloadTime();
    int getDamage();
    bool getShooting();

    void setReloadTime(int rel);
    void setBulletPosition(sf::Vector2f pos);
    void setShooting(bool s);
};
