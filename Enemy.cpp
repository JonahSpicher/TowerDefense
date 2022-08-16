#include "Enemy.h"
nEnemy::nEnemy(int posX, int posY){
    position.x = posX;
    position.y = posY;
    health = 10;
    moveSpeed = 5;
    isAlive = true;
    velocity = sf::Vector2f(4,0); //eventually will probably be a unit vector for direction multiplied by the moveSpeed
//properties of the enemy will also eventually be set by a enemyType variable passed in the constructor --not sure how we will change the shape
    enemyShape.setFillColor(sf::Color::Red);
    enemyShape.setSize(sf::Vector2f(20,20));
    enemyShape.setOrigin(10, 10);
    enemyShape.setPosition(posX,posY);
    //health bar set up
    enemyHealthBar.setFillColor(sf::Color::Green);
    enemyHealthBar.setSize(sf::Vector2f(20,5));
  //  enemyHealthBar.setOrigin(10, 10);    Origin should be top left so we can make it smaller easier?
    enemyHealthBar.setPosition(posX-10,posY-20); //probably should streamline this a bit
}

void nEnemy::move(){
  position += velocity;
  if (position.x > 600){
    position.x = 0;
  }
  enemyShape.setPosition(position);
  enemyHealthBar.setPosition(position.x-10,position.y-20); //not ideal but sets health bar above the enemy
}

bool nEnemy::takeDamage(int damage){ //takes in damage variable from tower
  enemyHealthBar.setSize(sf::Vector2f((health*2)-2,5)); //when health changes based on enemy type this will not work right
  health -= damage;

  if (health <=0){
    die();
    return true;
  }
  return false;
}

void nEnemy::die(){
  isAlive = false;
  
  //enemyShape.setFillColor(sf::Color::Black); //probably should do more things
  setPosition(sf::Vector2f(1000,1000));
  velocity = sf::Vector2f(0,0);
  //move();
}

sf::RectangleShape nEnemy::getShape(){
    return enemyShape;
}
sf::RectangleShape nEnemy::getHealthBarShape(){
  return enemyHealthBar;
}

sf::Vector2f nEnemy::getPosition(){
    return position;
}
sf::Vector2f nEnemy::getVelocity(){
    return velocity;
}
bool nEnemy::getAlive(){
    return isAlive;
}
void nEnemy::setPosition(sf::Vector2f newLoc){ //sets enemy position based on Vector2f input parameter
    position.x = newLoc.x;
    position.y = newLoc.y;
    enemyShape.setPosition(newLoc.x, newLoc.y);
}
