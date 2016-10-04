#pragma once

#include "Common.hpp"

class LoadTexture
{
public:
	//Initializes variables
	LoadTexture();

	//Deallocates memory
	~LoadTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path, sf::RenderTarget gRenderer);


	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue);

	//Set blending
	void setBlendMode(sf::BlendMode blending);

	//Set alpha modulation
	void setAlpha(sf::Uint8 alpha);

	//Renders texture at given point
	double angle = 0.0;
	void render(sf::RenderTarget gRenderer, int x, int y, sf::FloatRect clip, double angle, sf::Vertex center);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	sf::Texture mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};