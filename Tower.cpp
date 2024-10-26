#include "Tower.h"
#include <cmath>


nTower::nTower(int posX, int posY, sf::Font& font){
    position.x = posX;
    position.y = posY;
    shooting = false;
    //properties of the tower will eventually be set by a towerType variable passed in the constructor
    shootSpeed = 15;
    reloadTime = 30;
    damage = 1;
    range = 200;
    targetMode = 0;
    targetIndex = -1; //initialized at -1 I guess?
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

//text stuff
 //sf::Font font; moving this here caused a seg fault and makes it crash
 /*
 if (!font.loadFromFile("..//Assets//Sono-Regular.ttf"))
    {
      std::cout << "Font did not load" << std::endl;
    }
    else{
      std::cout << "Tower font loaded?"<< std::endl;
    */
  targetText.setFont(font);
  targetText.setString(std::to_string(targetIndex));
  targetText.setPosition(position.x,position.y+15);
  
  //targetText.setFillColor(sf::Color::White);
  //targetText.setCharacterSize(24);
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
sf::Vector2f nTower::getBulletVel(){
  return bulletVel;
}

int nTower::getReloadTime(){
  return currentReloadTime;
}
int nTower::getRange(){
  return range;
}
int nTower::getShootTime(){
  return shootTime;
}

int nTower::getTargetMode(){
  return targetMode;
}

int nTower::getTargetIndex(){
  return targetIndex;
}


void nTower::setBulletPosition(sf::Vector2f pos){
  bulletPos = pos;
  bullet.setPosition(pos);
}
void nTower::setBulletVel(sf::Vector2f vel){
  bulletVel = vel;

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
void nTower::setShootTime(int s){
    shootTime = s;
}
void nTower::moveBullet(){
    bulletPos = sf::Vector2f(bulletPos.x+bulletVel.x,bulletPos.y+bulletVel.y) ;
    bullet.setPosition(bulletPos);
}

void nTower::setTargetMode(int tm){
    targetMode = tm;
}

void nTower::setTargetIndex(int ti){
    targetIndex = ti;
}

int nTower::findDistance(nEnemy target){ //distance between tower and enemy
  sf::Vector2f ePos = target.getPosition();
  int dist = sqrt(pow(ePos.x - position.x,2) + pow(ePos.y - position.y,2));
  return dist;
}

bool nTower::BulletCollision(nEnemy target){ //distance between bullet and enemy
  sf::Vector2f ePos = target.getPosition();
  int dist = sqrt(pow(ePos.x - bulletPos.x,2) + pow(ePos.y - bulletPos.y,2));
  if (dist <= target.getShape().getSize().x){
    return true;
  }
  else
  return false;
}
int nTower::findTarget(std::vector<nEnemy> enemies){ //returns target index if there is a target within range, otherwise -1

  switch(targetMode){
    case 0: {//target enemy that showed up first
      //stuff
      int numEnemies = enemies.size();
      if (numEnemies == 0) {return -1;}
      int i = 0;
      while(findDistance(enemies[i]) > range){
        i++;
        if(i == numEnemies){
          i = -1; //signal that nothing was found
          break; //stop looking before we escape the array
        }
      }
      targetIndex = i;
      return i;
      break;
    }
    case 1: { //Shoot the enemy thats closest to the tower
      int numEnemies = enemies.size();
      int smallestDist = 10000; 
      int closest = 0;
      for (int i=0; i<numEnemies; i++){
        int dist = findDistance(enemies[i]);
        if (dist < range && dist < smallestDist){
          closest = i;
          smallestDist = dist;
        }
      }
      if (smallestDist == 10000){ //no enemy is in range
        targetIndex = -1;
        return -1;
      }
      else{
        targetIndex = closest;
        return closest;
      }
    }
    default:{
      //placeholder, not sure what behavior, doesn't really matter
      return 0;
    }
  
  
  }

}

void nTower::SetTargetText(int targetIndex){
    targetText.setString(std::to_string(targetIndex));
    
}