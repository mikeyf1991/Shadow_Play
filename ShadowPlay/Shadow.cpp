#include "Shadow.hpp"

Shadow::Shadow(sf::Vector2f position, sf::Vector2f size, sf::Color colour) // shadow constructor
{
	m_shape.setSize(size);
	m_shape.setOutlineThickness(1);
	m_shape.setOutlineColor(sf::Color::White);
	m_shape.setFillColor(colour);
	m_shape.setOrigin(size / 2.f);

	m_shape.setPosition(position);

	//spritesheet set up
	if (!shadowTexture.loadFromFile("Player/Player Shadow.png"))
		std::cout << "Error couldnt load Player" << std::endl;

	shadowImage.setTexture(shadowTexture);

	isource.x = 0;
	isource.y = 0;
	
	shadowImage.scale(0.2f, 0.2f);

	//spritesheet 2 set up
	if (!shadowCastTexture.loadFromFile("Player/Cast Shadow.png"))
		std::cout << "Error couldnt load Player" << std::endl;

	shadowCastImage.setTexture(shadowCastTexture);

	castisource.x = 0;
	castisource.y = 1430;


	shadowCastImage.scale(0.325f, 0.325f);

	shadow_vis_ = false;
}
float Shadow::set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset)
{
	float ypos = lvlh - ((m_shape.getSize().y) + (floor_no * floor_h) + ground_offset);	//sets the ypos
	return ypos;
}