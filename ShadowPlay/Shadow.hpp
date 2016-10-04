#ifndef SHADOW_HPP
#define SHADOW_HPP

#include "BaseShape.hpp"
#include "Common.hpp"
//----------------------------------------- The Shadow Class ------------------------------------------------------
class Shadow : public BaseShape<sf::RectangleShape>
{
public:
	Shadow(sf::Vector2f postion, sf::Vector2f size, sf::Color colour);//constructor
	float set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset);//setting the Yposition within the level

	sf::Vector2i getLpos() const { return Lpos; } // method for getting the last position of the shadow
	void setLpos(sf::Vector2f xlp) { Lpos.x = (int)xlp.x; Lpos.y = (int)xlp.y; } 

	bool getVisibleState() const { return shadow_vis_; }// method for getting if the shadow is currently visible
	void setVisibleState(bool s_v) { shadow_vis_ = s_v; }

	bool getCastState() const { return shadow_cast_; }//method for checking if the shadow has been cast
	void setCastState(bool s_c) { shadow_cast_ = s_c; }

	float getCoolDown() const { return cooldowntimer; }//method for getting the CoolDown of the shadow

	//set up for sprite sheets
	sf::Vector2i isource;
	sf::Texture shadowTexture;
	sf::Sprite shadowImage;
	bool casted = false;
	sf::Vector2i castisource;
	sf::Texture shadowCastTexture;
	sf::Sprite shadowCastImage;

	float framecounter = 0, frameswitch = 100, cooldown = 3000, cast = 100, cooldowntimer = 0, casttimer = 0;
	sf::Clock frameclock, clock1, clock2; // timers for the shadows

private:
	//variables in here
	sf::Vector2i Lpos;
	
	bool shadow_vis_;
	bool shadow_cast_;
};
//---------------------------------------------------------------------------------------------------------------------
#endif