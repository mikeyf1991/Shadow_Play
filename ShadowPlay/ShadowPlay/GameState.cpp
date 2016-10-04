#include "GameState.hpp"
#include "GameOverState.hpp"


#define LEVEL_WIDTH 1820
#define LEVEL_HEIGHT 1960

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960
#define TIER_HEIGHT 319
#define TIER_WIDTH 960
#define FLOOR_OFFSET 5

#pragma warning(disable : 4018)

GameState::GameState(StateManager& state_manager, bool loadFromFile) : AbstractState(state_manager, loadFromFile),
player_(sf::Vector2f(25, 885), sf::Vector2f(50, 100), sf::Color::Transparent),
exit_(sf::Vector2f(1650, 160), sf::Vector2f(50, 100), sf::Color::Black),
key1_(sf::Vector2f(key1_.getPositionX(), key1_.getPositionY()), sf::Vector2f(50, 100), sf::Color::Blue),
shadow_(shadow_.Shape().getPosition(), sf::Vector2f(50, 100), sf::Color::Transparent),
switch1_(sf::Vector2f(860, 885), sf::Vector2f(50, 50), sf::Color::Transparent, 0)
{
	if (load_game_ == true)
	{
		readPlayerInfo("Save_Info.xml");
		//==========================================================================================================================================================//
		//----------------------------- set the y positions of the object using the new y method -------------------------------------------------------------------//
		player_.Shape().setPosition(getLoadPlayerPos().x, getLoadPlayerPos().y);
		switch1_.Shape().setPosition(switch1_.Shape().getPosition().x, switch1_.set_Ypos(LEVEL_HEIGHT, 1, TIER_HEIGHT, FLOOR_OFFSET));
		switch1_.spriteImage.setPosition(switch1_.Shape().getPosition());
		//switch1_.set_Pulled(false);
		exit_.Shape().setPosition(exit_.Shape().getPosition().x, exit_.set_Ypos(LEVEL_HEIGHT, 2, TIER_HEIGHT, FLOOR_OFFSET));
		exit_.spriteImage.setPosition(exit_.Shape().getPosition());
		//==========================================================================================================================================================//
		create_lights();
		create_guards();
		guards_[0]->Shape().setPosition(getLoadGuard1Pos().x, getLoadGuard1Pos().y);
		guards_[1]->Shape().setPosition(getLoadGuard2Pos().x, getLoadGuard2Pos().y);

		userInter_1.init(view_main);
		key1_.setPositionX(1100);
		key1_.setPositionY(key1_.set_Ypos(LEVEL_HEIGHT, 1, TIER_HEIGHT, FLOOR_OFFSET));
		key1_.setPickupedUpState(getLoadDoorState());
		game_over_ = false;
		next_Level = false;
		change_MM = false;
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

		if (!floor.loadFromFile("floor2.png"))
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
			if (i >= 7)
			{
				float current_x = floor_sprite[j].getPosition().x;
				f_sprite.setPosition(current_x + floor.getSize().x, floor_sprite[j].getPosition().y);
				j++;
			}
			std::cout << "\nPosition: " << f_sprite.getPosition().y;
		}

		good_job_ = BASS_SampleLoad(FALSE, "good.wav", 0, 0, 1, NULL);
		main_channel_ = BASS_SampleGetChannel(good_job_, FALSE);

		Bg_music_ = BASS_StreamCreateFile(FALSE, "main_game_music.mp3", 0, 0, BASS_SAMPLE_LOOP);

		BASS_ChannelSetAttribute(Bg_music_, BASS_ATTRIB_VOL, 0.1f);
		BASS_ChannelPlay(Bg_music_, FALSE);
	}
	else
	{
		//==========================================================================================================================================================//
		//----------------------------- set the y positions of the object using the new y method -------------------------------------------------------------------//
		player_.Shape().setPosition(player_.Shape().getPosition().x, player_.set_Ypos(LEVEL_HEIGHT, 0, TIER_HEIGHT, FLOOR_OFFSET));
		switch1_.Shape().setPosition(switch1_.Shape().getPosition().x, switch1_.set_Ypos(LEVEL_HEIGHT, 3, TIER_HEIGHT, FLOOR_OFFSET) + 140);
		switch1_.spriteImage.setPosition(switch1_.Shape().getPosition());
		switch1_.spriteImage2.setPosition(switch1_.Shape().getPosition().x, switch1_.Shape().getPosition().y + 40);
		switch1_.set_Pulled(false);
		exit_.Shape().setPosition(exit_.Shape().getPosition().x, exit_.set_Ypos(LEVEL_HEIGHT, 3, TIER_HEIGHT, FLOOR_OFFSET));
		exit_.spriteImage.setPosition(exit_.Shape().getPosition());
		//==========================================================================================================================================================//
		create_lights();
		create_guards();
		userInter_1.init(view_main);
		key1_.setPositionX(480);
		key1_.setPositionY(key1_.set_Ypos(LEVEL_HEIGHT, 2, TIER_HEIGHT, FLOOR_OFFSET));

		game_over_ = false;
		next_Level = false;
		change_MM = false;

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

		if (!floor.loadFromFile("floor2.png"))
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
			if (i >= 7)
			{
				float current_x = floor_sprite[j].getPosition().x;
				f_sprite.setPosition(current_x + floor.getSize().x, floor_sprite[j].getPosition().y);
				j++;
			}
		}

		good_job_ = BASS_SampleLoad(FALSE, "good.wav", 0, 0, 1, NULL);
		main_channel_ = BASS_SampleGetChannel(good_job_, FALSE);

		Bg_music_ = BASS_StreamCreateFile(FALSE, "main_game_music.mp3", 0, 0, BASS_SAMPLE_LOOP);

		BASS_ChannelSetAttribute(Bg_music_, BASS_ATTRIB_VOL, 0.1f);
		BASS_ChannelPlay(Bg_music_, FALSE);

	}
}
int GameState::rng(int min, int max)
{
	// initialize once per thread
	static std::random_device srd;
	static std::mt19937 smt(srd());

	std::uniform_int_distribution<> dist(min, max); // Generate a number between min and max

	return dist(smt);
}
void GameState::create_lights()
{
	short int light1_x = 650; short int light1_y = 830; // x = 380
	Light light1(sf::Vector2f(light1_x, light1_y), sf::Vector2f(150, 200), sf::Color::Transparent, 0);
	light1.Shape().setPosition(light1.Shape().getPosition().x, light1.set_Ypos(LEVEL_HEIGHT, 0, TIER_HEIGHT, FLOOR_OFFSET));
	light1.set_In_Range(false);
	lights_.push_back(light1);

	short int light2_x = 370; short int light2_y = 510; // 90
	Light light2(sf::Vector2f(light2_x, light2_y), sf::Vector2f(150, 200), sf::Color::Transparent, 1);
	light2.Shape().setPosition(light2.Shape().getPosition().x, light2.set_Ypos(LEVEL_HEIGHT, 1, TIER_HEIGHT, FLOOR_OFFSET));
	light2.set_In_Range(false);
	lights_.push_back(light2);

	short int light3_x = 920; short int light3_y = 510; // 890
	Light light3(sf::Vector2f(light3_x, light3_y), sf::Vector2f(150, 200), sf::Color::Transparent, 2);
	light3.Shape().setPosition(light3.Shape().getPosition().x, light3.set_Ypos(LEVEL_HEIGHT, 1, TIER_HEIGHT, FLOOR_OFFSET));
	light3.set_In_Range(false);
	lights_.push_back(light3);
	short int light4_x = 190; short int light4_y = 195;//260
	Light light4(sf::Vector2f(light4_x, light4_y), sf::Vector2f(150, 200), sf::Color::Transparent, 3);
	light4.Shape().setPosition(light4.Shape().getPosition().x, light4.set_Ypos(LEVEL_HEIGHT, 2, TIER_HEIGHT, FLOOR_OFFSET));
	light4.set_In_Range(false);
	lights_.push_back(light4);
	short int light5_x = 1170; short int light5_y = 195;//650
	Light light5(sf::Vector2f(light5_x, light5_y), sf::Vector2f(150, 200), sf::Color::Transparent, 4);
	light5.Shape().setPosition(light5.Shape().getPosition().x, light5.set_Ypos(LEVEL_HEIGHT, 2, TIER_HEIGHT, FLOOR_OFFSET));
	light5.set_In_Range(false);
	lights_.push_back(light5);
	short int light6_x = 480; short int light6_y = 195;
	Light light6(sf::Vector2f(light6_x, light6_y), sf::Vector2f(150, 200), sf::Color::Transparent, 5);
	light6.Shape().setPosition(light6.Shape().getPosition().x, light6.set_Ypos(LEVEL_HEIGHT, 3, TIER_HEIGHT, FLOOR_OFFSET));
	light6.set_In_Range(false);
	lights_.push_back(light6);
}
void GameState::create_guards()
{
	guards_.emplace_back(std::move(std::make_unique<Guard>(sf::Vector2f(655, 560), 
		sf::Vector2f(50, 100), sf::Color::Red)));
	guards_[0]->Shape().setPosition(guards_[0]->Shape().getPosition().x, 
		guards_[0]->set_Ypos(LEVEL_HEIGHT, 1, TIER_HEIGHT, FLOOR_OFFSET));

	guards_.emplace_back(std::move(std::make_unique<Guard>(sf::Vector2f(1660, 245), 
		sf::Vector2f(50, 100), sf::Color::Yellow)));
	guards_[1]->Shape().setPosition(guards_[1]->Shape().getPosition().x, 
		guards_[1]->set_Ypos(LEVEL_HEIGHT, 2, TIER_HEIGHT, FLOOR_OFFSET));

	guards_.emplace_back(std::move(std::make_unique<Guard>(sf::Vector2f(190, 245),
		sf::Vector2f(50, 100), sf::Color::Yellow)));
	guards_[2]->Shape().setPosition(guards_[2]->Shape().getPosition().x,
		guards_[2]->set_Ypos(LEVEL_HEIGHT, 3, TIER_HEIGHT, FLOOR_OFFSET));
}
GameState::~GameState(){}
void GameState::pause()
{
	set_paused(true);
}

