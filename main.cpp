#include<SFML/Graphics.hpp>
#include<cmath>
#include"player.h"
#include"board.h"

#define deg 0.01745329252           //One degree in radians
#define rayNumber 60    //How many rays will be casted

void render2D(sf::RenderWindow& window, Player& player)
{
    window.clear();
    drawMap(window);
    for(int i=0;i<rayNumber;i++)
        player.castRay(window,player.getAngle()+(rayNumber*0.5-i)*deg);
    
    player.draw(window);
    window.display();
}

void render3D(sf::RenderWindow& window, Player& player)
{
    float wallWidth = window.getSize().x/rayNumber, wallHeight, distance;
    window.clear();
    
    for (int i = 0; i < rayNumber; i++)
    {
        distance = sqrt(player.castRay(window,player.getAngle()+(rayNumber*0.5-i)*deg));
        distance*=cos((rayNumber*0.5-i)*deg);
        wallHeight = window.getSize().y/distance*wallSize;

        sf::RectangleShape wall;
        wall.setFillColor(player.getColor());
        wall.setPosition(wallWidth*i,(window.getSize().y-wallHeight)*0.5);
        wall.setSize(sf::Vector2f(wallWidth,wallHeight));
        window.draw(wall);
    }
    window.display();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(wallSize*boardSize,wallSize*boardSize), "Raycaster");
    window.setFramerateLimit(60);

    Player player(wallSize*1.5,wallSize*1.5);
    #define angle player.getAngle()

    while (window.isOpen())
    {
        sf::Event event;
        if (window.pollEvent(event))
            if(event.type==sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
            if(!getMap((int)(player.getX()+cos(angle)*5)/wallSize,(int)(player.getY()+sin(angle)*5)/wallSize))
                player.move(cos(angle)*5,sin(angle)*5);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.rotate(3*deg);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
            if(!getMap((int)(player.getX()-cos(angle)*5)/wallSize,(int)(player.getY()-sin(angle)*5)/wallSize))
                player.move(-cos(angle)*5,-sin(angle)*5);;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.rotate(-3*deg);

        render3D(window,player);
    }
}