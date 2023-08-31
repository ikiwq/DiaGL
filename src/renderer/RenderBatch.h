#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <map>

#include <glad/glad.h>

constexpr unsigned int POS_SIZE = 3;
constexpr unsigned int COLOR_SIZE = 4;
constexpr unsigned int TEXTURE_COORDS_SIZE = 2;
constexpr unsigned int TEXTURE_ID_SIZE = 1;

constexpr unsigned int POS_OFFSET = 0;
constexpr unsigned int COLOR_OFFSET = POS_OFFSET + POS_SIZE * sizeof(float);
constexpr unsigned int TEXTURE_COORDS_OFFSET = COLOR_OFFSET + COLOR_SIZE * sizeof(float);
constexpr unsigned int TEXTURE_ID_OFFSET = TEXTURE_COORDS_OFFSET + TEXTURE_COORDS_SIZE * sizeof(float);

constexpr unsigned int VERTEX_SIZE = POS_SIZE + COLOR_SIZE + TEXTURE_COORDS_SIZE + TEXTURE_ID_SIZE;
constexpr unsigned int VERTEX_SIZE_BYTES = VERTEX_SIZE * sizeof(float);

class SpriteRenderer;
class Shader;
class Texture;

class RenderBatch
{
public:
    bool hasRoom;

private:
    std::vector<SpriteRenderer *> sprites;
    std::map<int, Texture*> texturesMap;

    int numSprites;

    float *vertices;
    int* indices;
    int* textureSlots;

    GLuint vaoID, vboID, eboID;
    int maxBatchSize;
    Shader *shader;

public:
    RenderBatch(int maxBatchSize);
    ~RenderBatch();
    void start();

    void addSprite(SpriteRenderer *sprite);

    void render();

    bool hasTextureRoom() {
        std::cout << texturesMap.size() << std::endl;
        return texturesMap.size() < 8;
    }

    bool hasTexure(int textureID) {
        return texturesMap.count(textureID);
    }

private:
    void loadVertexProperties(int index, int textureID);

    void generateIndices(int *indices);

    void loadElementIndices(int *indices, int index);
};