void GameState::resume()
{
	set_paused(false);
}

void GameState::handle_input(const sf::Time& delta)
{
	auto& inputManager = state_manager_.get_input_manager();

	sf::Vector2i windowO(view_main.getCenter().x - view_main.getSize().x / 2, view_main.getCenter().y - view_main.getSize().y / 2);
	
	mouse_pos.x = windowO.x + inputManager.get_mouse_x();
	mouse_pos.y = windowO.y + inputManager.get_mouse_y();

	if (inputManager.is_key_released(InputKey::escape))
	{
		std::cout << "Saving current Level Information...\n";
		savePlayerInfo("player_data.txt");

		std::cout << "\nQuitting\n";
		change_MM = true;
	}
	if (switch1_.in_Range() == true)
	{
		if (inputManager.is_key_pressed(InputKey::p))
		{
			switch1_.set_Pulled(true);
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
	if (inputManager.is_key_pressed(InputKey::a))
	{
		player_.Shape().move(sf::Vector2f(-5.0f, 0.0f));
		if (player_.Shape().getPosition().x - (player_.Shape().getSize().x / 2) < 0)
			player_.Shape().setPosition(0 + (player_.Shape().getSize().x / 2), player_.Shape().getPosition().y);
		player_.isource.y = 40;
		if (player_.framecounter >= player_.frameswitch)
		{
			player_.framecounter = 0;
			player_.isource.x += 30;
			if (player_.isource.x >= player_.spriteTexture.getSize().x)
				player_.isource.x = 0;
		}

	}
	else if (inputManager.is_key_pressed(InputKey::d))
	{
		player_.Shape().move(sf::Vector2f(5.0f, 0.0f));
		if (player_.Shape().getPosition().x + (player_.Shape().getSize().x / 2) >= LEVEL_WIDTH)
			player_.Shape().setPosition(LEVEL_WIDTH - (player_.Shape().getSize().x / 2), player_.Shape().getPosition().y);
		player_.isource.y = 0;
		if (player_.framecounter >= player_.frameswitch)
		{
			player_.framecounter = 0;
			player_.isource.x += 30;
			if (player_.isource.x >= player_.spriteTexture.getSize().x)
				player_.isource.x = 0;
		}

	}

	if (inputManager.is_key_released(InputKey::a))
	{
		player_.isource.y = 120;
		player_.isource.x = 0;
	}

	if (inputManager.is_key_released(InputKey::d))
	{
		player_.isource.y = 80;
		player_.isource.x = 0;
	}
	if (inputManager.is_key_pressed(InputKey::l))
	{
		readPlayerInfo("Save_Info.xml");
	}
	if (inputManager.is_key_pressed(InputKey::w))
	{
		player_.Shape().move(sf::Vector2f(0.0f, -5.0f));
		if (player_.Shape().getPosition().y - (player_.Shape().getSize().y / 2) <= 0)
			player_.Shape().setPosition(player_.Shape().getPosition().x, 0 + (player_.Shape().getSize().y / 2));
	}
	else if (inputManager.is_key_pressed(InputKey::s))
	{
		player_.Shape().move(sf::Vector2f(0.0f, 5.0f));
		if (player_.Shape().getPosition().y + player_.Shape().getSize().y > LEVEL_HEIGHT)
			player_.Shape().setPosition(player_.Shape().getPosition().x, LEVEL_HEIGHT - player_.Shape().getSize().y);
	}


}

void GameState::savePlayerInfo(const char* filename)
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

void GameState::LoadGame(Player& player, Guard& guards, Light& lights)
{
	auto& state_current = state_manager_;
	player.setLevelNumber(getLevelNumber());
	player.setPlayerPos(getLoadPlayerPos());
}

void GameState::readPlayerInfo(const char* filename)
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

void GameState::CheckOtherLights(Light& light)
{
	auto& inputManager = state_manager_.get_input_manager();

	for (auto& otherLight : lights_)
	{
		otherLight.set_shadow(false);

		if (light.ID() != otherLight.ID())
		{

			const auto& pos = light.Shape().getPosition();

			if (std::abs(otherLight.Shape().getPosition().x - pos.x) < 400 && (std::abs(otherLight.Shape().getPosition().y - pos.y) < 400))
			{

				if (otherLight.ID() == 0)
				{
					otherLight.set_In_Range(true);
					if (inputManager.right_clicked())
					{
						if (otherLight.Shape().getGlobalBounds().contains(mouse_pos))
						{
							otherLight.set_shadow(true);
							shadow_.setVisibleState(true);
							if (inputManager.left_clicked())
							{
								teleport_player(otherLight, otherLight.ID(), 0);
								otherLight.set_In_Range(false);

							}
						}
					}
				}

				if (otherLight.ID() == 1)
				{
					otherLight.set_In_Range(true);
					if (otherLight.Shape().getGlobalBounds().contains(mouse_pos))
					{
						if (inputManager.right_clicked())
						{
							otherLight.set_shadow(true);
							shadow_.setVisibleState(true);
							if (inputManager.left_clicked())
							{
								teleport_player(otherLight, otherLight.ID(), 1);
								otherLight.set_In_Range(false);

							}
						}
					}
				}

				if (otherLight.ID() == 2)
				{
					otherLight.set_In_Range(true);
					if (otherLight.Shape().getGlobalBounds().contains(mouse_pos))
					{
						if (inputManager.right_clicked())
						{
							otherLight.set_shadow(true);
							shadow_.setVisibleState(true);
							if (inputManager.left_clicked())
							{
								teleport_player(otherLight, otherLight.ID(), 1);
								otherLight.set_In_Range(false);

							}
						}
					}
				}

				if (otherLight.ID() == 3)
				{
					otherLight.set_In_Range(true);
					if (otherLight.Shape().getGlobalBounds().contains(mouse_pos))
					{
						if (inputManager.right_clicked())
						{
							otherLight.set_shadow(true);
							shadow_.setVisibleState(true);
							if (inputManager.left_clicked())
							{
								teleport_player(otherLight, otherLight.ID(), 2);
								otherLight.set_In_Range(false);

							}
						}
					}
				}

				if (otherLight.ID() == 4)
				{
					if (otherLight.Shape().getGlobalBounds().contains(mouse_pos))
					{
						otherLight.set_In_Range(true);

						if (inputManager.right_clicked())
						{
							otherLight.set_shadow(true);
							shadow_.setVisibleState(true);
							if (inputManager.left_clicked())
							{
								teleport_player(otherLight, otherLight.ID(), 2);
								otherLight.set_In_Range(false);

							}
						}
					}
				}
			}
		}
	}
}

void GameState::in_range()
{
	for (auto& light : lights_)
	{
		light.set_shadow(false);
		shadow_.setVisibleState(false);

		if (light.can_teleport())
		{
			CheckOtherLights(light);
			break;
		}
	}
}

void GameState::check_collisions()
{

	for (auto& light : lights_)
	{
		if (light.Shape().getGlobalBounds().intersects(player_.Shape().getGlobalBounds()))
		{
			light.set_teleport(true);
		}
		else
		{
			light.set_teleport(false);
			light.set_In_Range(false);
			shadow_.setVisibleState(false);
		}
	}

	if (exit_.Shape().getGlobalBounds().intersects(player_.Shape().getGlobalBounds()) && key1_.getPickupedUpState() == true)
	{
		player_.setLevelNumber(player_.getLevelNumber() + 1);
		BASS_ChannelPlay(main_channel_, FALSE);
		std::cout << "next level" << std::endl;
		std::cout << "Level number: " << player_.getLevelNumber() << std::endl;
		next_Level = true;
	}

	if (switch1_.Shape().getGlobalBounds().intersects(player_.Shape().getGlobalBounds()))
	{
		switch1_.set_inRange(true);
	}
}

void GameState::update(const sf::Time& delta)
{
	key1_.framecounter += key1_.frameclock.restart().asMilliseconds();
	if (key1_.framecounter >= key1_.frameswitch)
	{
		key1_.framecounter = 0;
		key1_.isource.x += 24;
		if (key1_.isource.x >= key1_.spriteTexture.getSize().x)
			key1_.isource.x = 0;
	}
	key1_.update(player_);

	key1_.spriteImage.setPosition(key1_.getPositionX(), key1_.getPositionY());
	userInter_1.updateKey(key1_, player_, view_main);
	userInter_1.updatePlayerPos(player_, view_main);

	for (auto& light : lights_)
	{
		userInter_1.updateLight(light, view_main);

		if (light.get_In_Range() == false)
			light.Shape().setOutlineColor(sf::Color::Yellow);
		else
			light.Shape().setOutlineColor(sf::Color::Green);

	}

	check_collisions();
	in_range();
	teleport_text.setPosition(player_.Shape().getPosition().x - 100, player_.Shape().getPosition().y - 100);

	for (auto& guard : guards_)
	{
		guard->updatePlayer(player_, shadow_);
		//guard->updateShadow(shadow_, player_);

		if (guard->framecounter >= guard->frameswitch)
		{
			guard->framecounter = 0;
			guard->isource.x += 30;
			if (guard->isource.x >= guard->spriteTexture.getSize().x)
				guard->isource.x = 0;
		}
		if (guard->goto_game_over() == true)
			game_over_ = true;
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
		player_.Shape().getPosition().y - player_.Shape().getSize().y / 2);


	if (shadow_.getVisibleState() == true)
	{

		shadow_.isource.y = 80;
		shadow_.spriteImage.setPosition(shadow_.Shape().getPosition().x - (shadow_.Shape().getSize().x / 2),
			shadow_.Shape().getPosition().y - (shadow_.Shape().getSize().y / 2));
	}
	player_.framecounter += player_.frameclock.restart().asMilliseconds();
}

void GameState::render()
{
	userInter_1.ui_lights_.clear();
	sf::RenderWindow& window = state_manager_.get_render_window();
	window.setView(view_main); // applying the view

	std::vector<std::string> light_ids;

	bool tele_available = false;
//	window.draw(bg_sprite);
	for (auto& f_sprite : floor_sprite)
	{
		window.draw(f_sprite);
	}
	window.draw(exit_.spriteImage);
	if (switch1_.has_Pulled() == false)
	window.draw(switch1_.spriteImage);
	else
		window.draw(switch1_.spriteImage2);

	player_.spriteImage.setTextureRect(sf::IntRect(player_.isource.x, player_.isource.y, 30, 40));
	window.draw(player_.spriteImage);


	if (key1_.getPickupedUpState() == false)
	{
		key1_.spriteImage.setTextureRect(sf::IntRect(key1_.isource.x, key1_.isource.y, 24, 41));
		window.draw(key1_.spriteImage);

	}

	for (const auto& light : lights_)
	{
		window.draw(light.Shape());

		if (light.draw_shadow())
		{
			//Shadow shadow_(light.Shape().getPosition(), sf::Vector2f(50, 100), sf::Color::Transparent);
			shadow_.spriteImage.setTextureRect(sf::IntRect(shadow_.isource.x, shadow_.isource.y, 30, 40));
			shadow_.Shape().setPosition(light.Shape().getPosition().x, light.Shape().getPosition().y + player_.Shape().getSize().y / 2);
			window.draw(shadow_.spriteImage);

			light_ids.push_back(std::to_string(light.ID()));


			tele_available = true;
		}
		if (light.get_In_Range() == true)
			userInter_1.ui_lights_.push_back(std::to_string(light.ID()));
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



	userInter_1.Draw(window, player_);
}

void GameState::teleport_player(Light& light, int teleport_id, int floor_no)
{
	if (light.ID() == teleport_id)
	{
		player_.Shape().setPosition(lights_.at(teleport_id).Shape().getPosition().x, player_.set_Ypos(LEVEL_HEIGHT, floor_no, TIER_HEIGHT, FLOOR_OFFSET));
	}
}

void GameState::handle_state_changes()
{
	auto& state_current = state_manager_;
	if (game_over_ == true)
	{
		state_current.change_state(state_manager_.state_ptr<GameOverState>());
		std::cout << "Game Over" << std::endl;
	}

	if (next_Level == true)
	{
		state_current.change_state(state_manager_.state_ptr<GameState2>());
		std::cout << "Level Changed" << std::endl;
	}
	if (change_MM == true)
		state_current.change_state(state_manager_.state_ptr<MainMenuState>(true));

}

