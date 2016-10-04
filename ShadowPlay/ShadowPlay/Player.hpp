#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Common.hpp"
#include "BaseShape.hpp"

class Player : public BaseShape < sf::RectangleShape >
{
public:
	Player(sf::Vector2f position, sf::Vector2f size, sf::Color colour);
	float set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset);

	sf::Vector2i getLpos() const { return Lpos; }
	void setLpos(sf::Vector2f xlp) { Lpos.x = (int)xlp.x; Lpos.y = (int)xlp.y; }

	bool getPlayerTextState() { return display_player_pos_; }
	void setPlayerTextState(bool d_p_p) { display_player_pos_ = d_p_p; }


	sf::Vector2i getPlayerPos() const { return player_Pos; }
	void setPlayerPos(sf::Vector2i ps_){ player_Pos.x = (int)ps_.x; player_Pos.y = (int)ps_.y; }



	int getLevelNumber(){ return level_number_; }
	void setLevelNumber(int ln){ level_number_ = ln; }

	//set up for sprite sheets
	sf::Vector2i isource;
	sf::Texture spriteTexture;
	sf::Sprite spriteImage;

	float framecounter = 0, frameswitch = 100, framespeed = 500;
	sf::Clock frameclock;
private:
	int level_number_;
	sf::Vector2i Lpos;
	sf::Vector2i player_Pos;
	bool display_player_pos_;
};

#endif