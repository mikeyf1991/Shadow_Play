#ifndef KEYPICKUP_HPP
#define KEYPICKUP_HPP

#include "BaseShape.hpp"
#include "Player.hpp"

class KeyPickup : public BaseShape < sf::RectangleShape >
{
public:
	KeyPickup(sf::Vector2f position, sf::Vector2f size, sf::Color colour);
	float set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset);

	void update(Player& player);

	int getPositionX() const { return pos.x; }
	void setPositionX(int pos_x_) { pos.x = pos_x_; }

	int getPositionY() const { return pos.y; }
	void setPositionY(int pos_y_){ pos.y = pos_y_; }

	bool getPickupedUpState() { return picked_up_; }
	void setPickupedUpState(bool p_u){ picked_up_ = p_u; }

	bool getVisibleState() { return visible; }
	void setVisibleState(bool vis){ visible = vis; }

	int getK_P_Lvl() const { return keys_per_lvl_; }
	void getK_P_Lvl(int kpl){ keys_per_lvl_ = kpl; }

	float framecounter = 0, frameswitch = 100, framespeed = 500;
	sf::Clock frameclock;

	//set up for sprite sheets
	sf::Vector2i isource;
	sf::Texture spriteTexture;
	sf::Sprite spriteImage;
private:


	bool picked_up_;

	sf::Vector2i pos;
	bool visible;

	int keys_per_lvl_;

	HSAMPLE pickup_sound_;
	HCHANNEL main_channel_;
};
#endif