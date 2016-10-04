#include "HighScoresState.hpp"
#include "MainMenuState.hpp"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 985

HighScoresState::HighScoresState(StateManager& state_manager) : // constructor
AbstractState(state_manager)
{
	view_main.setSize(sf::Vector2f(1200, 960));
	view_main.setCenter(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));

	// zoom the view relatively to its current size (apply a factor 0.5, so its final size is 600x400)
	view_main.zoom(1.0f);

	// define a centered viewport, with half the size of the window
	view_main.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));
	screen_no_ = 1;

	if (!font.loadFromFile("vahikai.ttf"))
	{
		std::cout << "HELP" << std::endl;
		std::cin.get();
	}

	font.getLineSpacing(5);

	if (!HS_background_.loadFromFile("BackGrounds/Credits Screen-01.png"))
	{
		std::cout << "Could not load image\n";
	}

	HS_bg_sprite_.setTexture(HS_background_);
}
HighScoresState::~HighScoresState(){} // destructor
void HighScoresState::handle_state_changes() // Handles all of the state changes
{}
void HighScoresState::update(const sf::Time& delta)//update for the state
{}
void HighScoresState::pause()//pause the state
{ 
	set_paused(true); 
}
void HighScoresState::resume()//resume the state
{ 
	set_paused(false); 
}

void HighScoresState::handle_input(const sf::Time& delta)// handle the input within the state
{
	auto& state_current = state_manager_;
	auto& inputManager = state_manager_.get_input_manager();

	if (inputManager.is_key_released(InputKey::escape))
	{
		state_current.change_state(state_manager_.state_ptr<MainMenuState>(false));
	}
}
void HighScoresState::render() // render the state
{

	sf::RenderWindow& window = state_manager_.get_render_window();
	window.setView(view_main); // applying the view
	window.draw(HS_bg_sprite_);


}