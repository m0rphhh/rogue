#ifndef CHARACTER_INCLUDED
#include "Charachter.h"
#endif

using namespace sf;

class HardEnemy :public Character {
public:
    HardEnemy(String F, float X, float Y, float W, float H, String name):Character(F,X,Y,W,H, name){
        dx = 0.1;
        health = 200;
    }

    float getplayercoordinateX(){
        return x;
    }
    float getplayercoordinateY(){
        return y;
    }

    void checkCollisionWithMap(float Dx, float Dy)//ф ция проверки столкновений с картой
    {
        for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
            for (int j = x / 32; j<(x + w) / 32; j++)
            {
                if (TileMap[i][j] == '0')//если элемент наш тайлик земли, то
                {
                    /*if (Dy>0){ y = i * 32 - h; }//по Y вниз=>идем в пол(стоим на месте) или падаем. В этот момент надо вытолкнуть персонажа и поставить его на землю, при этом говорим что мы на земле тем самым снова можем прыгать
                    if (Dy<0){ y = i * 32 + 32; }//столкновение с верхними краями карты(может и не пригодиться)*/
                    if (Dx>0){ x = j * 32 - w; dx = -0.1; sprite.scale(-1, 1); }//с правым краем карты
                    if (Dx<0){ x = j * 32 + 32; dx = 0.1; sprite.scale(-1, 1); }// с левым краем карты
                }
            }
    }

    void update(float time)
    {
        if (health <= 0){ life = false; }
        checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
        x += dx*time;
        sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
    }
};