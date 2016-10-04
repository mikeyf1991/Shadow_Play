#include "Guard.hpp"
#include "GameOverState.hpp"
#define LEVEL_WIDTH 1820
#define LEVEL_HEIGHT 985

Guard::Guard(sf::Vector2f position, sf::Vector2f size, sf::Color colour) // constructor for the guard
{
	m_shape.setSize(size);
	m_shape.setOutlineThickness(1);
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setFillColor(colour);
	m_shape.setOrigin(size / 2.f);
	m_shape.setPosition(position);
	start_position_ = position;

	I_Start_position_.x = (int)start_position_.x;
	I_Start_position_.y = (int)start_position_.y;

	//spritesheet set up
	if (!spriteTexture.loadFromFile("Guard/Guard Walk SpriteSheet-01.png"))
		std::cout << "Error couldnt load Guard" << std::endl;

	seen = false;
	caughtL = false;
	caughtR = false;

	spriteImage.setTexture(spriteTexture);

	walkLeft = 512;
	walkRight = 0;

	isource.x = 0;
	isource.y = walkLeft;
	m_shape.getSize();

	spriteImage.scale(0.37f, 0.37f);

	//spritesheet seen set up
	if (!seenspriteTexture.loadFromFile("Guard/Guard Spotted.png"))
		std::cout << "Error couldnt load Guard Seen" << std::endl;

	//spritesheet caught Left of player set up
	if (!caughtRspriteTexture.loadFromFile("Guard/Guard Caught Right.png"))
		std::cout << "Error couldnt load Guard caught Right" << std::endl;

	//spritesheet caught right of player set up
	if (!caughtLspriteTexture.loadFromFile("Guard/Guard Caught Left.png"))
		std::cout << "Error couldnt load Guard caught Left" << std::endl;

	seenspriteImage.setTexture(seenspriteTexture);

	caughtRspriteImage.setTexture(caughtRspriteTexture);

	caughtLspriteImage.setTexture(caughtLspriteTexture);

	seenisource.x = 0;
	seenisource.y = 0;

	caughtRisource.x = 0;
	caughtRisource.y = 0;

	caughtLisource.x = 0;
	caughtLisource.y = 0;

	seenspriteImage.scale(0.37f, 0.37f);
	caughtRspriteImage.scale(0.3f, 0.3175f);
	caughtLspriteImage.scale(0.3f, 0.3175f);
	//---------------------------------------------------------------------------



	movement_distance_ = 500.0f;
	AP_movement_distance_ = 250.0f;
	view_distance_ = 300.0f;
	distWalked = 0;
	temp_starting_pos_ = 0;
	sTemp_startingpos_ = 0;

	movement_speed_ = sf::Vector2f(SPEED1, 0.0f);
	Player_patrol_status_ = PlayerPatrolStatus::PATROL; // setting initial state to partrol
	//Shadow_patrol_status_ = ShadowPatrolStatus::PATROL;
	gotoXpos = 0;
	pOutofrange = true;
	pOutofrange2 = true;
	sOutofrange = true;
	sOutofrange2 = true;
	patrolled = false;
	turn_delay = 1.0f;
	state_delay = 5.0f;
	turnRight = false;
	game_over = false;
	played = false;
	played2 = false;

	faceLeft = true;
	seen_sound_ = BASS_SampleLoad(FALSE, "Sounds/player_spotted.wav", 0, 0, 1, NULL);
	main_channel_ = BASS_SampleGetChannel(seen_sound_, FALSE);

	lost_sound_ = BASS_SampleLoad(FALSE, "Sounds/player_escaped.wav", 0, 0, 1, NULL);
	main_channel2_ = BASS_SampleGetChannel(lost_sound_, FALSE);

	BASS_ChannelSetAttribute(main_channel_, BASS_ATTRIB_VOL, 0.4f);
	BASS_ChannelSetAttribute(main_channel2_, BASS_ATTRIB_VOL, 0.4f);
	offset = 1.0f;
	isit = false;
}


