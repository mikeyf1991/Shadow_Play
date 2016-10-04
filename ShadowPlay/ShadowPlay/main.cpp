#include "Common.hpp"
#include "StateManager.hpp" 
#include "MainMenuState.hpp"
#include "GameState.hpp"

int main(int argc, char* argv[])
{
	BASS_Init(-1, 44100, BASS_DEVICE_3D, NULL, NULL);
	BASS_SetVolume(0.2f);
	try
	{
		StateManager state_manager("ShadowPlay", 1280, 960);

		state_manager.change_state(state_manager.state_ptr<MainMenuState>(false));

		return state_manager.run();
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	BASS_Free();
}