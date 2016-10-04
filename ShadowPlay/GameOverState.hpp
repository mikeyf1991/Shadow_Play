#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include "Common.hpp"

#include "AbstractState.hpp"
#include "Player.hpp"
#include "LevelExit.hpp"
#include "Shadow.hpp"
#include "Light.hpp"


class Guard;
class MainMenuState;
//------------------------------------------------ Game over State --------------------------------------------------------------
class GameOverState : public AbstractState // This is thegame over state, this extends from the AbstractState class.
{
public:
	GameOverState(StateManager& state_manager); // constructor
	~GameOverState();//destructor

	void pause() override final;
	void resume() override final;
	void update(const sf::Time& delta) override final;
	void render() override final;
	void handle_input(const sf::Time& delta) override final;
	void handle_state_changes();

	void imageDraw(sf::Sprite thissprite, sf::Texture thistexture);
	void cleanup_game();
private:
	//variables in here
	HSAMPLE end_level_;
	HCHANNEL main_channel_;

	sf::View view_main;

	sf::Texture GO_background;
	sf::Sprite GO_bg_sprite;
	sf::Text Gg_text;
	sf::Font font;
};
//--------------------------------------------------------------------------------------------------------------------------------------------
#endif