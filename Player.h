#ifndef CHARACTER_INCLUDED
#include "Charachter.h"
#endif

using namespace sf;

class Player :public Character {
public:
    int playerScore;//эта переменная может быть только у игрока
    bool isPrincess, isShoot;
    std::string nickName;

    Player(String F, float X, float Y, float W, float H, String name, String nickName):Character(F, X, Y, W, H, name){
        playerScore = 0;
        isPrincess = 0;
        nickName = nickName;
    }

    float getplayercoordinateX(){
        return x;
    }
    float getplayercoordinateY(){
        return y;
    }

    void interactionWithMap()
    {

        for (int i = y / 32; i < (y + h) / 32; i++)
            for (int j = x / 32; j<(x + w) / 32; j++)
            {
                if (TileMap[i][j] == '0')
                {
                    if (dy>0)
                    {
                        y = i * 32 - h;
                    }
                    if (dy<0)
                    {
                        y = i * 32 + 32;
                    }
                    if (dx>0)
                    {
                        x = j * 32 - w;
                    }
                    if (dx < 0)
                    {
                        x = j * 32 + 32;
                    }
                }

                if (TileMap[i][j] == 's') {
                    playerScore += 20;
                    TileMap[i][j] = ' ';
                }

                if (TileMap[i][j] == 'd') {
                    health -= 40;
                    TileMap[i][j] = ' ';
                }

                if (TileMap[i][j] == 'h') {
                    health += 20;
                    TileMap[i][j] = ' ';
                }

                if (TileMap[i][j] == 'p') {
                    TileMap[i][j] = ' ';
                    isPrincess = 1;
                }

            }
    }

    void update(float time)
    {
        switch (dir)
        {
            case 0: dx = speed; dy = 0; break;
            case 1: dx = -speed; dy = 0; break;
            case 2: dx = 0; dy = speed; break;
            case 3: dx = 0; dy = -speed; break;
        }

        x += dx*time;
        y += dy*time;
        speed = 0;
        sprite.setPosition(x, y);
        interactionWithMap();
        if (health <= 0){ life = false; }
    }

    void control(float time) {
        if (life) {
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                dir = 1; speed = 0.1;
                sprite.setTextureRect(IntRect(36, 1, 32, 32));
            }

            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                dir = 0; speed = 0.1;
                sprite.setTextureRect(IntRect(1, 1, 32, 32));
            }

            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                dir = 3; speed = 0.1;
                sprite.setTextureRect(IntRect(1, 36, 32, 32));
            }

            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                dir = 2; speed = 0.1;
                sprite.setTextureRect(IntRect(36, 36, 32, 32));
            }

            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                isShoot = true;
            }
            setPlayerCoordinateForView(getplayercoordinateX(), getplayercoordinateY());
        }
    }
};