#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int ground = 100;
int a;

const int H = 12;
const int W = 40;

String TileMap[H] = {
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                B     B",
    "B                                BBB   B",
    "B                                B    BB",
    "B          BBB                   B     B",
    "B                             BBBBB    B",
    "B                B     BB              B",
    "BBB             BB                    BB",
    "B       B BB    BB         BB   BB     B",
    "B    B    BB  B BB       BBBB   BBBB   B",
    "B    B0000BB0000BB     BBBBBB000BBBBBB B",
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
};

class PLAYER {
public:
    float dx;
    float dy;
    FloatRect rect;
    bool onGround;
    Sprite sprite;
    float f;

    PLAYER(Texture& image) {
        sprite.setTexture(image);
        rect = FloatRect(3*32,9*32,50,74);
        dx = dy = 0.1;
        f = 3;
    }

    void update(float time) {
        rect.left += dx * time;
        Collision(0);
        if (!onGround) dy = dy + 0.0005 * time;

        rect.top += dy * time;
        onGround = false;
        Collision(1);
        f += 0.005 * time;

        if (f > 6) f -= 3;

        if (a == 0) sprite.setTextureRect(IntRect(160, 0, 85, 85));
        if (a == 1) sprite.setTextureRect(IntRect(240, 0, -85, 85));
        if (dx > 0) sprite.setTextureRect(IntRect(80 * int(f), 0, -85, 85));
        if (dx < 0) sprite.setTextureRect(IntRect(80 * int(f), 0, 85, 85));
        sprite.setPosition(rect.left, rect.top);
        dx = 0;
    }

    void Collision(int dir) {
        {
            for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
                for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
                {
                    if (TileMap[i][j] == 'B')
                    {
                        if ((dx > 0) && (dir == 0)) rect.left = j * 32 - rect.width;
                        if ((dx < 0) && (dir == 0)) rect.left = j * 32 + 32;
                        if ((dy > 0) && (dir == 1)) { rect.top = i * 32 - rect.height; dy = 0; onGround = true; }
                        if ((dy < 0) && (dir == 1)) { rect.top = i * 32 + 32; dy = 0; }
                    }
                    if (TileMap[i][j] == '0')
                    {
                        TileMap[i][j] = ' ';
                    }


                }
        }
    };
    };
    int main() {
        RenderWindow window(VideoMode(800, 375), "MY GAME");
        Texture t;
        t.loadFromFile("3.png");

        PLAYER p(t);

        Clock clock;
        RectangleShape rectangle(Vector2f(32, 32));

        while (window.isOpen()) {
            float time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time / 800;
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();
            }

            if (Keyboard::isKeyPressed(Keyboard::A)) {
                p.dx = -0.1;
                a = 0;
            }
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                p.dx = 0.1;
                a = 1;
            }
            if (Keyboard::isKeyPressed(Keyboard::W)) {
                if (p.onGround) { p.dy = -0.30; p.onGround = false; }
            }
            p.update(time);
            window.clear(Color::Blue);

            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                    if (TileMap[i][j] == 'B') {
                        rectangle.setFillColor(Color::Black);
                    }
                    else if (TileMap[i][j] == '0') {
                        rectangle.setFillColor(Color::Red);
                    }
                    else {
                        continue;
                    }

                    rectangle.setPosition(j * 32, i * 32);
                    window.draw(rectangle);
                }
            }

            window.draw(p.sprite);
            window.display();
        }

        return 0;
    }