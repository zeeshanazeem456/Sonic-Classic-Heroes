#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

class Scoreboard {
private:
	unsigned long long int seconds;
	int min;
	int currentScore;	// score jo ki abhi hai
	int noOfLivesRemaining;		// number of zindagi for cute sonic 
	int noOfRingsCollected;		// Rings jo ki collect howi hai during the game
	Clock clk;			// Clock for time
	Time elapsedTime;	// Time ko store krney ke liye variable
	Font scoreboardFont;	// Font for the scoreboard
	Text scoreText, ringsText, timerText, minText,secondText;	// Text jo ki output hongey

	// For character selections
	Sprite sonic, knuckles, tails;
	Texture sonicTexture, knucklesTexture, tailsTexture;
public:
	// Default parameters
	Scoreboard() {
		min = 0;
		currentScore = 0;
		noOfLivesRemaining = 3;
		noOfRingsCollected = 0;

		// Loading fonts
		scoreboardFont.loadFromFile("Fonts/joystix monospace.otf");

		// Character Selections ki loading
		sonicTexture.loadFromFile("Data/CharacterSelection/sonic.png");
		tailsTexture.loadFromFile("Data/CharacterSelection/tails.png");
		knucklesTexture.loadFromFile("Data/CharacterSelection/knuckles.png");

		sonic.setTexture(sonicTexture);
		knuckles.setTexture(knucklesTexture);
		tails.setTexture(tailsTexture);

		// Fonts ko set kiya
		minText.setFont(scoreboardFont);
		secondText.setFont(scoreboardFont);
		scoreText.setFont(scoreboardFont);
		ringsText.setFont(scoreboardFont);
		timerText.setFont(scoreboardFont);

		// Hit & try hi krna parta hai for position (I wish koi asaan tareeqa mil jaye)
		scoreText.setPosition(20, 10);
		ringsText.setPosition(20, 50);
		timerText.setPosition(20, 90);

		// size ko barha rakha taaki nazar aye
		scoreText.setCharacterSize(30);
		ringsText.setCharacterSize(30);
		timerText.setCharacterSize(30);

		// White hi universal hai so White is best
		scoreText.setFillColor(Color::White);
		ringsText.setFillColor(Color::White);
		timerText.setFillColor(Color::White);
	}


	// Draw function jo ki score show krega
	void draw(RenderWindow& window, int charSelected) {
		
		RectangleShape background;
		background.setSize({ 290, 180 });
		background.setPosition(10, 10);
		background.setFillColor(Color(0, 0, 0, 150));
		window.draw(background);

		window.draw(scoreText);	// Score
		window.draw(ringsText);	// RIngs
		window.draw(timerText);	// Timer


		// Lives ke liye sprite load ki hai
		Sprite heartSprite;
		Texture heartTexture;

		heartTexture.loadFromFile("Data/f0.png");
		heartSprite.setTexture(heartTexture);
		heartSprite.setScale(2, 2);

		// If consitions ke mutabik heat show hongey
		if (noOfLivesRemaining >= 1) {
			heartSprite.setPosition(20, 140);
			window.draw(heartSprite);
		}
		if (noOfLivesRemaining >= 2) {
			heartSprite.setPosition(80, 140);
			window.draw(heartSprite);
		}
		if (noOfLivesRemaining == 3) {
			heartSprite.setPosition(140, 140);
			window.draw(heartSprite);
		}

		// charSelected ke hisaab se show krega ki konsa selected hai
		if (charSelected == 0) {
			sonic.setScale(3, 3);
			sonic.setPosition(120, 830);
			window.draw(sonic);
			tails.setScale(2.5, 2.5);
			tails.setPosition(60, 830);
			window.draw(tails);
			knuckles.setScale(2.5, 2.5);
			knuckles.setPosition(0, 830);
			window.draw(knuckles);
		}
		else if (charSelected == 1) {
			tails.setScale(3, 3);
			tails.setPosition(120, 830);
			window.draw(tails);
			sonic.setScale(2.5, 2.5);
			sonic.setPosition(60, 830);
			window.draw(sonic);
			knuckles.setScale(2.5, 2.5);
			knuckles.setPosition(0, 830);
			window.draw(knuckles);
		}
		else if (charSelected == 2) {
			knuckles.setScale(3, 3);
			knuckles.setPosition(120, 830);
			window.draw(knuckles);
			sonic.setScale(2.5, 2.5);
			sonic.setPosition(60, 830);
			window.draw(sonic);
			tails.setScale(2.5, 2.5);
			tails.setPosition(0, 830);
			window.draw(tails);
		}

	}

	// update function jo ki output ko update krega
	void update(int rings) {
		if (clk.getElapsedTime().asSeconds() >= 1) {
		clk.restart();
		seconds++;
	}
		if (seconds >=60) {
			seconds = 0;
			min++;
		}
		int score = 0;
		scoreText.setString("Score: " + to_string(score));
		ringsText.setString("Rings: " + to_string(rings));
		timerText.setString("Time: 0" + to_string(min) + ":" + to_string(seconds));
	}

	// Score adder ka function
	void addScore(int value) { currentScore = currentScore + value; }

	// reducing heart ka function
	void reduceLife() {
		if (noOfLivesRemaining > 0) {
			noOfLivesRemaining--;
			cout << "In reduce " << noOfLivesRemaining << endl;
		}
	}
	void increaseLife() {
		if (noOfLivesRemaining < 3) {
			noOfLivesRemaining++;
			cout << "In increase " << noOfLivesRemaining << endl;
		}
	}
	// Rings collected ka function
	void collectRing() { noOfRingsCollected++; }

	// Timer reset ka function
	void resetTimer() { clk.restart(); }

	~Scoreboard() {

	}

};