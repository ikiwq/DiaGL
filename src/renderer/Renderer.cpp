#include "Renderer.h"

#include "../ecs/Ramiel.h"
#include "../renderer/Texture.h"

Renderer::~Renderer() {
    for (RenderBatch* r : batches) {
        delete r;
    }
}

void Renderer::add(Ramiel* ramiel)
{
    SpriteRenderer* sprite = ramiel->getComponent<SpriteRenderer>();
    add(sprite);
}

void Renderer::add(SpriteRenderer* sprite)
{
    for (RenderBatch* batch : batches)
    {
        if (batch->hasRoom)
        {
            Texture* texture = sprite->getTexture();
            if (texture == nullptr || batch->hasTexure(texture->getId()) || batch->hasTextureRoom()) {
                batch->addSprite(sprite);
                return;
            }
        }
    }

    RenderBatch* newBatch = new RenderBatch(MAX_BATCH_SIZE);
    newBatch->start();
    batches.emplace_back(newBatch);
    newBatch->addSprite(sprite);
}

void Renderer::render() {
    for (RenderBatch* batch : batches) {
        batch->render();
    }
}