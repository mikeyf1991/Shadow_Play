#include "KeyPickup.hpp"


KeyPickup::KeyPickup(sf::Vector2f position, sf::Vector2f size, sf::Color colour) // constructor for the key pickup
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
	if (!spriteTexture.loadFromFile("Misc/Security Pass-01.png"))
		std::cout << "Error couldnt load Player" << std::endl;

	spriteImage.setTexture(spriteTexture);
	spriteImage.setPosition(position);
	isource.x = 0;
	isource.y = 0;


	spriteImage.scale(0.15f, 0.15f);

	pickup_sound_ = BASS_SampleLoad(FALSE, "Sounds/keypickup.wav", 0, 0, 1, NULL);
	main_channel_ = BASS_SampleGetChannel(pickup_sound_, FALSE);
}
void KeyPickup::update(Player& player) // updating the key, check if it is picked up
{
	if (visible == true)
	{
		if (player.Shape().getGlobalBounds().intersects(spriteImage.getGlobalBounds()))
		{
			visible = false;
			picked_up_ = true;
			BASS_ChannelPlay(main_channel_, FALSE);
		}
	}
}
float KeyPickup::set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset)
{
	float ypos = lvlh - ((m_shape.getSize().y) + (floor_no * floor_h) + ground_offset);	//sets the ypos
	return ypos;
}