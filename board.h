#pragma once
#include<SFML/Graphics.hpp>

#define boardSize 10
#define wallSize 80

int map[boardSize][boardSize]=
{
    1,1,1,1,1,1,1,1,1,1,
    1,0,0,1,0,0,0,0,0,1,
    1,0,1,1,1,0,0,1,0,1,
    1,0,0,1,0,0,1,1,0,1,
    1,0,0,0,0,1,0,0,0,1,
    1,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,1,1,
    1,0,0,0,1,1,1,0,0,1,
    1,0,0,0,1,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,
};

int getMap(int x, int y) {
    if(x<0 || x>boardSize || y<0 || y>boardSize) return 1;
    return map[y][x];
}

void drawMap(sf::RenderWindow& window)
{
    sf::RectangleShape wall(sf::Vector2f(wallSize-2,wallSize-2));
    wall.setFillColor(sf::Color::White);
    for (int i = 0; i < boardSize; i++)
        for (int j = 0; j < boardSize; j++)
            if(map[i][j])
            {
                wall.setPosition(j*wallSize+1,i*wallSize+1);
                window.draw(wall);
            }
}