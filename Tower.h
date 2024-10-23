#ifndef TOWER_H
#define TOWER_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "Enemy.h"

//class nEnemy;

class nTower
{
private:   //all variables that are characteristics of the towers
    int shootSpeed;
    int reloadTime; //in frames
    int currentReloadTime;
    int damage;
    int shootTime; //time in frames it takes the bullet to hit the target
    int range;  //radius of circle rangeShape is set to and tower can shoot at
    int targetMode; //How tower targets
    int targetIndex; //Which enemy in array tower is targeting

    sf::Vector2f position; //position for tower
    sf::Vector2f bulletPos; //position for bullet
    sf::Vector2f bulletVel;  //velocity of bullet for towershoot function
    sf::CircleShape towerShape; //actual tower shape
    bool shooting; //checks if a bullet is currently moving
    sf::CircleShape bullet; //shape to draw bullet
    sf::CircleShape rangeShape; //shape to draw range, only want to draw if the mouse is over the tower
    //sf::Font font; //text and font to display target over tower
    sf::Text targetText;
   
public:
    nTower(int posX, int posY, sf::Font& font); //constructor
    //getter functions for shape, speed and position
    sf::CircleShape getShape();
    sf::CircleShape getBulletShape();
      sf::CircleShape getRangeShape();
    sf::Vector2f getBulletPosition();
      sf::Vector2f getBulletVel();
    sf::Vector2f getPosition();
    sf::Text getTargetText() {return targetText;}
    int getShootSpeed();
    int getReloadTime();
    int getDamage();
    int getRange();
    int getShootTime();
    bool getShooting();
    int getTargetMode();
    int getTargetIndex();

    void setReloadTime(int rel); //decrements reload time by rel
    void setBulletPosition(sf::Vector2f pos);
    void moveBullet();  //moves bullet based on current bullet velocitiy
      void setBulletVel(sf::Vector2f vel);
    void setShooting(bool s);
    void setShootTime(int s);
    void setTargetMode(int tm);
    void setTargetIndex(int ti);
    void SetTargetText(int targetIndex);
    void Reload(); //sets current reload time to tower reloadTime
    int findTarget(std::vector<nEnemy> enemies); //Given enemies, returns index of chosen target
    int findDistance(nEnemy target); //Checks how far away an enemy is
};
#endif
