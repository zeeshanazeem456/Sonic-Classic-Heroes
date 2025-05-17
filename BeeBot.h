#pragma once
#include "Flyers.h"

class BeeBot : public Flyers {
public:
	BeeBot(Texture t, float pace, float& xP, float& yP, float& xE, float& yE) : Flyers(t, pace, 5, xP, yP, xE, yE) { canShoot = true; }

	virtual void DecreaseHP() override {}

	virtual void Movement() override {
		// zig zag logic
	}


	virtual ~BeeBot() {}
};