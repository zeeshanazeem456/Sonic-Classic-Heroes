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
class Sonic: public player {
protected:		
	bool jumpError = 0;
	Texture sonicTex;
	Sprite sonicSprite;
	Texture  HitBoxTexture;
	Sprite HitBox;
	Texture sonicJumpRight, sonicJumpLeft;
	Texture texLeftRunSonic, texRightRunSonic, texLeftStillSonic, texRightStillSonic;
public:
	Sonic() {
		sonicTex.loadFromFile("Data/0right_still.png");
		HitBoxTexture.loadFromFile("Data/0hit_box.png");
		sonicSprite.setTexture(sonicTex);
		sonicSprite.setScale(scale_x, scale_y);
		HitBox.setTexture(HitBoxTexture);
		HitBox.setScale(scale_x, scale_y);
		HitBoxTexture.loadFromFile("Data/0hit_box.png");
		sonicJumpRight.loadFromFile("Data/0upR.png");
		sonicJumpLeft.loadFromFile("Data/0upL.png");
		texLeftRunSonic.loadFromFile("Data/0left.png");
		texRightRunSonic.loadFromFile("Data/0right.png");
		texLeftStillSonic.loadFromFile("Data/0left_still.png");
		texRightStillSonic.loadFromFile("Data/0right_still.png");
	}
	void jump(Clock& clock) {
		jumpError = 1;
		velocityY = jumpStrength;
		onGround = false;

		if (direction) {
			sonicSprite.setTexture(sonicJumpLeft);
		}
		else {
			sonicSprite.setTexture(sonicJumpRight);
		}
		animation.Jump(sonicSprite, 8, clock, currentfr, 40, 40);
	}
	void update(float player_x,float player_y,float offset_x) {
		this->player_x = player_x;
		this->player_y = player_y;
		this->offset_x = offset_x;
	}
	void draw_player(RenderWindow& window,char** lvl,float offset_x) {
		this->offset_x = offset_x;
		//HitBox.setPosition(player_x - offset_x, player_y);
		sonicSprite.setPosition(player_x - offset_x, player_y);
		player_gravity(lvl,direction);
		//window.draw(HitBox);
		window.draw(sonicSprite);

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
		sonicSprite.setTexture(texLeftRunSonic);
		animation.Run(sonicSprite, 8, clock, currentfr, 40, 40);
		player_x = player_x - 10;
	}
	virtual void runRight(Clock& clock) {
		isMovingHorizontally = true;
		direction = false;
		sonicSprite.setTexture(texRightRunSonic);
		animation.Run(sonicSprite, 6, clock, currentfr, 40, 40);
		player_x = player_x + 10;
	}
	virtual void StandStill() {
		if (!direction) {
			sonicSprite.setTexture(texRightStillSonic);
		}
		else {
			sonicSprite.setTexture(texLeftStillSonic);
		}
		sonicSprite.setTextureRect(IntRect(0, 0, 40, 40));
	}
	virtual void Jump(Clock& clock) {
		jumpError = 1;
		velocityY = jumpStrength;
		onGround = false;

		if (direction) {
			sonicSprite.setTexture(sonicJumpLeft);
		}
		else {
			sonicSprite.setTexture(sonicJumpRight);
		}
		animation.Jump(sonicSprite, 8, clock, currentfr, 40, 40);
	}
	virtual void JumpMove(Clock& clock) {
		jumpError = 1;
		if (direction) {
			sonicSprite.setTexture(sonicJumpLeft);
		}
		else {
			sonicSprite.setTexture(sonicJumpRight);
		}
	}
	virtual void JumpAnimation(Clock& clock){
		if (jumpError)
			animation.Jump(sonicSprite, 8, clock, currentfr, 40, 40);
	}
	virtual void Follow(float x, float y, int active, Clock clock) {
		if (x - 90 > player_x)
			runRight(clk);
		else if (x + 90 < player_x)
			runLeft(clk);
		else if ((x - 90 > player_x) && (x + 90 < player_x))
			StandStill();
		//cout << x - 120 << ">" << player_x << "&&"<<active <<endl;
		if (x - 180 > player_x && (active == 2 || active == 1))
		{
			if (clk.getElapsedTime().asSeconds() >= 1) {
				jump(clk);
				clk.restart();
			}
		}
		if (x + 180 < player_x && (active == 2 || active == 1))
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