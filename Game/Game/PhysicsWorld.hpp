#pragma once
//stl
#include <list>
#include <vector>
//other
#include "PhysicsObject.h"

class PhysicsWorld
{
private:
	std::list<PhysicsObject*> inhabitants;
	unsigned int size = 0;
	unsigned int chunks = 0;
	float worldOffset = 0;
	std::vector<std::vector<std::vector<std::list<PhysicsObject*>>>> space;
	
public:
	PhysicsWorld() {}
	void createWorld(unsigned int newSize, unsigned int newChunks) {
		size = newSize;
		chunks = newChunks;
		worldOffset = size / 2;

		std::vector<std::vector<std::vector<std::list<PhysicsObject*>>>> a(chunks); //x
		std::vector<std::vector<std::list<PhysicsObject*>>> b(chunks);              //y
		std::vector<std::list<PhysicsObject*>> c(chunks);                           //z

		//definitely slow but i'm not sure what else to do.
		for (auto& v : b) {
			v = c;
		}
		for (auto& v : a) {
			v = b;
		}

		space = a;
	}
	void addPhysicsObject(PhysicsObject* newObject) {
		inhabitants.push_back(newObject);
		Vec3<unsigned int> index = positionToIndex(newObject->getPosition());
		space[index.getX()][index.getY()][index.getZ()].push_back(newObject);
	}
	void physicsTick() {
		Vec3<unsigned int> index;
		for (auto i = inhabitants.begin(); i != inhabitants.end(); i++) {
			if ((*i)->exists()) {
				(*i)->physicsTick();
			}
			else {
				index = positionToIndex((*i)->getPosition());
				space[index.getX()][index.getY()][index.getZ()].remove(*i);
				inhabitants.erase(i);
			}
		}
		return;
	}
	Vec3<unsigned int> positionToIndex(Vec3<float> position) {
		Vec3<unsigned int> out(
			std::clamp(static_cast<unsigned int>(floor(position.getX() + worldOffset)), static_cast<unsigned int>(0), size),
			std::clamp(static_cast<unsigned int>(floor(position.getY() + worldOffset)), static_cast<unsigned int>(0), size),
			std::clamp(static_cast<unsigned int>(floor(position.getZ() + worldOffset)), static_cast<unsigned int>(0), size)
		);
		return out;
	}

	void updatePosition(Vec3<float> newPosition, Vec3<float> oldPosition, PhysicsObject* object) {
		Vec3<unsigned int> oldIndex = positionToIndex(oldPosition);
		Vec3<unsigned int> newIndex = positionToIndex(newPosition);

		unsigned int oldX = oldIndex.getX();
		unsigned int oldY = oldIndex.getX();
		unsigned int oldZ = oldIndex.getX();

		unsigned int newX = newIndex.getX();
		unsigned int newY = newIndex.getX();
		unsigned int newZ = newIndex.getX();
		
		space[oldX][oldY][oldZ].remove(object);
		space[newX][newY][newZ].push_back(object);
	}
};

