#ifndef SHADOW_HPP
#define SHADOW_HPP

#include "BaseShape.hpp"
#include "Common.hpp"

class Shadow : public BaseShape<sf::RectangleShape>
{
public:
	Shadow(sf::Vector2f postion, sf::Vector2f size, sf::Color colour);
	float set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset);
	sf::Vector2i getLpos() const { return Lpos; }
	void setLpos(sf::Vector2f xlp) { Lpos.x = (int)xlp.x; Lpos.y = (int)xlp.y; }
	bool getVisibleState() const { return shadow_vis_; }
	void setVisibleState(bool s_v) { shadow_vis_ = s_v; }

	//set up for sprite sheets
	sf::Vector2i isource;
	sf::Texture spriteTexture;
	sf::Sprite spriteImage;

	float framecounter = 0, frameswitch = 100, framespeed = 500;
	sf::Clock frameclock;
private:
	sf::Vector2i Lpos;

	bool shadow_vis_;
};

#endif