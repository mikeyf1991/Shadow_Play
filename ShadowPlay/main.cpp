#include "Common.hpp"
#include "StateManager.hpp" 
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "GameState2.hpp"
#include "GameState3.hpp"
int main(int argc, char* argv[]) // The main loop of ShadowPlay
{
	BASS_Init(-1, 44100, BASS_DEVICE_3D, NULL, NULL); // Initialise BASS
	BASS_SetVolume(0.2f);
	try
	{
		StateManager state_manager("ShadowPlay", 1280, 960); // make a window of the size 1280 x 960

		state_manager.change_state(state_manager.state_ptr<MainMenuState>(false)); // set the initial state to Main Menu state

		return state_manager.run(); // run the main menu state
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	BASS_Free(); // stop the BASS music and sounds
}
