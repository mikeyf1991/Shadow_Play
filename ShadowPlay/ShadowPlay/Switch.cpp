#include "Switch.hpp"

Switch::Switch(sf::Vector2f position, sf::Vector2f size, sf::Color colour, int id) :
id_(id),
pulled_(false)
{
	m_shape.setSize(size);
	m_shape.setOutlineThickness(2);
	m_shape.setOutlineColor(sf::Color::Black);
	m_shape.setFillColor(sf::Color::Transparent);
	m_shape.setOrigin(size / 2.f);
	m_shape.setPosition(position);

	//spritesheet set up

		if (!spriteTexture.loadFromFile("Lever.png"))
			std::cout << "Error couldnt load switch" << std::endl;

		if (!spriteTexture2.loadFromFile("Lever2.png"))
			std::cout << "Error couldnt load switch2" << std::endl;

			spriteImage.setTexture(spriteTexture);
	
			spriteImage2.setTexture(spriteTexture2);

	spriteImage.setPosition(position);
	spriteImage2.setPosition(position);
	isource.x = 0;
	isource.y = 0;


	//spriteImage.scale(0.75f, 0.75f);
}
float Switch::set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset)
{
	float ypos = lvlh - ((m_shape.getSize().y) + (floor_no * floor_h) - 45);	//sets the ypos
	return ypos;
}