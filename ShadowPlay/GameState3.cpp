#include "GameState3.hpp"
#include "GameOverState.hpp"


#define TIER_HEIGHT 319
#define TIER_WIDTH 960
#define LEVEL_WIDTH 1820
#define LEVEL_HEIGHT 4 * TIER_HEIGHT
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960
#define FLOOR_OFFSET 5
/********************************** CONSTRUCTOR FOR LEVEL 3, CHECKS IF LOAD GAME OR NOT & INITIALIZES ALL OBJECTS *************************************/
GameState3::GameState3(StateManager& state_manager, bool loadFromFile) : AbstractState(state_manager, loadFromFile),
player_(sf::Vector2f(25, 885), sf::Vector2f(120, 100), sf::Color::Transparent),
exit_(sf::Vector2f(1650, 160), sf::Vector2f(64, 100), sf::Color::Black),
key1_(sf::Vector2f(100, 0), sf::Vector2f(46, 100), sf::Color::Blue),
shadow_(sf::Vector2f(0, 0), sf::Vector2f(120, 100), sf::Color::Transparent),
switch1_(sf::Vector2f(340, 885), sf::Vector2f(43.2, 100), sf::Color::Yellow, 0),
switch2_(sf::Vector2f(1700, 885), sf::Vector2f(43.2, 100), sf::Color::Yellow, 0),
destroyable_wall1_(sf::Vector2f(1100, 600), sf::Vector2f(50, TIER_HEIGHT - FLOOR_OFFSET * 3), sf::Color::Transparent),
destroyable_wall2_(sf::Vector2f(240, 900), sf::Vector2f(50, TIER_HEIGHT - FLOOR_OFFSET * 3), sf::Color::Transparent),
undestroyable_wall1_(sf::Vector2f(850, 100), sf::Vector2f(50, TIER_HEIGHT - FLOOR_OFFSET * 3), sf::Color::Transparent),
undestroyable_wall2_(sf::Vector2f(450, 600), sf::Vector2f(50, TIER_HEIGHT - FLOOR_OFFSET * 3), sf::Color::Transparent),
undestroyable_wall3_(sf::Vector2f(800, 300), sf::Vector2f(50, TIER_HEIGHT - FLOOR_OFFSET * 3), sf::Color::Transparent)
{
	setMusicState(false);
	if (getMusicState() == true)
	{
		BASS_ChannelStop(Bg_music_);
		setMusicState(false);
	}
	if (load_game_ == true)
	{
		readPlayerInfo("Save_Info.xml");
		//==========================================================================================================================================================//
		//----------------------------- set the y positions of the object using the new y method -------------------------------------------------------------------//
		player_.Shape().setPosition(getLoadPlayerPos().x, getLoadPlayerPos().y);
		switch1_.Shape().setPosition(switch1_.Shape().getPosition().x, switch1_.set_Ypos(LEVEL_HEIGHT, 0, TIER_HEIGHT, FLOOR_OFFSET));

		destroyable_wall1_.Shape().setPosition(destroyable_wall1_.Shape().getPosition().x, destroyable_wall1_.set_Ypos(LEVEL_HEIGHT, 2, TIER_HEIGHT, FLOOR_OFFSET));
		destroyable_wall1_.spriteImage.setPosition(destroyable_wall1_.Shape().getPosition().x - destroyable_wall1_.Shape().getSize().x / 2, destroyable_wall1_.Shape().getPosition().y - destroyable_wall1_.Shape().getSize().y / 2 - 5);

		undestroyable_wall1_.Shape().setPosition(undestroyable_wall1_.Shape().getPosition().x, undestroyable_wall1_.set_Ypos(LEVEL_HEIGHT, 2, TIER_HEIGHT, FLOOR_OFFSET));
		undestroyable_wall1_.spriteImage2.setPosition(undestroyable_wall1_.Shape().getPosition().x - undestroyable_wall1_.Shape().getSize().x / 2, undestroyable_wall1_.Shape().getPosition().y - undestroyable_wall1_.Shape().getSize().y / 2 - 5);

		switch1_.spriteImage.setPosition(switch1_.Shape().getPosition().x - switch1_.Shape().getSize().x / 2, switch1_.Shape().getPosition().y - switch1_.Shape().getSize().y - 40);
		switch1_.spriteImage2.setPosition(switch1_.Shape().getPosition().x - switch1_.Shape().getSize().x / 2, switch1_.Shape().getPosition().y - switch1_.Shape().getSize().y - 20);
		exit_.Shape().setPosition(exit_.Shape().getPosition().x, exit_.set_Ypos(LEVEL_HEIGHT, 2, TIER_HEIGHT, FLOOR_OFFSET));
		exit_.spriteImage.setPosition(exit_.Shape().getPosition().x - exit_.Shape().getSize().x / 2, exit_.Shape().getPosition().y);
		//==========================================================================================================================================================//
		create_lights();
		create_guards();
		guards_[0]->Shape().setPosition(getLoadGuard1Pos().x, getLoadGuard1Pos().y);
		guards_[1]->Shape().setPosition(getLoadGuard2Pos().x, getLoadGuard2Pos().y);

		userInter_1.init(view_main);
		//key1_.setPositionX(480);
		//key1_.setPositionY(key1_.set_Ypos(LEVEL_HEIGHT, 1, TIER_HEIGHT, FLOOR_OFFSET));
		key1_.setPickupedUpState(getLoadDoorState());
		game_over_ = false;
		next_Level = false;
		change_MM = false;
		player_caught = false;
		player_.setLevelNumber(getLevelNumber());

		floor_sprite.resize(14); // SET THIS TO THE NO OF FLOORS

		view_main.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
		view_main.setCenter(sf::Vector2f(player_.Shape().getPosition().x, player_.Shape().getPosition().y));
		// zoom the view relatively to its current size (apply a factor 0.5, so its final size is 600x400)
		view_main.zoom(1.0f);
		// define a centered viewport, with half the size of the window
		view_main.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));

		if (!font.loadFromFile("vahikai.ttf"))
		{
			// error...
		}
		font.getLineSpacing(5);
		teleport_text.setFont(font);
		// set the character size
		teleport_text.setCharacterSize(40); // in pixels, not points!


		// set the color
		teleport_text.setColor(sf::Color::White);

		// set the text style
		teleport_text.setStyle(sf::Text::Regular);

		if (!floor.loadFromFile("BackGrounds/floor2.png"))
		{
			std::cout << "Could not load image\n";
		}
		int i = 0;
		int j = 0;
		floor_x = 0;
		for (auto& f_sprite : floor_sprite)
		{
			f_sprite.setTexture(floor);
			f_sprite.setPosition(f_sprite.getPosition().x, LEVEL_HEIGHT - (floor.getSize().y + (i * TIER_HEIGHT)));
			i++;
			if (f_sprite.getPosition().y + floor.getSize().y / 2 >= LEVEL_HEIGHT)
			{
				float current_x = floor_sprite[j].getPosition().x;
				f_sprite.setPosition(current_x + floor.getSize().x, floor_sprite[j].getPosition().y);
				j++;
			}
		}
		good_job_ = BASS_SampleLoad(FALSE, "Sounds/nextlevel.wav", 0, 0, 1, NULL);
		main_channel_ = BASS_SampleGetChannel(good_job_, FALSE);
		BASS_ChannelSetAttribute(main_channel_, BASS_ATTRIB_VOL, 0.4f);

		shufflesound = BASS_SampleLoad(FALSE, "Sounds/shufflesound.wav", 0, 0, 1, NULL);
		main_channel1_ = BASS_SampleGetChannel(shufflesound, FALSE);
		BASS_ChannelSetAttribute(main_channel1_, BASS_ATTRIB_VOL, 1.0f);

		gottagetKey = BASS_SampleLoad(FALSE, "Sounds/gottagetkey.wav", 0, 0, 1, NULL);
		main_channel2_ = BASS_SampleGetChannel(gottagetKey, FALSE);
		BASS_ChannelSetAttribute(main_channel2_, BASS_ATTRIB_VOL, 0.4f);

		leverPull = BASS_SampleLoad(FALSE, "Sounds/levelpull.wav", 0, 0, 1, NULL);
		main_channel3_ = BASS_SampleGetChannel(leverPull, FALSE);
		BASS_ChannelSetAttribute(main_channel3_, BASS_ATTRIB_VOL, 0.4f);

		switchSound = BASS_SampleLoad(FALSE, "Sounds/switchsound.wav", 0, 0, 1, NULL);
		main_channel4_ = BASS_SampleGetChannel(switchSound, FALSE);
		BASS_ChannelSetAttribute(main_channel4_, BASS_ATTRIB_VOL, 0.4f);

		Bg_music_ = BASS_StreamCreateFile(FALSE, "Sounds/main_game_music.mp3", 0, 0, BASS_SAMPLE_LOOP);

		BASS_ChannelSetAttribute(Bg_music_, BASS_ATTRIB_VOL, 0.1f);
		if (getMusicState() == false)
		{
			BASS_ChannelPlay(Bg_music_, FALSE);
			setMusicState(true);
		}
	}
	else
	{
		//==========================================================================================================================================================//
		//----------------------------- set the y positions of the object using the new y method -------------------------------------------------------------------//
		player_.Shape().setPosition(player_.Shape().getPosition().x, player_.set_Ypos(LEVEL_HEIGHT, 1, TIER_HEIGHT, FLOOR_OFFSET));

		destroyable_wall1_.Shape().setPosition(destroyable_wall1_.Shape().getPosition().x, destroyable_wall1_.set_Ypos(LEVEL_HEIGHT, 2, TIER_HEIGHT, FLOOR_OFFSET));
		destroyable_wall1_.spriteImage.setPosition(destroyable_wall1_.Shape().getPosition().x - destroyable_wall1_.Shape().getSize().x / 2,
			destroyable_wall1_.Shape().getPosition().y - destroyable_wall1_.Shape().getSize().y / 2 - 5);


		destroyable_wall2_.Shape().setPosition(destroyable_wall2_.Shape().getPosition().x, destroyable_wall2_.set_Ypos(LEVEL_HEIGHT, 2, TIER_HEIGHT, FLOOR_OFFSET));
		destroyable_wall2_.spriteImage.setPosition(destroyable_wall2_.Shape().getPosition().x - destroyable_wall2_.Shape().getSize().x / 2,
			destroyable_wall2_.Shape().getPosition().y - destroyable_wall2_.Shape().getSize().y / 2 - 5);


		undestroyable_wall1_.Shape().setPosition(undestroyable_wall1_.Shape().getPosition().x, undestroyable_wall1_.set_Ypos(LEVEL_HEIGHT, 3, TIER_HEIGHT, FLOOR_OFFSET));
		undestroyable_wall1_.spriteImage2.setPosition(undestroyable_wall1_.Shape().getPosition().x - undestroyable_wall1_.Shape().getSize().x / 2,
			undestroyable_wall1_.Shape().getPosition().y - undestroyable_wall1_.Shape().getSize().y / 2 - 5);

		undestroyable_wall2_.Shape().setPosition(undestroyable_wall2_.Shape().getPosition().x, undestroyable_wall2_.set_Ypos(LEVEL_HEIGHT, 2, TIER_HEIGHT, FLOOR_OFFSET));
		undestroyable_wall2_.spriteImage2.setPosition(undestroyable_wall2_.Shape().getPosition().x - undestroyable_wall2_.Shape().getSize().x / 2,
			undestroyable_wall2_.Shape().getPosition().y - undestroyable_wall2_.Shape().getSize().y / 2 - 5);

		undestroyable_wall3_.Shape().setPosition(undestroyable_wall3_.Shape().getPosition().x, undestroyable_wall3_.set_Ypos(LEVEL_HEIGHT, 1, TIER_HEIGHT, FLOOR_OFFSET));
		undestroyable_wall3_.spriteImage2.setPosition(undestroyable_wall3_.Shape().getPosition().x - undestroyable_wall3_.Shape().getSize().x / 2,
			undestroyable_wall3_.Shape().getPosition().y - undestroyable_wall3_.Shape().getSize().y / 2 - 5);

		switch1_.Shape().setPosition(switch1_.Shape().getPosition().x, switch1_.set_Ypos(LEVEL_HEIGHT, 2, TIER_HEIGHT, FLOOR_OFFSET));
		switch1_.spriteImage.setPosition(switch1_.Shape().getPosition().x - switch1_.Shape().getSize().x / 2, switch1_.Shape().getPosition().y - switch1_.Shape().getSize().y - 40);
		switch1_.spriteImage2.setPosition(switch1_.Shape().getPosition().x - switch1_.Shape().getSize().x / 2, switch1_.Shape().getPosition().y - switch1_.Shape().getSize().y - 20);
		switch1_.set_Pulled(false);

		switch2_.Shape().setPosition(switch2_.Shape().getPosition().x, switch2_.set_Ypos(LEVEL_HEIGHT, 0, TIER_HEIGHT, FLOOR_OFFSET));
		switch2_.spriteImage.setPosition(switch2_.Shape().getPosition().x - switch2_.Shape().getSize().x / 2, switch2_.Shape().getPosition().y - switch2_.Shape().getSize().y - 40);
		switch2_.spriteImage2.setPosition(switch2_.Shape().getPosition().x - switch2_.Shape().getSize().x / 2, switch2_.Shape().getPosition().y - switch2_.Shape().getSize().y - 20);
		switch2_.set_Pulled(false);

		exit_.Shape().setPosition(exit_.Shape().getPosition().x, exit_.set_Ypos(LEVEL_HEIGHT, 2, TIER_HEIGHT, FLOOR_OFFSET));
		exit_.spriteImage.setPosition(exit_.Shape().getPosition().x - exit_.Shape().getSize().x *1.5,
			exit_.Shape().getPosition().y - exit_.Shape().getSize().y * 2 - FLOOR_OFFSET * 4);
		//==========================================================================================================================================================//
		create_lights();
		for (auto& light : lights_image_)
		{
			if (light->draw_shadow() == false)
				shadow_.Shape().setPosition(player_.Shape().getPosition());
		}

		create_guards();
		userInter_1.init(view_main);

		key1_.Shape().setPosition(925, key1_.set_Ypos(LEVEL_HEIGHT, 3, TIER_HEIGHT, FLOOR_OFFSET));

		game_over_ = false;
		next_Level = false;
		change_MM = false;
		player_caught = false;
		shadow_.setCastState(false);

		player_.setLevelNumber(1);

		floor_sprite.resize(14); // SET THIS TO THE NO OF FLOORS

		view_main.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
		view_main.setCenter(sf::Vector2f(player_.Shape().getPosition().x, player_.Shape().getPosition().y));
		// zoom the view relatively to its current size (apply a factor 0.5, so its final size is 600x400)
		view_main.zoom(1.0f);
		// define a centered viewport, with half the size of the window
		view_main.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));

		if (!font.loadFromFile("vahikai.ttf"))
		{
			// error...
		}
		font.getLineSpacing(5);
		teleport_text.setFont(font);
		// set the character size
		teleport_text.setCharacterSize(40); // in pixels, not points!


		// set the color
		teleport_text.setColor(sf::Color::White);

		// set the text style
		teleport_text.setStyle(sf::Text::Regular);

		if (!floor.loadFromFile("BackGrounds/floor2.png"))
		{
			std::cout << "Could not load image\n";
		}
		int i = 0;
		int j = 0;
		floor_x = 0;
		for (auto& f_sprite : floor_sprite)
		{
			f_sprite.setTexture(floor);
			f_sprite.setPosition(f_sprite.getPosition().x, LEVEL_HEIGHT - (floor.getSize().y + (i * TIER_HEIGHT)));
			i++;
			if (f_sprite.getPosition().y + floor.getSize().y / 2 >= LEVEL_HEIGHT)
			{
				float current_x = floor_sprite[j].getPosition().x;
				f_sprite.setPosition(current_x + floor.getSize().x, floor_sprite[j].getPosition().y);
				j++;
			}
		}
		good_job_ = BASS_SampleLoad(FALSE, "Sounds/nextlevel.wav", 0, 0, 1, NULL);
		main_channel_ = BASS_SampleGetChannel(good_job_, FALSE);
		BASS_ChannelSetAttribute(main_channel_, BASS_ATTRIB_VOL, 0.4f);

		shufflesound = BASS_SampleLoad(FALSE, "Sounds/shufflesound.wav", 0, 0, 1, NULL);
		main_channel1_ = BASS_SampleGetChannel(shufflesound, FALSE);
		BASS_ChannelSetAttribute(main_channel1_, BASS_ATTRIB_VOL, 1.0f);

		gottagetKey = BASS_SampleLoad(FALSE, "Sounds/gottagetkey.wav", 0, 0, 1, NULL);
		main_channel2_ = BASS_SampleGetChannel(gottagetKey, FALSE);
		BASS_ChannelSetAttribute(main_channel2_, BASS_ATTRIB_VOL, 0.4f);

		leverPull = BASS_SampleLoad(FALSE, "Sounds/levelpull.wav", 0, 0, 1, NULL);
		main_channel3_ = BASS_SampleGetChannel(leverPull, FALSE);
		BASS_ChannelSetAttribute(main_channel3_, BASS_ATTRIB_VOL, 0.4f);

		switchSound = BASS_SampleLoad(FALSE, "Sounds/switchsound.wav", 0, 0, 1, NULL);
		main_channel4_ = BASS_SampleGetChannel(switchSound, FALSE);
		BASS_ChannelSetAttribute(main_channel4_, BASS_ATTRIB_VOL, 0.4f);
	}
}

