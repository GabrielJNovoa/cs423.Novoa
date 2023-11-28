#pragma once
//sfml

//stl
#include <list>
#include <vector>
//other
#include "GameObject.h"
#include "PhysicsObject.h"

class PhysicsObject;

class PhysicsWorld
{
private:
	std::list<PhysicsObject*> inhabitants;
	unsigned int size = 0;
	unsigned int chunks = 0;
	float worldOffset = 0;
	std::vector<std::vector<std::vector<std::list<PhysicsObject*>>>> space;

public:
	PhysicsWorld();
	void createWorld(unsigned int newSize, unsigned int newChunks);
	void addPhysicsObject(PhysicsObject* newObject);
	void physicsTick();
	Vec3<unsigned int> positionToIndex(Vec3<float> position);
	void updatePosition(Vec3<float> newPosition, Vec3<float> oldPosition, PhysicsObject* object);
	bool checkCollision(PhysicsObject* object, bool sendMessage);
};

