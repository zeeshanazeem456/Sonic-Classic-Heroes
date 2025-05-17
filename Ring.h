#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include "Collectibles.h"

using namespace std;
using namespace sf;

class Ring : public Collectibles {
	int once = 0;
	SoundBuffer ringBuffer;
	Sound* s = new sf::Sound();
	Sprite RingSprite;
	Texture RingTexture;
	int currentfr;
	Clock clock1;
public:

	Ring(float x, float y) : Collectibles(x, y), currentfr(0) {
		if (!ringBuffer.loadFromFile("Ring.wav")) {
			//std::cerr << "Failed to load ring.wav" << std::endl;
		}
		s->setBuffer(ringBuffer);
		RingTexture.loadFromFile("Data/rings/rings.png");
		RingSprite.setTexture(RingTexture);
		RingSprite.setTextureRect(IntRect(0, 0, 40, 40));
		RingSprite.setScale(1.5f, 1.5f);
	}

	virtual void showCollectible(RenderWindow& window, Clock& clock, float offset_x, bool show) {
		if (show) {
			isCollected = 1;
			if (!once) {
				s->play();
				once = 1;
			}
		}
		//if(isCollected)
		//cout << isCollected << endl;
		if (!isCollected) {
			RingSprite.setPosition(x_coordinate - offset_x, y_coordinate);
			animation.coinAnimation(RingSprite, 4, clock1, currentfr, 40, 40);
			window.draw(RingSprite);
		}
	}

	virtual ~Ring() { delete s; }

};