GameState3::~GameState3(){}//Destructor

int GameState3::rng(int min, int max)
{
	// initialize once per thread
	static std::random_device srd;
	static std::mt19937 smt(srd());

	std::uniform_int_distribution<> dist(min, max); // Generate a number between min and max

	return dist(smt);
}

void GameState3::create_lights()// Creating the lighs done in here
{
	short int light1_x = 200; short int light1_y = 1000; 
	lights_image_.emplace_back(std::make_unique<Light>(sf::Vector2f(light1_x, light1_y), sf::Vector2f(152, 300), sf::Color::Transparent, 0));
	lights_image_[0]->Shape().setPosition(lights_image_[0]->Shape().getPosition().x, lights_image_[0]->set_Ypos(LEVEL_HEIGHT, 0, TIER_HEIGHT, FLOOR_OFFSET));
	lights_image_[0]->set_In_Range(false);

	short int light2_x = 1575; short int light2_y = 1000;
	lights_image_.emplace_back(std::make_unique<Light>(sf::Vector2f(light2_x, light2_y), sf::Vector2f(152, 300), sf::Color::Transparent, 1));
	lights_image_[1]->Shape().setPosition(lights_image_[1]->Shape().getPosition().x, lights_image_[1]->set_Ypos(LEVEL_HEIGHT, 0, TIER_HEIGHT, FLOOR_OFFSET));
	lights_image_[1]->set_In_Range(false);

	short int light3_x = 160; short int light3_y = 900;
	lights_image_.emplace_back(std::make_unique<Light>(sf::Vector2f(light3_x, light3_y), sf::Vector2f(152, 300), sf::Color::Transparent, 2));
	lights_image_[2]->Shape().setPosition(lights_image_[2]->Shape().getPosition().x, lights_image_[2]->set_Ypos(LEVEL_HEIGHT, 1, TIER_HEIGHT, FLOOR_OFFSET));
	lights_image_[2]->set_In_Range(false);

	short int light4_x = 1100; short int light4_y = 900;
	lights_image_.emplace_back(std::make_unique<Light>(sf::Vector2f(light4_x, light4_y), sf::Vector2f(152, 300), sf::Color::Transparent, 3));
	lights_image_[3]->Shape().setPosition(lights_image_[3]->Shape().getPosition().x, lights_image_[3]->set_Ypos(LEVEL_HEIGHT, 1, TIER_HEIGHT, FLOOR_OFFSET));
	lights_image_[3]->set_In_Range(false);

	short int light5_x = 1550; short int light5_y = 900;
	lights_image_.emplace_back(std::make_unique<Light>(sf::Vector2f(light5_x, light5_y), sf::Vector2f(152, 300), sf::Color::Transparent, 4));
	lights_image_[4]->Shape().setPosition(lights_image_[4]->Shape().getPosition().x, lights_image_[4]->set_Ypos(LEVEL_HEIGHT, 1, TIER_HEIGHT, FLOOR_OFFSET));
	lights_image_[4]->set_In_Range(false);

	short int light6_x = 20; short int light6_y = 610;
	lights_image_.emplace_back(std::make_unique<Light>(sf::Vector2f(light6_x, light6_y), sf::Vector2f(152, 300), sf::Color::Transparent, 5));
	lights_image_[5]->Shape().setPosition(lights_image_[5]->Shape().getPosition().x, lights_image_[5]->set_Ypos(LEVEL_HEIGHT, 2, TIER_HEIGHT, FLOOR_OFFSET));
	lights_image_[5]->set_In_Range(false);

	short int light7_x = 800; short int light7_y = 610;
	lights_image_.emplace_back(std::make_unique<Light>(sf::Vector2f(light7_x, light7_y), sf::Vector2f(152, 300), sf::Color::Transparent, 6));
	lights_image_[6]->Shape().setPosition(lights_image_[6]->Shape().getPosition().x, lights_image_[6]->set_Ypos(LEVEL_HEIGHT, 2, TIER_HEIGHT, FLOOR_OFFSET));
	lights_image_[6]->set_In_Range(false);

	short int light8_x = 550; short int light8_y = 300;
	lights_image_.emplace_back(std::make_unique<Light>(sf::Vector2f(light8_x, light8_y), sf::Vector2f(152, 300), sf::Color::Transparent, 7));
	lights_image_[7]->Shape().setPosition(lights_image_[7]->Shape().getPosition().x, lights_image_[7]->set_Ypos(LEVEL_HEIGHT, 3, TIER_HEIGHT, FLOOR_OFFSET));
	lights_image_[7]->set_In_Range(false);

	short int light9_x = 1000 ; short int light9_y = 300;
	lights_image_.emplace_back(std::make_unique<Light>(sf::Vector2f(light9_x, light9_y), sf::Vector2f(152, 300), sf::Color::Transparent, 8));
	lights_image_[8]->Shape().setPosition(lights_image_[8]->Shape().getPosition().x, lights_image_[8]->set_Ypos(LEVEL_HEIGHT, 3, TIER_HEIGHT, FLOOR_OFFSET));
	lights_image_[8]->set_In_Range(false);

}

