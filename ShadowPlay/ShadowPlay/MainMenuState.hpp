#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include "Common.hpp"
#include "AbstractState.hpp"
#include "Player.hpp"
#include"Light.hpp"
#include "Guard.hpp"


enum class HUD_ID {
	NEW_GAME,
	LOAD_GAME,
	INSTRUCTIONS,
	HIGH_SCORE,
	QUIT
};
class GameState;
class HighScoresState;
class InstructionsState;
class MainMenuState : public AbstractState // This is thegame over state, this extends from the AbstractState class.
{
public:
	MainMenuState(StateManager& state_manager, bool playedgame);
	~MainMenuState();
	void pause() override final;
	void resume() override final;
	void update(const sf::Time& delta) override final;
	void render() override final;
	void handle_input(const sf::Time& delta) override final;
	void handle_state_changes();
	void imageDraw(sf::Sprite thissprite, sf::Texture thistexture);
	void cleanup_game();

private:

	HSAMPLE new_game_sound_;
	HCHANNEL main_channel_;

	sf::View view_main;

	sf::Texture Menu_background;
	sf::Sprite Menu_bg_sprite;

	sf::Texture MainMenuButton[11];
	sf::Sprite Menu_Button_SpriteNG1;//NEW GAME
	sf::Sprite Menu_Button_SpriteNG2;//NEW GAME HOVER

	sf::Sprite Menu_Button_SpriteLG1;//LOAD GAME LOCKED
	sf::Sprite Menu_Button_SpriteLG2;//LOAD GAME
	sf::Sprite Menu_Button_SpriteLG3;//LOAD GAME HOVER

	sf::Sprite Menu_Button_SpriteIS1;//INSTRUCTIONS
	sf::Sprite Menu_Button_SpriteIS2;//INSTRUCTIONS HOVER

	sf::Sprite Menu_Button_SpriteHS1;//HIGHSCORES
	sf::Sprite Menu_Button_SpriteHS2;//HIGHSCORES HOVER

	sf::Sprite Menu_Button_SpriteQG1; //QUIT GAME
	sf::Sprite Menu_Button_SpriteQG2; //QUIT GAME HOVER
	sf::Text HUD_Text[5];
	sf::Font font;
	StateManager* this_state_manager;

	bool change_ng;
	bool change_lg;
	bool change_is;
	bool change_hs;
	bool change_quit;
	bool played_;
	bool keeptrackplayed;

	bool new_game_highlight_;
	bool load_game_highlight_;
	bool instructions_highlight_;
	bool highscores_highlight_;
	bool quit_highlight_;
};

#endif