#pragma once

#include <vector>
#include "RenderBatch.h"

constexpr unsigned int MAX_BATCH_SIZE = 1000;

class Ramiel;

class Renderer
{
    std::vector<RenderBatch *> batches;

public:
    Renderer() = default;
    ~Renderer();

    void add(Ramiel* ramiel);

    void add(SpriteRenderer* sprite);

    void render();
};