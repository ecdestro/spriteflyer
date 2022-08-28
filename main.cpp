#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

int main() 
{
    int vidWidth = 1280;
    int vidHeight = 720;
    RenderWindow app(VideoMode(vidWidth, vidHeight, 32), "Sprite Flight");
    app.setFramerateLimit(60);

    Texture back, block;
    back.loadFromFile("images/background.png");
    block.loadFromFile("images/flyer.png");

    Sprite sBack(back), sBlock(block);
    sBack.setPosition(0, 0);
    sBlock.setOrigin(22, 22);

    float maxSpeed = 15.0;
    float acc = 0.2;
    float dec = 0.3;
    float turnSpeed = 0.08;
    float redX = vidWidth / 2;
    float redY = vidHeight / 2;
    float redSpeed = 0;
    float redAngle = 0;
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
    if (Up && redSpeed < maxSpeed)
    {
        if (redSpeed < 0)
        { redSpeed += dec; }
        else
        { redSpeed += acc; }
    }
    if (Down && redSpeed > -maxSpeed)
    {
        if (redSpeed > 0)
        { redSpeed -= dec; }
        else
        { redSpeed -= acc; }
    }
    if (!Up && !Down)
    {
        if (redSpeed - dec > 0)
        { redSpeed -= dec; }
        else if (redSpeed + dec < 0)
        { redSpeed += dec; }
        else
        { redSpeed = 0; }
    }
    if (Right && redSpeed != 0)
    { redAngle += turnSpeed * redSpeed / maxSpeed; }
    if (Left && redSpeed != 0)
    { redAngle -= turnSpeed * redSpeed / maxSpeed; }

    redX += sin(redAngle) * redSpeed;
    redY -= cos(redAngle) * redSpeed;    

    if (redX > vidWidth / 2)
    { offsetX = redX - vidWidth / 2; }
    if (redY > vidHeight / 2)
    { offsetY = redY - vidHeight /2; }
    if (redX > (2000 - vidWidth / 2) )
    { offsetX = 2000 - vidWidth - radius; }
    if (redY > (2000 - vidHeight / 2) )
    { offsetY = 2000 - vidHeight - radius; }

    // Edge Collision //
    if (redX <= 20) { redX = 22; }
    if (redX >= 1980) { redX = 1978; }
    if (redY <= 20) { redY = 22; }
    if (redY >= 1980) { redY = 1978; }

    // Draw Window //
    app.clear(Color::Black);
    sBack.setPosition(-offsetX, -offsetY);
    app.draw(sBack);

    sBlock.setPosition(redX - offsetX, redY - offsetY);
    sBlock.setRotation(redAngle * 180 / 3.141592);
    app.draw(sBlock);

    app.display();
    }

    return 0;
}