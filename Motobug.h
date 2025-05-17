#pragma once
#include "Crawlers.h"

class Motobug : public Crawlers {
public:
	Motobug(Texture t, float pace, float& xP, float& yP, float& xE, float& yE) : Crawlers(t, pace, 2, xP, yP, xE, yE) { canShoot = false; }

	virtual void DecreaseHP() override {}

	virtual void Movement() override {
		if (player_x < enemy_x) {
			enemy_x = enemy_x - 5;
		}
		if (player_y < enemy_y) {
			enemy_y = enemy_y - 5;
		}
		if (player_x > enemy_x) {
			enemy_x = enemy_x + 5;
		}
		if (player_x > enemy_x) {
			enemy_x = enemy_x + 5;
		}

		if (player_x == enemy_x && player_y == enemy_y) {
			// Collison howi hai
		}

	}

	virtual ~Motobug() {}
};