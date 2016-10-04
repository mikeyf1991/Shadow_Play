#include "InputManager.hpp"

#include "StateManager.hpp"

InputManager::InputManager(sf::Window& window) : // Constructor for the input manager class
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

void InputManager::initialise() // initialising the class
{
	left_click_ = false;
	right_click_ = false;

	for (int i = 0; i < InputKey::key_count; ++i)
	{
		key_released_[i] = false;
		key_pressed_[i] = false;
	}
}
void InputManager::giveStateManager(StateManager * mgr) // method for setting the current state up for the mouse
{
	stateManager = mgr;
}

void InputManager::setRegionSize() // setting the region size with the defined camera width and height in each level
{
	if (stateManager == NULL) {
		std::cout << "I havent got the statemanager yet" << std::endl;
	}
	else {
		regionwidth = stateManager->getregionWidth();
		regionheight = stateManager->getregionHeight();
	}
}

void InputManager::setwindowSize(int ww, int wh) //setting up the window size
{
	windowwidth = ww;
	windowheight = wh;
}

float InputManager::mousecal_x() // calculating the mouse X
{
	if (regionwidth != 0)
		return (float)(windowwidth / regionwidth);
	else
		return 1.0f;
}

float InputManager::mousecal_y() // calculating the mouse Y
{
	if (regionheight != 0)
		return (float)(windowheight / regionheight);
	else
		return 1.0f;
}


void InputManager::reset() // reset for the input manager
{
	for (int i = 0; i < InputKey::key_count; ++i)
	{
		key_released_[i] = false;
	}
}

void InputManager::setLevelSize(int lw, int lh) // setting up the level size of the window
{
	levelWidth = lw;
	levelHeight = lh;
}

void InputManager::update() // the update method for the Input Manager 
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


