#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Tower.cpp"
#include "Enemy.cpp"
/* To-Do list
    Get render window                       DONE
    Clock cycle                             DONE
    Enemy move across screen                DONE
    Make Tower                              DONE
    Make Enemy shoot tower what no          NEVER
        Both Blink                          DONE and then REMOVED
        Bullet animation (snall circle)     DONE
            Shoot at original spot          DONE
            track future position           DONE
    Okay im skipping to classifying things cause it makes more sense
            Tower has range
            tower has reloadTime            DONE
    Enemy health
        Health Bar?                         DONE
    Add another Path
    Add tower placement
    Tower menu
    multiple towers at once
        towershoot loops through each tower and picks target
    **CLASSIFY towers                     DONE
    and enemies                           DONE!
    more than one enemy - tower shoots closest
    Enemy death                           DONE
    Implement text files for levels
        Routes, turns, number of
        enemies and type
    Currency to purchase towers
    Tower select menu charges curency
    Different enemie and tower types
    Upgrades

    */

   //Passes a Tower and an enemy target, shows bullet animation and decreases health of enemy, on a timer. should bullet be a property of the tower?
   //void drawScreen(nEnemy& enemy, nTower& tower); //function call to handle updating and drawing objects on the screen I actually dont know if this is better
   void towershoot(nEnemy& enemy, nTower& tower, sf::Vector2f& targetMove, int& blinktime);  //function for tower shooting enemy
int main(){

int winHeight = 600;
int winWidth = 600;
sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "More Lines");

//sf::CircleShape Tower;                      //Tower Setup  --soon handled by class --woo
int xPosT(winWidth/2),yPosT(winHeight/2-100); //starting tower position
// Tower.setFillColor(sf::Color::Blue);
// Tower.setRadius(20);
// Tower.setOrigin(20, 20);
// Tower.setPosition(xPosT,yPosT);             //position variables for tower
nTower Tower(xPosT, yPosT); //creating object ntower




//sf::RectangleShape Enemy;                   //Enemy Setup
int xPosE(0),yPosE(winHeight/2);

nEnemy Enemy(xPosE, yPosE);
// Enemy.setFillColor(sf::Color::Red);
// Enemy.setSize(sf::Vector2f(20,20));
// Enemy.setOrigin(10, 10);
// Enemy.setPosition(xPosE,yPosE);             //position variables for enemy
/*
sf::CircleShape bullet;                      //Bullet Setup now in Tower Class
int xPosB(1000),yPosB(1000);
bullet.setFillColor(sf::Color::White);
bullet.setRadius(4);
bullet.setOrigin(4, 4);
bullet.setPosition(xPosB,yPosB);
*/
int blinktime(0);
//bool shooting(0); //if a tower is shooting, is now a tower property
sf::Vector2f targetMove(0,0); //?
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
      /*
        xPosE +=4;
        if (xPosE > winWidth){
            xPosE = 0;
        }
        Enemy.setPosition(sf::Vector2f(xPosE,yPosE));
*/ //should be replaced by move function
        Enemy.move();  //wow so clean
        if(Tower.getReloadTime()>=1){
        Tower.setReloadTime(1);  //decrements reloadtime by 1
      }

      //currently called every frame to shoot bullet and also move bullet to the enemy and wait for reload
        towershoot(Enemy,Tower,targetMove, blinktime); //maybe two functions, one that picks a list of towers/enemys to shoot and another that actually shoots
      
        window.clear();
        if(Enemy.getAlive()){
          window.draw(Enemy.getShape());
          window.draw(Enemy.getHealthBarShape());
        }

        window.draw(Tower.getRangeShape());
        window.draw(Tower.getShape());
        window.draw(Tower.getBulletShape());

        window.display();

        clock.restart();
    }
}
      return 0;
}


void towershoot(nEnemy& enemy, nTower& tower, sf::Vector2f& targetMove, int& blinktime){   //Eventually this will probably loop through every tower and each will pick a target
//placeholder blink animation
  if (tower.getReloadTime()<=0){    //tower tries to shoot automatically when reloaded
//sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&    //temporary towershoot trigger
//Tower.setFillColor(sf::Color(176,213,217));
//Enemy.setFillColor(sf::Color(255,127,127));
    if(!tower.getShooting()){
      sf::Vector2f targetLocation = enemy.getPosition(); //for now, just where the enemy is

      sf::Vector2f direction = targetLocation - tower.getPosition();
      float dist = sqrt(pow(direction.x,2) + pow(direction.y,2)); // gets distnace between tower and target
    //  std::cout << dist << std::endl;
      if(dist <= tower.getRange()){ //only shoots if distance is below range
        tower.setShooting(true);
        tower.Reload();//only resets reload time when you first shoot
        tower.setBulletPosition(tower.getPosition()); //put bullet at tower position

        float scale = tower.getShootSpeed()/dist; //where getShootSpeed is pixels/frame
        blinktime = 1/scale;                            //1/scale is number of frames it will take to hit the original location (not perfect)
        //  sf::Vector2f enemyspeed(4,0);                   //the speed the enemy is moving as a vector, should be enemy property - now it is yay
        sf::Vector2f endPos = targetLocation+sf::Vector2f((1/scale)*enemy.getVelocity().x,1/scale*enemy.getVelocity().y);   //calculate the approximate end position of enemy
        direction = endPos - tower.getBulletPosition();            //set new direction vector to be end position
        sf::Vector2f vel(scale*direction.x, scale*direction.y);
        targetMove = vel;
      }
    }
  }
// if (blinktime >=5){
// Tower.setFillColor(sf::Color::Blue);
// Enemy.setFillColor(sf::Color::Red);
// blinktime = 0;
// }


if (tower.getShooting()){ //bullet is currently moving
  tower.setBulletPosition(sf::Vector2f(tower.getBulletPosition().x+targetMove.x, tower.getBulletPosition().y+targetMove.y));
  blinktime--;
  if (blinktime == 0){ //bullet has hit the enemy
    tower.setBulletPosition(sf::Vector2f(1000, 1000));
    tower.setShooting(false);
    enemy.takeDamage(tower.getDamage());
  }
}

}
/*
void drawScreen(nEnemy& enemy, nTower& tower){ //function call to handle updating and drawing objects on the screen
  window.clear();
  window.draw(enemy.getShape());
  window.draw(enemy.getHealthBarShape());
  window.draw(tower.getShape());
  window.draw(tower.getBulletShape());
}
*/