void GameState3::create_guards()// creation of guards done in here
{
	guards_.emplace_back(std::move(std::make_unique<Guard>(sf::Vector2f(450, 300),
		sf::Vector2f(50, 100), sf::Color::Red)));
	guards_[0]->Shape().setPosition(guards_[0]->Shape().getPosition().x,
		guards_[0]->set_Ypos(LEVEL_HEIGHT, 3, TIER_HEIGHT, FLOOR_OFFSET));

	guards_.emplace_back(std::move(std::make_unique<Guard>(sf::Vector2f(1350, 300),
		sf::Vector2f(50, 100), sf::Color::Yellow)));
	guards_[1]->Shape().setPosition(guards_[1]->Shape().getPosition().x,
		guards_[1]->set_Ypos(LEVEL_HEIGHT, 3, TIER_HEIGHT, FLOOR_OFFSET));

	guards_.emplace_back(std::move(std::make_unique<Guard>(sf::Vector2f(800, 100),
		sf::Vector2f(50, 100), sf::Color::Red)));
	guards_[2]->Shape().setPosition(guards_[2]->Shape().getPosition().x,
		guards_[2]->set_Ypos(LEVEL_HEIGHT, 2, TIER_HEIGHT, FLOOR_OFFSET));
}

void GameState3::pause()// pause the State
{
	set_paused(true);
}
void GameState3::resume()
{
	set_paused(false);
}

