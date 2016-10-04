#include "Guard.hpp"
#include "GameOverState.hpp"
#define LEVEL_WIDTH 1280
#define LEVEL_HEIGHT 985

Guard::Guard(sf::Vector2f position, sf::Vector2f size, sf::Color colour)
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
	if (!spriteTexture.loadFromFile("sonic-1.png"))
		std::cout << "Error couldnt load Guard" << std::endl;
	else
		std::cout << "im telling you it loaded" << std::endl;

	spriteImage.setTexture(spriteTexture);


	isource.x = 0;
	isource.y = 40;
	m_shape.getSize();

	spriteImage.scale(2.5f, 2.5f);

	movement_distance_ = 500.0f;
	AP_movement_distance_ = 250.0f;
	view_distance_ = 150.0f;
	distWalked = 0;
	temp_starting_pos_ = 0;
	sTemp_startingpos_ = 0;

	movement_speed_ = sf::Vector2f(SPEED1, 0.0f);
	Player_patrol_status_ = PlayerPatrolStatus::PATROL;
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
	seen_sound_ = BASS_SampleLoad(FALSE, "player_spotted.wav", 0, 0, 1, NULL);
	main_channel_ = BASS_SampleGetChannel(seen_sound_, FALSE);

	lost_sound_ = BASS_SampleLoad(FALSE, "player_escaped.wav", 0, 0, 1, NULL);
	main_channel2_ = BASS_SampleGetChannel(lost_sound_, FALSE);

	BASS_ChannelSetAttribute(main_channel_, BASS_ATTRIB_VOL, 0.4f);
	BASS_ChannelSetAttribute(main_channel2_, BASS_ATTRIB_VOL, 0.4f);
	offset = 1.0f;
	isit = false;
}


//-----------------------PLAYER SEARCHING-----------------------------------------
void Guard::updatePlayer(const Player& player, const Shadow& shadow)
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

	spriteImage.setPosition(Shape().getPosition().x - Shape().getSize().x / 2,
		Shape().getPosition().y - Shape().getSize().y / 2);

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
		std::cout << "Game Over" << std::endl;
		break;
	default:
		break;
	}
}

void Guard::Patrol(Player player, Shadow shadow) {

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
		isource.y = 0;
	}

	if (Shape().getPosition().x >= start_position_.x && turnRight == false) {
		turnAround();
		isource.y = 40;
	}

	if (player.Shape().getPosition().y == Shape().getPosition().y){
		if (player.Shape().getPosition().x < Shape().getPosition().x && (Shape().getPosition().x - player.Shape().getPosition().x) < view_distance_ && faceLeft){
			Player_patrol_status_ = PlayerPatrolStatus::SEARCH;
		}

		if (player.Shape().getPosition().x > Shape().getPosition().x && (player.Shape().getPosition().x - Shape().getPosition().x) < view_distance_ && !faceLeft){
			Player_patrol_status_ = PlayerPatrolStatus::SEARCH;
		}
	}

	if (shadow.Shape().getPosition().y == Shape().getPosition().y){
		if (shadow.Shape().getPosition().x < Shape().getPosition().x && (Shape().getPosition().x - shadow.Shape().getPosition().x) < view_distance_ && faceLeft){
			//SET POSITION HERE BEFORE YOU 
			Player_patrol_status_ = PlayerPatrolStatus::SEARCH;
		}
		if (shadow.Shape().getPosition().x > Shape().getPosition().x && (shadow.Shape().getPosition().x - Shape().getPosition().x) < view_distance_ && !faceLeft){
			Player_patrol_status_ = PlayerPatrolStatus::SEARCH;
		}
	}
}

