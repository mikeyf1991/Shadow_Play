#ifndef INSTRUCTIONSSTATE_HPP
#define INSTRUCTIONSSTATE_HPP

#include "Common.hpp"
#include "AbstractState.hpp"
class MainMenuState;
class InstructionsState : public AbstractState // This is thegame over state, this extends from the AbstractState class.
{
public:
	InstructionsState(StateManager& state_manager);
	~InstructionsState();

	void pause() override final;
	void resume() override final;
	void update(const sf::Time& delta) override final;
	void render() override final;
	void handle_input(const sf::Time& delta) override final;
	void handle_state_changes();

	void imageDraw(sf::Sprite thissprite, sf::Texture thistexture);
	void cleanup_game();
private:

	sf::View view_main;
	int screen_no_;
	sf::Texture Instruct_screen[4];
	sf::Sprite instruct_bg_sprite[4];

	sf::Text text;
	sf::Font font;
};

#endif