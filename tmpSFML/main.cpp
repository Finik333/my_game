#include <SFML/Graphics.hpp>

using namespace sf;

int ground = 300;
int a;

const int H = 12;
const int W = 40;

String TileMap[H] = {
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                B     B",
    "B                                B     B",
    "B                                B     B",
    "B                                B     B",
    "B         0000                BBBB     B",
    "B                                B     B",
    "BBB                              B     B",
    "B              BB                BB    B",
    "B              BB                      B",
    "B    B         BB         BB           B",
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
    
     PLAYER (Texture &image) {
        sprite.setTexture(image);
        rect = FloatRect(0, 0, 40, 50);
        dx = dy = 0.1;
        f = 3;
    }
    void update(float time) {

        rect.left += dx * time;

        if (!onGround) dy = dy + 0.0005 * time;

        rect.top += dy * time;

        onGround = false;

        if (rect.top > ground) { rect.top = ground; dy = 0; onGround = true;}
        f += 0.005 * time;

        if (f > 6)f -= 3;

       if (a == 0) sprite.setTextureRect(IntRect(160, 0, 85, 85));
       if (a == 1) sprite.setTextureRect(IntRect(240, 0, -85, 85));
       if(dx>0) sprite.setTextureRect(IntRect(80 * int(f), 0, -85, 85));
       if(dx<0) sprite.setTextureRect(IntRect(80 * int(f), 0, 85, 85));
        sprite.setPosition(rect.left, rect.top);
        dx = 0;
    }
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
                if (p.onGround) { p.dy = -0.25; p.onGround = false; }
            }
            p.update(time);
            window.clear(Color::White);

            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                    if (TileMap[i][j] == 'B') {
                        rectangle.setFillColor(Color::Black);
                    }
                    else if (TileMap[i][j] == '0') {
                        rectangle.setFillColor(Color::Green);
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