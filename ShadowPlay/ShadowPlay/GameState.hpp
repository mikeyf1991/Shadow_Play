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
#include "UI.hpp"


class GameOverState;
class GameState : public AbstractState // This is the main game state where everthing needed is created, this extends from the AbstractState class.
{
public:
	GameState(StateManager& state_manager, bool LoadFromFile);
	~GameState();

	void pause() override final;
	void resume() override final;
	void update(const sf::Time& delta) override final;
	
	void render() override final;
	void handle_input(const sf::Time& delta) override final;
	void handle_state_changes() override final;
	void savePlayerInfo(const char* filename);
	void readPlayerInfo(const char* filename);
	void LoadGame(Player& player, Guard& guards, Light& lights);

	int getLevelNumber() { return level_number_; }
	void setLevelNumber(int ln) { level_number_ = ln; }

	sf::Vector2i getLoadPlayerPos() const { return player_pos; }
	void setLoadPlayerPosX(int ps_x){ player_pos.x = ps_x; }
	void setLoadPlayerPosY(int ps_y){ player_pos.y = ps_y; }

	sf::Vector2i getLoadGuard1Pos() const { return guard1_pos; }
	void setLoadGuard1PosX(int psOne_x){ guard1_pos.x = psOne_x; }
	void setLoadGuard1PosY(int psOne_y){ guard1_pos.y = psOne_y; }

	sf::Vector2i getLoadGuard2Pos() const { return guard2_pos; }
	void setLoadGuard2PosX(int psTwo_x){ guard2_pos.x = psTwo_x; }
	void setLoadGuard2PosY(int psTwo_y){ guard2_pos.y = psTwo_y; }

	bool getLoadDoorState() { return door_unlocked; }
	void setLoadDoorState(bool d_s) { door_unlocked = d_s; }

private:
	void create_lights();
	void create_guards();
	void create_exit();
	void check_collisions();
	void teleport_player(Light& light, int teleport_id, int floor_no);
	void in_range();
	void CheckOtherLights(Light& light);
	void cleanUp(Player& player, Guard& guards, Light& lights, KeyPickup& key);

	Player player_;
	Shadow shadow_;
	UI userInter_1;
	KeyPickup key1_;
	Switch switch1_;
	LevelExit exit_;
	bool game_over_;
	bool next_Level;
	bool change_MM;

	HSAMPLE good_job_;
	HCHANNEL main_channel_;

	HSTREAM Bg_music_;
	//HCHANNEL main_channel_2;

	std::vector<Light> lights_;
	std::vector<std::unique_ptr<Guard>> guards_;

	sf::View view_main;
	sf::Texture background;
	sf::Sprite bg_sprite;

	sf::Texture floor;
	std::vector <sf::Sprite> floor_sprite;

	sf::Text teleport_text;
	sf::Font font;

	int rng(int min, int max);

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

	int level_number_;
	int floor_x;
	sf::Vector2i player_pos;
	sf::Vector2i guard1_pos;
	sf::Vector2i guard2_pos;
	bool door_unlocked;
	std::vector<sf::Vector2i> guard_pos;

	sf::Vector2f mouse_pos;
};

#endif