void GameState3::handle_input(const sf::Time& delta)// Handle the input for the State
{
	auto& inputManager = state_manager_.get_input_manager();

	sf::Vector2i windowO(view_main.getCenter().x - view_main.getSize().x / 2, view_main.getCenter().y - view_main.getSize().y / 2);

	mouse_pos.x = windowO.x + inputManager.get_mouse_x();
	mouse_pos.y = windowO.y + inputManager.get_mouse_y();
	for (auto& guard : guards_)
		if (guard->caughtL == true || guard->caughtR == true)
			player_caught = true;
	if (inputManager.is_key_released(InputKey::escape))
	{
		std::cout << "Saving current Level Information...\n";
		savePlayerInfo("player_data.txt");

		std::cout << "\nQuitting\n";
		change_MM = true;
		setMusicState(false);
		BASS_ChannelStop(Bg_music_) == true;
	}
	bool onlynow = false;
	if (switch1_.in_Range() == true)
	{
		if (inputManager.is_key_pressed(InputKey::e))
		{
			switch1_.set_Pulled(true);
			BASS_ChannelPlay(main_channel4_, FALSE);
			onlynow = true;
		}
		if (onlynow)
		{
			BASS_ChannelPlay(main_channel3_, FALSE);
			onlynow = false;
		}
	}

	if (switch2_.in_Range() == true)
	{
		if (inputManager.is_key_pressed(InputKey::e))
		{
			switch2_.set_Pulled(true);
			BASS_ChannelPlay(main_channel4_, FALSE);
			onlynow = true;
		}
		if (onlynow)
		{
			BASS_ChannelPlay(main_channel3_, FALSE);
			onlynow = false;
		}
	}

	if (player_.getPlayerTextState() == true)
	{
		if (inputManager.is_key_pressed(InputKey::f_1))
		{
			player_.setPlayerTextState(false);
		}
	}
	else
		if (inputManager.is_key_pressed(InputKey::f_1))
		{
		player_.setPlayerTextState(true);
		}

	if (inputManager.is_key_pressed(InputKey::f_2))
	{
		player_.setPlayerTextState(false);
	}
	if (inputManager.is_key_pressed(InputKey::a) && player_.casting == false && player_caught == false)
	{
		BASS_ChannelPlay(main_channel1_, FALSE);
		player_.Shape().move(sf::Vector2f(-5.0f, 0.0f));
		if (player_.Shape().getPosition().x - (player_.Shape().getSize().x / 2) < 0)
			player_.Shape().setPosition(0 + (player_.Shape().getSize().x / 2), player_.Shape().getPosition().y);
		player_.isource.y = 1040;
		if (player_.framecounter >= player_.frameswitch)
		{
			player_.framecounter = 0;
			player_.isource.x += 682;
			if (player_.isource.x + 682 >= player_.spriteTexture.getSize().x)
				player_.isource.x = 0;
		}
		player_.walkleft = true;
	}
	else if (inputManager.is_key_pressed(InputKey::d) && player_.casting == false && player_caught == false)
	{
		BASS_ChannelPlay(main_channel1_, FALSE);
		player_.Shape().move(sf::Vector2f(5.0f, 0.0f));
		if (player_.Shape().getPosition().x + (player_.Shape().getSize().x / 2) >= LEVEL_WIDTH)
			player_.Shape().setPosition(LEVEL_WIDTH - (player_.Shape().getSize().x / 2), player_.Shape().getPosition().y);
		player_.isource.y = 0;
		if (player_.framecounter >= player_.frameswitch)
		{
			player_.framecounter = 0;
			player_.isource.x += 682;
			if (player_.isource.x + 682 >= player_.spriteTexture.getSize().x)
				player_.isource.x = 0;
		}
		player_.walkleft = false;
	}

	if (inputManager.is_key_released(InputKey::a))
	{
		player_.isource.x = 0;
	}

	if (inputManager.is_key_released(InputKey::d))
	{
		player_.isource.x = 0;
	}

	/*if (inputManager.is_key_pressed(InputKey::w))
	{
		player_.Shape().setPosition(player_.Shape().getPosition().x, player_.Shape().getPosition().y - 5);
	}

	if (inputManager.is_key_pressed(InputKey::s))
	{
		player_.Shape().setPosition(player_.Shape().getPosition().x, player_.Shape().getPosition().y + 5);
	}*/
}

void GameState3::savePlayerInfo(const char* filename)// Saving the player information to file
{
	std::cout << "Saving current level number...\n";
	tinyxml2::XMLDocument document;

	build = document.NewElement("SAVED");
	document.InsertFirstChild(build);
	build2 = document.NewElement("LEVEL_INFO");
	build->InsertFirstChild(build2);
	build->InsertEndChild(build2);

	e1_levelNo = document.NewElement("level_no");
	e1_levelNo->SetText(player_.getLevelNumber());

	build2->InsertFirstChild(e1_levelNo);
	build2->InsertEndChild(e1_levelNo);


	std::cout << "Saving current player Position to file...\n";

	e2_PlayerX = document.NewElement("Player_X");
	e2_PlayerX->SetText(player_.Shape().getPosition().x);
	build2->InsertFirstChild(e2_PlayerX);
	build2->InsertEndChild(e2_PlayerX);

	e3_PlayerY = document.NewElement("Player_Y");
	e3_PlayerY->SetText(player_.Shape().getPosition().y);
	build2->InsertAfterChild(e2_PlayerX, e3_PlayerY);
	build2->InsertEndChild(e3_PlayerY);

	std::cout << "\nSaving door information...\n";

	e4_Door = document.NewElement("Door_Unlocked");
	if (key1_.getPickupedUpState() == true)
		e4_Door->SetText("1");
	else
		e4_Door->SetText("0");
	build2->InsertAfterChild(e3_PlayerY, e4_Door);
	build2->InsertEndChild(e4_Door);

	std::cout << "\nSaving all guard positions...\n";
	e5_Guard1_X = document.NewElement("Guard_1_X");
	e5_Guard1_X->SetText(guards_[0]->Shape().getPosition().x);
	build2->InsertAfterChild(e4_Door, e5_Guard1_X);
	build2->InsertEndChild(e5_Guard1_X);

	e6_Guard1_Y = document.NewElement("Guard_1_Y");
	e6_Guard1_Y->SetText(guards_[0]->Shape().getPosition().y);
	build2->InsertAfterChild(e5_Guard1_X, e6_Guard1_Y);
	build2->InsertEndChild(e6_Guard1_Y);

	e7_Guard2_X = document.NewElement("Guard_2_X");
	e7_Guard2_X->SetText(guards_[1]->Shape().getPosition().x);
	build2->InsertAfterChild(e6_Guard1_Y, e7_Guard2_X);
	build2->InsertEndChild(e7_Guard2_X);

	e8_Guard2_Y = document.NewElement("Guard_2_Y");
	e8_Guard2_Y->SetText(guards_[1]->Shape().getPosition().y);
	build2->InsertAfterChild(e7_Guard2_X, e8_Guard2_Y);
	build2->InsertEndChild(e8_Guard2_Y);

	build->InsertEndChild(build2);
	document.InsertEndChild(build);
	document.SaveFile("Save_Info.xml");
}

void GameState3::LoadGame(Player& player, Guard& guards, Light& lights)// Loading game method
{
	auto& state_current = state_manager_;
	player.setLevelNumber(getLevelNumber());
	player.setPlayerPos(getLoadPlayerPos());
}

