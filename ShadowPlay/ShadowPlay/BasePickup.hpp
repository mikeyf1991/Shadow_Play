#pragma once
#include "Common.hpp"


class BasePickup
{
public:
	int getPositionX() const { return pos.x; }
	void setPositionX(int pos_x_) { pos.x = pos_x_; }

	int getPositionY() const { return pos.y; }
	void setPositionY(int pos_y_){ pos.y = pos_y_; }

	bool getPickupedUpState() { return picked_up_; }
	void setPickupedUpState(bool p_u){ picked_up_ = p_u; }
private:
	sf::Vector2i pos;
	bool picked_up_;


};