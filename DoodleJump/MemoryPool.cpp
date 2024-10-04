#include "MemoryPool.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Invincibility.h"

// Constructor for MemoryPool
MemoryPool::MemoryPool(size_t capacity, Rectangle gameObjectBox, const char* spritePath) : capacity(capacity) {
    // Allocate memory for the pool
    pool.reserve(capacity);
    for (size_t i = 0; i < capacity; ++i) {
        pool.push_back(new Enemy(gameObjectBox, spritePath));
    }
}

MemoryPool::MemoryPool(size_t capacity, Rectangle gameObjectBox, float lifetime, float speed, const char* spritePath) : capacity(capacity)
{
    pool.reserve(capacity);
    for (size_t i = 0; i < capacity; ++i) {
        pool.push_back(new Projectile(gameObjectBox, lifetime, speed, spritePath));
    }
}

MemoryPool::MemoryPool(size_t capacity, Rectangle gameObjectBox, float duration, const char* spritePath) // If there was several abilities we could use switch and ability effect, to create different abilities
    : capacity(capacity)
{
	pool.reserve(capacity);
    for (size_t i = 0; i < capacity; ++i) {
		pool.push_back(new Invincibility(gameObjectBox, duration, spritePath));
	}
}


MemoryPool::~MemoryPool() {
    for (GameObject* object : pool) {
        delete object;
    }
}

// Method to get an object from the pool
GameObject* MemoryPool::allocate() {
    if (!pool.empty()) {
        GameObject* object = pool.back();
        pool.pop_back();
        return object;
    }
    else {
        return nullptr;
    }
}

// Method to return an object to the pool
void MemoryPool::deallocate(GameObject* object) {
    if (object != nullptr && pool.size() < capacity) {
        pool.push_back(object);
    }
}

void MemoryPool::scalePoolObjects(float x, float y)
{
    for (GameObject* object : pool)
    {
		object->ScaleObjectProperties(x, y);
	}
}
