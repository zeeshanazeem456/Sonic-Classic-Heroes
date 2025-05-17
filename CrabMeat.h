#pragma once
#include "Crawlers.h"

class CrabMeat : public Crawlers {
public:
	CrabMeat(Texture t, float pace, float& xP, float& yP, float& xE, float& yE) : Crawlers(t, pace, 4, xP, yP, xE, yE) { canShoot = true; }

	virtual void DecreaseHP() override {}

	virtual void Movement() override {
		if (rand() % 2 == 0) {
			enemy_x++;
		}
		else {
			enemy_x--;
		}

		if (player_x == enemy_x && player_y == enemy_y) {
			// Collison howi hai
		}

	}

	virtual ~CrabMeat() {}
};