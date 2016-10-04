#include "StateManager.hpp"
#include "AbstractState.hpp"

StateManager::StateManager(std::string window_title, int window_width, int window_height) : // Constructor
running_(true),
time_per_frame_(sf::seconds(1.0f / 60.0f)),
render_window_(sf::VideoMode(window_width, window_height), window_title),
input_manager_((render_window_))
{
	setregionWidth(window_width);
	setregionHeight(window_height);
}

StateManager::~StateManager() // destructor
{
	while (!states_.empty())
	{
		states_.pop();
	}
}

void StateManager::change_state(std::unique_ptr<AbstractState> state) // changing the state method
{
	while (!states_.empty())
	{
		states_.pop();
	}

	states_.push(std::move(state));
}

void StateManager::push_state(std::unique_ptr<AbstractState> state) // pushing the state in the stack
{
	if (!states_.empty())
	{
		states_.top()->pause();
	}

	states_.push(std::move(state));
}

void StateManager::pop_state() // popping the state from the stack
{
	if (!states_.empty())
	{
		states_.pop();
	}

	if (!states_.empty())
	{
		states_.top()->resume();
	}
}

int StateManager::run() // running each individual state
{
	sf::Clock clock;
	sf::Time time_since_last_update = sf::Time::Zero;
	while (is_running())
	{
		sf::Time elapsed_time = clock.restart();
		time_since_last_update += elapsed_time;
		while (time_since_last_update > time_per_frame_)
		{
			time_since_last_update -= time_per_frame_;

			handle_input(time_per_frame_);
			update(time_per_frame_);
		}
		render();
		handle_state_changes();
	}

	return (int)return_codes::success;
}

void StateManager::handle_input(const sf::Time& delta) // handle the input within the state
{
	if (!states_.empty())
	{
		//input_manager_.setRegionSize();
		input_manager_.update();
		if (!states_.top()->get_paused())
		{
			states_.top()->handle_input(delta);
		}
	}
}

void StateManager::update(const sf::Time& delta) // update the current state
{
	if (!states_.empty())
	{
		if (!states_.top()->get_paused())
		{
			states_.top()->update(delta);
		}
	}
}

void StateManager::render() //render the current state
{
	if (!states_.empty())
	{
		render_window_.clear();
		if (!states_.top()->get_paused())
		{
			states_.top()->render();
		}
		render_window_.display();
	}
}

void StateManager::handle_state_changes() // Handle the changes to the current State
{
	if (!states_.empty())
	{
		if (!states_.top()->get_paused())
		{
			states_.top()->handle_state_changes();
		}
	}
}