#pragma once

#include "Scene.h"

#include <string>
#include <glad/glad.h>

class LevelEditorScene : public Scene
{
public:
    LevelEditorScene();
    ~LevelEditorScene();

    void update(float dt) override;

    void init() override;
};