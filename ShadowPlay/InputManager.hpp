#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include "Common.hpp"
#include "InputKey.hpp"
#pragma warning(disable : 4244)

class StateManager;
//---------------------------------The Input manager class---------------------------
class InputManager
{
public:
	InputManager(sf::Window& window);
	void recolab();
	void update();

	//-----------methods for mouse controls----------------
	inline const bool left_clicked() const
	{
		return left_click_;
	}

	inline const bool right_clicked() const
	{
		return right_click_;
	}
	//----------------------------------------------------
	//------------Check for Key press and Release---------
	inline const bool is_key_released(int key) const
	{
		return key_released_[key];
	}

	inline const bool is_key_pressed(int key) const
	{
		return key_pressed_[key];
	}
	//---------------------------------------------------
	//----------- Methods for getting the Mouse Positions------------
	int get_mouse_x() const
	{
		return mouse_x_;
	}

	int get_mouse_y() const
	{
		return mouse_y_;
	}
	//-----------------------------------------------------------------
	void setRegionSize();//this sets the region size for the camera
	

	void setLevelSize(int lw, int lh); // gets the size of the level

	void setwindowSize(int ww, int wh); // set the window size

	float mousecal_x();
	float mousecal_y();

	void giveStateManager(StateManager * mgr); // this allows us to make sure -regardless of the level sizes- the mouse works


private:
	//---------------------Variables-----------------
	sf::Window& window_;
	StateManager * stateManager;
	bool key_released_[sf::Keyboard::KeyCount];
	bool key_pressed_[sf::Keyboard::KeyCount];

	bool left_click_;
	bool right_click_;

	float mouse_x_;
	float mouse_y_;

	void initialise();
	void reset();

	int regionwidth;
	int regionheight;

	int windowwidth;
	int windowheight;

	int levelWidth;
	int levelHeight;
	//--------------------------------------------
};
//------------------------------------------------------------------------------
#endif