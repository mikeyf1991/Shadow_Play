#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "HighScoresState.hpp"
#include "InstructionsState.hpp"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960

MainMenuState::MainMenuState(StateManager& state_manager, bool playedgame) :
AbstractState(state_manager)
{
	view_main.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	view_main.setCenter(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));

	// zoom the view relatively to its current size (apply a factor 0.5, so its final size is 600x400)
	view_main.zoom(1.0f);

	// define a centered viewport, with half the size of the window
	view_main.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));

	if (!Menu_background.loadFromFile("MM_background.png"))
	{
		std::cout << "Could not load image\n";
	}
	else
		std::cout << "Menu Image Loaded..." << std::endl;

	Menu_bg_sprite.setTexture(Menu_background);

	MainMenuButton[0].loadFromFile("New_GameNOT.png");
	MainMenuButton[1].loadFromFile("New_GameYES.png");
	MainMenuButton[2].loadFromFile("Load_GameLOCKED.png");
	MainMenuButton[3].loadFromFile("Load_GameNOT.png");
	MainMenuButton[4].loadFromFile("Load_GameYES.png");
	MainMenuButton[5].loadFromFile("InstructNOT.png");
	MainMenuButton[6].loadFromFile("InstructYES.png");
	MainMenuButton[7].loadFromFile("HighScoresNOT.png");
	MainMenuButton[8].loadFromFile("HighScoresYES.png");
	MainMenuButton[9].loadFromFile("QuitNOT.png");
	MainMenuButton[10].loadFromFile("QuitYES.png");


	Menu_Button_SpriteNG1.setTexture(MainMenuButton[0]);
	Menu_Button_SpriteNG1.setPosition(400, 500);
	Menu_Button_SpriteNG2.setTexture(MainMenuButton[1]);
	Menu_Button_SpriteNG2.setPosition(400, 500);

	Menu_Button_SpriteLG1.setTexture(MainMenuButton[2]);
	Menu_Button_SpriteLG1.setPosition(700, 500);
	Menu_Button_SpriteLG2.setTexture(MainMenuButton[3]);
	Menu_Button_SpriteLG2.setPosition(700, 500);
	Menu_Button_SpriteLG3.setTexture(MainMenuButton[4]);
	Menu_Button_SpriteLG3.setPosition(700, 500);

	Menu_Button_SpriteIS1.setTexture(MainMenuButton[5]);
	Menu_Button_SpriteIS1.setPosition(400, 600);
	Menu_Button_SpriteIS2.setTexture(MainMenuButton[6]);
	Menu_Button_SpriteIS2.setPosition(400, 600);

	Menu_Button_SpriteHS1.setTexture(MainMenuButton[7]);
	Menu_Button_SpriteHS1.setPosition(700, 600);
	Menu_Button_SpriteHS2.setTexture(MainMenuButton[8]);
	Menu_Button_SpriteHS2.setPosition(700, 600);

	Menu_Button_SpriteQG1.setTexture(MainMenuButton[9]);
	Menu_Button_SpriteQG1.setPosition(550, 700);
	Menu_Button_SpriteQG2.setTexture(MainMenuButton[10]);
	Menu_Button_SpriteQG2.setPosition(550, 700);

	new_game_sound_ = BASS_SampleLoad(FALSE, "lets_rock.wav", 0, 0, 1, NULL);
	main_channel_ = BASS_SampleGetChannel(new_game_sound_, FALSE);
	BASS_ChannelSetAttribute(main_channel_, BASS_ATTRIB_VOL, 0.3f);
	if (playedgame == false)
		played_ = false;
	else
		played_ = true;

	new_game_highlight_ = false;
	load_game_highlight_ = false;
	instructions_highlight_ = false;
	highscores_highlight_ = false;
	quit_highlight_ = false;


	change_ng = false;
	change_lg = false;
	change_is = false;
	change_hs = false;
	change_quit = false;
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::handle_state_changes()
{
	auto& state_current = state_manager_;
	if (change_ng == true)
	{
		state_current.change_state(state_manager_.state_ptr<GameState>(false));
	}
	else
		if (change_lg == true)
			state_current.change_state(state_manager_.state_ptr<GameState>(true));
		else
			if (change_is == true)
				state_current.change_state(state_manager_.state_ptr<InstructionsState>());
			else
				if (change_hs == true)
					state_current.change_state(state_manager_.state_ptr<HighScoresState>());
				else
					if (change_quit == true)
						state_manager_.quit();
}

