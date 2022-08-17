#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Tower.h"
#include "Enemy.h"

/* To-Do list

    Move all checks outside of towershoot, towershoot shoots
    Move bullet handling to enemy - Jonah
    Add tower placement                     IN PROGRESS?
    multiple towers at once
        towershoot loops through each tower and picks target

    Add simple background texture
    Tower menu
    Different enemy types
    Different tower types
    Currency to purchase towers
    Tower select menu charges curency
    Tower upgrades
    Create a Path
    Implement text files for levels
        Routes, turns, number of
        enemies and type



  BUGS:
    Bullet freezes when enemies leave range - keeps moving on initial path when they re-enter, does damage when it gets to original target
      - Possible fixes: move to enemies
    Sometimes the tower refuses to shoot? Have seen it shoot at the start and stop when towers are added, probably an issue with targeting. BAD
      Also, new towers only seem to shoot once. Original tower behavior has stayed consistent though
        - Possible fixes: Literally no idea
    Occasionally, target will change before a bullet hits, and I believe the damage is transferred to the new target. Bullet movement should maybe be an enemy property? Also solves bullet freezing
      - Possible fixes: move to enemies

    */

   //Passes a Tower and an enemy target, shows bullet animation and decreases health of enemy, on a timer. should bullet be a property of the tower?

enum gameState{Menu, Game, Exit};
void MenuLoop(sf::RenderWindow& win, gameState&  state);
void gameLoop(sf::RenderWindow& window, gameState& state);
   bool towershoot(nEnemy& enemy, nTower& tower);  //function for tower shooting enemy
   void addEnemy(std::vector<nEnemy>& Enemy);



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
  int xPosE(0),yPosE(300);   //enemy initial position
  std::vector<nEnemy> Enemy;
  Enemy.push_back(nEnemy(xPosE, yPosE+10)); //add one enemy to the vector



  //temporary stuff
  sf::Vector2i mousePos;
  bool mouseDownL = false; //Just using to stop spawning so many enemies
  bool mouseDownR = false;

  sf::Clock clock;

  while (window.isOpen())
  {
          sf::Time time1 = clock.getElapsedTime();  //time for measuring elapsed times
          sf::Event event;

          while (window.pollEvent(event)) {
              if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                  window.close();
                  state = Exit;


          }

      if (time1.asSeconds() >= .01){  //timer I dont know if we still need this



        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){ //Enemy spawning
          if (!mouseDownL){ //don't spam enemies
            mousePos = sf::Mouse::getPosition(window);
            //std::cout << mousePos.x << "   " <<mousePos.y << std::endl;
            Enemy.push_back(nEnemy(mousePos.x,mousePos.y)); //add one enemy to the vector
            std::cout << Enemy.size() << std::endl;
            mouseDownL = true;
          }
        }
        else{mouseDownL = false;} //Ok its ok to spawn now

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){ //Add towers
          if (!mouseDownR){
            mousePos = sf::Mouse::getPosition(window);

            //std::cout << mousePos.x << "   " <<mousePos.y << std::endl;
            Tower.push_back(nTower(mousePos.x,mousePos.y));
            mouseDownR = true;
          }
        }
        else{mouseDownR = false;}



        for (int i =0; i< Enemy.size(); i++ ){  //for loop for every enemy
            Enemy[i].move();  //wow so clean
          }
        for (int i=0; i<Tower.size(); i++){
          if(Tower[i].getReloadTime()>=1){
              Tower[i].setReloadTime(1);  //decrements reloadtime by 1
            }
        }


        //currently called every frame to shoot bullet and also move bullet to the enemy and wait for reload

        for(int i=0; i<Tower.size(); i++){ //For each tower:
          //Tower[i].setTargetMode(1); //Optional, shoot closest instead of Oldest

          int target = Tower[i].findTarget(Enemy); //Figure out which one you should shoot
          //std::cout << "Made it" << std::endl;
          if(target>=0){
            bool death = towershoot(Enemy[target],Tower[i]); //Shoot it
            if(death){
              std::cout << "Fired at:" << std::endl;
              std::cout << target << std::endl;
              Enemy.erase(Enemy.begin()+target);

              std::cout << Enemy.size() << std::endl;
            }
          }
        }

          window.clear();
        for (int i =0; i< Enemy.size(); i++ ){

          if(Enemy[i].getAlive()){
            window.draw(Enemy[i].getShape());
            window.draw(Enemy[i].getHealthBarShape());

          }
        }
        for (int i=0; i<Tower.size(); i++){
          window.draw(Tower[i].getRangeShape());
          window.draw(Tower[i].getShape());
          window.draw(Tower[i].getBulletShape());
        }

          window.display();

          clock.restart();
      }
  }
}


void addEnemy(std::vector<nEnemy>& Enemy){

}

bool towershoot(nEnemy& enemy, nTower& tower){   //Eventually this will probably loop through every tower and each will pick a target
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



if (tower.getShooting()){ //bullet is currently moving, continue to move bullet
  tower.moveBullet(); //moves bullet by bulletVelocity
  tower.setShootTime(tower.getShootTime()-1); //number of frames the bullet will take to hit the target goes down by one
  if (tower.getShootTime() == 0){ //bullet has hit the enemy
    tower.setBulletPosition(sf::Vector2f(1000, 1000));
    tower.setShooting(false);
    bool death = enemy.takeDamage(tower.getDamage());

    return death;
  }
}
return false;

}
