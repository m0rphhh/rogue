#include "TextBox.h"

void menu(RenderWindow & window, std::string &nickName) {
    Font font;
    font.loadFromFile("C:\\Users\\Tom\\Desktop\\opengl\\arial.ttf");
    TextBox textbox(15, sf::Color::White, true);
    textbox.setFont(font);
    textbox.setPosition({200, 200});
    Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
    menuTexture1.loadFromFile("C:\\Users\\Tom\\Desktop\\opengl\\images\\111.png");
    menuTexture2.loadFromFile("C:\\Users\\Tom\\Desktop\\opengl\\images\\222.png");
    menuTexture3.loadFromFile("C:\\Users\\Tom\\Desktop\\opengl\\images\\333.png");
    Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
    bool isMenu = 1;
    int menuNum = 0;
    menu1.setPosition(100, 30);
    menu2.setPosition(100, 90);
    menu3.setPosition(100, 150);
    menuBg.setPosition(345, 0);

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


        Event textBoxEvent;
        while (window.pollEvent(textBoxEvent))
        {
            if (textBoxEvent.type == sf::Event::Closed)
                window.close();
            if (textBoxEvent.type == sf::Event::TextEntered) {textbox.typedOn(textBoxEvent);}
        }

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1) {
                nickName = textbox.getText();
                isMenu = false;
            }//если нажали первую кнопку, то выходим из меню
            /*if (menuNum == 2) { while (!Keyboard::isKeyPressed(Keyboard::Escape)){window.draw(about); window.display();} }*/
            if (menuNum == 3)  { window.close(); isMenu = false; }

        }


        window.draw(menu1);
        window.draw(menu2);
        window.draw(menu3);
        textbox.drawTo(window);

        window.display();
    }
    ////////////////////////////////////////////////////
}