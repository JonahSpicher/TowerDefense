#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Tower.h"
#include "Enemy.h"

#include <string>
#include <limits.h>
#include <unistd.h>

 std::string getexepath()
{
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  return std::string( result, (count > 0) ? count : 0 );
}


/* To-Do list

    Move all checks outside of towershoot, towershoot shoots
    Move bullet handling to enemy - Cancelled
    Add tower placement                                      IN PROGRESS?  DONE
    multiple towers at once                                               DONE
        towershoot loops through each tower and picks target              
    

    Towers:
      Tower shooting modes
      Different tower types
      Currency to purchase towers
      Tower select menu charges curency
      Tower upgrades

    Enemies:
      Make sure we are properly deleting when killed (currently erasing from vector and moving offscreen) --actually after some research it seems like this is exactly correct
          Different enemy types

    Graphics:
    Add simple background texture
    Add simple Enemy and Tower sprites
    Tower menu

    
    Create a Path
    Implement text files for levels
        Routes, turns, number of
        enemies and type



  BUGS:
   1. Bullet freezes when enemies leave range - keeps moving on initial path when they re-enter, does damage when it gets to original target ---FIXED
      - Possible fixes: move to enemies
    2. Sometimes the tower refuses to shoot? Have seen it shoot at the start and stop when towers are added, probably an issue with targeting. BAD
        I saw this happen when the tower "missed" the bullet didnt hit anything and went off screen, and the tower never shot again
        Except now it happens when you start the game, seemingly radnomly either works fine or doesnt at all. 
        Possible Fixes: This is scary but maybe erasing bullets and enemies and everything on quit? not sure if that could affect the next game launch 

      Also, new towers only seem to shoot once. Original tower behavior has stayed consistent though -- I cant replicate this
      Also this isn't totally true, right now the first tower doesn't shoot consistently either and sometimes new ones do shoot a few times
      before stopping. ahhhhhhhhhh
        - Possible fixes: Literally no idea 
        - I think fixing known bullet bugs may also fix this
    Occasionally, target will change before a bullet hits, and I believe the damage is transferred to the new target. Bullet movement should maybe be an enemy property? Also solves bullet freezing
      - Possible fixes: move to enemies
      - With the new system of only calling findtarget when the tower is done shooting, this scenario crashes the game
    When placing a new tower, it shoots once and then stops
      - Possible fixes: Maybe somewhere, its only calling Tower[0] still --is this fixed? not happening anymore


    */

   //Passes a Tower and an enemy target, shows bullet animation and decreases health of enemy, on a timer. should bullet be a property of the tower?

enum gameState{Menu, Game, Exit};
void MenuLoop(sf::RenderWindow& win, gameState&  state);
void gameLoop(sf::RenderWindow& window, gameState& state);
   bool towershoot(nEnemy& enemy, nTower& tower);  //function for tower shooting enemy
   void addEnemy(std::vector<nEnemy>& Enemy);
//MenuLoop //what is this


int main(){ 
  
 std::cout << getexepath() << std::endl;


gameState state = Menu; //start with menu

int winHeight = 600;
int winWidth = 600;
//Menu text setup


bool quit = false;
sf::RenderWindow _window(sf::VideoMode(winWidth, winHeight), "More Lines");
_window.setFramerateLimit(60);                 //keeps framerate at 60

    while(!quit){

      switch (state){
          case Menu: {
            MenuLoop(_window,state);
            break;
          }
          case Game:{
            gameLoop(_window,state);
            break;
          }
          case Exit: {
         
            quit = true;
            break;
          }
        }
      }

      return 0;
}


void MenuLoop(sf::RenderWindow& win,gameState& state){ //handles beginning menu loop and maybe pause screen for now hit enter to move on
  //Menu Setup
  sf::Event event;
  sf::Font font;
 
if (!font.loadFromFile("..//Assets//Sono-Regular.ttf"))
    {
      std::cout << "Font did not load"<< std::endl;
    }
    else{
      std::cout << "Menu font loaded"<< std::endl;
    }
  sf::Text menuText;
  menuText.setFont(font);
  menuText.setString("Press Enter to start");
  menuText.setPosition(win.getSize().x/4,win.getSize().y/2);

  //Menu Loop
  while (state == Menu){


    while (win.pollEvent(event)) {
        if (event.type == sf::Event::Closed){
            win.close();
            state = Exit;
          }
    }
    //sf::RectangleShape box; Not sure what this box was for, but we were calling it every single loop update so thatts gotta be bad
   

    win.clear();
    win.draw(menuText);
    win.display();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
      state = Game;
    }

  }
}


 //handles the game loop, now all objects are created locally in game loop method