//-----------------------PLAYER SEARCHING-----------------------------------------
void Guard::updatePlayer(Player& player, Shadow& shadow)//this method updates the guard in terms of the player and shadow 
{
	I_pos_.x = (int)(Shape().getPosition().x);
	I_pos_.y = (int)Shape().getPosition().y;

	if (I_pos_.x < 0) {
		Shape().setPosition(0 + (Shape().getSize().x / 2), Shape().getPosition().y);
		turnRight = true;
		turnAround();
	}

	if (I_pos_.x >= LEVEL_WIDTH) {
		Shape().setPosition(LEVEL_WIDTH - (Shape().getSize().x / 2), Shape().getPosition().y);
		turnAround();
	}

	framecounter += frameclock.restart().asMilliseconds();

	spriteImage.setPosition(Shape().getPosition().x - Shape().getSize().x *1.75f, Shape().getPosition().y - Shape().getSize().y * 1.2f);


	switch (Player_patrol_status_) {

	case PlayerPatrolStatus::PATROL:
		//std::cout << "Player State 1" << std::endl;
		Patrol(player, shadow);
		break;
	case PlayerPatrolStatus::SEARCH:
		//std::cout << "State 2" << std::endl;
		Search(player, shadow);
		if (!played) {
			BASS_ChannelPlay(main_channel_, FALSE);
			played = true;
		}
		break;
	case PlayerPatrolStatus::AREAPATROL:
		//std::cout << "State 3" << std::endl;
		Area_patrol(player, shadow);
		break;
	case PlayerPatrolStatus::RETURN:
		//std::cout << "State 4" << std::endl;
		ReturnPatrol(player, shadow);
		if (!played2) {
			BASS_ChannelPlay(main_channel2_, FALSE);
			played2 = true;
		}
		break;
	case PlayerPatrolStatus::FOUND:
		//std::cout << "State 5" << std::endl;
		game_over = true;
		goto_game_over();
		break;
	default:
		break;
	}
}

void Guard::Patrol(Player& player, Shadow& shadow) // This function performs the patrol for the player or shadow
{

	Shape().move(movement_speed_);
	distWalked = (start_position_.x - Shape().getPosition().x);

	if (movement_speed_.x < 0) {
		faceLeft = true;
	}
	else
		faceLeft = false;

	if (distWalked >= movement_distance_) {
		turnRight = true;
		turnAround();
		isource.y = walkRight;
	}

	if (Shape().getPosition().x >= start_position_.x && turnRight == false) {
		turnAround();
		isource.y = walkLeft;
	}

	if ((Shape().getPosition().x - Shape().getSize().x / 2) <= 0)
	{
		Shape().setPosition(0 + Shape().getSize().x / 2, Shape().getPosition().y);
		turnRight = true;
		turnAround();
		isource.y = walkRight;
	}

	if ((Shape().getPosition().x + Shape().getSize().x / 2) >= LEVEL_WIDTH)
	{
		Shape().setPosition(LEVEL_WIDTH - Shape().getSize().x, Shape().getPosition().y);
		turnAround();
		isource.y = walkLeft;
	}


	if (player.Shape().getPosition().y == Shape().getPosition().y){
		if (player.Shape().getPosition().x < Shape().getPosition().x && (Shape().getPosition().x - player.Shape().getPosition().x) < view_distance_ && faceLeft){
			seen = true;
			Player_patrol_status_ = PlayerPatrolStatus::SEARCH;
		}

		if (player.Shape().getPosition().x > Shape().getPosition().x && (player.Shape().getPosition().x - Shape().getPosition().x) < view_distance_ && !faceLeft){
			seen = true;
			Player_patrol_status_ = PlayerPatrolStatus::SEARCH;
		}
	}

	if (shadow.Shape().getPosition().y == Shape().getPosition().y && shadow.getVisibleState() == true){
		if (shadow.Shape().getPosition().x < Shape().getPosition().x && (Shape().getPosition().x - shadow.Shape().getPosition().x) < view_distance_ && faceLeft)
		{
			if (shadow.getVisibleState() == true)
			{
				seen = true;
				Player_patrol_status_ = PlayerPatrolStatus::SEARCH;
			}
		}
		if (shadow.Shape().getPosition().x > Shape().getPosition().x && (shadow.Shape().getPosition().x - Shape().getPosition().x) < view_distance_ && !faceLeft){
			if (shadow.getVisibleState() == true)
			{
				seen = true;
				Player_patrol_status_ = PlayerPatrolStatus::SEARCH;
			}
		}
	}
}

