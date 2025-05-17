#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "player.h"
#include "Sonic.h"
#include "Collectibles.h"
#include "Ring.h"
#include "Tails.h"
#include "ExtraLife.h"
#include "SpecialBoost.h"
#include "knuckles.h"
#include "Scoreboard.h"
#include "Enemies.h"
#include "EggStringer.h"
using namespace sf;
using namespace std;
//int SwitchCharacters(int& a, int& b, int& c);
class BossLevel {
	EggStinger Egg;
	int health;
	int Score;
	int Rings;
	bool Boost;
	Scoreboard scoreboard;
	bool zKeyWasPressedLastFrame = false;
	Clock clock;
	player* playables;
	int ActivePlayer;
	int SonicIndex = 0;
	int TailsIndex = 1;
	int KnucklesIndex = 2;
	float offset_x = 0;
	float offset_y = 0;
	Music lvlMus;
	char** lvl;
	const int cell_size = 64;
	const int height = 14;
	const int width = 20;
	Texture wallTex1, wallTex2, wallTex3, TrapTexture, HitBoxTexture, bgTexture, halfTileTexture, PurpleCrystalTexture, wallTex4, monsterTileTexture, BlueCrystal1Texture, BlueCrystal2Texture, branchTexture;
	Sprite wallSprite1, wallSprite2, wallSprite3, TrapSprite, HitBox, bgSprite, halfTile, PurpleCrystal, wallSprite4, monsterTile, BlueCrystal1, BlueCrystal2, branch;
public:
	BossLevel() :lvl(nullptr) {
		//for (int i = 0;i < 137;i++)
			//rings[i] = new Ring(100, 100);
		playables = new Sonic;
		ActivePlayer = SonicIndex;
		// Music for Menu
		lvlMus.openFromFile("Sound Effects/boss.mp3");
		lvlMus.setVolume(40);
		//lvlMus.play();
		lvlMus.setLoop(true);
		// lvl array for level designing
		lvl = new char* [height];
		for (int i = 0; i < height; i += 1)
		{
			lvl[i] = new char[width] {'\0'};
		}
		// Putting letters into lvl array
		ifstream file("BossLevel.txt");
		if (!file.is_open()) {
			std::cerr << "Error: Cannot open file level 2.\n";
		}
		int position = 0;
		int pos = 0;
		int value = 0;
		int row = 0;
		for (int row = 0; row < height; row++)
		{
			for (int col = 0; col < width;col++)
			{

				file >> value;

				if (value == -1) {
					lvl[row][col] = 's';
				}
				else if (value == 0) {
					lvl[row][col] = 'h';
				}
				else if (value == 1) {
					lvl[row][col] = 'w';
				}
				else if (value == 2) {
					lvl[row][col] = 'e';
				}
				else if (value == 3) {
					lvl[row][col] = 'q';
				}
				else if (value == 4) {
					lvl[row][col] = 'p';
				}
				else if (value == 5) {
					lvl[row][col] = 't';
				}
				else if (value == 6) {
					lvl[row][col] = 'm';
				}
				else if (value == 8) {
					lvl[row][col] = 'b';
				}
				else if (value == 7) {
					lvl[row][col] = 'c';
				}
				else if (value == 9) {
					lvl[row][col] = 'd';
				}
				else if (value == 10) {
					//lvl[row][col] = 'r';
					//rings[position++] = new Ring(col * 64, row * 64);
				}
				else if (value == 11) {
					lvl[row][col] = 'l';
				}
				else if (value == 12) {
					//lvl[row][col] = 'x';
					//specialBoost[pos++] = new SpecialBoost(col * 64, row * 64);
				}
			}
		}
		// Putting textures into Sprites mostly bricks
		wallTex1.loadFromFile("Data/DeathZone/brick1.png");
		wallSprite1.setTexture(wallTex1);

		wallTex2.loadFromFile("Data/DeathZone/brick2.png");
		wallSprite2.setTexture(wallTex2);

		wallTex3.loadFromFile("Data/DeathZone/brick3.png");
		wallSprite3.setTexture(wallTex3);

		TrapTexture.loadFromFile("Data/DeathZone/Spike.png");
		TrapSprite.setTexture(TrapTexture);

		halfTileTexture.loadFromFile("Data/DeathZone/halfTileDeath.png");
		halfTile.setTexture(halfTileTexture);

		PurpleCrystalTexture.loadFromFile("Data/DeathZone/crystal.png");
		PurpleCrystal.setTexture(PurpleCrystalTexture);

		wallTex4.loadFromFile("Data/IceZone/brick1.png");
		wallSprite4.setTexture(wallTex4);

		monsterTileTexture.loadFromFile("Data/DeathZone/mons.png");
		monsterTile.setTexture(monsterTileTexture);

		BlueCrystal1Texture.loadFromFile("Data/DeathZone/flip.png");
		BlueCrystal1.setTexture(BlueCrystal1Texture);

		BlueCrystal2Texture.loadFromFile("Data/DeathZone/blue1.png");
		BlueCrystal2.setTexture(BlueCrystal2Texture);

		branchTexture.loadFromFile("Data/DeathZone/ceiling.png");
		branch.setTexture(branchTexture);

		// Applying BackGround for Game
		if (!bgTexture.loadFromFile("Data/DeathZone/bg.png")) {
			cout << "Error agaya g. Cannot open background file!\n";
		}
		bgSprite.setTexture(bgTexture);
	}