void gameLoop(sf::RenderWindow& window,gameState& state){  
 sf::Font font;
 
if (!font.loadFromFile("..//Assets//Sono-Regular.ttf"))
    {
      std::cout << "Font did not load"<< std::endl;
    }
    else{
      std::cout << "Menu font loaded"<< std::endl;
    }

  int xPosT(300),yPosT(300-100); //starting tower position
    std::vector<nTower> Tower; //vector of type nTower (from tower.h)
  //nTower Tower(xPosT, yPosT); //creating vector tower
  Tower.push_back(nTower(xPosT, yPosT,font)); //add one tower to the vector, not sure how to get font to work without passing it




  //sf::RectangleShape Enemy;                   //Enemy Setup
  int xPosE(0),yPosE(300);   //enemy initial position
  std::vector<nEnemy> Enemy;
  Enemy.push_back(nEnemy(xPosE, yPosE+10)); //add one enemy to the vector



  //temporary stuff
  sf::Vector2i mousePos;
  bool mouseDownL = false; //Just using to stop spawning so many enemies
  bool mouseDownR = false;
 int target = -1; //initalize target
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

      //if (time1.asSeconds() >= .01){  //timer I dont know if we still need this



        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){ //Enemy spawning -should move to addenemy function
          if (!mouseDownL){ //don't spam enemies
            mousePos = sf::Mouse::getPosition(window);
            //std::cout << mousePos.x << "   " <<mousePos.y << std::endl;
            Enemy.push_back(nEnemy(mousePos.x,mousePos.y)); //add one enemy to the vector
            std::cout << Enemy.size() << std::endl;
            mouseDownL = true;
          }
        }
        else{mouseDownL = false;} //Ok its ok to spawn now

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){ //Add towers - probably should make function
          if (!mouseDownR){
            mousePos = sf::Mouse::getPosition(window);

            //std::cout << mousePos.x << "   " <<mousePos.y << std::endl;
            Tower.push_back(nTower(mousePos.x,mousePos.y,font));
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
          if(!Tower[i].getShooting()){ //only find a new target if the bullet isnt moving
            Tower[i].findTarget(Enemy); //Figure out which one you should shoot
          }
            target = Tower[i].getTargetIndex();
            Tower[i].SetTargetText(target);
        //  }
          //std::cout << "Made it" << std::endl;
          if(target>=0){
            bool death = towershoot(Enemy[target],Tower[i]); //Shoot it, i think returns true if it kills enemy?
            if(death){
              std::cout << "Killed:" << std::endl;
              std::cout << target << std::endl;
              Enemy.erase(Enemy.begin()+target);    //need to find out if this calls deconstructor for shape? We want to delete properly
              for (int j=0; j<Tower.size(); j++){   /*do we know what this does?     i think it decreases the traget by one if the target is destroyed, not sure this is necesary*/
                if (Tower[j].getTargetIndex() > target){
                  Tower[j].setTargetIndex(target-1);
                }
              }

              std::cout << Enemy.size() << std::endl; // prints the size of the enemy vector after an enemy dies
            }
          }
        }

          //End of every-frame logic

          window.clear();
        for (int i =0; i< Enemy.size(); i++ ){ //draw alive enemies and health bars

          if(Enemy[i].getAlive()){
            window.draw(Enemy[i].getShape());
            window.draw(Enemy[i].getHealthBarShape());

          }
        }
        for (int i=0; i<Tower.size(); i++){ //draw all towers and bullets
          window.draw(Tower[i].getRangeShape());
          window.draw(Tower[i].getShape());
          window.draw(Tower[i].getBulletShape());
          window.draw(Tower[i].getTargetText());
        }

          window.display();

          clock.restart();
      //}
  }
  std::cout << "exiting Game loop";
  Tower.clear();
  Enemy.clear();
}


void addEnemy(std::vector<nEnemy>& Enemy){ /*not currently used*/

}

bool towershoot(nEnemy& enemy, nTower& tower){   //Eventually this will probably loop through every tower and each will pick a target, or now every tower calls it in main loop when it has a target
//placeholder blink animation
  if (tower.getReloadTime()<=0){    //tower tries to shoot automatically when reloaded
//sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&    //temporary towershoot trigger
//Tower.setFillColor(sf::Color(176,213,217));
//Enemy.setFillColor(sf::Color(255,127,127));
//BUG:: currently only shoots if enemy is below tower? -haavent seen this
    if(!tower.getShooting()){    //bullet is not currently moving
      sf::Vector2f targetLocation = enemy.getPosition(); //for now, just where the enemy is

      sf::Vector2f direction = targetLocation - tower.getPosition();
      float dist = sqrt(pow(direction.x,2) + pow(direction.y,2)); // gets distnace between tower and target --we have a function for this?
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



if (tower.getShooting()){ //bullet is currently moving, continue to move bullet - right now it stops if towershoot isnt called (when enemy moves outside of range)
  tower.moveBullet(); //moves bullet by bulletVelocity
  tower.setShootTime(tower.getShootTime()-1); //number of frames the bullet will take to hit the target goes down by one
  if (tower.getShootTime() == 0){ //bullet has hit the enemy
    bool death = false;

   // if (tower.findDistance(enemy) <= tower.getRange()){ //iff bullet hit enemy and enemy is in range, move bullet far away and deal damage. im going to remove range check

      tower.setBulletPosition(sf::Vector2f(1000, 1000));
      tower.setShooting(false);
      death = enemy.takeDamage(tower.getDamage());
   // }

    tower.setTargetIndex(-1);
    return death;
  }
}
return false;

}
