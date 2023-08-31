#pragma once

#include <vector>
#include <array>

#include "../../renderer/Texture.h"
#include "Sprite.h"

class Spritesheet {
	Texture* texture;
	std::vector<Sprite*> sprites;
public:
	Spritesheet(Texture* texture, int spriteWidth, int spriteHeight, int numSprites, int spacing) {
		this->texture = texture;

		int currentX = 0;
		int currentY = texture->height - spriteHeight;

		for (int i = 0; i < numSprites; i++) {
			float topY = (currentY + spriteHeight) / (float) texture->height;
			float rightX = (currentX + spriteWidth) / (float) texture->width;
			float leftX = currentX / (float) texture->width;
			float bottomY = currentY / (float) texture->height;

			std::array<glm::vec2, 4> textCoordinates = {
				glm::vec2(rightX, topY),
				glm::vec2(rightX, bottomY),
				glm::vec2(leftX, bottomY),
				glm::vec2(leftX, topY),
			};

			std::cout << rightX << std::endl;

			Sprite* sprite = new Sprite(this->texture, textCoordinates);
			this->sprites.push_back(sprite);

			currentX += spriteWidth + spacing;
			if (currentX >= texture->width) {
				currentX = 0;
				currentY -= spriteHeight + spacing;
			}
		}
	}

	Sprite* getSprite(int index) {
		if (index >= sprites.size()) {
			std::cerr << "Index out of bounds. \n";
			return nullptr;
		}

		return sprites[index];
	}

private:
	void loadSprites() {

	}
};