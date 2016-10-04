#include "Wall.hpp"

Wall::Wall(sf::Vector2f position, sf::Vector2f size, sf::Color colour) // constructor for the walls in the game
{
	m_shape.setSize(size);
	m_shape.setOutlineThickness(2);
	m_shape.setOutlineColor(sf::Color::Yellow);
	m_shape.setFillColor(sf::Color::Transparent);
	m_shape.setOrigin(size / 2.f);
	m_shape.setPosition(position);
	//spritesheet set up

	if (!spriteTexture.loadFromFile("Misc/Destroyable_Wall.png"))
		std::cout << "Error couldnt load switch" << std::endl;

	if (!spriteTexture2.loadFromFile("Misc/UnDestroyable_Wall.png"))
		std::cout << "Error couldnt load switch2" << std::endl;

	spriteImage.setTexture(spriteTexture);

	spriteImage2.setTexture(spriteTexture2);

	spriteImage.setPosition(position);
	spriteImage2.setPosition(position);
	isource.x = 0;
	isource.y = 0;
}
float Wall::set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset)
{
	float ypos = lvlh - ((m_shape.getSize().y/2) + (floor_no * floor_h) + ground_offset*2);	//sets the ypos
	return ypos;
}