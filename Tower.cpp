#include "Tower.h"
nTower::nTower(int posX, int posY){
    position.x = posX;
    position.y = posY;
    
towerShape.setFillColor(sf::Color::Blue);
towerShape.setRadius(20);
towerShape.setOrigin(20, 20);
towerShape.setPosition(posX,posY); 
}

sf::CircleShape nTower::getShape(){
    return towerShape;
}
sf::Vector2f nTower::getPosition(){
    return position;
}