#include "GameOverState.hpp"
#include "MainMenuState.hpp"
#include "Guard.hpp"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 985

GameOverState::GameOverState(StateManager& state_manager) : // constructor
AbstractState(state_manager)
{
	view_main.setSize(sf::Vector2f(1200, 960));
	view_main.setCenter(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	// zoom the view relatively to its current size (apply a factor 0.5, so its final size is 600x400)
	view_main.zoom(1.0f);
	// define a centered viewport, with half the size of the window
	view_main.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));



	end_level_ = BASS_SampleLoad(FALSE, "Sounds/bottle_x.wav", 0, 0, 1, NULL);
	main_channel_ = BASS_SampleGetChannel(end_level_, FALSE);
	BASS_ChannelSetAttribute(main_channel_, BASS_ATTRIB_VOL, 0.2f);

	if (!font.loadFromFile("vahikai.ttf"))
	{
		// error...
	}
	font.getLineSpacing(5);
	Gg_text.setFont(font);
	// set the character size
	Gg_text.setCharacterSize(40); // in pixels, not points!


	// set the color
	Gg_text.setColor(sf::Color::Yellow);

	// set the text style
	Gg_text.setStyle(sf::Text::Bold);



	if (!GO_background.loadFromFile("BackGrounds/GO_background.png"))
	{
		std::cout << "Could not load image\n";
	}

	GO_bg_sprite.setTexture(GO_background);
}

GameOverState::~GameOverState() // Destructor for the GameOver State
{

}

void GameOverState::handle_state_changes() // all changes in the states are done in here
{

}

void GameOverState::update(const sf::Time& delta) // update for class
{

}

void GameOverState::pause() // pause method 
{
	set_paused(true);
}

void GameOverState::resume() // resume method
{
	set_paused(false);
}
void GameOverState::handle_input(const sf::Time& delta) // handling the input in the GameOver State
{
	auto& inputManager = state_manager_.get_input_manager();

	if (inputManager.is_key_released(InputKey::escape))
	{
		state_manager_.quit();
	}
	if (inputManager.is_key_released(InputKey::return_key))
	{
		//BASS_ChannelPlay(main_channel_, FALSE);
		state_manager_.change_state(state_manager_.state_ptr<MainMenuState>(false));
	}
}
void GameOverState::render()// rendering the game over state
{

	sf::RenderWindow& window = state_manager_.get_render_window();
	window.setView(view_main); // applying the view
	window.draw(GO_bg_sprite);
	std::string GameOver_txt_ = "Game Over, press 'Return' to go back to main menu.\n Or press Escape to Quit.";

	Gg_text.setString(GameOver_txt_);
	Gg_text.setPosition(300, 700);
	window.draw(Gg_text);
}