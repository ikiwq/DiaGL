#include "LevelEditorScene.h"

#include <iostream>

#include "../engine/KeyListener.h"
#include "../engine/MouseListener.h"
#include "../engine/Camera.h"
#include "../engine/ResourceManager.h"

#include "../renderer/Shader.h"
#include "../renderer/Texture.h"
#include "../renderer/Renderer.h"

#include "../ecs/components/SpriteRenderer.h"
#include "../ecs/components/Sprite.h"
#include "../ecs/components/Spritesheet.h"
#include "../ecs/Ramiel.h"


LevelEditorScene::LevelEditorScene()
{
}

LevelEditorScene::~LevelEditorScene() {

}

void LevelEditorScene::init()
{
	camera = new Camera(glm::vec2(-250, 0));

	//TODO: FIXARE QUESTO
	//SE SI CARICA LO SPRITESHEET SI SFANCULA TUTTO
	ResourceManager::addSpritesheet("Supermario Spritesheet", new Spritesheet(ResourceManager::getTexture("spritesheet.png"),
		16, 16, 26, 0));

	Spritesheet* sprites = ResourceManager::getSpritesheet("Supermario Spritesheet");

	/*Ramiel* r1 = new Ramiel("Obj 1", new Transform(glm::vec2(100, 100), glm::vec2(256, 256)));
	r1->addComponent<SpriteRenderer>(sprites->getSprite(0));
	addRamielToScene(r1);

	Ramiel* r2 = new Ramiel("Obj 2", new Transform(glm::vec2(400, 100), glm::vec2(256, 256)));
	r2->addComponent<SpriteRenderer>(sprites->getSprite(10));
	addRamielToScene(r2);*/

	Ramiel* r3 = new Ramiel("Obl 3", new Transform(glm::vec2(200, 100), glm::vec2(256, 256)));
	r3->addComponent<SpriteRenderer>(new Sprite(ResourceManager::getTexture("layla.png")));
	addRamielToScene(r3);

	Shader* shader = ResourceManager::getShader("default");
}

void LevelEditorScene::update(float dt)
{
	for (Ramiel* ramiel : ramiels) {
		ramiel->update(dt);
	}

	renderer->render();

	if (MouseListener::mouseButtonDown(0))
		camera->setPosition(camera->getPosition().x + MouseListener::getDx(), camera->getPosition().y - MouseListener::getDy());

	if (MouseListener::getScrollY() != 0) {
		this->camera->setScaleFactor(this->camera->getScaleFactor() + MouseListener::getScrollY());
	}

	MouseListener::endFrame();
}