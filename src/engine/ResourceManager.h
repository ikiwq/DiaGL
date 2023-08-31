#pragma once
#include <map>
#include "string"

class Shader;
class Texture;
class Spritesheet;

class ResourceManager {
	static std::map<std::string, Shader*> shaders;
	static std::map<std::string, Texture*> textures;
	static std::map<std::string, Spritesheet*> spritesheets;

public:
	static Shader* getShader(std::string resourceName);
	static Texture* getTexture(std::string resourceName);
	static void addSpritesheet(std::string resourceName, Spritesheet* spritesheet);
	static Spritesheet* getSpritesheet(std::string resourceName);
};