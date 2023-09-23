#include<SFML/Graphics.hpp>
#include<cmath>
#include"board.h"

class Player
{
    float x,y,angle=0;
    sf::Color color=sf::Color::White;

    public:
    Player(float x, float y)
    {
        this->x=x;
        this->y=y;
    }

    float getAngle() { return angle; }
    float getX() {return x; }
    float getY() {return y; }
    sf::Color getColor() {return color; }
    
    void move(float dx, float dy)
    {
        x+=dx;  y+=dy;
    }

    void rotate(float da)
    {
        angle+=da;
        if(angle<0) angle+=M_PI*2;
        else if(angle>2*M_PI) angle-=M_PI*2;
    }

    float castRay(sf::RenderWindow& window, float a) //a - angle, returns distance from player to wall
    {
        if(a>M_PI*2) a-=M_PI*2; //without this condition there might be bugs
        else if(a<0) a+=M_PI*2;
        float rayVerticalX, rayVerticalY, rayHorizontalX, rayHorizontalY, ctg = 1/tan(a), tg = tan(a);
        //Horizontal lines
        if(a==0||a==2*M_PI) { rayHorizontalX=100000; rayHorizontalY = 100000;}
        else if(a>M_PI){
            rayHorizontalY = y - (int)y%wallSize;
            rayHorizontalX = x - ((int)y%wallSize)*ctg;

            while(!getMap((int)rayHorizontalX/wallSize,(int)(rayHorizontalY-1)/wallSize))
            {
                rayHorizontalY-=wallSize;
                rayHorizontalX = x - (y-rayHorizontalY)*ctg;
            }
        }
        else if(a<M_PI){
            rayHorizontalY = y + wallSize-(int)y%wallSize;
            rayHorizontalX = x + (wallSize-(int)y%wallSize)*ctg;

            while(!getMap((int)rayHorizontalX/wallSize,(int)(rayHorizontalY+1)/wallSize))
            {
                rayHorizontalY+=wallSize;
                rayHorizontalX = x + (rayHorizontalY-y)*ctg;
            }
        }

        //Vertical lines
        if(a==M_PI_2||a==M_PI_2*3) { rayVerticalX=100000; rayVerticalY=100000; }

        else if(a>M_PI_2&&a<M_PI_2*3)
        {
            rayVerticalX=x-(int)x%wallSize;
            rayVerticalY=y-((int)x%wallSize)*tg;

            while(!getMap((int)(rayVerticalX-1)/wallSize,(int)rayVerticalY/wallSize))
            {
                rayVerticalX-=wallSize;
                rayVerticalY= y+(rayVerticalX-x)*tg;
            }
            
        }
        else if(a<M_PI_2||a>M_PI_2*3)
        {
            rayVerticalX=x+wallSize-(int)(x)%wallSize;
            rayVerticalY=y+(wallSize-(int)x%wallSize)*tg;

            while(!getMap((int)(rayVerticalX+1)/wallSize,(int)rayVerticalY/wallSize))
            {
                rayVerticalX+=wallSize;
                rayVerticalY= y + (rayVerticalX-x)*tg;
            }            
        }

        //Drawing ray
        #define pythagoras(a, b) (a-x)*(a-x)+(b-y)*(b-y)    //Need to calculate length of ray
        if(pythagoras(rayHorizontalX,rayHorizontalY)<pythagoras(rayVerticalX,rayVerticalY))
        {
            rayVerticalX = rayHorizontalX;
            rayVerticalY = rayHorizontalY;
            color = sf::Color(171,171,171);
        }
        else color = sf::Color::White;
        sf::Vertex ray[2]=
        {
            sf::Vertex(sf::Vector2f(x,y), sf::Color::Green),
            sf::Vertex(sf::Vector2f(rayVerticalX,rayVerticalY), sf::Color::Green),
        };
        window.draw(ray,2,sf::Lines);
        return pythagoras(rayVerticalX,rayVerticalY);
    }

    void draw(sf::RenderWindow& window)
    {
        sf::Vertex v[2]={
            sf::Vertex(sf::Vector2f(x,y), sf::Color::Red),
            sf::Vertex(sf::Vector2f(x+cos(angle)*20,y+sin(angle)*20), sf::Color::Red),
        };
        window.draw(v,2,sf::Lines);
    }
};