#ifndef GAMESTATE2_HPP
#define GAMESTATE2_HPP

#include "Common.hpp"

#include "AbstractState.hpp"
#include "MainMenuState.hpp"
#include "Player.hpp"
#include "LevelExit.hpp"
#include "Shadow.hpp"
#include "Light.hpp"
#include "Guard.hpp"
#include "KeyPickup.hpp"
#include "UI.hpp"

#pragma warning(disable : 4018)
class GameOverState;
class GameState2 : public AbstractState
{
public:
	GameState2(StateManager& state_manager);
	~GameState2();

	void pause() override final;
	void resume() override final;
	void update(const sf::Time& delta) override final;
	
	void render() override final;
	void handle_input(const sf::Time& delta) override final;
	void handle_state_changes();
	void cleanup_game();

	void savePlayerInfo(const char* filename);
	void readPlayerInfo(const char* filename);
	void LoadGame(Player& player, Guard& guards, Light& lights);

	sf::Vector2i getLoadPlayerPos() const { return player_pos; }
	void setLoadPlayerPosX(int ps_x){ player_pos.x = ps_x; }
	void setLoadPlayerPosY(int ps_y){ player_pos.y = ps_y; }

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
	int rng(int min, int max);

	Player player_;
	Shadow shadow_;
	UI userInter_1;
	KeyPickup key1_;
	LevelExit exit_;
	bool game_over_;
	bool next_Level;

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


	int floor_x;
	sf::Vector2i player_pos;
	bool door_unlocked;
	std::vector<sf::Vector2i> guard_pos;

	sf::Vector2f mouse_pos;
};

#endif