void Guard::Search(Player& player, Shadow& shadow) //The function and calculations for searching for the player or shadow
{

	int pTempDistance = (Shape().getPosition().x - player.Shape().getPosition().x);
	int pTempDistance2 = -pTempDistance;

	int sTempDistance = (Shape().getPosition().x - shadow.Shape().getPosition().x);
	int sTempDistance2 = -sTempDistance;

	if (pTempDistance <= view_distance_ && player.Shape().getPosition().y == Shape().getPosition().y && pTempDistance >= 0)
		pOutofrange = false;
	if (pTempDistance2 <= view_distance_ && player.Shape().getPosition().y == Shape().getPosition().y && pTempDistance2 >= 0)
		pOutofrange2 = false;

	if (sTempDistance <= view_distance_ && shadow.Shape().getPosition().y == Shape().getPosition().y && sTempDistance >= 0)
		sOutofrange = false;
	if (sTempDistance2 <= view_distance_ && shadow.Shape().getPosition().y == Shape().getPosition().y && sTempDistance2 >= 0)
		sOutofrange2 = false;


	if (!pOutofrange || !pOutofrange2) {
		player.setLpos(player.Shape().getPosition());
		gotoXpos = player.getLpos().x;
	}
	if (!sOutofrange || !sOutofrange2) {
		shadow.setLpos(shadow.Shape().getPosition());
		gotoXpos = shadow.getLpos().x;
	}

	if (player.Shape().getPosition().y != Shape().getPosition().y || pTempDistance >= view_distance_)
		pOutofrange = true;

	if (player.Shape().getPosition().y != Shape().getPosition().y || pTempDistance2 >= view_distance_)
		pOutofrange2 = true;

	if (shadow.Shape().getPosition().y != Shape().getPosition().y || sTempDistance >= view_distance_)
		sOutofrange = true;

	if (shadow.Shape().getPosition().y != Shape().getPosition().y || sTempDistance2 >= view_distance_)
		sOutofrange2 = true;

	if (Shape().getPosition().x > gotoXpos && !caughtL && !caughtR) {
		movement_speed_ = sf::Vector2f(SPEED1, 0.0f);
		Shape().move(movement_speed_);
		isource.y = walkLeft;
	}

	if (Shape().getPosition().x < gotoXpos && !caughtL && !caughtR) {
		movement_speed_ = sf::Vector2f(-SPEED1, 0.0f);
		Shape().move(movement_speed_);
		isource.y = walkRight;
	}

	if ((Shape().getPosition().x - gotoXpos) == 0 || ((Shape().getPosition().x - gotoXpos) + offset) == 0 || ((Shape().getPosition().x - gotoXpos) - offset) == 0) {  //
		temp_starting_pos_ = gotoXpos;
		Player_patrol_status_ = PlayerPatrolStatus::AREAPATROL;
	}

	if (player.Shape().getPosition().y == Shape().getPosition().y)
	{
		go_Time.restart().Zero;
		Check_distance(player, shadow);
	}
	
}
void Guard::Check_distance(const Player& player, const Shadow& shadow) // function to check the distance between the player and guard of shadow and guard.
{
	//go_Time.restart();
	int tempDist1 = 150;

		go_Timer += go_Time.restart().asMilliseconds();

		if (player.Shape().getPosition().x < Shape().getPosition().x && (Shape().getPosition().x - player.Shape().getPosition().x) < tempDist1 && movement_speed_.x <= 0)
		{
			caughtL = true;
			go_Timer += go_Time.restart().asMicroseconds();
			if (go_Timer >= 250)
				Player_patrol_status_ = PlayerPatrolStatus::FOUND;
		}

		if (player.Shape().getPosition().x > Shape().getPosition().x && (player.Shape().getPosition().x - Shape().getPosition().x) < tempDist1 && movement_speed_.x >= 0)
		{
			caughtR = true;
			go_Timer += go_Time.restart().asMicroseconds();
			if (go_Timer >= 250)
				Player_patrol_status_ = PlayerPatrolStatus::FOUND;
		}

}

