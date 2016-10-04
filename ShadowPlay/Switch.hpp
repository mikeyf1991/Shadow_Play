#ifndef SWITCH_HPP
#define SWITCH_HPP

#include "BaseShape.hpp"
#include "Common.hpp"
//-----------------------------------The Switch class----------------------------------
class Switch : public BaseShape < sf::RectangleShape >
{
public:
	Switch(sf::Vector2f postion, sf::Vector2f size, sf::Color colour, int id);
	float set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset); // setting the Yposition in the level

	bool has_Pulled() const { return pulled_; } // method to check if the switch has been pulled
	void set_Pulled(bool pul) { pulled_ = pul; }

	bool in_Range() const { return in_range_; } // method to check if the player is in range of the switch
	void set_inRange(bool iR) { in_range_ = iR; }

	const int ID() const { return id_; } // the ID of the switch, so that it can be co-ordintated with the walls in the level

	//setting up the images for the switched
	sf::Vector2i isource;
	sf::Texture spriteTexture;
	sf::Texture spriteTexture2;
	sf::Sprite spriteImage;
	sf::Sprite spriteImage2;
private:
	int id_;
	bool pulled_;
	bool in_range_;
};
//--------------------------------------------------------------------------------------
#endif