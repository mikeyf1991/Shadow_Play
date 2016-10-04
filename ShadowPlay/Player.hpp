#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Common.hpp"
#include "BaseShape.hpp"
//-------------------------------------------The player class------------------------------------
class Player : public BaseShape < sf::RectangleShape >
{
public:
	Player(sf::Vector2f position, sf::Vector2f size, sf::Color colour);//constructor
	float set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset);//setting the Yposition within the level

	sf::Vector2i getLpos() const { return Lpos; }//getting the player last postion, is used within the guard class
	void setLpos(sf::Vector2f xlp) { Lpos.x = (int)xlp.x; Lpos.y = (int)xlp.y; }

	bool getPlayerTextState() { return display_player_pos_; }// method for debugging purposes to display the players position in the game
	void setPlayerTextState(bool d_p_p) { display_player_pos_ = d_p_p; }


	sf::Vector2i getPlayerPos() const { return player_Pos; } // getting the players position within the game
	void setPlayerPos(sf::Vector2i ps_){ player_Pos.x = (int)ps_.x; player_Pos.y = (int)ps_.y; }

	bool casting = false;
	bool walkleft = false;

	int getLevelNumber(){ return level_number_; }
	void setLevelNumber(int ln){ level_number_ = ln; }

	//set up for sprite sheets
	sf::Vector2i isource;
	sf::Texture spriteTexture;
	sf::Sprite spriteImage;

	float framecounter = 0, frameswitch = 150, framespeed = 500;
	sf::Clock frameclock; // clock for the spritesheet
private:
	//variables are made in here
	int level_number_;
	sf::Vector2i Lpos;
	sf::Vector2i player_Pos;
	bool display_player_pos_;

};
//-----------------------------------------------------------------------------------------------------------------------------------
#endif