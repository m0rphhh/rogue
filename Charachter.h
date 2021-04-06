#define CHARACTER_INCLUDED

using namespace sf;

class Character {
private:

public:
    float w, h, dx, dy, speed, x, y = 0;
    int dir, health;
    bool life;
    String File, Name;
    Image image;
    Texture texture;
    Sprite sprite;
    Character(String F, float X, float Y, float W, float H, String name){
        dir = 0; speed = 0; health = 100; dx=0;dy=0;
        life = true;
        File = F;
        Name = name;
        w = W; h = H;
        image.loadFromFile("C:\\Users\\Tom\\Desktop\\opengl\\images\\" + File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X; y = Y;
        sprite.setTextureRect(IntRect(0, 0, w, h));
    }

    FloatRect getRect(){
        return FloatRect(x, y, w, h);
    }

    virtual void update(float time) {};
};