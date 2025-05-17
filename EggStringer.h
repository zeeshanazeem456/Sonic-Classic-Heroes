#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "Animation.h"
#include "Enemies.h"

using namespace sf;
using namespace std;

class EggStinger: public Enemies {
private:
    int scale = 2.0f;
    Texture FaceLeft,FaceRight;
public:
    EggStinger(float startX = 100, float startY = 100) {
        x = startX;
        y = startY;
        y = 64 * 2;
        FaceLeft.loadFromFile("Data/EggRight.png");
        FaceRight.loadFromFile("Data/EggLeft.png");
        sprite.setTexture(FaceLeft);
        sprite.setScale(2.0f, 2.0f);
    }

    void update(float sonicX, float sonicY, char** lvl) {
        if (sonicX > x + 8) {
            x += 3;
            sprite.setTexture(FaceLeft);
            }
        else if (sonicX < x - 8) {
            x -= 3;
            sprite.setTexture(FaceRight);
        }
            else if ((sonicX - x) < cell_size/2 && clock.getElapsedTime().asSeconds() >= 1 ) {
               y += 90;
                clock.restart();
            }
            sprite.setPosition(x, y);

            if ((sonicX - x) > cell_size || (x - sonicX) > cell_size )
                y = 64 * 2;
        if (y > 64 * 8)
            y = 64 * 2;


        float bottomX = x + (76 * scale) / 2;
        float bottomY = y + (53 * scale);

        int gridX = (int)(bottomX) / cell_size;
        int gridY = (int)(bottomY) / cell_size;

        if (lvl[gridY][gridX] == 'h' )
            lvl[gridY][gridX] = 's';
    }

    void draw(RenderWindow& window, float offsetX) {
        sprite.setPosition(x - offsetX, y);
        window.draw(sprite);
    }
};