void MainMenuState::update(const sf::Time& delta)
{

}

void MainMenuState::pause()
{
	set_paused(true);
}

void MainMenuState::resume()
{
	set_paused(false);
}
void MainMenuState::handle_input(const sf::Time& delta)
{

	auto inputManager = state_manager_.get_input_manager();

	inputManager.giveStateManager(&state_manager_);
	inputManager.setRegionSize();
	inputManager.setwindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);  //should be lwvel not window will change it later ;-)

	if (inputManager.is_key_released(InputKey::escape) || inputManager.is_key_released(InputKey::q))
	{
		state_manager_.quit();
	}
	if (inputManager.is_key_released(InputKey::n))
	{
		BASS_ChannelPlay(main_channel_, FALSE);


	}
	if (inputManager.is_key_released(InputKey::l))
	{
		//readPlayerInfo("Save_Info.xml");
		change_lg = true;
	}
	if (inputManager.is_key_released(InputKey::i))
	{
		change_is = true;
	}
	if (inputManager.is_key_released(InputKey::h))
	{
		change_hs = true;
	}

	if (new_game_highlight_ == true)
	{
		if (inputManager.left_clicked())
		{
			change_ng = true;
			played_ = true;
		}
	}
	else
		if (load_game_highlight_ == true)
		{
			if (played_ == true)
			{
				if (inputManager.left_clicked())
					change_lg = true;
			}
		}
		else
			if (instructions_highlight_ == true)
			{
		if (inputManager.left_clicked())
			change_is = true;
			}
			else
				if (highscores_highlight_ == true)
				{
		if (inputManager.left_clicked())
			change_hs = true;
				}
				else
					if (quit_highlight_ == true)
					{
		if (inputManager.left_clicked())
			change_quit = true;
					}
	sf::Vector2f mouse_pos;


	mouse_pos.x = inputManager.get_mouse_x();
	mouse_pos.y = inputManager.get_mouse_y();

	std::cout << "\nmouse X" << mouse_pos.x;
	std::cout << "\nmouse Y" << mouse_pos.y;

	if (Menu_Button_SpriteNG1.getGlobalBounds().contains(mouse_pos))
		new_game_highlight_ = true;
	else
		new_game_highlight_ = false;


	if (Menu_Button_SpriteLG1.getGlobalBounds().contains(mouse_pos))
		load_game_highlight_ = true;
	else
		load_game_highlight_ = false;


	if (Menu_Button_SpriteIS1.getGlobalBounds().contains(mouse_pos))
		instructions_highlight_ = true;
	else
		instructions_highlight_ = false;


	if (Menu_Button_SpriteHS1.getGlobalBounds().contains(mouse_pos))
		highscores_highlight_ = true;
	else
		highscores_highlight_ = false;

	if (Menu_Button_SpriteQG1.getGlobalBounds().contains(mouse_pos))
		quit_highlight_ = true;
	else
		quit_highlight_ = false;
}
void MainMenuState::render()
{

	sf::RenderWindow& window = state_manager_.get_render_window();
	window.setView(view_main); // applying the view
	window.draw(Menu_bg_sprite);

	if (new_game_highlight_ == false)
		window.draw(Menu_Button_SpriteNG1);
	else
		window.draw(Menu_Button_SpriteNG2);
	if (played_ == false)
	{
		window.draw(Menu_Button_SpriteLG1);
	}
	else 
		if (played_ == true && load_game_highlight_ == false)
		window.draw(Menu_Button_SpriteLG2);
	else 
		if (played_ == true && load_game_highlight_ == true)
		window.draw(Menu_Button_SpriteLG3);

	if (instructions_highlight_ == false)
		window.draw(Menu_Button_SpriteIS1);
	else
		window.draw(Menu_Button_SpriteIS2);

	if (highscores_highlight_ == false)
		window.draw(Menu_Button_SpriteHS1);
	else
		window.draw(Menu_Button_SpriteHS2);
	if (quit_highlight_ == false)
		window.draw(Menu_Button_SpriteQG1);
	else
		window.draw(Menu_Button_SpriteQG2);
}