#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "BaseShape.hpp"
#include "Common.hpp"
//----------------------------------------the Light class-----------------------------------------
class Light : public BaseShape<sf::RectangleShape>
{
public:
	Light(sf::Vector2f postion, sf::Vector2f size, sf::Color colour, int id);//constructor
	float set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset);//setting the Yposition within the level

	bool can_teleport() const { return teleport_; }//method to check if the player can teleport from the light
	void set_teleport(bool val) { teleport_ = val; }

	const int ID() const { return id_; } // the unique ID of each light

	bool draw_shadow() const { return shadow_; } // method to check if a shadow is being drawn within the light
	void set_shadow(bool val) { shadow_ = val; }

	void setimgpos();// setting the image postiion method

	bool get_shadow_text() const { return shadow_textdraw_; }// drawing the shadows text
	void set_shadow_text(bool val) { shadow_textdraw_ = val; }

	void Draw(sf::RenderWindow& window);

	bool get_In_Range() const { return in_range_; } // method to check if the light is in range of another
	void set_In_Range(bool ir) { in_range_ = ir; }

	//setting up the images for the lights
	sf::Vector2i isource;
	sf::Texture spriteTexture;
	sf::Texture spriteTexture2;
	sf::Sprite spriteImage;
	sf::Sprite spriteImage2;

private:
	//variables are in here
	int id_;
	bool teleport_;
	bool in_range_;
	bool shadow_;
	bool shadow_textdraw_;

	float pos_y;
};
//------------------------------------------------------------------------------------------------
#endif