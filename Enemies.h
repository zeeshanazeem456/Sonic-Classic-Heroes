#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "Animation.h"

using namespace sf;
using namespace std;

class Enemies {
protected:
    Clock clock;
    Sprite sprite;
    const int cell_size = 64;
    float x, y;
};