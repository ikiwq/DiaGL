#include "ResourceManager.h"

#include <iostream>

#include "../renderer/Shader.h"
#include "../renderer/Texture.h"

#include "../ecs/components/Spritesheet.h"


std::map<std::string, Shader*> ResourceManager::shaders = std::map<std::string, Shader*>();
std::map<std::string, Texture*> ResourceManager::textures = std::map<std::string, Texture*>();
std::map<std::string, Spritesheet*> ResourceManager::spritesheets = std::map<std::string, Spritesheet*>();

Shader* ResourceManager::getShader(std::string resourceName) {
	if (!shaders.count(resourceName)) {
		Shader* shader = new Shader("assets/shaders/" + resourceName + ".glsl");
		shader->compile();
		shaders.emplace(resourceName, shader);
	}
	return shaders.at(resourceName);
}

Texture* ResourceManager::getTexture(std::string resourceName) {
	if (!ResourceManager::textures.count(resourceName)) {
		Texture* texture = new Texture("assets/images/" + resourceName);
		textures.emplace(resourceName, texture);
	}
	return textures.at(resourceName);
}


void ResourceManager::addSpritesheet(std::string resourceName, Spritesheet* spritesheet) {
	if (!spritesheets.count(resourceName)) {
		spritesheets.emplace(resourceName, spritesheet);
	}
}
Spritesheet* ResourceManager::getSpritesheet(std::string resourceName) {
	if (!spritesheets.count(resourceName)) {
		std::cerr << "No spritesheet found with that resourcename. \n";
		return nullptr;
	}
	return spritesheets.at(resourceName);
}