void Guard::Area_patrol(Player& player, Shadow& shadow) // function to handle the area patrol of the guard
{
	//std::cout << "Patroling Area" << std::endl;

	state_delay -= 0.005f; // Change for how long Guard is in Patrol State for.

	if (state_delay >= 0.0f)
	{
		moveme = true;
		turn_delay -= 0.2f;

		if (turn_delay <= 0.0f)
		{
			if (moveme)
				Shape().move(movement_speed_);

			distWalked = (temp_starting_pos_ - Shape().getPosition().x - Shape().getSize().x / 2);


			if (distWalked >= AP_movement_distance_ || (Shape().getPosition().x - Shape().getSize().x / 2) <= 0) {
				turnRight = true;
				turnAround();
				moveme = false;
				isource.y = walkRight;
			}


			if (Shape().getPosition().x >= temp_starting_pos_ + AP_movement_distance_ || (Shape().getPosition().x + Shape().getSize().x / 2) >= LEVEL_WIDTH) {
				turnRight = false;
				turnAround();
				moveme = false;
				isource.y = walkLeft;
			}

			if (player.Shape().getPosition().y == Shape().getPosition().y) {
				Check_distance(player, shadow);
			}
		}
	}
	else {
		seen = false;
		Player_patrol_status_ = PlayerPatrolStatus::RETURN;
	}
}
void Guard::ReturnPatrol(Player& player, Shadow& shadow) // the return patrol function for the guard
{
	movement_speed_ = sf::Vector2f(2.0, 0.0f);

	if (I_pos_.x < I_Start_position_.x)
	{
		Shape().move(movement_speed_);
		isource.y = 0; // Annimation
	}

	if (I_pos_.x > I_Start_position_.x)
	{
		Shape().move(-movement_speed_);
		isource.y = walkLeft; //Animation related
	}
	if (player.Shape().getPosition().y == Shape().getPosition().y)
	{
		Check_distance(player, shadow);
	}


	if ((I_pos_.x - I_Start_position_.x) == 0 || ((I_pos_.x - I_Start_position_.x) + offset) == 0 || ((I_pos_.x - I_Start_position_.x) - offset) == 0)
	{
		Player_patrol_status_ = PlayerPatrolStatus::PATROL;
		softReset();
	}
}
//--------------------------------------------------------------------------------
void Guard::turnAround() // method to turn the guard around when he is moving.
{

	if (!turnRight)
	{
		movement_speed_ = sf::Vector2f(0.0f, 0.0f);
		turn_delay -= 0.2f;
		if (turn_delay <= 0.0f)
		{
			movement_speed_ = sf::Vector2f(SPEED1, 0.0f);
			distWalked = 0;
			turn_delay = 1.0f;
			isource.y = walkLeft;
		}
	}
	if (turnRight)
	{
		movement_speed_ = sf::Vector2f(0.0f, 0.0f);
		turn_delay -= 0.2f; // Reinitialize turn delay
		if (turn_delay <= 0.0f)
		{
			movement_speed_ = sf::Vector2f(-SPEED1, 0.0f);
			distWalked = 0;
			turn_delay = 1.0f;
			turnRight = false;
			isource.y = walkRight;
		}
	}
}
bool Guard::goto_game_over() // bool to make the game go to game over
{
	return game_over;
}
void Guard::softReset() // method for a soft reset for the guards
{

	pOutofrange = true;
	pOutofrange2 = true;
	sOutofrange = true;
	sOutofrange2 = true;

	state_delay = 5.0f;
	turn_delay = 1.0f;
	distWalked = 0; // distance walked
	gotoXpos = NULL;
	moveme = false;
	played = false;
	played2 = false;
}
void Guard::Draw(sf::RenderWindow& window) // Draw method
{
	spriteImage.setTextureRect(sf::IntRect(isource.x, isource.y, 512, 512));
	seenspriteImage.setPosition(m_shape.getPosition().x - 10, m_shape.getPosition().y - m_shape.getSize().y * 2.05f);
	caughtRspriteImage.setPosition(m_shape.getPosition().x - 20, m_shape.getPosition().y - m_shape.getSize().y * 1.77f);
	caughtLspriteImage.setPosition(m_shape.getPosition().x - m_shape.getSize().x - 5, m_shape.getPosition().y - m_shape.getSize().y * 1.77f);
	//spriteImage.setPosition(Shape().getPosition().x - Shape().getSize().x *1.75f, Shape().getPosition().y - Shape().getSize().y * 1.2f);

	if (!caughtL && !caughtR)
		window.draw(spriteImage);
	if (seen && !caughtL && !caughtR)
	{
		window.draw(seenspriteImage);
	}
	else if (caughtR)
		window.draw(caughtRspriteImage);
	else if (caughtL)
		window.draw(caughtLspriteImage);
}

float Guard::set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset) // setting the guards Y position within the level
{
	float ypos = lvlh - ((m_shape.getSize().y) + (floor_no * floor_h) + ground_offset);	//sets the ypos
	return ypos;
}