#include "InputManager.hpp"

#include "StateManager.hpp"

InputManager::InputManager(sf::Window& window) :
window_(window),
left_click_(false),
right_click_(false),
mouse_x_(0),
mouse_y_(0)
{
	stateManager = NULL;
	initialise();

	windowheight = 0;
	windowwidth = 0;
	regionheight = 0;
	regionwidth = 0;
}

void InputManager::initialise()
{
	left_click_ = false;
	right_click_ = false;

	for (int i = 0; i < InputKey::key_count; ++i)
	{
		key_released_[i] = false;
		key_pressed_[i] = false;
	}
}
void InputManager::giveStateManager(StateManager * mgr)
{
	stateManager = mgr;
}

void InputManager::setRegionSize()
{
	if (stateManager == NULL) {
		std::cout << "I havent got the statemanager yet" << std::endl;
	}
	else {
		regionwidth = stateManager->getregionWidth();
		regionheight = stateManager->getregionHeight();
	}
}

void InputManager::setwindowSize(int ww, int wh)
{
	windowwidth = ww;
	windowheight = wh;
}

float InputManager::mousecal_x()
{
	if (regionwidth != 0)
		return (float)(windowwidth / regionwidth);
	else
		return 1.0f;
}

float InputManager::mousecal_y()
{
	if (regionheight != 0)
		return (float)(windowheight / regionheight);
	else
		return 1.0f;
}


void InputManager::reset()
{
	for (int i = 0; i < InputKey::key_count; ++i)
	{
		key_released_[i] = false;
	}
}

void InputManager::setLevelSize(int lw, int lh)
{
	levelWidth = lw;
	levelHeight = lh;
}

void InputManager::update()
{
	reset();

	sf::Event event;

	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window_.close();
		}

		if (event.type == sf::Event::KeyPressed)
		{
			for (int i = 0; i < key_count; ++i)
			{
				if (event.key.code == i)
				{
					key_pressed_[i] = true;
				}
			}
		}

		if (event.type == sf::Event::KeyReleased)
		{
			for (int i = 0; i < key_count; ++i)
			{
				if (event.key.code == i)
				{
					key_pressed_[i] = false;
					key_released_[i] = true;
				}
			}
		}
	}

	left_click_ = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	right_click_ = sf::Mouse::isButtonPressed(sf::Mouse::Right);

	mouse_x_ = sf::Mouse::getPosition(window_).x;
	mouse_y_ = sf::Mouse::getPosition(window_).y;
}