void GameState3::readPlayerInfo(const char* filename)// reading in all of the saved information
{

	// READING
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename);
	tinyxml2::XMLElement *rootnode;
	doc.LoadFile("Save_Info.xml");

	rootnode = doc.FirstChildElement("SAVED")->FirstChildElement("LEVEL_INFO");
	doc.Print();
	std::cout << "\n\n";
	printf("Level number: %s\n", rootnode->FirstChildElement()->GetText());
	rootnode = rootnode->FirstChildElement();


	while (rootnode->NextSiblingElement() != NULL)
	{
		std::cout << rootnode->NextSiblingElement()->Value() << ": " << rootnode->NextSiblingElement()->GetText() << "\n";


		if (std::string(rootnode->Value()) == "level_no")
		{
			int num = atoi(rootnode->GetText());
			setLevelNumber(num);
			rootnode = rootnode->NextSiblingElement();
		}
		if (std::string(rootnode->Value()) == "Player_X")
		{
			int num = atoi(rootnode->GetText());
			setLoadPlayerPosX(num);
			rootnode = rootnode->NextSiblingElement();
		}
		if (std::string(rootnode->Value()) == "Player_Y")
		{
			int num = atoi(rootnode->GetText());
			setLoadPlayerPosY(num);
			rootnode = rootnode->NextSiblingElement();
		}
		if (std::string(rootnode->Value()) == "Door_Unlocked")
		{
			int num = atoi(rootnode->GetText());
			if (num == 0)
				setLoadDoorState(false);
			else
			{
				if (num == 1)
					setLoadDoorState(true);
			}
			rootnode = rootnode->NextSiblingElement();
		}
		if (std::string(rootnode->Value()) == "Guard_1_X")
		{
			int num = atoi(rootnode->GetText());
			setLoadGuard1PosX(num);
			rootnode = rootnode->NextSiblingElement();
		}
		if (std::string(rootnode->Value()) == "Guard_1_Y")
		{
			int num = atoi(rootnode->GetText());
			setLoadGuard1PosY(num);
			rootnode = rootnode->NextSiblingElement();
		}
		if (std::string(rootnode->Value()) == "Guard_2_X")
		{
			int num = atoi(rootnode->GetText());
			setLoadGuard2PosX(num);
			rootnode = rootnode->NextSiblingElement();
		}
		if (std::string(rootnode->Value()) == "Guard_2_Y")
		{
			int num = atoi(rootnode->GetText());
			setLoadGuard2PosY(num);
		}
	}
	std::cout << "\nLOADED Level No: " << getLevelNumber() << "\n";
	std::cout << "LOADED Player X: " << getLoadPlayerPos().x << "\n";
	std::cout << "LOADED Player Y: " << getLoadPlayerPos().y << "\n";
	std::cout << "LOADED Door State: " << getLoadDoorState() << "\n";
	std::cout << "LOADED Guard1 X: " << getLoadGuard1Pos().x << "\n";
	std::cout << "LOADED Guard1 Y: " << getLoadGuard1Pos().y << "\n";
	std::cout << "LOADED Guard2 X: " << getLoadGuard2Pos().x << "\n";
	std::cout << "LOADED Guard2 Y: " << getLoadGuard2Pos().y << "\n";
	if (doc.ErrorID() != 0)
	{
		printf("load file=%s failed\n", doc.GetErrorStr1());
		printf("\nSECOND load file=[%s] failed\n", doc.GetErrorStr2());
	}
}

