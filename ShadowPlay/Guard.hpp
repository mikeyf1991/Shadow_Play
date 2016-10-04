#pragma once

#include "Common.hpp"

#include "Player.hpp"
#include "Shadow.hpp"
#include "BaseShape.hpp"
#include "StateManager.hpp"
#include "wall.hpp"

#pragma warning(disable : 4244)
#pragma warning(disable : 4552)

class GameOverState;
//--------------------------The guard class----------------------------------
class Guard : public BaseShape < sf::RectangleShape >
{

public:
	Guard(sf::Vector2f postion, sf::Vector2f size, sf::Color colour);//constructor
	float set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset); // setting the Yposition within the world
	void updatePlayer(Player& player, Shadow& shadow); // the update for the guards
	void updateShadow(Shadow& shadow, Player& player); // ^^^^^^^^^^^^^^^^^^^^^^^^^
	bool goto_game_over(); // boolean to get the player switched to game over
	void turnAround(); // function to make guards turn around when told to.

	//set up for sprite sheets
	sf::Vector2i isource;
	sf::Texture spriteTexture;
	sf::Sprite spriteImage;

	//set up for sprite sheets
	sf::Vector2i seenisource;
	sf::Texture seenspriteTexture;
	sf::Sprite seenspriteImage;
	sf::Texture caughtRspriteTexture;
	sf::Sprite caughtRspriteImage;
	sf::Vector2i caughtRisource;
	sf::Texture caughtLspriteTexture;
	sf::Sprite caughtLspriteImage;
	sf::Vector2i caughtLisource;

	//set up the timers for the guards
	sf::Clock go_Time, go_Time2;
	float go_Timer = 0, go_Timer2 = 0;

	bool caughtL;
	bool caughtR;

	bool turnRight;

	float framecounter = 0, frameswitch = 150, framespeed = 500;

	sf::Clock searchClock;

	bool searchLeft = false, searchRight = false, caughtLeft = false, caughtRight = false;

	void Draw(sf::RenderWindow& window);

private:
	//\/\/\/\/\/\/All variables for guards are  in here\/\/\/\/\/\/

	//---------------------------Methods for the guards------------------
	void move_guard();

	void Patrol(Player& player, Shadow& shadow);
	void Search(Player& player, Shadow& shadow);
	void Check_distance(const Player& player, const Shadow& shadow);
	void Area_patrol(Player& player, Shadow& shadow);
	void ReturnPatrol(Player& player, Shadow& shadow);
	//-------------------------------------------------------------------


	void softReset();
	//setting up the sounds for the guards
	HSAMPLE seen_sound_;
	HSAMPLE lost_sound_;
	HSAMPLE game_over_sound_;
	HCHANNEL main_channel_;
	HCHANNEL main_channel2_;
	HCHANNEL main_channel3_;

	bool played;
	bool played2;
	bool seen;

	sf::Vector2f start_position_;
	sf::Vector2f movement_speed_;

	sf::Vector2i I_last_player_position_;
	sf::Vector2i I_Start_position_;
	sf::Vector2i I_pos_;

	sf::Clock frameclock; // clock for the guard images

	int movement_distance_;
	int AP_movement_distance_;
	float view_distance_;

	int distWalked;
	int gotoXpos;
	int temp_starting_pos_;
	int sTemp_startingpos_;

	bool pOutofrange;
	bool pOutofrange2;
	bool sOutofrange;
	bool sOutofrange2;

	bool patrolled;

	bool moveme;
	bool game_over;

	float turn_delay;
	float state_delay;

	const int SPEED1 = -1;
	const int SPEED2 = -2;

	int walkLeft;
	int walkRight;

	int offset;
	bool isit;

	bool faceLeft;
	// Managing the guard states
	enum class PlayerPatrolStatus
	{
		IDLE,
		PATROL,
		AREAPATROL,
		SEARCH,
		RETURN,
		FOUND
	};
	PlayerPatrolStatus Player_patrol_status_;

};
//--------------------------------------------------------------------------------------------------