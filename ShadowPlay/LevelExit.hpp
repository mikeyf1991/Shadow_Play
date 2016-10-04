#ifndef LEVELEXIT_HPP
#define LEVELEXIT_HPP

#include "BaseShape.hpp"
#include "Common.hpp"
//------------------------------------------The level Exit Class---------------------------------------------
class LevelExit : public BaseShape<sf::RectangleShape>
{
public:
	LevelExit(sf::Vector2f position, sf::Vector2f size, sf::Color colour);//constructor
	float set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset);// set the Yposition in the level
	//set up for sprite sheets
	sf::Vector2i isource;
	sf::Texture spriteTexture;
	sf::Sprite spriteImage;
private:
};
//-----------------------------------------------------------------------------------------------------------
#endif