void GameState3::CheckOtherLights(Light& light)//method for checking a light against all of the other lights in the game
{
	auto& inputManager = state_manager_.get_input_manager();

	for (auto& otherLight : lights_image_)
	{
		otherLight->set_shadow(false);

		if (light.ID() != otherLight->ID())
		{
			const auto& pos = light.Shape().getPosition();

			if (std::abs(otherLight->Shape().getPosition().x - pos.x) < 400 && (std::abs(otherLight->Shape().getPosition().y - pos.y) < 400))
			{
				if (otherLight->ID() == 0)
				{

					otherLight->set_In_Range(true);
					if (otherLight->Shape().getGlobalBounds().contains(mouse_pos))
					{
						if (player_.walkleft)
						{
							shadow_.castisource.y = 0;
							shadow_.isource.y = 1025;
						}
						else
						{
							shadow_.castisource.y = 1480;
							shadow_.isource.y = 0;
						}

						if (inputManager.right_clicked() && CoolD == false)
						{
							player_.casting = true;
							shadow_.casttimer += shadow_.clock1.restart().asMilliseconds();
							shadow_.setCastState(true);
							if (shadow_.casttimer >= shadow_.cast)
							{
								shadow_.casttimer = 0;
								shadow_.castisource.x += 510;
								if (shadow_.castisource.x + 510 >= shadow_.shadowCastTexture.getSize().x)
								{
									shadow_.castisource.x = shadow_.shadowCastTexture.getSize().x - 510;
									shadow_.casted = true;
								}
							}
							shadow_.Shape().setPosition(otherLight->Shape().getPosition().x + 45, otherLight->Shape().getPosition().y + 45);
							if (shadow_.casted == true)
							{
								player_.casting = true;
								otherLight->set_shadow(true);
								shadow_.setVisibleState(true);
								if (inputManager.left_clicked())
								{
									teleport_player(*otherLight, otherLight->ID(), 0);
									otherLight->set_In_Range(false);
									CoolD = true;
									shadow_.cooldowntimer = 0;
									shadow_.castisource.x = 0;
									shadow_.casted = false;
									player_.casting = false;
									shadow_.setCastState(false);
								}
							}
						}
					}
				}

				if (otherLight->ID() == 1)
				{
					otherLight->set_In_Range(true);
					if (otherLight->Shape().getGlobalBounds().contains(mouse_pos))
					{
						if (player_.walkleft)
						{
							shadow_.castisource.y = 0;
							shadow_.isource.y = 1025;
						}
						else
						{
							shadow_.castisource.y = 1480;
							shadow_.isource.y = 0;
						}

						if (inputManager.right_clicked() && CoolD == false)
						{
							player_.casting = true;
							shadow_.casttimer += shadow_.clock1.restart().asMilliseconds();
							shadow_.setCastState(true);
							if (shadow_.casttimer >= shadow_.cast)
							{
								shadow_.casttimer = 0;
								shadow_.castisource.x += 510;
								if (shadow_.castisource.x + 510 >= shadow_.shadowCastTexture.getSize().x)
								{
									shadow_.castisource.x = shadow_.shadowCastTexture.getSize().x - 510;
									shadow_.casted = true;
								}
							}
							shadow_.Shape().setPosition(otherLight->Shape().getPosition().x + 45, otherLight->Shape().getPosition().y + 45);
							if (shadow_.casted == true)
							{
								otherLight->set_shadow(true);
								shadow_.setVisibleState(true);
								if (inputManager.left_clicked())
								{
									teleport_player(*otherLight, otherLight->ID(), 0);
									otherLight->set_In_Range(false);
									CoolD = true;
									shadow_.cooldowntimer = 0;
									shadow_.castisource.x = 0;
									shadow_.casted = false;
									player_.casting = false;
									shadow_.setCastState(false);
								}
							}
						}
					}
				}

				if (otherLight->ID() == 2)
				{
					otherLight->set_In_Range(true);
					if (otherLight->Shape().getGlobalBounds().contains(mouse_pos))
					{
						if (player_.walkleft)
						{
							shadow_.castisource.y = 0;
							shadow_.isource.y = 1025;
						}
						else
						{
							shadow_.castisource.y = 1480;
							shadow_.isource.y = 0;
						}

						if (inputManager.right_clicked() && CoolD == false)
						{
							player_.casting = true;
							shadow_.casttimer += shadow_.clock1.restart().asMilliseconds();
							shadow_.setCastState(true);
							if (shadow_.casttimer >= shadow_.cast)
							{
								shadow_.casttimer = 0;
								shadow_.castisource.x += 510;
								if (shadow_.castisource.x + 510 >= shadow_.shadowCastTexture.getSize().x)
								{
									shadow_.castisource.x = shadow_.shadowCastTexture.getSize().x - 510;
									shadow_.casted = true;
								}
							}
							shadow_.Shape().setPosition(otherLight->Shape().getPosition().x + 45, otherLight->Shape().getPosition().y + 45);
							if (shadow_.casted == true)
							{
								otherLight->set_shadow(true);
								shadow_.setVisibleState(true);
								if (inputManager.left_clicked())
								{
									teleport_player(*otherLight, otherLight->ID(), 1);
									otherLight->set_In_Range(false);
									CoolD = true;
									shadow_.cooldowntimer = 0;
									shadow_.castisource.x = 0;
									shadow_.casted = false;
									player_.casting = false;
									shadow_.setCastState(false);
								}
							}
						}
					}
				}

				if (otherLight->ID() == 3)
				{
					otherLight->set_In_Range(true);
					if (otherLight->Shape().getGlobalBounds().contains(mouse_pos))
					{
						if (player_.walkleft)
						{
							shadow_.castisource.y = 0;
							shadow_.isource.y = 1025;
						}
						else
						{
							shadow_.castisource.y = 1480;
							shadow_.isource.y = 0;
						}

						if (inputManager.right_clicked() && CoolD == false)
						{
							player_.casting = true;
							shadow_.casttimer += shadow_.clock1.restart().asMilliseconds();
							shadow_.setCastState(true);
							if (shadow_.casttimer >= shadow_.cast)
							{
								shadow_.casttimer = 0;
								shadow_.castisource.x += 510;
								if (shadow_.castisource.x + 510 >= shadow_.shadowCastTexture.getSize().x)
								{
									shadow_.castisource.x = shadow_.shadowCastTexture.getSize().x - 510;
									shadow_.casted = true;
								}
							}
							shadow_.Shape().setPosition(otherLight->Shape().getPosition().x + 45, otherLight->Shape().getPosition().y + 45);
							if (shadow_.casted == true)
							{
								otherLight->set_shadow(true);
								shadow_.setVisibleState(true);
								if (inputManager.left_clicked())
								{
									teleport_player(*otherLight, otherLight->ID(), 1);
									otherLight->set_In_Range(false);
									CoolD = true;
									shadow_.cooldowntimer = 0;
									shadow_.castisource.x = 0;
									shadow_.casted = false;
									player_.casting = false;
									shadow_.setCastState(false);
									if (switch1_.has_Pulled() == true && key1_.getPickupedUpState() == false)
										BASS_ChannelPlay(main_channel2_, FALSE);
								}
							}
						}
					}
				}

				if (otherLight->ID() == 4)
				{
					if (otherLight->Shape().getGlobalBounds().contains(mouse_pos))
					{
						otherLight->set_In_Range(true);

						if (player_.walkleft)
						{
							shadow_.castisource.y = 0;
							shadow_.isource.y = 1025;
						}
						else
						{
							shadow_.castisource.y = 1480;
							shadow_.isource.y = 0;
						}

						if (inputManager.right_clicked() && CoolD == false)
						{
							player_.casting = true;
							shadow_.casttimer += shadow_.clock1.restart().asMilliseconds();
							shadow_.setCastState(true);
							if (shadow_.casttimer >= shadow_.cast)
							{
								shadow_.casttimer = 0;
								shadow_.castisource.x += 510;
								if (shadow_.castisource.x + 510 >= shadow_.shadowCastTexture.getSize().x)
								{
									shadow_.castisource.x = shadow_.shadowCastTexture.getSize().x - 510;
									shadow_.casted = true;
								}
							}
							shadow_.Shape().setPosition(otherLight->Shape().getPosition().x + 45, otherLight->Shape().getPosition().y + 45);
							if (shadow_.casted == true)
							{
								otherLight->set_shadow(true);
								shadow_.setVisibleState(true);
								if (inputManager.left_clicked())
								{
									teleport_player(*otherLight, otherLight->ID(), 1);
									otherLight->set_In_Range(false);
									CoolD = true;
									shadow_.cooldowntimer = 0;
									shadow_.castisource.x = 0;
									shadow_.casted = false;
									player_.casting = false;
									shadow_.setCastState(false);
								}
							}
						}
					}
				}
				if (otherLight->ID() == 5)
				{
					if (otherLight->Shape().getGlobalBounds().contains(mouse_pos))
					{
						otherLight->set_In_Range(true);

						if (player_.walkleft)
						{
							shadow_.castisource.y = 0;
							shadow_.isource.y = 1025;
						}
						else
						{
							shadow_.castisource.y = 1480;
							shadow_.isource.y = 0;
						}

						if (inputManager.right_clicked() && CoolD == false)
						{
							player_.casting = true;
							shadow_.casttimer += shadow_.clock1.restart().asMilliseconds();
							shadow_.setCastState(true);
							if (shadow_.casttimer >= shadow_.cast)
							{
								shadow_.casttimer = 0;
								shadow_.castisource.x += 510;
								if (shadow_.castisource.x + 510 >= shadow_.shadowCastTexture.getSize().x)
								{
									shadow_.castisource.x = shadow_.shadowCastTexture.getSize().x - 510;
									shadow_.casted = true;
								}
							}
							shadow_.Shape().setPosition(otherLight->Shape().getPosition().x + 45, otherLight->Shape().getPosition().y + 45);
							if (shadow_.casted == true)
							{
								otherLight->set_shadow(true);
								shadow_.setVisibleState(true);
								if (inputManager.left_clicked())
								{
									teleport_player(*otherLight, otherLight->ID(), 2);
									otherLight->set_In_Range(false);
									CoolD = true;
									shadow_.cooldowntimer = 0;
									shadow_.castisource.x = 0;
									shadow_.casted = false;
									player_.casting = false;
									shadow_.setCastState(false);
								}
							}
						}
					}
				}

				if (otherLight->ID() == 6)
				{
					if (otherLight->Shape().getGlobalBounds().contains(mouse_pos))
					{
						otherLight->set_In_Range(true);
						if (player_.walkleft)
						{
							shadow_.castisource.y = 0;
							shadow_.isource.y = 1025;
						}
						else
						{
							shadow_.castisource.y = 1480;
							shadow_.isource.y = 0;
						}

						if (inputManager.right_clicked() && CoolD == false)
						{
							player_.casting = true;
							shadow_.casttimer += shadow_.clock1.restart().asMilliseconds();
							shadow_.setCastState(true);
							if (shadow_.casttimer >= shadow_.cast)
							{
								shadow_.casttimer = 0;
								shadow_.castisource.x += 510;
								if (shadow_.castisource.x + 510 >= shadow_.shadowCastTexture.getSize().x)
								{
									shadow_.castisource.x = shadow_.shadowCastTexture.getSize().x - 510;
									shadow_.casted = true;
								}
							}
							shadow_.Shape().setPosition(otherLight->Shape().getPosition().x + 45, otherLight->Shape().getPosition().y + 45);
							if (shadow_.casted == true)
							{
								otherLight->set_shadow(true);
								shadow_.setVisibleState(true);
								if (inputManager.left_clicked())
								{
									teleport_player(*otherLight, otherLight->ID(), 2);
									otherLight->set_In_Range(false);
									CoolD = true;
									shadow_.cooldowntimer = 0;
									shadow_.castisource.x = 0;
									shadow_.casted = false;
									player_.casting = false;
									shadow_.setCastState(false);
								}
							}
						}
					}
				}

				if (otherLight->ID() == 7)
				{
					if (otherLight->Shape().getGlobalBounds().contains(mouse_pos))
					{
						otherLight->set_In_Range(true);
						if (player_.walkleft)
						{
							shadow_.castisource.y = 0;
							shadow_.isource.y = 1025;
						}
						else
						{
							shadow_.castisource.y = 1480;
							shadow_.isource.y = 0;
						}

						if (inputManager.right_clicked() && CoolD == false)
						{
							player_.casting = true;
							shadow_.casttimer += shadow_.clock1.restart().asMilliseconds();
							shadow_.setCastState(true);
							if (shadow_.casttimer >= shadow_.cast)
							{
								shadow_.casttimer = 0;
								shadow_.castisource.x += 510;
								if (shadow_.castisource.x + 510 >= shadow_.shadowCastTexture.getSize().x)
								{
									shadow_.castisource.x = shadow_.shadowCastTexture.getSize().x - 510;
									shadow_.casted = true;
								}
							}
							shadow_.Shape().setPosition(otherLight->Shape().getPosition().x + 45, otherLight->Shape().getPosition().y + 45);
							if (shadow_.casted == true)
							{
								otherLight->set_shadow(true);
								shadow_.setVisibleState(true);
								if (inputManager.left_clicked())
								{
									teleport_player(*otherLight, otherLight->ID(), 3);
									otherLight->set_In_Range(false);
									CoolD = true;
									shadow_.cooldowntimer = 0;
									shadow_.castisource.x = 0;
									shadow_.casted = false;
									player_.casting = false;
									shadow_.setCastState(false);
								}
							}
						}
					}
				}

				if (otherLight->ID() == 8)
				{
					if (otherLight->Shape().getGlobalBounds().contains(mouse_pos))
					{
						otherLight->set_In_Range(true);
						if (player_.walkleft)
						{
							shadow_.castisource.y = 0;
							shadow_.isource.y = 1025;
						}
						else
						{
							shadow_.castisource.y = 1480;
							shadow_.isource.y = 0;
						}

						if (inputManager.right_clicked() && CoolD == false)
						{
							player_.casting = true;
							shadow_.casttimer += shadow_.clock1.restart().asMilliseconds();
							shadow_.setCastState(true);
							if (shadow_.casttimer >= shadow_.cast)
							{
								shadow_.casttimer = 0;
								shadow_.castisource.x += 510;
								if (shadow_.castisource.x + 510 >= shadow_.shadowCastTexture.getSize().x)
								{
									shadow_.castisource.x = shadow_.shadowCastTexture.getSize().x - 510;
									shadow_.casted = true;
								}
							}
							shadow_.Shape().setPosition(otherLight->Shape().getPosition().x + 45, otherLight->Shape().getPosition().y + 45);
							if (shadow_.casted == true)
							{
								otherLight->set_shadow(true);
								shadow_.setVisibleState(true);

								if (inputManager.left_clicked())
								{
									teleport_player(*otherLight, otherLight->ID(), 3);
									otherLight->set_In_Range(false);
									CoolD = true;
									shadow_.cooldowntimer = 0;
									shadow_.castisource.x = 0;
									shadow_.casted = false;
									player_.casting = false;
									shadow_.setCastState(false);
								}
							}
						}
					}
				}
				if (inputManager.right_clicked() == false)
				{
					shadow_.castisource.x = 0;
					shadow_.casted = false;
					player_.casting = false;
					shadow_.setCastState(false);
				}
			}
		}
	}
}