void Guard::Search(Player player, Shadow shadow) {

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

	if (Shape().getPosition().x > gotoXpos) {
		movement_speed_ = sf::Vector2f(SPEED1, 0.0f);
		Shape().move(movement_speed_);
		isource.y = 40;
	}

	if (Shape().getPosition().x < gotoXpos) {
		movement_speed_ = sf::Vector2f(-SPEED1, 0.0f);
		Shape().move(movement_speed_);
		isource.y = 0;
	}

	if ((Shape().getPosition().x - gotoXpos) == 0 || ((Shape().getPosition().x - gotoXpos) + offset) == 0 || ((Shape().getPosition().x - gotoXpos) - offset) == 0) {  //
		temp_starting_pos_ = gotoXpos;
		Player_patrol_status_ = PlayerPatrolStatus::AREAPATROL;
	}

	if (player.Shape().getPosition().y == Shape().getPosition().y)
		Check_distance(player, shadow);

}
void Guard::Check_distance(const Player& player, const Shadow& shadow)
{
	int tempDist1 = 150;
	if (player.Shape().getPosition().x < Shape().getPosition().x && (Shape().getPosition().x - player.Shape().getPosition().x) < tempDist1 && movement_speed_.x <= 0)
		Player_patrol_status_ = PlayerPatrolStatus::FOUND;

	if (player.Shape().getPosition().x > Shape().getPosition().x && (player.Shape().getPosition().x - Shape().getPosition().x) < tempDist1 && movement_speed_.x >= 0)
		Player_patrol_status_ = PlayerPatrolStatus::FOUND;
}

void Guard::Area_patrol(Player player, Shadow shadow)
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
				isource.y = 0;
			}


			if (Shape().getPosition().x >= temp_starting_pos_ + AP_movement_distance_ || (Shape().getPosition().x + Shape().getSize().x / 2) >= LEVEL_WIDTH) {
				turnRight = false;
				turnAround();
				moveme = false;
				isource.y = 40;
			}

			if (player.Shape().getPosition().y == Shape().getPosition().y) {
				Check_distance(player, shadow);
			}
		}
	}
	else {
		Player_patrol_status_ = PlayerPatrolStatus::RETURN;
	}
}
void Guard::ReturnPatrol(Player player, Shadow shadow)
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
		isource.y = 40; //Animation related
	}
	if (player.Shape().getPosition().y == Shape().getPosition().y)
	{
		Check_distance(player, shadow);
	}
	//std::cout << "guard X: " << I_pos_.x;
	//std::cout << "\nint: " << I_Start_position_.x;


	if ((I_pos_.x - I_Start_position_.x) == 0 || ((I_pos_.x - I_Start_position_.x) + offset) == 0 || ((I_pos_.x - I_Start_position_.x) - offset) == 0)
	{
		Player_patrol_status_ = PlayerPatrolStatus::PATROL;
		softReset();
	}

	/*if (I_pos_.x == I_Start_position_.x)
	{
	Player_patrol_status_ = PlayerPatrolStatus::PATROL;
	softReset();
	}*/
}
//---------------------------------------------------------------------------------



