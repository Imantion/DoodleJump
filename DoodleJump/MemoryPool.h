#pragma once
#include <vector>
#include "Rectangle.h"

class GameObject;

class MemoryPool {
public:
    MemoryPool(size_t capacity, Rectangle gameObjectBox, const char* spritePath); // Constructor for Enemy pool, using switch and flag. Can be used for other objects
    MemoryPool(size_t capacity, Rectangle gameObjectBox, float speed, float lifetime, const char* spritePath); // Constructor for Projectile pool
    MemoryPool(size_t capacity, Rectangle gameObjectBox, float duration, const char* spritePath); // Constructor for Ability pool

    ~MemoryPool();

    GameObject* allocate();

    void deallocate(GameObject* object);

    void scalePoolObjects(float x, float y);

private:
    size_t capacity;
    std::vector<GameObject*> pool;
};