void GameState3::in_range()// method for checking if you're in range of another light
{
	for (auto& light : lights_image_)
	{
		light->set_shadow(false);
		shadow_.setVisibleState(false);

		if (light->can_teleport())
		{
			CheckOtherLights(*light);
			break;
		}
	}
}

void GameState3::check_collisions()// checking the collisions in the game
{

	for (auto& light : lights_image_)
	{
		if (light->Shape().getGlobalBounds().intersects(player_.Shape().getGlobalBounds()))
		{
			light->set_teleport(true);
		}
		else
		{
			light->set_teleport(false);
			light->set_In_Range(false);
			shadow_.setVisibleState(false);
		}
	}

	if (exit_.Shape().getGlobalBounds().intersects(player_.Shape().getGlobalBounds()) && key1_.getPickupedUpState() == true)
	{
		player_.setLevelNumber(player_.getLevelNumber() + 1);
		BASS_ChannelPlay(main_channel_, FALSE);
		next_Level = true;
	}

	if (switch1_.Shape().getGlobalBounds().intersects(player_.Shape().getGlobalBounds()))
	{
		switch1_.set_inRange(true);
	}
	else
		switch1_.set_inRange(false);

	if (switch2_.Shape().getGlobalBounds().intersects(player_.Shape().getGlobalBounds()))
	{
		switch2_.set_inRange(true);
	}
	else
		switch2_.set_inRange(false);

	if (player_.Shape().getGlobalBounds().intersects(destroyable_wall1_.Shape().getGlobalBounds()) && switch1_.has_Pulled() == false)
	{
		if (player_.Shape().getPosition().x < destroyable_wall1_.Shape().getPosition().x)
			player_.Shape().setPosition(destroyable_wall1_.Shape().getPosition().x - destroyable_wall1_.Shape().getSize().x / 2 - (player_.Shape().getSize().x / 2),
			player_.Shape().getPosition().y);
		if (player_.Shape().getPosition().x > destroyable_wall1_.Shape().getPosition().x)
			player_.Shape().setPosition(destroyable_wall1_.Shape().getPosition().x + destroyable_wall1_.Shape().getSize().x / 2 + player_.Shape().getSize().x / 2,
			player_.Shape().getPosition().y);
	}

	if (player_.Shape().getGlobalBounds().intersects(destroyable_wall2_.Shape().getGlobalBounds()) && switch2_.has_Pulled() == false)
	{
		if (player_.Shape().getPosition().x < destroyable_wall2_.Shape().getPosition().x)
			player_.Shape().setPosition(destroyable_wall2_.Shape().getPosition().x - destroyable_wall2_.Shape().getSize().x / 2 - (player_.Shape().getSize().x / 2),
			player_.Shape().getPosition().y);
		if (player_.Shape().getPosition().x > destroyable_wall2_.Shape().getPosition().x)
			player_.Shape().setPosition(destroyable_wall2_.Shape().getPosition().x + destroyable_wall2_.Shape().getSize().x / 2 + player_.Shape().getSize().x / 2,
			player_.Shape().getPosition().y);
	}

	if (player_.Shape().getGlobalBounds().intersects(undestroyable_wall1_.Shape().getGlobalBounds()))
	{
		if (player_.Shape().getPosition().x < undestroyable_wall1_.Shape().getPosition().x)
			player_.Shape().setPosition(undestroyable_wall1_.Shape().getPosition().x - undestroyable_wall1_.Shape().getSize().x / 2 - (player_.Shape().getSize().x / 2),
			player_.Shape().getPosition().y);
		if (player_.Shape().getPosition().x > undestroyable_wall1_.Shape().getPosition().x)
			player_.Shape().setPosition(undestroyable_wall1_.Shape().getPosition().x + undestroyable_wall1_.Shape().getSize().x / 2 + player_.Shape().getSize().x / 2,
			player_.Shape().getPosition().y);
	}

	if (player_.Shape().getGlobalBounds().intersects(undestroyable_wall2_.Shape().getGlobalBounds()))
	{
		if (player_.Shape().getPosition().x < undestroyable_wall2_.Shape().getPosition().x)
			player_.Shape().setPosition(undestroyable_wall2_.Shape().getPosition().x - undestroyable_wall2_.Shape().getSize().x / 2 - (player_.Shape().getSize().x / 2),
			player_.Shape().getPosition().y);
		if (player_.Shape().getPosition().x > undestroyable_wall2_.Shape().getPosition().x)
			player_.Shape().setPosition(undestroyable_wall2_.Shape().getPosition().x + undestroyable_wall2_.Shape().getSize().x / 2 + player_.Shape().getSize().x / 2,
			player_.Shape().getPosition().y);
	}

	if (player_.Shape().getGlobalBounds().intersects(undestroyable_wall3_.Shape().getGlobalBounds()))
	{
		if (player_.Shape().getPosition().x < undestroyable_wall3_.Shape().getPosition().x)
			player_.Shape().setPosition(undestroyable_wall3_.Shape().getPosition().x - undestroyable_wall3_.Shape().getSize().x / 2 - (player_.Shape().getSize().x / 2),
			player_.Shape().getPosition().y);
		if (player_.Shape().getPosition().x > undestroyable_wall3_.Shape().getPosition().x)
			player_.Shape().setPosition(undestroyable_wall3_.Shape().getPosition().x + undestroyable_wall3_.Shape().getSize().x / 2 + player_.Shape().getSize().x / 2,
			player_.Shape().getPosition().y);
	}
}

