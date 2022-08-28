#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;

struct Flyer
{
    float x, y, speed, angle;

    Flyer() {speed = 2; angle = 0;}

    void move ()
    {
        x += sin(angle) * speed;
        y -= cos(angle) * speed;
    }
};

int main() 
{
    RenderWindow app(VideoMode(1920, 1080, 32), "Sprite Flight");
    app.setFramerateLimit(60);

    Texture back, block;
    back.loadFromFile("images/background.png");
    block.loadFromFile("images/flyer.png");

    Sprite sBack(back), sBlock(block);
    sBlock.setPosition(0, 0);
    sBlock.setOrigin(22, 22);

    Flyer redBlock;
    redBlock.x = 960;
    redBlock.y = 540;
    redBlock.speed = 7;

    float x = 960, y = 540;
    float speed = 0, angle = 0;
    float maxSpeed = 15.0;
    float acc = 0.2, dec = 0.3;
    float turnSpeed = 0.08;

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
    if (Up && speed < maxSpeed)
    {
        if (speed < 0)
        { speed += dec; }
        else
        { speed += acc; }
    }
    if (Down && speed > -maxSpeed)
    {
        if (speed > 0)
        { speed -= dec; }
        else
        { speed -= acc; }
    }
    if (!Up && !Down)
    {
        if (speed - dec > 0)
        { speed -= dec; }
        else if (speed + dec < 0)
        { speed += dec; }
        else
        { speed = 0; }
    }
    if (Right && speed != 0)
    { angle += turnSpeed * speed / maxSpeed; }
    if (Left && speed != 0)
    { angle -= turnSpeed * speed / maxSpeed; }

    if (redBlock.x > 960)
    { offsetX = redBlock.x - 960; }
    if (redBlock.y > 540)
    { offsetY = redBlock.y - 540; }
    if (redBlock.x > 1040 )
    { offsetX = 58; }
    if (redBlock.y > 1460 )
    { offsetY = 898; }

    // Edge Collision //
    // if (x <= 20) { x = 22; }
    // if (x >= 1980) { x = 1956; }
    // if (y <= 20) { y = 22; }
    // if (y >= 1980) { y = 1956; }

    redBlock.speed = speed;
    redBlock.angle = angle;

    // Draw Window //
    app.clear(Color::Black);
    sBack.setPosition(-offsetX, -offsetY);
    app.draw(sBack);

    sBlock.setPosition(redBlock.x - offsetX, redBlock.y - offsetY);
    sBlock.setRotation(redBlock.angle * 180 / 3.141592);
    app.draw(sBlock);

    std::cout << x << " by " << y << std::endl;

    app.display();
    }

    return 0;
}