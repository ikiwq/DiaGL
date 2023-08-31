#pragma once
#include "Scene.h"

#include "../ecs/Ramiel.h"
#include "../renderer/Renderer.h"

Scene::Scene() {
	renderer = new Renderer();
}

Scene::~Scene() {
	for (Ramiel* r : ramiels) {
		delete r;
	}
	delete camera;
	delete renderer;
}

void Scene::addRamielToScene(Ramiel* r) {
	if (!running) {
		ramiels.emplace_back(r);
	}
	else {
		ramiels.emplace_back(r);
		r->init();
		renderer->add(r);
	}
}

void Scene::start() {
	for (Ramiel* ramiel : ramiels) {
		ramiel->init();
		this->renderer->add(ramiel);
	}
	running = true;
}