void GameState3::update(const sf::Time& delta)// updating the game
{
	shadow_.cooldowntimer += shadow_.clock2.restart().asMilliseconds();

	if (shadow_.cooldowntimer >= shadow_.cooldown)
		CoolD = false;

	key1_.framecounter += key1_.frameclock.restart().asMilliseconds();
	if (key1_.framecounter >= key1_.frameswitch)
	{
		key1_.framecounter = 0;
		key1_.isource.x += 512;
		if (key1_.isource.x + 512 >= key1_.spriteTexture.getSize().x)
			key1_.isource.x = 0;
	}
	key1_.update(player_);

	key1_.spriteImage.setPosition(key1_.Shape().getPosition().x - key1_.Shape().getSize().x / 2, key1_.Shape().getPosition().y - key1_.Shape().getSize().y / 1.5f);
	userInter_1.updateKey(key1_, player_, view_main);
	userInter_1.updatePlayerPos(player_, shadow_, view_main);

	for (auto& light : lights_image_)
	{
		userInter_1.updateLight(*light, view_main);

		if (light->get_In_Range() == false)
			light->Shape().setOutlineColor(sf::Color::Yellow);
		else
			light->Shape().setOutlineColor(sf::Color::Green);

	}

	check_collisions();
	in_range();


	teleport_text.setPosition(player_.Shape().getPosition().x - 100, player_.Shape().getPosition().y - 100);


	for (auto& guard : guards_)
	{
		guard->updatePlayer(player_, shadow_);

		if (guard->framecounter >= guard->frameswitch)
		{
			guard->framecounter = 0;
			guard->isource.x += 512;
			if (guard->isource.x + 512 >= guard->spriteTexture.getSize().x)
				guard->isource.x = 0;
		}

		if (guard->goto_game_over() == true)
			game_over_ = true;

		if (guards_[2]->Shape().getPosition().x - guards_[2]->Shape().getSize().x / 2 < undestroyable_wall2_.Shape().getPosition().x + undestroyable_wall2_.Shape().getSize().x/2)
		{
			//guards_[1]->Shape().setPosition(guards_[1]->Shape().getPosition().x + 10, guards_[1]->Shape().getPosition().y);
			guards_[2]->turnRight = true;
			guards_[2]->turnAround();
		}

		if (guards_[1]->Shape().getPosition().x - guards_[1]->Shape().getSize().x / 2 < undestroyable_wall1_.Shape().getPosition().x + undestroyable_wall1_.Shape().getSize().x /2)
		{
			guards_[1]->turnRight = true;
			guards_[1]->turnAround();
		}

		if (guards_[2]->Shape().getPosition().x + guards_[1]->Shape().getSize().x / 2 > destroyable_wall1_.Shape().getPosition().x + destroyable_wall1_.Shape().getSize().x / 2)
		{
			guards_[2]->turnRight = false;
			guards_[2]->turnAround();
		}
	}

	view_main.setCenter(player_.Shape().getPosition().x, player_.Shape().getPosition().y - player_.Shape().getSize().y);

	if (view_main.getCenter().x + (view_main.getSize().x / 2) >= LEVEL_WIDTH)
		view_main.setCenter(LEVEL_WIDTH - (view_main.getSize().x / 2), view_main.getCenter().y);

	if (view_main.getCenter().x - (view_main.getSize().x / 2) <= 0)
		view_main.setCenter(0 + (view_main.getSize().x / 2), view_main.getCenter().y);

	if (view_main.getCenter().y - (view_main.getSize().y / 2) <= 0)
		view_main.setCenter(view_main.getCenter().x, 0 + (view_main.getSize().y / 2));

	if (view_main.getCenter().y + view_main.getSize().y / 2 >= LEVEL_HEIGHT)
		view_main.setCenter(view_main.getCenter().x, LEVEL_HEIGHT - (view_main.getSize().y / 2));

	player_.spriteImage.setPosition(player_.Shape().getPosition().x - player_.Shape().getSize().x / 2,
		player_.Shape().getPosition().y + player_.Shape().getSize().y / 2 - 1020 * player_.spriteImage.getScale().y + 3);

	if (shadow_.getVisibleState() == true)
	{
		shadow_.isource.y = 0;
		shadow_.shadowImage.setPosition(shadow_.Shape().getPosition().x - (shadow_.Shape().getSize().x / 2),
			shadow_.Shape().getPosition().y + shadow_.Shape().getSize().y / 2 - 204);
	}

	player_.framecounter += player_.frameclock.restart().asMilliseconds();
}

void GameState3::render() // Drawing all of the Game Level
{
	userInter_1.ui_lights_.clear();
	sf::RenderWindow& window = state_manager_.get_render_window();
	window.setView(view_main); // applying the view

	std::vector<std::string> light_ids;

	bool tele_available = false;

	for (auto& f_sprite : floor_sprite)
	{
		window.draw(f_sprite);
	}
	window.draw(exit_.spriteImage);
	if (switch1_.has_Pulled() == false)
	{
		window.draw(destroyable_wall1_.spriteImage);
		window.draw(switch1_.spriteImage);
	}
	else
		window.draw(switch1_.spriteImage2);

	if (switch2_.has_Pulled() == false)
	{
		window.draw(destroyable_wall2_.spriteImage);
		window.draw(switch2_.spriteImage);
	}
	else
		window.draw(switch2_.spriteImage2);

	if (shadow_.getCastState() == false)
	{
		player_.spriteImage.setTextureRect(sf::IntRect(player_.isource.x, player_.isource.y, 682, 1020));
		window.draw(player_.spriteImage);
	}
	else
	{
		//Shadow shadow_(light.Shape().getPosition(), sf::Vector2f(50, 100), sf::Color::Transparent);
		shadow_.shadowCastImage.setTextureRect(sf::IntRect(shadow_.castisource.x, shadow_.castisource.y, 509, 619));
		if (!player_.walkleft)
			shadow_.shadowCastImage.setPosition(player_.Shape().getPosition().x - player_.Shape().getSize().x / 2, player_.Shape().getPosition().y - (player_.Shape().getSize().y) - 25);
		else
			shadow_.shadowCastImage.setPosition(player_.Shape().getPosition().x - player_.Shape().getSize().x / 2, player_.Shape().getPosition().y - (player_.Shape().getSize().y) - 45);
		window.draw(shadow_.shadowCastImage);
	}

	window.draw(undestroyable_wall1_.spriteImage2);
	window.draw(undestroyable_wall2_.spriteImage2);
	window.draw(undestroyable_wall3_.spriteImage2);

	if (key1_.getPickupedUpState() == false)
	{
		key1_.spriteImage.setTextureRect(sf::IntRect(key1_.isource.x, key1_.isource.y, 512, 1024));
		window.draw(key1_.spriteImage);
	}

	if (tele_available)
	{
		std::string teleport_text_str = "Teleport available to Light(s) : ";

		for (const auto& str : light_ids)
		{
			if (light_ids.size() > 1)
			{
				teleport_text_str += str + ", ";
			}
			else
				teleport_text_str += str;
		}

		teleport_text.setString(teleport_text_str);
		window.draw(teleport_text);
	}

	for (auto& guard : guards_)
	{
		guard->Draw(window);
	}

	for (const auto& light : lights_image_)
	{


		if (light->draw_shadow())
		{
			//Shadow shadow_(light.Shape().getPosition(), sf::Vector2f(50, 100), sf::Color::Transparent);
			shadow_.shadowImage.setTextureRect(sf::IntRect(shadow_.isource.x, shadow_.isource.y, 1024, 1024));
			//shadow_.Shape().setPosition(light->Shape().getPosition().x + 5, light->Shape().getPosition().y + FLOOR_OFFSET * 12);
			shadow_.shadowImage.setPosition(shadow_.Shape().getPosition().x - shadow_.Shape().getSize().x + 20, shadow_.Shape().getPosition().y - (shadow_.Shape().getSize().y * 1.5));
			window.draw(shadow_.shadowImage);
			//window.draw(shadow_.Shape());

			light_ids.push_back(std::to_string(light->ID()));


			tele_available = true;
		}

		light->Draw(window);

		if (light->get_In_Range() == true)
			userInter_1.ui_lights_.push_back(std::to_string(light->ID()));
	}

	userInter_1.Draw(window, player_, switch1_);
}

void GameState3::teleport_player(Light& light, int teleport_id, int floor_no)// Method for teleporting the player
{
	if (light.ID() == teleport_id)
	{
		player_.Shape().setPosition(lights_image_.at(teleport_id)->Shape().getPosition().x, player_.set_Ypos(LEVEL_HEIGHT, floor_no, TIER_HEIGHT, FLOOR_OFFSET));
	}
}

void GameState3::handle_state_changes()// change of states handled in here
{
	auto& state_current = state_manager_;
	if (game_over_ == true)
	{
		cleanUp();
		state_current.change_state(state_manager_.state_ptr<GameOverState>());
	}
	else
		if (next_Level == true)
		{
		cleanUp();
		state_current.change_state(state_manager_.state_ptr<MainMenuState>(false));
		}
		else
			if (change_MM == true)
				state_current.change_state(state_manager_.state_ptr<MainMenuState>(true));

}
void GameState3::cleanUp()// cleanup of the game
{
	lights_image_.clear();
	guards_.clear();
}

