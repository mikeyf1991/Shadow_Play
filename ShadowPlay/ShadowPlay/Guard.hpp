#pragma once

#include "Common.hpp"

#include "Player.hpp"
#include "Shadow.hpp"
#include "BaseShape.hpp"
#include "StateManager.hpp"

#pragma warning(disable : 4244)
#pragma warning(disable : 4552)

class GameOverState;
class Guard : public BaseShape<sf::RectangleShape> {

public:
	Guard(sf::Vector2f postion, sf::Vector2f size, sf::Color colour);
	float set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset);
	void updatePlayer(const Player& player, const Shadow& shadow);
	void updateShadow(const Shadow& shadow, const Player& player);
	bool goto_game_over();

	//set up for sprite sheets
	sf::Vector2i isource;
	sf::Texture spriteTexture;
	sf::Sprite spriteImage;

	float framecounter = 0, frameswitch = 100, framespeed = 500;

	void Draw(sf::RenderWindow& window);

private:
	void move_guard();

	void Patrol(Player player, Shadow shadow);
	void Search(Player player, Shadow shadow);
	void Check_distance(const Player& player, const Shadow& shadow);
	void Area_patrol(Player player, Shadow shadow);
	void ReturnPatrol(Player player, Shadow shadow);

	bool turnRight;
	void turnAround();
	void softReset();

	HSAMPLE seen_sound_;
	HSAMPLE lost_sound_;
	HSAMPLE game_over_sound_;
	HCHANNEL main_channel_;
	HCHANNEL main_channel2_;
	HCHANNEL main_channel3_;
	bool played;
	bool played2;

	sf::Vector2f start_position_;
	sf::Vector2f movement_speed_;

	sf::Vector2i I_last_player_position_;
	sf::Vector2i I_Start_position_;
	sf::Vector2i I_pos_;

	sf::Clock frameclock;

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

	int offset;
	bool isit;

	bool faceLeft;

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
	//
	//enum class ShadowPatrolStatus
	//{
	//	IDLE,
	//	PATROL,
	//	AREAPATROL,
	//	SEARCH,
	//	RETURN,
	//	FOUND
	//};

	//ShadowPatrolStatus Shadow_patrol_status_;
};