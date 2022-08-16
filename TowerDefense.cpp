#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Tower.h"
#include "Enemy.h"
//#include "Enemy.cpp"
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
            also just shoot at current position   DONE
    Okay im skipping to classifying things cause it makes more sense
            Tower has range                 DONE
            tower has reloadTime            DONE
    Enemy health                             DONE
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

enum gameState{Menu, Game, Exit};
void MenuLoop(sf::RenderWindow& win, gameState&  state);
void gameLoop(sf::RenderWindow& window, gameState& state);
   void towershoot(nEnemy& enemy, nTower& tower);  //function for tower shooting enemy
   void addEnemy(std::vector<nEnemy>& Enemy, int& enemyNum);



int main(){
gameState state = Menu; //start with menu

int winHeight = 600;
int winWidth = 600;

bool quit = false;
sf::RenderWindow _window(sf::VideoMode(winWidth, winHeight), "More Lines");

    _window.setFramerateLimit(60);                 //keeps framerate at 60
    while(!quit){
      switch (state){
          case Menu: {
            MenuLoop(_window,state);
          }
          case Game:{
            gameLoop(_window,state);
          }
          case Exit: {
            quit = true;
          }
        }
      }

      return 0;
}


void MenuLoop(sf::RenderWindow& win,gameState& state){ //handles beginning menu loop and maybe pause screen for now hit enter to move on
  int quit(0);
    sf::Event event;
  while (state == Menu){


    while (win.pollEvent(event)) {
        if (event.type == sf::Event::Closed){
            win.close();
            state = Exit;
          }
    }
    sf::RectangleShape box;
    win.clear();
    win.draw(box);
    win.display();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
      state = Game;
    }

  }
}
void gameLoop(sf::RenderWindow& window,gameState& state){   //handles the game loop, now all objects are created locally in game loop method

  int xPosT(300),yPosT(300-100); //starting tower position
    std::vector<nTower> Tower;
  //nTower Tower(xPosT, yPosT); //creating vector tower
  Tower.push_back(nTower(xPosT, yPosT)); //add one tower to the vector




  //sf::RectangleShape Enemy;                   //Enemy Setup
  int enemyNum(0);
  int xPosE(0),yPosE(300);   //enemy initial position
  std::vector<nEnemy> Enemy;
  Enemy.push_back(nEnemy(xPosE, yPosE+10)); //add one enemy to the vector
  enemyNum+=1;



  //temporary stuff
  sf::Vector2i mousePos;
  bool mouseDown = false; //Just using to stop spawning so many enemies

      sf::Clock clock;

  while (window.isOpen())
  {
          sf::Time time1 = clock.getElapsedTime();  //time for measuring elapsed times
          sf::Event event;

          while (window.pollEvent(event)) {
              if (event.type == sf::Event::Closed)
                  window.close();
                  state = Exit;

          }

      if (time1.asSeconds() >= .01){  //timer I dont know if we still need this


        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
          if (!mouseDown){ //don't spam enemies
            mousePos = sf::Mouse::getPosition(window);
            //std::cout << mousePos.x << "   " <<mousePos.y << std::endl;
            Enemy.push_back(nEnemy(mousePos.x,mousePos.y)); //add one enemy to the vector
            enemyNum += 1;
            std::cout << enemyNum << std::endl;
            mouseDown = true;
          }

        }
        else{mouseDown = false;} //Ok its ok to spawn now

        for (int i =0; i< enemyNum; i++ ){  //for loop for every enemy
            Enemy[i].move();  //wow so clean
          }
        if(Tower[0].getReloadTime()>=1){
            Tower[0].setReloadTime(1);  //decrements reloadtime by 1
          }

        //currently called every frame to shoot bullet and also move bullet to the enemy and wait for reload
          towershoot(Enemy[0],Tower[0]); //maybe two functions, one that picks a list of towers/enemys to shoot and another that actually shoots

          window.clear();
        for (int i =0; i< enemyNum; i++ ){
          if(Enemy[i].getAlive()){
            window.draw(Enemy[i].getShape());
            window.draw(Enemy[i].getHealthBarShape());

          }
        }
          window.draw(Tower[0].getRangeShape());
          window.draw(Tower[0].getShape());
          window.draw(Tower[0].getBulletShape());

          window.display();

          clock.restart();
      }
  }
}


void addEnemy(std::vector<nEnemy>& Enemy, int& enemyNum){

}

void towershoot(nEnemy& enemy, nTower& tower){   //Eventually this will probably loop through every tower and each will pick a target
//placeholder blink animation
  if (tower.getReloadTime()<=0){    //tower tries to shoot automatically when reloaded
//sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&    //temporary towershoot trigger
//Tower.setFillColor(sf::Color(176,213,217));
//Enemy.setFillColor(sf::Color(255,127,127));
    if(!tower.getShooting()){   //currently only shoots if enemy is below tower?
      sf::Vector2f targetLocation = enemy.getPosition(); //for now, just where the enemy is

      sf::Vector2f direction = targetLocation - tower.getPosition();
      float dist = sqrt(pow(direction.x,2) + pow(direction.y,2)); // gets distnace between tower and target
    //  std::cout << dist << std::endl;
      if(dist <= tower.getRange()){ //only shoots if distance is below range
        tower.setShooting(true);
        tower.Reload();//only resets reload time when you first shoot
        tower.setBulletPosition(tower.getPosition()); //put bullet at tower position

        float scale = tower.getShootSpeed()/dist; //where getShootSpeed is pixels/frame
        tower.setShootTime(1/scale);           //1/scale is number of frames it will take to hit the original location (not perfect)
        //  sf::Vector2f enemyspeed(4,0);                   //the speed the enemy is moving as a vector, should be enemy property - now it is yay
        sf::Vector2f endPos = targetLocation+sf::Vector2f((1/scale)*enemy.getVelocity().x,1/scale*enemy.getVelocity().y);   //calculate the approximate end position of enemy
        direction = endPos - tower.getBulletPosition();            //set new direction vector to be end position
        sf::Vector2f vel(scale*direction.x, scale*direction.y);
        tower.setBulletVel(vel);     //set bullet velocity towards the enemys end location
      }
    }
  }



if (tower.getShooting()){ //bullet is currently moving, continue to move bullet
  tower.moveBullet(); //moves bullet by bulletVelocity
  tower.setShootTime(tower.getShootTime()-1); //number of frames the bullet will take to hit the target goes down by one
  if (tower.getShootTime() == 0){ //bullet has hit the enemy
    tower.setBulletPosition(sf::Vector2f(1000, 1000));
    tower.setShooting(false);
    enemy.takeDamage(tower.getDamage());
  }
}

}
