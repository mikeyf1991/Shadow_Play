#include "Light.hpp"

Light::Light(sf::Vector2f position, sf::Vector2f size, sf::Color colour, int id) :
id_(id),
teleport_(false)
{
	m_shape.setSize(size);
	m_shape.setOutlineThickness(2);
	m_shape.setOutlineColor(sf::Color::Yellow);
	m_shape.setFillColor(sf::Color::Transparent);
	m_shape.setOrigin(size / 2.f);
	m_shape.setPosition(position);
}
float Light::set_Ypos(int lvlh, int floor_no, int floor_h, int ground_offset)
{
	float ypos = lvlh - ((m_shape.getSize().y) + (floor_no * floor_h) - 45);	//sets the ypos
	return ypos;
}