#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "Common.hpp"

#include "AbstractState.hpp"
#include "MainMenuState.hpp"
#include "GameState2.hpp"
#include "Player.hpp"
#include "LevelExit.hpp"
#include "Shadow.hpp"
#include "Light.hpp"
#include "Guard.hpp"
#include "KeyPickup.hpp"
#include "Switch.hpp"
#include "Wall.hpp"
#include "UI.hpp"


class GameOverState;
//---------------------------------------------------------GameState class---------------------------------------------------------------------
class GameState : public AbstractState // This is the main game state where everthing needed is created, this extends from the AbstractState class.
{
public:
	GameState(StateManager& state_manager, bool LoadFromFile); // constructor
	~GameState(); // destructor

	void pause() override final;
	void resume() override final;
	void update(const sf::Time& delta) override final;

	void render() override final;
	void handle_input(const sf::Time& delta) override final;
	void handle_state_changes() override final;
	void savePlayerInfo(const char* filename);
	void readPlayerInfo(const char* filename);
	void LoadGame(Player& player, Guard& guards, Light& lights);

	int getLevelNumber() { return level_number_; } // function to get teh level number
	void setLevelNumber(int ln) { level_number_ = ln; }

	sf::Vector2i getLoadPlayerPos() const { return player_pos; } // function for getting the loaded player pos
	void setLoadPlayerPosX(int ps_x){ player_pos.x = ps_x; }
	void setLoadPlayerPosY(int ps_y){ player_pos.y = ps_y; }

	sf::Vector2i getLoadGuard1Pos() const { return guard1_pos; } // getting the loaded guard 1 positions
	void setLoadGuard1PosX(int psOne_x){ guard1_pos.x = psOne_x; }
	void setLoadGuard1PosY(int psOne_y){ guard1_pos.y = psOne_y; }

	sf::Vector2i getLoadGuard2Pos() const { return guard2_pos; } // getting the loaded guard 2 positions
	void setLoadGuard2PosX(int psTwo_x){ guard2_pos.x = psTwo_x; }
	void setLoadGuard2PosY(int psTwo_y){ guard2_pos.y = psTwo_y; }

	bool getLoadDoorState() { return door_unlocked; } // method for getting the door state
	void setLoadDoorState(bool d_s) { door_unlocked = d_s; }

	bool getMusicState() { return music_state_; } // method for getting the music state
	void setMusicState(bool m_s) { music_state_ = m_s; }

private:
	//\/\/\/\/\/ VARIABLES IN HERE \/\/\/\/\/

	void create_lights(); // create all the lights method
	void create_guards(); // create all the guards method
	void create_walls(); // create all the walls methods
	void create_exit(); // create the exit method
	void check_collisions(); // method for checking collisions
	void teleport_player(Light& light, int teleport_id, int floor_no); // method that teleports player
	void in_range(); // method to checking if lights are in range
	void CheckOtherLights(Light& light); // methods for checking the other lights
	void cleanUp();
	//---------------Class objects----------------------
	Player player_;
	Shadow shadow_;
	UI userInter_1;
	KeyPickup key1_;
	Switch switch1_;
	Wall destroyable_wall_;
	Wall undestroyable_wall_;
	LevelExit exit_;
	//---------------------------------------------------

	bool game_over_;
	bool next_Level;
	bool change_MM;
	bool player_caught;

	//--------------- Sounds ----------------------
	HSAMPLE good_job_;
	HCHANNEL main_channel_;

	HSAMPLE shufflesound;
	HCHANNEL main_channel1_;

	HSAMPLE gottagetKey;
	HCHANNEL main_channel2_;

	HSAMPLE leverPull;
	HCHANNEL main_channel3_;

	HSAMPLE switchSound;
	HCHANNEL main_channel4_;
	
	HSTREAM Bg_music_;
	//HCHANNEL main_channel_2;
	//------------------------------------------

	//std::vector<Light> lights_;
	std::vector<std::unique_ptr<Light>> lights_image_;
	std::vector<std::unique_ptr<Guard>> guards_;

	sf::View view_main;
	sf::Texture background;
	sf::Sprite bg_sprite;

	sf::Texture floor;
	std::vector <sf::Sprite> floor_sprite;

	sf::Text teleport_text;
	sf::Font font;

	int rng(int min, int max);
	//--------------------setting up the nodes for saving the elements within the file----------------------
	tinyxml2::XMLElement * build;
	tinyxml2::XMLElement * build2;
	tinyxml2::XMLElement * e1_levelNo;
	tinyxml2::XMLElement * e2_PlayerX;
	tinyxml2::XMLElement * e3_PlayerY;
	tinyxml2::XMLElement * e4_Door;
	tinyxml2::XMLElement * e5_Guard1_X;
	tinyxml2::XMLElement * e6_Guard1_Y;
	tinyxml2::XMLElement * e7_Guard2_X;
	tinyxml2::XMLElement * e8_Guard2_Y;
	//-------------------------------------------------------------------------------------------------------
	int level_number_;
	int floor_x;
	sf::Vector2i player_pos;
	sf::Vector2i guard1_pos;
	sf::Vector2i guard2_pos;
	bool door_unlocked;
	bool music_state_;
	std::vector<sf::Vector2i> guard_pos;

	bool CoolD = false;

	sf::Vector2f mouse_pos;
};
//---------------------------------------------------------------------------------------------------------------------------------------
#endif