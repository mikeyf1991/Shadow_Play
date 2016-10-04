#ifndef HIGHSCORESSTATE_HPP
#define HIGHSCORESSTATE_HPP

#include "Common.hpp"
#include "AbstractState.hpp"


class MainMenuState;
//-------------------------------------HighScores State---------------------------------------------------------------
class HighScoresState : public AbstractState // This is the highscore state, this extends from the AbstractState class.
{
public:
	HighScoresState(StateManager& state_manager);//constructor
	~HighScoresState();//destructor

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
	sf::View view_main;
	int screen_no_;
	sf::Texture HS_background_;
	sf::Sprite HS_bg_sprite_;

	sf::Text text;
	sf::Font font;
};
//----------------------------------------------------------------------------------------------------------------------
#endif