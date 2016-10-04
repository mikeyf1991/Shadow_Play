#include "Light.hpp"

Light::Light(sf::Vector2f position, sf::Vector2f size, sf::Color colour, int id) : // constructor for the lights 
id_(id),
teleport_(false)
{
	m_shape.setSize(size);
	m_shape.setOutlineThickness(2);
	m_shape.setOutlineColor(sf::Color::Yellow);
	m_shape.setFillColor(sf::Color::Transparent);
	m_shape.setOrigin(size / 2.f);
	m_shape.setPosition(position);

	//spritesheet set up

	if (!spriteTexture.loadFromFile("Misc/LightNiR-00.png"))
		std::cout << "Error couldnt load light" << std::endl;

	spriteImage.setTexture(spriteTexture);
	spriteImage.setScale(0.4f, 0.4f);
	isource.x = 0;
	isource.y = 0;


	if (!spriteTexture2.loadFromFile("Misc/LightiR-00.png"))
		std::cout << "Error couldnt load light" << std::endl;


}

void Light::setimgpos() // setting the image positions for the lights
{
	spriteImage.setPosition(m_shape.getPosition().x - m_shape.getSize().x / 2, pos_y - m_shape.getSize().y*0.65);
}

float Light::set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset)
{
	float ypos = lvlh - ((m_shape.getSize().y/2) + (floor_no * floor_h));	//sets the ypos
	pos_y = ypos;
	m_shape.setPosition(m_shape.getPosition().x, ypos);
	setimgpos();
	return ypos;
}

void Light::Draw(sf::RenderWindow& window) // drawing method for the lights
{
	spriteImage.setTexture(spriteTexture);
	//window.draw(m_shape);
	if (get_In_Range() == true)
		spriteImage.setTexture(spriteTexture2);
	else
		spriteImage.setTexture(spriteTexture);



		window.draw(spriteImage);
}