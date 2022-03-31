#include <SFML/Graphics.hpp>
#include <iostream>
/* To-Do list
    Get render window                       DONE
    Clock cycle                             DONE
    Enemy move across screen                DONE
    Make Tower                              DONE
    Make Enemy shoot tower
        Both Blink
        Bullet animation (snall circle)
            Shoot at original spot
            track future position
    Enemy health
    Add another Path
    Add tower placement
    Tower menu
    multiple towers at once
    **CLASSIFY towers and enemies 
    more than one enemy
    Enemy death
    Implement text files for levels
        Routes, turns, number of 
        enemies and type
    Currency to purchase towers
    Tower select menu charges curency
    Different enemie and tower types
    Upgrades

    */
int main(){
  
int winHeight = 600;
int winWidth = 600; 
sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "More Lines"); 

sf::CircleShape Tower;                      //Tower Setup
int xPosT(winWidth/2),yPosT(winHeight/2-100);  
Tower.setFillColor(sf::Color::Blue);
Tower.setRadius(20);
Tower.setPosition(xPosT,yPosT);             //position variables for tower

sf::RectangleShape Enemy;                   //Enemy Setup
int xPosE(0),yPosE(winHeight/2);  
Enemy.setFillColor(sf::Color::Red);
Enemy.setSize(sf::Vector2f(20,20));
Enemy.setPosition(xPosE,yPosE);             //position variables for enemy


    sf::Clock clock;                        //Clock object for frames

while (window.isOpen())
{
        sf::Time time1 = clock.getElapsedTime();  //time for measuring elapsed times
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
     
    if (time1.asSeconds() > .05){  //condition to set fps
    
        xPosE +=4;
        Enemy.setPosition(sf::Vector2f(xPosE,yPosE));
        window.clear();
        window.draw(Enemy);
        window.draw(Tower);

        window.display();

        clock.restart();
    }
}
      return 0;
}
