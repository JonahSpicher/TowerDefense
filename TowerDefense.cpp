#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Tower.cpp"
/* To-Do list
    Get render window                       DONE
    Clock cycle                             DONE
    Enemy move across screen                DONE
    Make Tower                              DONE
    Make Enemy shoot tower
        Both Blink                          DONE
        Bullet animation (snall circle)     DONE
            Shoot at original spot          DONE
            track future position           DONE
    Okay im skipping to classifying things cause it makes more sense
            Tower has range
    Enemy health
        Health Bar?
    Add another Path
    Add tower placement
    Tower menu
    multiple towers at once
        towershoot loops through each tower and picks target
    **CLASSIFY towers                     DONE
    and enemies
    more than one enemy - tower shoots closest
    Enemy death
    Implement text files for levels
        Routes, turns, number of
        enemies and type
    Currency to purchase towers
    Tower select menu charges curency
    Different enemie and tower types
    Upgrades

    */

   //Passes a Tower and an enemy target, shows bullet animation and decreases health of enemy, on a timer
   void towershoot(sf::RectangleShape& Enemy, nTower Tower, sf::CircleShape& bullet, sf::Vector2f& targetMove, int& blinktime, bool& shooting);  //function for tower shooting enemy
int main(){

int winHeight = 600;
int winWidth = 600;
sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "More Lines");

//sf::CircleShape Tower;                      //Tower Setup  --soon handled by class
int xPosT(winWidth/2),yPosT(winHeight/2-100);
// Tower.setFillColor(sf::Color::Blue);
// Tower.setRadius(20);
// Tower.setOrigin(20, 20);
// Tower.setPosition(xPosT,yPosT);             //position variables for tower
nTower Tower(xPosT, yPosT); //creating object ntower

sf::RectangleShape Enemy;                   //Enemy Setup
int xPosE(0),yPosE(winHeight/2);
Enemy.setFillColor(sf::Color::Red);
Enemy.setSize(sf::Vector2f(20,20));
Enemy.setOrigin(10, 10);
Enemy.setPosition(xPosE,yPosE);             //position variables for enemy

sf::CircleShape bullet;                      //Tower Setup
int xPosB(1000),yPosB(1000);
bullet.setFillColor(sf::Color::White);
bullet.setRadius(4);
bullet.setOrigin(4, 4);
bullet.setPosition(xPosB,yPosB);

int blinktime(0);
bool shooting(0);
sf::Vector2f targetMove(0,0);
    sf::Clock clock;                        //Clock object for frames

while (window.isOpen())
{
        sf::Time time1 = clock.getElapsedTime();  //time for measuring elapsed times
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

    if (time1.asSeconds() > .02){  //condition to set fps

        xPosE +=4;
        if (xPosE > winWidth){
            xPosE = 0;
        }
        Enemy.setPosition(sf::Vector2f(xPosE,yPosE));

        towershoot(Enemy,Tower,bullet,targetMove, blinktime,shooting);

        window.clear();
        window.draw(Enemy);
        window.draw(Tower.getShape());
        window.draw(bullet);

        window.display();

        clock.restart();
    }
}
      return 0;
}


void towershoot(sf::RectangleShape& Enemy, nTower Tower, sf::CircleShape& bullet, sf::Vector2f& targetMove, int& blinktime, bool& shooting){   //Eventually this will probably loop through every tower and each will pick a target
//placeholder blink animation
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){    //temporary towershoot trigger
//Tower.setFillColor(sf::Color(176,213,217));
//Enemy.setFillColor(sf::Color(255,127,127));
    if(!shooting){
      shooting = true;
      bullet.setPosition(Tower.getPosition());
      sf::Vector2f targetLocation = Enemy.getPosition(); //for now, just where the enemy is

      sf::Vector2f direction = targetLocation - bullet.getPosition();
      float dist = sqrt(pow(direction.x,2) + pow(direction.y,2));
      float scale = 15/dist; //where 15 is pixels/frame
      blinktime = 1/scale;                            //1/scale is number of frames it will take to hit the original location (not perfect)
      sf::Vector2f enemyspeed(4,0);                   //the speed the enemy is moving as a vector      
      sf::Vector2f endPos = targetLocation+sf::Vector2f((1/scale)*enemyspeed.x,1/scale*enemyspeed.y);   //calculate the approximate end position of enemy   
      direction = endPos - bullet.getPosition();            //set new direction vector to be end position                                    
      sf::Vector2f vel(scale*direction.x, scale*direction.y);
      targetMove = vel;
    
    }
  }
// if (blinktime >=5){
// Tower.setFillColor(sf::Color::Blue);
// Enemy.setFillColor(sf::Color::Red);
// blinktime = 0;
// }


if (shooting){
  bullet.setPosition(bullet.getPosition().x+targetMove.x, bullet.getPosition().y+targetMove.y);
  blinktime--;
  if (blinktime == 0){
    bullet.setPosition(1000, 1000);
    shooting = false;
  }
}

}
