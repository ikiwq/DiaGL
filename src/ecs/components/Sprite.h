#pragma once

#include <array>
#include <glm/glm.hpp>

class Texture;

class Sprite {
private:
	Texture* texture;
	std::array<glm::vec2, 4> textureCoords;
public:
	Sprite(Texture* texture) {
		this->texture = texture;
		textureCoords = {
			glm::vec2(1, 1),
			glm::vec2(1, 0),
			glm::vec2(0, 0),
			glm::vec2(0, 1)
		};
	}

	Sprite(Texture* texture, std::array<glm::vec2, 4> textureCoords) {
		this->texture = texture;
		this->textureCoords = textureCoords;
	}

	Texture* getTexture() {
		return texture;
	}

	std::array<glm::vec2, 4> getTextureCoords(){
		return textureCoords;
	}
};