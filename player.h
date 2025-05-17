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
class player {
protected:
	Clock clk;
	bool isMovingHorizontally;
	bool direction;
	float player_x = 100;
	float player_y = 100;

	float max_speed = 15;

	float velocityX = 0;
	float velocityY = 0;

	float jumpStrength = -20; // Initial jump velocity
	float gravity = 1;  // Gravity acceleration

	float scale_x = 2.5;
	float scale_y = 2.5;

	bool onGround = false;

	float offset_x = 0;
	float offset_y = 0;

	float terminal_Velocity = 20;

	const int cell_size = 64;

	float acceleration = 0.2;

	Animation animation;

	int currentfr;
	int hit_box_factor_x = 8 * scale_x;//20
	int hit_box_factor_y = 5 * scale_y;//12.5
	int raw_img_x = 24;
	int raw_img_y = 35;
	int Pheight = raw_img_y * scale_y;
	int Pwidth = raw_img_x * scale_x;
public:
	player() {
		isMovingHorizontally = false;
		currentfr = 0;
		direction = false;
	}
	bool getOnGround(){ return onGround; }
	float getX() { return player_x; }
	float getY() { return player_y; }
	void set(int x,int y) {
		player_x = x;
		player_y = y;
	}
	void getOnGround(bool g) { onGround = g; }
	virtual void jump(Clock& clock) = 0;
	virtual void draw_player(RenderWindow& window, char** lvl, float offset_x) {}
	virtual int getDirection() {return direction;}
	virtual void setDirection(bool d) {}
	void player_gravity(char** lvl,bool direction);
	virtual void runLeft(Clock& clock) {}
	virtual void runRight(Clock& clock) {}
	virtual void StandStill() = 0;
	virtual void Jump(Clock& clock) = 0;
	virtual void JumpMove(Clock& clock) = 0;
	virtual void JumpAnimation(Clock& clock) = 0;
	virtual void Follow(float x, float y, int active, Clock clock) = 0;
	bool CollectItems(char** lvl, int i, int j);
	int getRow(){ return (int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size; }
	int getCol(){ return (int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size; }
	bool DetectHorizontalTile(char** lvl, int targetRow, int targetCol,char ch);
	bool DetectFloor(char** lvl,char ch); 
};

bool player::DetectFloor(char** lvl, char ch) {
	int footRow = (int)(player_y + hit_box_factor_y + Pheight) / cell_size;
	int feetCol = (int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size;

	// Calculate left and right X positions (bounding edges)
	int colLeft = (int)(player_x + hit_box_factor_x) / cell_size;
	int colRight = (int)(player_x + hit_box_factor_x + Pwidth) / cell_size;

	// Check if either foot is exactly above the target tile
	if (lvl[footRow][feetCol] == ch) {
		return true;
	}

	return false;
}

bool player::DetectHorizontalTile(char** lvl, int targetRow, int targetCol,char ch) {
	// Get the center row of the player
	int row = (int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size;


	// Check left and right side from the player's center
	int colLeft = (int)(player_x + hit_box_factor_x) / cell_size;
	int colRight = (int)(player_x + hit_box_factor_x + Pwidth) / cell_size;

	int top_y = (int)((player_y + hit_box_factor_y) / cell_size);
	int mid_y = (int)((player_y + hit_box_factor_y + Pheight / 2) / cell_size);
	int bottom_y = (int)((player_y + hit_box_factor_y + Pheight) / cell_size);
	int left_x = (int)((player_x + hit_box_factor_x) / cell_size);
	int right_x = (int)((player_x + hit_box_factor_x + Pwidth) / cell_size);

	// Optional: Check left collision
	if (lvl[row][colLeft] == ch && colLeft == targetCol && row == targetRow) {
		return true;
	}
	if (lvl[row-1][colLeft] == ch && colLeft == targetCol && row == targetRow) {
		return true;
	}

	// Optional: Check right collision
	if (lvl[row - 1][colRight] == ch && colRight == targetCol && row == targetRow) {
		lvl[row - 1][colRight] = 's';
		return true;
	}
	if (lvl[row][colRight] == ch && colRight == targetCol && row == targetRow) {
		return true;
	}

	return false;
}


bool player::CollectItems(char** lvl,int i,int j)
{
	int row = (int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size;
	int col = (int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size;

	char tile = lvl[row][col];
	if (tile == 'r' ) {
		cout << row << " " << col << endl;
		//lvl[row][col] = 's'; // clear the ring from map
		return true;
	}
	return false;
}




void player::player_gravity(char** lvl, bool movement_Left_Or_Right)
{
	offset_y = player_y;
	offset_y += velocityY;

	// --------- VERTICAL COLLISION (Ground) ---------
	int bottom_y_index = (int)(offset_y + hit_box_factor_y + Pheight) / cell_size;
	int left_x_index = (int)(player_x + hit_box_factor_x) / cell_size;
	int right_x_index = (int)(player_x + hit_box_factor_x + Pwidth) / cell_size;
	int mid_x_index = (int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size;

	char bottom_left = lvl[bottom_y_index][left_x_index];
	char bottom_mid = lvl[bottom_y_index][mid_x_index];
	char bottom_right = lvl[bottom_y_index][right_x_index];

	if (bottom_mid == 'w' || bottom_mid == 'q' || bottom_mid == 'v' || bottom_mid == 'e' || bottom_mid == 'h' || bottom_mid == 't')
	{

		onGround = true;
		velocityY = 0;
		player_y = bottom_y_index * cell_size - hit_box_factor_y - Pheight;
	}
	else
	{
		onGround = false;
		velocityY += gravity;
		if (velocityY >= terminal_Velocity)
			velocityY = terminal_Velocity;

		player_y += velocityY;
	}
	// --------- HORIZONTAL COLLISION ---------
	int top_y = (int)((player_y + hit_box_factor_y) / cell_size);
	int mid_y = (int)((player_y + hit_box_factor_y + Pheight / 2) / cell_size);
	int bottom_y = (int)((player_y + hit_box_factor_y + Pheight) / cell_size);
	int left_x = (int)((player_x + hit_box_factor_x) / cell_size);
	int right_x = (int)((player_x + hit_box_factor_x + Pwidth) / cell_size);

	// Check RIGHT wall collision
	if (isMovingHorizontally) {
		if (!movement_Left_Or_Right && (
			lvl[top_y][right_x] == 'w' || lvl[mid_y][right_x] == 'w' ||
			lvl[top_y][right_x] == 'q' || lvl[mid_y][right_x] == 'q' ||lvl[mid_y][right_x] == 't' ||
			lvl[top_y][right_x] == 'e' || lvl[mid_y][right_x] == 'e' ||
			lvl[mid_y][right_x] == 'v'))
		{
			float right_tile_left = right_x * cell_size;
			player_x = right_tile_left - hit_box_factor_x - Pwidth - 0.2f;
		}

		if (movement_Left_Or_Right && (
			lvl[top_y][left_x] == 'w' || lvl[mid_y][left_x] == 'w'  ||
			lvl[top_y][left_x] == 'q' || lvl[mid_y][left_x] == 'q' || lvl[mid_y][left_x] == 't' ||
			lvl[top_y][left_x] == 'e' || lvl[mid_y][left_x] == 'e' || 
			lvl[mid_y][left_x] == 'v'))
		{
			float left_tile_right = (left_x + 1) * cell_size;
			player_x = left_tile_right - hit_box_factor_x + 0.2f;
		}
	}

	// --------- CEILING COLLISION ---------
	int top_y_index = (int)((player_y + hit_box_factor_y) / cell_size);

	char top_left = lvl[top_y_index][left_x_index];
	char top_mid = lvl[top_y_index][mid_x_index];
	char top_right = lvl[top_y_index][right_x_index];

	// Only check if moving upward (velocityY < 0)
	if (velocityY < 0 &&
		(top_left == 'w' || top_mid == 'w' || top_right == 'w' || top_left == 'q' || top_mid == 'q' || top_right == 'q'|| top_mid == 'e'))
	{
		velocityY = 0;
		player_y = (top_y_index + 1) * cell_size - hit_box_factor_y;
	}
	if (velocityY < 0 &&
		(top_left == 'h' || top_mid == 'h' || top_right == 'h'))
	{
		player_y -= 80;
	}
}