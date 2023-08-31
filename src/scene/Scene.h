#pragma once

#include <vector>

class Camera;
class Renderer;
class Ramiel;

class Scene {
public:
	Renderer* renderer;
protected:
	Camera* camera;
	bool running;

	std::vector<Ramiel*> ramiels;
public:
	Scene();
	~Scene();

	virtual void init() = 0;

	virtual void update(float dt) = 0;
	
	void addRamielToScene(Ramiel* r);

	virtual void start();

	Camera* getCamera(){
		return camera;
	}
};