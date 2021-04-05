#include <SFML/Graphics.hpp>
#include "menu.h"
#include "Player.h"
#include "EasyEnemy.h"
#include "HardEnemy.h"
#include "Bullet.h"
#include "LeaderBoard.h"
#include <vector>
#include <list>

const int numberOfEasyEnemies = 4;
const int numberOfHardEnemies = 3;
/*const int fogRange = 5;*/
const int bulletDamage = 20;
/*bool fogged = false;*/
using namespace sf;
/*float distance = 0;//это расстояние от объекта до тыка курсора*/
std::string nickName;


bool launchGameProcess()
{
    int easyEnemiesPos[numberOfEasyEnemies][2] = {
            { 250, 250 },
            { 64, 704 },
            { 704, 50 },
            { 160, 256 },
    };

    int hardEnemiesPos[numberOfHardEnemies][2] = {
            { 64, 128 },
            { 672, 224 },
            { 96, 448 },
    };

    RenderWindow window(sf::VideoMode(1376, 768), "rogue!");
    menu(window, nickName);
    Image map_image;
    map_image.loadFromFile("C:\\Users\\Tom\\Desktop\\opengl\\images\\map.png");
    Texture map;
    map.loadFromImage(map_image);
    Sprite s_map;
    s_map.setTexture(map);
    Player p("hero.png", 32, 32, 32.0, 32.0, "Player", nickName);

    Font font;//шрифт
    font.loadFromFile("C:\\Users\\Tom\\Desktop\\opengl\\arial.ttf");//передаем нашему шрифту файл шрифта
    Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    std::list<Character*>  characters;//создаю список, сюда буду кидать объекты.например врагов.
    std::list<Character*>::iterator it;//итератор чтобы проходить по эл-там списка
    std::list<Character*>::iterator it2;

    for (int i = 0; i < numberOfEasyEnemies; i++)//проходимся по элементам этого вектора(а именно по врагам)
        characters.push_back(new EasyEnemy("easyenemy.png", easyEnemiesPos[i][0], easyEnemiesPos[i][1], 32.0, 32.0, "eEnemy"));//и закидываем в список всех наших врагов с карты

    for (int i = 0; i < numberOfHardEnemies; i++)//проходимся по элементам этого вектора(а именно по врагам)
        characters.push_back(new HardEnemy("hardenemy.png", hardEnemiesPos[i][0], hardEnemiesPos[i][1], 64.0, 64.0, "hEnemy"));

    Clock clock;
    Clock gameTimeClock;
    Clock lastHit;
    int createObjectForMapTimer = 0;
    int gameTime = 0;

    while (window.isOpen())
    {
        if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }//если эскейп, то выходим из игры
        float time = clock.getElapsedTime().asMicroseconds();

        if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();
        clock.restart();
        time = time / 800;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (p.isShoot) { p.isShoot = false; characters.push_back(new Bullet("bullet.png", p.x, p.y, 16, 16, p.dir, "bullet")); }
        }



        createObjectForMapTimer += time;//наращиваем таймер
        p.control(time);
        p.update(time);
        if(p.isPrincess) {p.playerScore += 100; LeaderBoard(window, p.playerScore, nickName); p.life = false; }

        for (it = characters.begin(); it != characters.end();)//говорим что проходимся от начала до конца
        {
            Character *b = *it;
            b->update(time);//вызываем ф-цию update для всех объектов (по сути для тех, кто жив)
            if ((b->life == false)&&(b->Name == "eEnemy")){ it = characters.erase(it); delete b; p.playerScore += 20;}// если этот объект мертв, то удаляем его
            if ((b->life == false)&&(b->Name == "hEnemy")){ it = characters.erase(it); delete b; p.playerScore += 50;}
            if ((b->life == false)&&(b->Name == "bullet")) { it = characters.erase(it); delete b;}
            else it++;//и идем курсором (итератором) к след объекту. так делаем со всеми объектами списка
        }

        float LastHit = lastHit.getElapsedTime().asSeconds();

        for (it = characters.begin(); it != characters.end(); it++)//проходимся по эл-там списка
        {
            if ((*it)->getRect().intersects(p.getRect()))//если прямоугольник спрайта объекта пересекается с игроком
            {
                if(LastHit >= 3) {
                    if((*it)->Name == "eEnemy" ) { //разный урон (зависит от противника)
                        p.health -= 10;
                    }else if((*it)->Name == "hEnemy" ) {
                        p.health -= 20;
                    }else {
                        (*it)->life = false;
                    }
                    lastHit.restart();
                }
            }


            for (it2 = characters.begin(); it2 != characters.end(); it2++){
                if ((*it)->getRect() != (*it2)->getRect())//разные прямоугольники
                    if (((*it)->getRect().intersects((*it2)->getRect())))//если столкнулись два объекта и они враги
                    {
                        if((*it)->Name == "bullet") {
                            (*it2)->health -= bulletDamage;
                            (*it)->life = false;
                        }
                    }
            }
        }

        window.setView(view);
        window.clear();


        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                /*if (!fogged) {
                    s_map.setTextureRect(IntRect(192, 0, 32, 32));
                    if (TileMap[i][j] == 'c') {
                        fogged = true;
                    }
                }*/

               /* int xCrossing = (int) (p.getplayercoordinateX() / 32);
                int yCrossing = (int) (p.getplayercoordinateY() / 32);*/


                if (TileMap[i][j] == 'f') s_map.setTextureRect(IntRect(192, 0, 32, 32));
                if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
                if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
                if ((TileMap[i][j] == '0') || ((TileMap[i][j] == 'c'))) s_map.setTextureRect(IntRect(64, 0, 32, 32));
                if ((TileMap[i][j] == 'd')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
                if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));
                if ((TileMap[i][j] == 'p')) s_map.setTextureRect(IntRect(160, 0, 32, 32));


                p.update(time);

                s_map.setPosition(j * 32, i * 32);
                window.draw(s_map);
            }

        std::ostringstream HPString;
        HPString << p.health;		//занесли в переменную число очков, то есть формируем строку
        text.setString("HP:" + HPString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str()
        text.setPosition(view.getCenter().x - 165, view.getCenter().y - 200);//задаем позицию текста, отступая от центра камеры
        window.draw(text);//рисую этот текст

        window.draw(p.sprite);
        for (it = characters.begin(); it != characters.end(); it++){
            window.draw((*it)->sprite); //рисуем врагов и пули
        }

        window.display();
    }

    return false;
}

void gameRunning(){//ф-ция перезагружает игру , если это необходимо (почему-то не работает)
    if (!launchGameProcess()) { gameRunning();}
}
