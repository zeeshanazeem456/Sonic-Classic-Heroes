#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "player.h"
using namespace std;
using namespace sf;
class knuckles : public player {
protected:
	bool jumpError = 0;
	Texture KnucklesTexture;
	Sprite KnucklesSprite;
	Texture  HitBoxTexture;
	Sprite HitBox;
	Texture KnucklesJumpRight, KnucklesJumpLeft;
	Texture texLeftRunKnuckles, texRightRunKnuckles, texLeftStillKnuckles, texRightStillKnuckles, texLeftFly;
public:
	knuckles() {
		KnucklesTexture.loadFromFile("Data/Knuckles/knuckles/idle/Right.png");
		KnucklesSprite.setTexture(KnucklesTexture);
		KnucklesSprite.setScale(scale_x, scale_y);
		HitBoxTexture.loadFromFile("Data/0hit_box.png");
		HitBox.setTexture(HitBoxTexture);
		HitBox.setScale(scale_x, scale_y);
		KnucklesJumpRight.loadFromFile("Data/Knuckles/KnucklesJumpLeft.png");
		KnucklesJumpLeft.loadFromFile("Data/knuckles/KnucklesJumpLeft.png");
		texLeftRunKnuckles.loadFromFile("Data/knuckles/KnucklesWalkLeft.png");
		texRightRunKnuckles.loadFromFile("Data/knuckles/KnucklesWalkRight.png");
		texLeftStillKnuckles.loadFromFile("Data/Knuckles/knuckles/idle/Left.png");
		texRightStillKnuckles.loadFromFile("Data/Knuckles/knuckles/idle/Right.png");
	}
	void jump(Clock& clock) {
		jumpError = 1;
		velocityY = jumpStrength;
		onGround = false;
		animation.Jump(KnucklesSprite, 6, clock, currentfr, 40, 40);
	}
	void update(float player_x, float player_y, float offset_x) {
		this->player_x = player_x;
		this->player_y = player_y;
		this->offset_x = offset_x;
	}
	void draw_player(RenderWindow& window, char** lvl, float offset_x) {
		this->offset_x = offset_x;
		KnucklesSprite.setPosition(player_x - offset_x, player_y);
		player_gravity(lvl, direction);
		window.draw(KnucklesSprite);

	}
	void setDirection(bool d)
	{
		direction = d;
	}
	int getDirection() {
		return direction;
	}
	virtual void runLeft(Clock& clock) {
		isMovingHorizontally = true;
		direction = true;
		KnucklesSprite.setTexture(texLeftRunKnuckles);
		animation.Run(KnucklesSprite, 6, clock, currentfr, 40, 40);
		player_x = player_x - 10;
	}
	virtual void runRight(Clock& clock) {
		isMovingHorizontally = true;
		direction = false;
		KnucklesSprite.setTexture(texRightRunKnuckles);
		animation.Run(KnucklesSprite, 8, clock, currentfr, 40, 40);
		player_x = player_x + 10;
	}
	virtual void StandStill() {
		if (!direction) {
			KnucklesSprite.setTexture(texRightStillKnuckles);
		}
		else {
			KnucklesSprite.setTexture(texLeftStillKnuckles);
		}
		KnucklesSprite.setTextureRect(IntRect(0, 0, 40, 40));
	}
	virtual void Jump(Clock& clock) {
		jumpError = 1;
		velocityY = jumpStrength;
		onGround = false;
		KnucklesSprite.setTexture(KnucklesJumpLeft);
		animation.Jump(KnucklesSprite, 8, clock, currentfr, 40, 40);
	}
	virtual void JumpMove(Clock& clock) {
		jumpError = 1;
		KnucklesSprite.setTexture(KnucklesJumpRight);
	}
	virtual void JumpAnimation(Clock& clock) {
		if (jumpError)
			animation.Jump(KnucklesSprite, 6, clock, currentfr, 40, 40);
	}
	virtual void Follow(float x, float y, int active, Clock clock) {
		if (x - 80 > player_x)
			runRight(clk);
		else if (x + 80 < player_x)
			runLeft(clk);
		else if ((x - 80 > player_x) && (x + 80 < player_x))
			StandStill();
		//cout << x - 120 << ">" << player_x << "&&"<<active <<endl;
		if (x - 120 > player_x && (active == 0 || active == 1))
		{
			if (clk.getElapsedTime().asSeconds() >= 1) {
				jump(clk);
				clk.restart();
			}
		}
		if (x + 120 < player_x && (active == 0 || active == 1))
		{
			if (clk.getElapsedTime().asSeconds() >= 1) {
				jump(clk);
				clk.restart();
			}
		}
		if (x + 800 < player_x)
		{
			player_x = x + 700;
			player_y = y;
		}
		if (x + 800 < player_x && clk.getElapsedTime().asSeconds() >= 3)
		{
			player_x = x + 600;
			player_y = y;
			clk.restart();
		}
		if (x - 800 > player_x)
		{
			player_x = x - 700;
			player_y = y;
		}
		if (x - 800 > player_x && clk.getElapsedTime().asSeconds() >= 3)
		{
			player_x = x - 600;
			player_y = y;
			clk.restart();
		}
	}
};