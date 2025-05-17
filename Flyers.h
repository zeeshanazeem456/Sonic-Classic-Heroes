#pragma once
#include "Enemies.h"

class Flyers: public Enemies {
public:
	Flyers(Texture t, float pace, float hp, float& xP, float& yP, float& xE, float& yE): Enemies(t, pace, hp, xP, yP, xE, yE){}

	virtual void shoot() override {}	// empty kyu ki abhi nhi pta if it can shoot or not

	virtual void DecreaseHP() override {}

	virtual void Movement() override{}

	virtual ~Flyers(){}
};