#ifndef WALL_HPP
#define WALL_HPP

#include "BaseShape.hpp"
#include "Common.hpp"
//-------------------------------------The Wall class---------------------------------
class Wall : public BaseShape<sf::RectangleShape>
{
public:
	Wall(sf::Vector2f postion, sf::Vector2f size, sf::Color colour);
	float set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset); // setting the Yposition within the level

	bool get_Touching() const { return touching_; } // method to check if the player is touching the wall
	void set_Touching(bool t) { touching_ = t; }

	//setting up the images for the level
	sf::Vector2i isource;
	sf::Texture spriteTexture;
	sf::Texture spriteTexture2;
	sf::Sprite spriteImage;
	sf::Sprite spriteImage2;
private:
	//variables in here
	bool touching_;
};
//------------------------------------------------------------------------------------
#endif