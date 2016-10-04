/*#include "LoadTexture.hpp"


LoadTexture::LoadTexture()
{
//Initialize
mTexture;
mWidth = 0;
mHeight = 0;
}

LoadTexture::~LoadTexture()
{
//Deallocate
free();
}

bool LoadTexture::loadFromFile(std::string path, sf::RenderTexture gRenderer)
{
//Get rid of preexisting texture
free();

//The final texture
sf::Texture newTexture;

//Load image at specified path
sf::GlResource loadedSurface;
loadedSurface = sf::Image(path.c_str());
if (loadedSurface == NULL)
{
printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
}
else
{
//Color key image
sf::Color(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255));

//Create texture from surface pixels
newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
if (newTexture == NULL)
{
printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
}
else
{
//Get image dimensions
mWidth = loadedSurface->w;
mHeight = loadedSurface->h;
}

//Get rid of old loaded surface
SDL_FreeSurface(loadedSurface);
}

//Return success
mTexture = newTexture;
return mTexture != NULL;
}

void LoadTexture::free()
{
//Free texture if it exists
if (mTexture != NULL)
{
SDL_DestroyTexture(mTexture);
mTexture = NULL;
mWidth = 0;
mHeight = 0;
}
}

void LoadTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
//Modulate texture rgb
SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LoadTexture::setBlendMode(SDL_BlendMode blending)
{
//Set blending function
SDL_SetTextureBlendMode(mTexture, blending);
}

void LoadTexture::setAlpha(Uint8 alpha)
{
//Modulate texture alpha
SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LoadTexture::render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
//Set rendering space and render to screen
SDL_Rect renderQuad = { x, y, mWidth, mHeight };

//Set clip rendering dimensions
if (clip != NULL)
{
renderQuad.w = clip->w;
renderQuad.h = clip->h;
}

//Render to screen
SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LoadTexture::getWidth()
{
return mWidth;
}

int LoadTexture::getHeight()
{
return mHeight;
}*/