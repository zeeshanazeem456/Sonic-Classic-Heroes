#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace sf;
using namespace std;

class Health {
	int health;
public:
	Health():health(3){}
	void reduceHealth() {
		if (health > 0) {
			health--;
		}
	}
	bool isAlive() { return health; }
	void AddHealth() {
		if (health < 3)
			health++;
	}
};