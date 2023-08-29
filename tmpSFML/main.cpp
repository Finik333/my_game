#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(600, 400), "MY GAME");


    CircleShape shape(100.f, 4);
    shape.setFillColor(Color::Magenta);

    Texture t;
    t.loadFromFile("3.png");
    float f = 3;
        Sprite s;
        s.setTexture(t);
        s.setTextureRect(IntRect(740,0,800,85));
        s.setPosition(50, 100);

        Clock clock;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            s.move(-0.0003*time, 0);
            f += 0.00001*time;
            if (f > 6)f -= 4;

            s.setTextureRect(IntRect(80 * int(f), 0, 85, 85));
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            s.move(0.0003*time, 0);
            f += 0.00001*time;
            if (f > 7)f -= 4;
           
            s.setTextureRect(IntRect(80*int(f), 0, -85, 85));

        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            s.move(0, -0.03);
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            s.move(0, 0.03);
        }
        window.clear(Color::Blue);
        window.draw(s);
        window.display();
    }
    return 0;
}