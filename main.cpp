#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;

class Flyer
{
public:
    Flyer(float x, float y, float speed, float angle) {} //{x = 0; y = 0; speed = 0; angle = 0;}
    
    float getX() {return x;}

    void setX(float playerX) {x = playerX;}

    float getY() {return y;}

    void setY(float playerY) {y = playerY;}

    float getSpeed() {return speed;}

    void setSpeed(float playerSpeed) {speed = playerSpeed;}

    float getAngle() {return angle;}

    void setAngle(float playerAngle) {angle = playerAngle;}

    void move ()
    {
        setX(sin(getAngle() * getSpeed()));
        setY(getY() - cos(getAngle() * getSpeed()));
    }

private:
    float x, y, speed, angle;
};

int main() 
{
    RenderWindow app(VideoMode(1920, 1080, 32), "Sprite Flight");
    app.setFramerateLimit(60);

    Texture back, block;
    back.loadFromFile("images/background.png");
    block.loadFromFile("images/flyer.png");

    Sprite sBack(back), sBlock(block);
    sBack.setPosition(0, 0);
    sBlock.setOrigin(22, 22);

    Flyer redBlock(960, 540, 0, 0);
    // redBlock.setX(960);
    // redBlock.setY(540);

    const float maxSpeed = 15.0;
    const float acc = 0.2;
    const float dec = 0.3;
    const float turnSpeed = 0.08;
    int offsetX = 0;
    int offsetY = 0;
    float radius = 22;

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                app.close();
            }
        }
    
    bool Up = 0, Right = 0, Down = 0, Left = 0;
    if (Keyboard::isKeyPressed(Keyboard::Up)) Up = 1;
    if (Keyboard::isKeyPressed(Keyboard::Right)) Right = 1;
    if (Keyboard::isKeyPressed(Keyboard::Down)) Down = 1;
    if (Keyboard::isKeyPressed(Keyboard::Left)) Left = 1;

    // Sprite Movement //
    if (Up && redBlock.getSpeed() < maxSpeed)
    {
        if (redBlock.getSpeed() < 0)
        { redBlock.setSpeed(redBlock.getSpeed() + dec); }
        else
        { redBlock.setSpeed(redBlock.getSpeed() + acc); }
    }
    if (Down && redBlock.getSpeed() > -maxSpeed)
    {
        if (redBlock.getSpeed() > 0)
        { redBlock.setSpeed(redBlock.getSpeed() - dec); }
        else
        { redBlock.setSpeed(redBlock.getSpeed() - acc); }
    }
    if (!Up && !Down)
    {
        if (redBlock.getSpeed() - dec > 0)
        { redBlock.setSpeed(redBlock.getSpeed() - dec); }
        else if (redBlock.getSpeed() + dec < 0)
        { redBlock.setSpeed(redBlock.getSpeed() + dec); }
        else
        { redBlock.setSpeed(0); }
    }
    if (Right && redBlock.getSpeed() != 0)
    { redBlock.setAngle(redBlock.getAngle() + turnSpeed * redBlock.getSpeed() / maxSpeed); }
    if (Left && redBlock.getSpeed() != 0)
    { redBlock.setAngle(redBlock.getAngle() - turnSpeed * redBlock.getSpeed() / maxSpeed); }

    redBlock.setSpeed(redBlock.getSpeed());
    redBlock.setAngle(redBlock.getAngle());
    redBlock.move();

    if (redBlock.getX() > 960)
    { offsetX = redBlock.getX() - 960; }
    if (redBlock.getY() > 540)
    { offsetY = redBlock.getY() - 540; }
    if (redBlock.getX() > 1040 )
    { offsetX = 58; }
    if (redBlock.getY() > 1460 )
    { offsetY = 898; }

    // Edge Collision //
    if (redBlock.getX() <= 20) { redBlock.setX(redBlock.getX() + 22); }
    if (redBlock.getX() >= 1980) { redBlock.setX(redBlock.getX() + 1956); }
    if (redBlock.getY() <= 20) { redBlock.setY(redBlock.getY() + 22); }
    if (redBlock.getY() >= 1980) { redBlock.setY(redBlock.getY() + 1956); }

    // Draw Window //
    app.clear(Color::Black);
    sBack.setPosition(-offsetX, -offsetY);
    app.draw(sBack);

    sBlock.setPosition(redBlock.getX() - offsetX, redBlock.getY() - offsetY);
    sBlock.setRotation(redBlock.getAngle() * 180 / 3.141592);
    app.draw(sBlock);

    std::cout << redBlock.getX() << " by " << redBlock.getY() << std::endl;
    std::cout << redBlock.getSpeed() << " at " << redBlock.getAngle() << std::endl;
    app.display();
    }

    return 0;
}