#ifndef CHARACTER_INCLUDED
#include "Charachter.h"
#endif

#include <list>

class Bullet :public Character{
public:
    int direction;

    Bullet(String F, float X, float Y, int W, int H, int dir, const String& name) :Character(F, X, Y, W, H, name){
        x = X;
        y = Y;
        direction = dir;
        speed = 0.5;
        w = h = 16;
        life = true;
    }


    void update(float time)
    {
        switch (direction)
        {
            case 0: dx = speed; dy = 0;   break;//интовое значение right
            case 1: dx = -speed; dy = 0;   break;//интовое значение  left
            case 2: dx = 0; dy = speed;   break;//интовое значение  down
            case 3: dx = 0; dy = -speed;   break;//интовое значение  up
        }

        x += dx*time;//само движение пули по х
        y += dy*time;//по у

        if (x <= 0) x = 1;
        if (y <= 0) y = 1;
        if (x >= WIDTH_MAP * 32) life = false;
        if (y >= HEIGHT_MAP * 32) life = false;


        sprite.setPosition(x+w/2, y+h/2);//задается позиция пуле
    }
};