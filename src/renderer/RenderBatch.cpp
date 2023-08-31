#include "RenderBatch.h"

#include "../renderer/Shader.h"
#include "../renderer/Texture.h"
#include "../engine/Camera.h"
#include "../scene/Scene.h"
#include "../engine/Window.h"
#include "../ecs/components/SpriteRenderer.h"
#include "../ecs/Ramiel.h"
#include "../engine/ResourceManager.h"

RenderBatch::~RenderBatch() {
    delete vertices, indices, vaoID, vboID, eboID;
    delete[] textureSlots;
}

RenderBatch::RenderBatch(int maxBatchSize)
{
    shader = ResourceManager::getShader("default");

    this->maxBatchSize = maxBatchSize;
    this->vertices = new float[maxBatchSize * 4 * VERTEX_SIZE];
    this->indices = new int[6 * maxBatchSize];

    this->numSprites = 0;
    this->hasRoom = true;

    textureSlots = new int[8];
    for (int i = 0; i < 8; i++) {
        textureSlots[i] = i;
    }
}

void RenderBatch::start()
{
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    generateIndices(this->indices);

    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * maxBatchSize * 4 * VERTEX_SIZE, vertices, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &eboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 6 * maxBatchSize, indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, POS_SIZE, GL_FLOAT, false, VERTEX_SIZE_BYTES, (void *)POS_OFFSET);
    glEnableVertexAttribArray(0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, COLOR_SIZE, GL_FLOAT, false, VERTEX_SIZE_BYTES, (void *)COLOR_OFFSET);

    glVertexAttribPointer(2, TEXTURE_COORDS_SIZE, GL_FLOAT, false, VERTEX_SIZE_BYTES, (void*)TEXTURE_COORDS_OFFSET);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, TEXTURE_ID_SIZE, GL_FLOAT, false, VERTEX_SIZE_BYTES, (void*)TEXTURE_ID_OFFSET);
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void RenderBatch::addSprite(SpriteRenderer *sprite)
{
    int index = numSprites++;
    sprites.push_back(sprite);

    if (sprite->getTexture() != nullptr) {
        int textureID = sprite->getTexture()->getId();
        if (!texturesMap.count(textureID)) {
            texturesMap.emplace(textureID, sprite->getTexture());
        }
        loadVertexProperties(index, textureID);
    }
    else {
        loadVertexProperties(index, 0);
    }
    
    
    if (numSprites >= maxBatchSize)
    {
        this->hasRoom = false;
    }
}

void RenderBatch::render()
{   
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * maxBatchSize * 4 * VERTEX_SIZE, vertices);

    shader->use();

    shader->uploadMat4f("uProj", Window::getInstance()->getScene()->getCamera()->getProjectionMatrix());
    shader->uploadMat4f("uView", Window::getInstance()->getScene()->getCamera()->getViewMatrix());

    int i = 1;
    for (auto& texture : texturesMap) {
        glActiveTexture(GL_TEXTURE0 + i++);
        texture.second->bind();
    }

    shader->uploadIntArray("uTextures", textureSlots);

    glBindVertexArray(vaoID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glDrawElements(GL_TRIANGLES, this->numSprites * 6, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glBindVertexArray(0);

    for (auto& texture : texturesMap) {
        texture.second->unbind();
    }

    shader->detach();
}

void RenderBatch::loadVertexProperties(int index, int textureID)
{
    SpriteRenderer *sprite = this->sprites[index];
    int offset = index * 4 * VERTEX_SIZE;

    glm::vec4 color = sprite->getColor();

    float xAdd = 1.0f;
    float yAdd = 1.0f;
    for (int i = 0; i < 4; i++) {
        if (i == 1) {
            yAdd = 0.0f;
        }
        else if (i == 2) {
            xAdd = 0.0f;
        }
        else if (i == 3) {
            yAdd = 1.0f;
        }

        vertices[offset] = sprite->getOwner()->transform->position.x + (xAdd * sprite->getOwner()->transform->scale.x);
        vertices[offset + 1] = sprite->getOwner()->transform->position.y + (yAdd * sprite->getOwner()->transform->scale.y);
        vertices[offset + 2] = 0;
        vertices[offset + 3] = color.x;
        vertices[offset + 4] = color.y;
        vertices[offset + 5] = color.z;
        vertices[offset + 6] = color.w;

        vertices[offset + 7] = sprite->getTextureCoords()[i].x;
        vertices[offset + 8] = sprite->getTextureCoords()[i].y;

        vertices[offset + 9] = textureID;

        offset += VERTEX_SIZE;
    }
}

void RenderBatch::generateIndices(int *indices)
{
    for (int i = 0; i < maxBatchSize; i++)
    {
        int offsetArrayIndex = 6 * i;
        int offset = 4 * i;

        indices[offsetArrayIndex] = offset + 3;
        indices[offsetArrayIndex + 1] = offset + 2;
        indices[offsetArrayIndex + 2] = offset + 0;

        indices[offsetArrayIndex + 3] = offset + 0;
        indices[offsetArrayIndex + 4] = offset + 2;
        indices[offsetArrayIndex + 5] = offset + 1;
    }
}