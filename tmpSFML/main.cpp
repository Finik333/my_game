#include <SFML/Graphics.hpp>

using namespace sf;

int ground = 150;

class PLAYER {
public:
    float dx, dy;
    FloatRect rect;
    bool onGround;
    Sprite sprite;
    float f;
    

     PLAYER (Texture &image) {
        sprite.setTexture(image);
        rect = FloatRect(0, 0, 40, 50);
        dx = dy - 0;
        f = 0;
    }
    void update(float time) {

        rect.left += dx * time;

        if (!onGround) dy = dy + 0.0005 * time;

        rect.top += dy * time;

        onGround = false;

        if (rect.top > ground) { rect.top = ground; dy = 0; onGround = true;}
        f += 0.005 * time;

        if (f > 6)f -= 4;

       if(dx>0) sprite.setTextureRect(IntRect(80 * int(f), 0, 85, 85));
       if(dx<0) sprite.setTextureRect(IntRect(80 * int(f), 0, -85, 85));
        sprite.setPosition(rect.left, rect.top);
        dx = 0;
    }
};

int main()
{
   
    RenderWindow window(VideoMode(600, 400), "MY GAME");
    Texture t;
    t.loadFromFile("3.png");
    float f = 0;

    PLAYER p(t);

        Clock clock;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            p.dx = -0.1;
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            p.dx = 0.1;
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            if (p.onGround) { p.dy = -0.25; p.onGround = false; }
        }
        p.update(time);

        window.clear(Color::Blue);
        window.draw(p.sprite);
        window.display();
    }
    return 0;
}