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
using namespace sf;
using namespace std;
//int SwitchCharacters(int& a, int& b, int& c);
class Level3 {
	int health;
	int Lives;
	int Score;
	int Rings;
	bool Boost;
	Scoreboard scoreboard;
	bool zKeyWasPressedLastFrame = false;
	Clock clock;
	Collectibles* rings[188];
	Collectibles* specialBoost[2];
	Collectibles* lives;
	int RingIndex = 0;
	int BoostIndex = 1;
	int LifeIndex = 2;
	player* playables[3];
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
	const int width = 300;
	Texture wallTex1, wallTex2, wallTex3, TrapTexture, HitBoxTexture, bgTexture, halfTileTexture, PurpleCrystalTexture, wallTex4, monsterTileTexture, BlueCrystal1Texture, BlueCrystal2Texture, branchTexture;
	Sprite wallSprite1, wallSprite2, wallSprite3, TrapSprite, HitBox, bgSprite, halfTile, PurpleCrystal, wallSprite4, monsterTile, BlueCrystal1, BlueCrystal2, branch;
public:
	Level3() :lvl(nullptr) {
		//for (int i = 0;i < 137;i++)
			//rings[i] = new Ring(100, 100);
		playables[0] = new Sonic;
		playables[1] = new Tails;
		playables[2] = new knuckles;
		ActivePlayer = SonicIndex;
		// Music for Menu
		lvlMus.openFromFile("Sound Effects/level3.mp3");
		lvlMus.setVolume(30);
		//lvlMus.play();
		lvlMus.setLoop(true);
		// lvl array for level designing
		lvl = new char* [height];
		for (int i = 0; i < height; i += 1)
		{
			lvl[i] = new char[width] {'\0'};
		}
		// Putting letters into lvl array
		ifstream file("Data/DeathZone/level3.txt");
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
					lvl[row][col] = 'r';
					rings[position++] = new Ring(col * 64, row * 64);
				}
				else if (value == 11) {
					lvl[row][col] = 'l';
					lives = new ExtraLife(col * 64, row * 64);
				}
				else if (value == 12) {
					lvl[row][col] = 'x';
					specialBoost[pos++] = new SpecialBoost(col * 64, row * 64);
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
					if (playables[KnucklesIndex]->DetectHorizontalTile(lvl, i, j,'q'))
						lvl[i][j] = 's';
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
				if (lvl[i][j] == 'r') {
					rings[position]->showCollectible(window, clock, offset_x, i == playables[ActivePlayer]->getRow() && j == playables[ActivePlayer]->getCol()); // 0 to show rings
					position++;
				}
				if (lvl[i][j] == 'x') {
					specialBoost[pos++]->showCollectible(window, clock, offset_x, i == playables[ActivePlayer]->getRow() && j == playables[ActivePlayer]->getCol());
				}
				if (lvl[i][j] == 'l') {
					if (playables[KnucklesIndex]->DetectHorizontalTile(lvl, i, j,'l') || playables[ActivePlayer]->DetectFloor(lvl, 'l')) {
						health++;
						scoreboard.increaseLife();
					}
					lives->showCollectible(window, clock, offset_x, i == playables[ActivePlayer]->getRow() && j == playables[ActivePlayer]->getCol());
				}
				if (playables[ActivePlayer]->DetectFloor(lvl, 't') && lvl[i][j + 1] == 't' && clock.getElapsedTime().asSeconds() > 3) {
					health--;
					scoreboard.reduceLife();
					clock.restart();
				}
			}
		}
		if (playables[ActivePlayer]->getX() > 1200 / 2) {
			offset_x = playables[ActivePlayer]->getX() - 1200 / 2;
		}
		else {
			offset_x = 0;
		}

		//Displaying collectables
		//for (int i = 0;i < 137;i++)
		//	rings[i]->showCollectible(window, clock, offset_x,playables[ActivePlayer]->CollectItems(lvl));

		Rings = 0;
		for (int i = 0;i < 178;i++)
			Rings += rings[i]->getisCollected();
		//Displaying players
		for (int i = 0;i < 3;i++) {
			if (i != ActivePlayer)
				playables[i]->draw_player(window, lvl, offset_x);
		}
		playables[ActivePlayer]->draw_player(window, lvl, offset_x);

		scoreboard.update(Rings);
		scoreboard.draw(window, ActivePlayer);
	}

	int SwitchCharacters(int& a, int& b, int& c) {
		static int callCount = 0;
		int returnValue;
		callCount++;
		if (callCount % 3 == 0) {
			returnValue = a;
		}
		else if (callCount % 3 == 1) {
			returnValue = b;
		}
		else {
			returnValue = c;
		}
		return returnValue;
	}
	bool isComplete() {
		cout << playables[ActivePlayer]->getX() << endl;
		if (playables[ActivePlayer]->getX() > 18800) {
			lvlMus.stop();
			return true;
		}
		else
			return false;
	}
	void setCh(int i) { ActivePlayer = i; }
	int getCh() { return ActivePlayer; }

	void LevelHandleInput() {
		bool zKeyPressed = Keyboard::isKeyPressed(Keyboard::Z);
		if (Keyboard::isKeyPressed(Keyboard::Z) && !zKeyWasPressedLastFrame) {
			ActivePlayer = SwitchCharacters(SonicIndex, TailsIndex, KnucklesIndex);
		}
		zKeyWasPressedLastFrame = zKeyPressed;
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			playables[ActivePlayer]->runLeft(clock);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right)) {
			playables[ActivePlayer]->runRight(clock);
		}
		else if (playables[ActivePlayer]->getOnGround()) {
			playables[ActivePlayer]->StandStill();
		}
		if (Keyboard::isKeyPressed(Keyboard::Space) && playables[ActivePlayer]->getOnGround()) {
			playables[ActivePlayer]->Jump(clock);
		}
		if ((!(playables[ActivePlayer]->getOnGround()) && Keyboard::isKeyPressed(Keyboard::Left)) || (Keyboard::isKeyPressed(Keyboard::Right) && !(playables[ActivePlayer]->getOnGround()))) {
			playables[ActivePlayer]->JumpMove(clock);
		}
		for (int i = 0;i < 3;i++)
			if (i == ActivePlayer) {
				continue;
			}
			else if ((playables[i]->getOnGround())) {
				playables[i]->StandStill();
			}
		if (!(playables[ActivePlayer]->getOnGround())) {
			playables[ActivePlayer]->JumpAnimation(clock);
		}
		for (int i = 0;i < 3;i++) {
			if (i != ActivePlayer)
				playables[i]->Follow(playables[ActivePlayer]->getX(), playables[ActivePlayer]->getY(), ActivePlayer, clock);
		}
	}
	~Level3() {
		for (int i = 0;i < 3;i++) {
			delete[] playables[i];
		}
		for (int i = 0; i < height; i += 1)
		{
			delete[] lvl[i];
		}
		for (int i = 0; i < 3; i += 1)
		{
			delete[] playables[i];
		}
		for (int i = 0; i < 188; i++)
		{
			delete[] rings[i];
		}
		for (int i = 0; i < 2; i++)
		{
			delete[] specialBoost[i];
		}
		delete lvl;
		lvl = nullptr;
	}


	void startMusic() { lvlMus.play(); }
};