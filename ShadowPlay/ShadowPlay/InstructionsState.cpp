#include "InstructionsState.hpp"
#include "MainMenuState.hpp" 
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 985

InstructionsState::InstructionsState(StateManager& state_manager) :
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

	if (!Instruct_screen[1].loadFromFile("Instructions_1.png"))
	{
		std::cout << "Could not load first image\n";
	}
	if (!Instruct_screen[2].loadFromFile("Instructions_2.png"))
	{
		std::cout << "Could not load second image\n";
	}
	if (!Instruct_screen[3].loadFromFile("Instructions_3.png"))
	{
		std::cout << "Could not load third image\n";
	}





	if (screen_no_ == 1)
		instruct_bg_sprite[1].setTexture(Instruct_screen[1]);

	if (screen_no_ == 2)
		instruct_bg_sprite[2].setTexture(Instruct_screen[2]);

	if (screen_no_ == 3)
		instruct_bg_sprite[3].setTexture(Instruct_screen[3]);

}

InstructionsState::~InstructionsState()
{

}

void InstructionsState::handle_state_changes()
{

}

void InstructionsState::update(const sf::Time& delta)
{

}

void InstructionsState::pause()
{
	set_paused(true);
}

void InstructionsState::resume()
{
	set_paused(false);
}
void InstructionsState::handle_input(const sf::Time& delta)
{
	auto& state_current = state_manager_;
	auto& inputManager = state_manager_.get_input_manager();

	if (inputManager.is_key_released(InputKey::escape))
	{
		state_current.change_state(state_manager_.state_ptr<MainMenuState>(false));
	}


	if (inputManager.is_key_released(InputKey::left))
	{
		if (screen_no_ != 1)
		{
			screen_no_ -= 1;
			instruct_bg_sprite[screen_no_].setTexture(Instruct_screen[screen_no_]);
		}
		else
			std::cout << "already at screen 1" << std::endl;
	}
	if (inputManager.is_key_released(InputKey::right))
	{
		if (screen_no_ != 3)
		{
			screen_no_ += 1;
			instruct_bg_sprite[screen_no_].setTexture(Instruct_screen[screen_no_]);
		}
		else
			std::cout << "already at screen: " << screen_no_ << std::endl;
	}

}
void InstructionsState::render()
{

	sf::RenderWindow& window = state_manager_.get_render_window();
	window.setView(view_main); // applying the view
	window.draw(instruct_bg_sprite[screen_no_]);


}