//-----------------------Shadow SEARCHING------------------------------------------
//void Guard::updateShadow(const Shadow& shadow, const Player& player) {
//	switch (Shadow_patrol_status_) {
//
//	case ShadowPatrolStatus::PATROL:
//		std::cout << "Shadow State 1" << std::endl;
//		patrol(shadow);
//		break;
//	case ShadowPatrolStatus::SEARCH:
//		std::cout << "State 2" << std::endl;
//		search(shadow, player);
//		if (!played) {
//			BASS_ChannelPlay(main_channel_, FALSE);
//			played = true;
//		}
//		break;
//	case ShadowPatrolStatus::AREAPATROL:
//		std::cout << "State 3" << std::endl;
//		area_patrol(shadow);
//		break;
//	case ShadowPatrolStatus::RETURN:
//		std::cout << "State 4" << std::endl;
//		returnPatrol(shadow);
//		if (!played2) {
//			BASS_ChannelPlay(main_channel2_, FALSE);
//			played2 = true;
//		}
//		break;
//	case ShadowPatrolStatus::FOUND:
//		std::cout << "State 5" << std::endl;
//		game_over = true;
//		goto_game_over();
//		std::cout << "Game Over" << std::endl;
//		break;
//	default:
//		break;
//	}
//}
//
//void Guard::patrol(Shadow shadow) {
//
//	 Possible to Have distance for viewing Shadow a closer distance than player
//
//	if (shadow.Shape().getPosition().y == Shape().getPosition().y){
//		if (shadow.Shape().getPosition().x < Shape().getPosition().x && (Shape().getPosition().x - shadow.Shape().getPosition().x) < view_distance_ && faceLeft){
//			Shadow_patrol_status_ = ShadowPatrolStatus::SEARCH;
//		}
//
//		if (shadow.Shape().getPosition().x > Shape().getPosition().x && (shadow.Shape().getPosition().x - Shape().getPosition().x) < view_distance_ && !faceLeft){
//			Shadow_patrol_status_ = ShadowPatrolStatus::SEARCH;
//		}
//	}
//}
//void Guard::search(Shadow shadow, Player player) {
//	int tempDistance = (Shape().getPosition().x - shadow.Shape().getPosition().x);
//	int tempDistance2 = -tempDistance;
//
//	if (tempDistance <= view_distance_ && shadow.Shape().getPosition().y == Shape().getPosition().y && tempDistance >= 0) 
//		outofrange = false;
//	if (tempDistance2 <= view_distance_ && player.Shape().getPosition().y == Shape().getPosition().y && tempDistance2 >= 0)
//		outofrange2 = false;
//
//
//	if (!outofrange || !outofrange2) {
//		shadow.setLpos(shadow.Shape().getPosition());
//		gotoXpos = shadow.getLpos().x;
//	}
//
//	if (shadow.Shape().getPosition().y != Shape().getPosition().y || tempDistance >= view_distance_)
//		outofrange = true;
//
//	if (shadow.Shape().getPosition().y != Shape().getPosition().y || tempDistance2 >= view_distance_)
//		outofrange2 = true;
//
//	if (Shape().getPosition().x > gotoXpos) {
//		movement_speed_ = sf::Vector2f(SPEED1, 0.0f);
//		Shape().move(movement_speed_);
//		isource.y = 40;
//	}
//
//	if (Shape().getPosition().x < gotoXpos) {
//		movement_speed_ = sf::Vector2f(-SPEED1, 0.0f);
//		Shape().move(movement_speed_);
//		isource.y = 0;
//	}
//	std::cout << gotoXpos << "Go To X Pos" << std::endl;
//	std::cout << sTemp_startingpos_ << "Shadow Temp Start Pos" << std::endl;
//
//	if ((Shape().getPosition().x - gotoXpos) == 0 || ((Shape().getPosition().x - gotoXpos) + offset) == 0 || ((Shape().getPosition().x - gotoXpos) - offset) == 0) {  //
//		sTemp_startingpos_ = gotoXpos;
//		Player_patrol_status_ = PlayerPatrolStatus::AREAPATROL;
//	}
//
//	
//
//	if (shadow.Shape().getPosition().y == Shape().getPosition().y)
//		pCheck_distance(player);
//}
//void Guard::check_distance(const Shadow& shadow)
//{
//
//}
//
//void Guard::area_patrol(Shadow shadow)
//{
//
//}
//void Guard::returnPatrol(Shadow shadow)
//{
//
//}
//---------------------------------------------------------------------------------

void Guard::turnAround()
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
		}
	}
}
bool Guard::goto_game_over()
{
	return game_over;
}
void Guard::softReset()
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
void Guard::Draw(sf::RenderWindow& window)
{
	spriteImage.setTextureRect(sf::IntRect(isource.x, isource.y, 30, 40));
	//window.draw(m_shape);
	window.draw(spriteImage);
}

float Guard::set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset)
{
	float ypos = lvlh - ((m_shape.getSize().y) + (floor_no * floor_h) + ground_offset);	//sets the ypos
	return ypos;
}