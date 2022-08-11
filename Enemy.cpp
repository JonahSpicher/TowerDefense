#include "Enemy.h"
nEnemy::nEnemy(int posX, int posY){
    position.x = posX;
    position.y = posY;
    health = 10;
    moveSpeed = 5;
    velocity = sf::Vector2f(4,0); //eventually will probably be a unit vector for direction multiplied by the moveSpeed
//properties of the enemy will also eventually be set by a enemyType variable passed in the constructor --not sure how we will change the shape
    enemyShape.setFillColor(sf::Color::Red);
    enemyShape.setSize(sf::Vector2f(20,20));
    enemyShape.setOrigin(10, 10);
    enemyShape.setPosition(posX,posY);
}

void nEnemy::move(){
  position += velocity;
  if (position.x > 600){
    position.x = 0;
  }
  enemyShape.setPosition(position);
}

void nEnemy::takeDamage(int damage){ //takes in damage variable from tower
  health -= damage;
  if (health <=0){
    die();
  }
}

void nEnemy::die(){
  enemyShape.setFillColor(sf::Color::Black); //probably should do more things
}

sf::RectangleShape nEnemy::getShape(){
    return enemyShape;
}
sf::Vector2f nEnemy::getPosition(){
    return position;
}
sf::Vector2f nEnemy::getVelocity(){
    return velocity;
}

void nEnemy::setPosition(sf::Vector2f newLoc){ //sets enemy position based on Vector input parameter
    position.x = newLoc.x;
    position.y = newLoc.y;
    enemyShape.setPosition(newLoc.x, newLoc.y);
}
