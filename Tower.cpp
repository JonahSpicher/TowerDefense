#include "Tower.h"
nTower::nTower(int posX, int posY){
    position.x = posX;
    position.y = posY;
shooting = false;
    //properties of the tower will eventually be set by a towerType variable passed in the constructor
    shootSpeed = 15;
    reloadTime = 30;
    damage = 1;
    range = 200;
towerShape.setFillColor(sf::Color::Blue);
towerShape.setRadius(20);
towerShape.setOrigin(20, 20);
towerShape.setPosition(posX,posY);

bullet.setFillColor(sf::Color::White); //create towers bullet
bullet.setRadius(4);
bullet.setOrigin(4, 4);
bullet.setPosition(1000,1000); //temporary solution mayber

rangeShape.setFillColor(sf::Color(0,255,0,70)); //create semi transparent range circle
rangeShape.setRadius(range);
rangeShape.setOrigin(range, range);
rangeShape.setPosition(posX,posY); //temporary solution mayber
}

sf::CircleShape nTower::getShape(){
    return towerShape;
}
sf::Vector2f nTower::getPosition(){
    return position;
}

int nTower::getShootSpeed(){
    return shootSpeed;
}
int nTower::getDamage(){
    return damage;
}
bool nTower::getShooting(){
  return shooting;
}

sf::CircleShape nTower::getBulletShape(){
  return bullet;
}

sf::CircleShape nTower::getRangeShape(){
  return rangeShape;
}
sf::Vector2f nTower::getBulletPosition(){
  return bulletPos;
}
int nTower::getReloadTime(){
  return currentReloadTime;
}
int nTower::getRange(){
  return range;
}



void nTower::setBulletPosition(sf::Vector2f pos){
  bulletPos = pos;
  bullet.setPosition(pos);
}
void nTower::Reload(){
  currentReloadTime = reloadTime;
}
void nTower::setReloadTime(int rel){
  currentReloadTime -= rel;
}

void nTower::setShooting(bool s){
    shooting = s;
}
