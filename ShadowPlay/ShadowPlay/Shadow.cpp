#include "Shadow.hpp"

Shadow::Shadow(sf::Vector2f position, sf::Vector2f size, sf::Color colour)
{
	m_shape.setSize(size);
	m_shape.setOutlineThickness(1);
	m_shape.setOutlineColor(sf::Color::White);
	m_shape.setFillColor(colour);
	m_shape.setOrigin(size / 2.f);

	m_shape.setPosition(position);

	//spritesheet set up
	if (!spriteTexture.loadFromFile("shadow.png"))
		std::cout << "Error couldnt load Player" << std::endl;

	spriteImage.setTexture(spriteTexture);

	isource.x = 0;
	isource.y = 80;


	spriteImage.scale(2.5f, 2.5f);

	shadow_vis_ = false;
}
float Shadow::set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset)
{
	float ypos = lvlh - ((m_shape.getSize().y) + (floor_no * floor_h) + ground_offset);	//sets the ypos
	return ypos;
}