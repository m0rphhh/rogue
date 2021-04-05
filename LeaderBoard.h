#include <sstream>
#include <fstream>
#include <sstream>
/*#include "json-develop/include/nlohmann/json.hpp"*/

void LeaderBoard(RenderWindow & window, int playerScore, std::string &nickName) {
    Font font;//шрифт
    font.loadFromFile("C:\\Users\\Tom\\Desktop\\opengl\\arial.ttf");//передаем нашему шрифту файл шрифта
    Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст.

    Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
    menuTexture1.loadFromFile("C:\\Users\\Tom\\Desktop\\opengl\\images\\again.png");
    menuTexture2.loadFromFile("C:\\Users\\Tom\\Desktop\\opengl\\images\\222.png");
    menuTexture3.loadFromFile("C:\\Users\\Tom\\Desktop\\opengl\\images\\333.png");
    Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3);
    bool isMenu = 1;
    int menuNum = 0;
    menu1.setPosition(20, 100);
    menu2.setPosition(20, 160);
    menu3.setPosition(20, 220);

    //////////////////////////////МЕНЮ///////////////////
    while (isMenu)
    {
        menu1.setColor(Color::White);
        menu2.setColor(Color::White);
        menu3.setColor(Color::White);
        menuNum = 0;
        window.clear(Color(129, 181, 221));

        if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
        if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
        if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню; кнопка должна будет перезапустить игру
            if (menuNum == 2)  {  } //здесь можно будет выбрать миссию
            if (menuNum == 3)  { window.close(); isMenu = false; }
        }

        Event Event;
        while (window.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
                window.close();
        }

        std::ostringstream playerScoreString;
        playerScoreString << playerScore;		//занесли в переменную число очков, то есть формируем строку
        text.setString("Points:" + playerScoreString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str()
        text.setPosition(view.getCenter().x - 165, view.getCenter().y - 200);//задаем позицию текста, отступая от центра камеры
        window.draw(text);//рисую этот текст

        std::ostringstream playersNickName;
        playersNickName << nickName;		//занесли в переменную число очков, то есть формируем строку
        text.setString("NickName:" + playersNickName.str());//задаем строку тексту и вызываем сформированную выше строку методом .str()
        text.setPosition(view.getCenter().x - 165, view.getCenter().y - 150);//задаем позицию текста, отступая от центра камеры
        window.draw(text);//рисую этот текст

        window.draw(menu1);
        window.draw(menu2);
        window.draw(menu3);

        window.display();
    }
    ////////////////////////////////////////////////////
}