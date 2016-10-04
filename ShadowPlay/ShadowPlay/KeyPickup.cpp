#include "KeyPickup.hpp"


KeyPickup::KeyPickup(sf::Vector2f position, sf::Vector2f size, sf::Color colour)
{
	setPickupedUpState(false);
	setVisibleState(true);

	m_shape.setSize(size);
	m_shape.setOutlineThickness(1);
	m_shape.setOutlineColor(sf::Color::Blue);
	m_shape.setFillColor(sf::Color::Blue);
	m_shape.setOrigin(size / 2.f);

	m_shape.setPosition(position);

	//spritesheet set up
	if (!spriteTexture.loadFromFile("sonic-3.png"))
		std::cout << "Error couldnt load Player" << std::endl;

	spriteImage.setTexture(spriteTexture);
	spriteImage.setPosition(getPositionX(), getPositionY());
	isource.x = 0;
	isource.y = 0;


	spriteImage.scale(2.5f, 2.5f);

	pickup_sound_ = BASS_SampleLoad(FALSE, "bottle_x.wav", 0, 0, 1, NULL);
	main_channel_ = BASS_SampleGetChannel(pickup_sound_, FALSE);
}
void KeyPickup::update(Player& player)
{
	if (visible == true)
	{
		if (player.Shape().getGlobalBounds().intersects(spriteImage.getGlobalBounds()))
		{
			visible = false;
			picked_up_ = true;
			BASS_ChannelPlay(main_channel_, FALSE);
			std::cout << "Key picked up, can exit now." << std::endl;
		}
	}
}
float KeyPickup::set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset)
{
	float ypos = lvlh - ((m_shape.getSize().y *1.5f) + (floor_no * floor_h) + ground_offset);	//sets the ypos
	return ypos;
}