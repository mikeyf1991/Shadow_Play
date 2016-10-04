#include "LevelExit.hpp"

LevelExit::LevelExit(sf::Vector2f position, sf::Vector2f size, sf::Color colour) // constructor for the level exit shape
{
	m_shape.setSize(size);
	m_shape.setOutlineThickness(1);
	m_shape.setOutlineColor(sf::Color::White);
	m_shape.setFillColor(sf::Color::White);
	m_shape.setOrigin(size / 2.f);
	m_shape.setPosition(position);

	//spritesheet set up
	if (!spriteTexture.loadFromFile("Misc/End Level Door2.png"))
		std::cout << "Error couldnt load Player" << std::endl;

	spriteImage.setTexture(spriteTexture);
	spriteImage.setPosition(position);
	isource.x = 0;
	isource.y = 0;


	spriteImage.scale(0.5f, 0.5f);
}
float LevelExit::set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset)
{
	float ypos = lvlh - ((m_shape.getSize().y) + (floor_no * floor_h) + ground_offset);	//sets the ypos
	return ypos;
}