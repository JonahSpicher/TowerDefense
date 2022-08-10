#include "Enemy.h"
nEnemy::nEnemy(int posX, int posY){
    position.x = posX;
    position.y = posY;

    enemyShape.setFillColor(sf::Color::Red);
    enemyShape.setSize(sf::Vector2f(20,20));
    enemyShape.setOrigin(10, 10);
    enemyShape.setPosition(posX,posY);
}

sf::RectangleShape nEnemy::getShape(){
    return enemyShape;
}
sf::Vector2f nEnemy::getPosition(){
    return position;
}

void nEnemy::setPosition(sf::Vector2f newLoc){
    position.x = newLoc.x;
    position.y = newLoc.y;
    enemyShape.setPosition(newLoc.x, newLoc.y);
}