	// This Function will run Level 1
	void display_level(RenderWindow& window)
	{
		int position = 0;
		int pos = 0;
		bgSprite.setScale(3.8, 3.8);
		window.draw(bgSprite);
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (lvl[i][j] == 'w')
				{
					wallSprite1.setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(wallSprite1);
				}
				if (lvl[i][j] == 'e') {
					wallSprite2.setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(wallSprite2);
				}
				if (lvl[i][j] == 'q') {
					wallSprite3.setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(wallSprite3);
				}
				if (lvl[i][j] == 't') {
					TrapSprite.setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(TrapSprite);
				}
				if (lvl[i][j] == 'v') {
					wallSprite4.setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(wallSprite4);
				}
				if (lvl[i][j] == 'd') {
					branch.setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(branch);
				}
				if (lvl[i][j] == 'm') {
					monsterTile.setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(monsterTile);
				}
				if (lvl[i][j] == 'b') {
					BlueCrystal1.setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(BlueCrystal1);
				}
				if (lvl[i][j] == 'c') {
					BlueCrystal2.setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(BlueCrystal2);
				}
				if (lvl[i][j] == 'h') {
					halfTile.setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(halfTile);
				}
				if (lvl[i][j] == 'p') {
					PurpleCrystal.setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(PurpleCrystal);
				}
				if (playables->DetectFloor(lvl, 't') && lvl[i][j + 1] == 't' && clock.getElapsedTime().asSeconds() > 3) {
					health--;
					scoreboard.reduceLife();
					clock.restart();
				}
			}
		}

		Egg.update(playables->getX(), playables->getY(),lvl);
		Egg.draw(window,offset_y);
		playables->draw_player(window, lvl, offset_x);

		scoreboard.update(Rings);
		scoreboard.draw(window, ActivePlayer);
	}
	void LevelHandleInput() {
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			playables->runLeft(clock);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right)) {
			playables->runRight(clock);
		}
		else if (playables->getOnGround()) {
			playables->StandStill();
		}
		if (Keyboard::isKeyPressed(Keyboard::Space) && playables->getOnGround()) {
			playables->Jump(clock);
		}
		if ((!(playables->getOnGround()) && Keyboard::isKeyPressed(Keyboard::Left)) || (Keyboard::isKeyPressed(Keyboard::Right) && !(playables->getOnGround()))) {
			playables->JumpMove(clock);
		}
		if (!(playables->getOnGround())) {
			playables->JumpAnimation(clock);
		}
	}
	~BossLevel() {
			delete[] playables;
		for (int i = 0; i < height; i += 1)
		{
			delete[] lvl[i];
		}
		delete lvl;
		lvl = nullptr;
	}
	bool isComplete() {
		if (playables->getX() > 100000) {
			lvlMus.stop();
			return true;
		}
		else
			return false;
	}

	void startMusic() { lvlMus.play(); }
};