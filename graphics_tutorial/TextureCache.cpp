#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>



TextureCache::TextureCache()
{

}
TextureCache::~TextureCache()
{

}

GLTexture TextureCache::getTexture(std::string texturePath)
{
	//lookup the texture and see if its the map
	auto mit = _textureMap.find(texturePath);

	//check if its not in the map
	if (mit == _textureMap.end())
	{
		//Load new texture
		GLTexture newTexture = ImageLoader::loadPNG(texturePath);

		//Insert in to the map
		_textureMap.insert(make_pair(texturePath, newTexture));

		std::cout << "Loaded Cache Texture!\n";
		return newTexture;
	}
	std::cout << "Used Cache Texture!\n";
	return mit->second; 

}