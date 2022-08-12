#include <iostream>
#include <SFML/Graphics.hpp>


class nTower
{
private:   //all variables that are characteristics of the towers
    int shootSpeed;
    int reloadTime; //in frames
    int currentReloadTime;
    int damage;
    int range;  //radius of circle rangeShape is set to and tower can shoot at
    sf::Vector2f position; //position for tower
    sf::Vector2f bulletPos; //position for bullet

    sf::CircleShape towerShape; //actual tower shape
    bool shooting; //checks if a bullet is currently moving
    sf::CircleShape bullet; //shape to draw bullet
    sf::CircleShape rangeShape; //shape to draw range, only want to draw if the mouse is over the tower
public:
    nTower(int posX, int posY); //constructor
    //getter functions for shape, speed and position
    sf::CircleShape getShape();
    sf::CircleShape getBulletShape();
      sf::CircleShape getRangeShape();
    sf::Vector2f getBulletPosition();
    sf::Vector2f getPosition();
    int getShootSpeed();
    int getReloadTime();
    int getDamage();
    int getRange();
    bool getShooting();

    void Reload(); //sets current reload time to tower reloadTime
    void setReloadTime(int rel); //decrements reload time by rel
    void setBulletPosition(sf::Vector2f pos);
    void setShooting(bool s);
};
