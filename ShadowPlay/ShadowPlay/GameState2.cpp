#include "GameState2.hpp"
#include "GameOverState.hpp"


#define LEVEL_WIDTH 1280
#define LEVEL_HEIGHT 1960

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960
#define TIER_HEIGHT 319
#define TIER_WIDTH 960
#define FLOOR_OFFSET 5

GameState2::GameState2(StateManager& state_manager) :
AbstractState(state_manager),
player_(sf::Vector2f(25, 885), sf::Vector2f(50, 100), sf::Color::Transparent),
exit_(sf::Vector2f(1100, 160), sf::Vector2f(50, 100), sf::Color::Black),
key1_(sf::Vector2f(key1_.getPositionX(), key1_.getPositionY()), sf::Vector2f(50, 100), sf::Color::Blue),
shadow_(shadow_.Shape().getPosition(), sf::Vector2f(50, 100), sf::Color::Transparent)
{
	//==========================================================================================================================================================//
	//----------------------------- set the y positions of the object using the new y method -------------------------------------------------------------------//
	player_.Shape().setPosition(player_.Shape().getPosition().x, player_.set_Ypos(LEVEL_HEIGHT, 0, TIER_HEIGHT, FLOOR_OFFSET));

	exit_.Shape().setPosition(exit_.Shape().getPosition().x, exit_.set_Ypos(LEVEL_HEIGHT, 2, TIER_HEIGHT, FLOOR_OFFSET));
	exit_.spriteImage.setPosition(exit_.Shape().getPosition());
	//==========================================================================================================================================================//
	create_lights();
	create_guards();
	userInter_1.init(view_main);
	key1_.setPositionX(1100);
	key1_.setPositionY(key1_.set_Ypos(LEVEL_HEIGHT, 1, TIER_HEIGHT, FLOOR_OFFSET));

	game_over_ = false;
	next_Level = false;
	//change_MM = false;

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
int GameState2::rng(int min, int max)
{
	// initialize once per thread
	static std::random_device srd;
	static std::mt19937 smt(srd());

	std::uniform_int_distribution<> dist(min, max); // Generate a number between min and max

	return dist(smt);
}
void GameState2::create_lights()
{
	short int light1_x = 380; short int light1_y = 830;
	Light light1(sf::Vector2f(light1_x, light1_y), sf::Vector2f(150, 200), sf::Color::Transparent, 0);
	light1.Shape().setPosition(light1.Shape().getPosition().x, light1.set_Ypos(LEVEL_HEIGHT, 0, TIER_HEIGHT, FLOOR_OFFSET));
	light1.set_In_Range(false);
	lights_.push_back(light1);

	short int light2_x = 600; short int light2_y = 510;
	Light light2(sf::Vector2f(light2_x, light2_y), sf::Vector2f(150, 200), sf::Color::Transparent, 1);
	light2.Shape().setPosition(light2.Shape().getPosition().x, light2.set_Ypos(LEVEL_HEIGHT, 0, TIER_HEIGHT, FLOOR_OFFSET));
	light2.set_In_Range(false);
	lights_.push_back(light2);

	short int light3_x = 500; short int light3_y = 510;
	Light light3(sf::Vector2f(light3_x, light3_y), sf::Vector2f(150, 200), sf::Color::Transparent, 2);
	light3.Shape().setPosition(light3.Shape().getPosition().x, light3.set_Ypos(LEVEL_HEIGHT, 1, TIER_HEIGHT, FLOOR_OFFSET));
	light3.set_In_Range(false);
	lights_.push_back(light3);
}

void GameState2::create_guards()
{
	guards_.emplace_back(std::move(std::make_unique<Guard>(sf::Vector2f(700, 560), sf::Vector2f(50, 100), sf::Color::Red)));
	guards_[0]->Shape().setPosition(guards_[0]->Shape().getPosition().x, guards_[0]->set_Ypos(LEVEL_HEIGHT, 0, TIER_HEIGHT, FLOOR_OFFSET));

	guards_.emplace_back(std::move(std::make_unique<Guard>(sf::Vector2f(600, 245), sf::Vector2f(50, 100), sf::Color::Yellow)));
	guards_[1]->Shape().setPosition(guards_[1]->Shape().getPosition().x, guards_[1]->set_Ypos(LEVEL_HEIGHT, 0, TIER_HEIGHT, FLOOR_OFFSET));
}

GameState2::~GameState2()
{
}

void GameState2::handle_state_changes()
{

}
void GameState2::handle_input(const sf::Time& delta)
{
	auto& inputManager = state_manager_.get_input_manager();

	if (inputManager.is_key_released(InputKey::escape))
	{
		state_manager_.quit();
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
}

void GameState2::update(const sf::Time& delta)
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
void GameState2::pause()
{
	set_paused(true);
}

void GameState2::resume()
{
	set_paused(false);
}


//void GameState2::render()
//{
//
//	sf::RenderWindow& window = state_manager_.get_render_window();
//	window.setView(view_main); // applying the view
//	window.draw(bg_sprite);
//	std::string Next_Level_txt = " Next_Level ";
//
//	player_.spriteImage.setTextureRect(sf::IntRect(player_.isource.x, player_.isource.y, 30, 40));
//	window.draw(player_.spriteImage);
//
//	for (auto& guard : guards_)
//		guard->Draw(window);
//
//	for (const auto& light : lights_)
//	{
//		window.draw(light.Shape());
//	}
//	for (auto& f_sprite : floor_sprite)
//	{
//		window.draw(f_sprite);
//	}
//	
//}
void GameState2::CheckOtherLights(Light& light)
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
void GameState2::in_range()
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
void GameState2::check_collisions()
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
}

void GameState2::render()
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
void GameState2::savePlayerInfo(const char* filename){}

void GameState2::readPlayerInfo(const char* filename){}

void GameState2::LoadGame(Player& player, Guard& guards, Light& lights){}

void GameState2::create_exit(){}

void GameState2::teleport_player(Light& light, int teleport_id, int floor_no){}