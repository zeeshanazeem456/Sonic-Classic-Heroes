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
class Tails : public player {
protected:
	bool jumpError = 0;
	Texture TailsTexture;
	Sprite TailsSprite;
	Texture  HitBoxTexture;
	Sprite HitBox;
	Texture TailsJumpRight, TailsJumpLeft;
	Texture texLeftRunTails, texRightRunTails, texLeftStillTails, texRightStillTails,texLeftFly;
public:
	Tails() {
		TailsTexture.loadFromFile("Data/Tails/TailsRightStill.png");
		TailsSprite.setTexture(TailsTexture);
		TailsSprite.setScale(scale_x, scale_y);
		HitBoxTexture.loadFromFile("Data/0hit_box.png");
		HitBox.setTexture(HitBoxTexture);
		HitBox.setScale(scale_x, scale_y);
		TailsJumpRight.loadFromFile("Data/Tails/TailsJump/TailsJump.png");
		TailsJumpLeft.loadFromFile("Data/Tails/TailsJump/TailsJump.png");
		texLeftRunTails.loadFromFile("Data/Tails/RunLeft/RunLeft.png");
		texRightRunTails.loadFromFile("Data/Tails/RunRight/RunRight.png");
		texLeftStillTails.loadFromFile("Data/Tails/TailsLeftStill.png");
		texRightStillTails.loadFromFile("Data/Tails/TailsRightStill.png");
	}
	void jump(Clock& clock) {
		jumpError = 1;
		velocityY = jumpStrength;
		onGround = false;
		animation.Jump(TailsSprite, 6, clock, currentfr, 40, 40);
	}
	void update(float player_x, float player_y, float offset_x) {
		this->player_x = player_x;
		this->player_y = player_y;
		this->offset_x = offset_x;
	}
	void draw_player(RenderWindow& window, char** lvl, float offset_x) {
		this->offset_x = offset_x;
		TailsSprite.setPosition(player_x - offset_x, player_y);
		player_gravity(lvl, direction);
		window.draw(TailsSprite);

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
		TailsSprite.setTexture(texLeftRunTails);
		animation.Run(TailsSprite, 6, clock, currentfr, 40, 40);
		player_x = player_x - 10;
	}
	virtual void runRight(Clock& clock) {
		isMovingHorizontally = true;
		direction = false;
		TailsSprite.setTexture(texRightRunTails);
		animation.Run(TailsSprite, 6, clock, currentfr, 40, 40);
		player_x = player_x + 10;
	}
	virtual void StandStill() {
		if (!direction) {
			TailsSprite.setTexture(texRightStillTails);
		}
		else {
			TailsSprite.setTexture(texLeftStillTails);
		}
		TailsSprite.setTextureRect(IntRect(0, 0, 40, 40));
	}
	virtual void Jump(Clock& clock) {
		jumpError = 1;
		velocityY = jumpStrength;
		onGround = false;
			TailsSprite.setTexture(TailsJumpLeft);
		animation.Jump(TailsSprite, 6, clock, currentfr, 40, 40);
	}
	virtual void JumpMove(Clock& clock) {
		jumpError = 1;
		TailsSprite.setTexture(TailsJumpRight);
	}
	virtual void JumpAnimation(Clock& clock) {
		if (jumpError)
			animation.Jump(TailsSprite, 6, clock, currentfr, 40, 40);
	}
	virtual void Follow(float x, float y, int active, Clock clock) {
		if (x - 130 > player_x){
			runRight(clk);
			player_x += 5;
		}
		else if (x + 130 < player_x) {
			runLeft(clk);
			player_x -= 5;
		}	
		else if ((x - 130 > player_x) && (x + 130 < player_x))
			StandStill();



		if (x - 180 > player_x && (active == 0 || active == 2))
		{
			if (clk.getElapsedTime().asSeconds() >= 1) {
				jump(clk);
				clk.restart();
			}
		}

		if (x + 180 < player_x && (active == 0 || active == 2))
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
		if (x + 800 < player_x && clk.getElapsedTime().asSeconds() >= 2)
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