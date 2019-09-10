#pragma once
class Player
{
public:
	Player();
	virtual void pickCard();
	virtual void dropCard();
	void goOut();
	~Player();

};

