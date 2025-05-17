#pragma once
#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include "Animation.h"

using namespace std;
using namespace sf;

class Collectibles {
protected:
	float x_coordinate;
	float y_coordinate;
	bool isCollected;
	Animation animation;
public:
	Collectibles( float x, float y) {
		x_coordinate = x;
		y_coordinate = y;
		isCollected = false;
	}
	Collectibles(): x_coordinate(100), y_coordinate(100){}
	virtual bool getisCollected() {return isCollected;}
	virtual void showCollectible(RenderWindow& window, Clock& clock, float offset_x, bool show)  {}

	virtual void setPosition(float x, float y) {
		x_coordinate = x;
		y_coordinate = y;
	}

	virtual ~Collectibles() {

	}

};


