#pragma once
#include "PhysicsWorld.h"
//sfml

//stl
#include <algorithm>
//other

PhysicsWorld::PhysicsWorld() {}
void PhysicsWorld::createWorld(unsigned int newSize, unsigned int newChunks) {
	size = newSize;
	chunks = newChunks;
	worldOffset = size / 2;
	std::cout << "creating world with " << chunks << " chunks, and a size of " << size << "\n";
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
void PhysicsWorld::addPhysicsObject(PhysicsObject* newObject) {
	inhabitants.push_back(newObject);
	newObject->setHome(this);
	Vec3<unsigned int> index = positionToIndex(newObject->getPosition());
	std::cout << "attempting to add object at chunk:" << index.toString();
	space[index.getX()][index.getY()][index.getZ()].push_back(newObject);
}
void PhysicsWorld::physicsTick() {
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
Vec3<unsigned int> PhysicsWorld::positionToIndex(Vec3<float> position) {
	Vec3<unsigned int> out(
		std::clamp(static_cast<unsigned int>(floor(position.getX() + worldOffset)) / chunks, static_cast<unsigned int>(0), size),
		std::clamp(static_cast<unsigned int>(floor(position.getY() + worldOffset)) / chunks, static_cast<unsigned int>(0), size),
		std::clamp(static_cast<unsigned int>(floor(position.getZ() + worldOffset)) / chunks, static_cast<unsigned int>(0), size)
	);
	return out;
}
void PhysicsWorld::updatePosition(Vec3<float> newPosition, Vec3<float> oldPosition, PhysicsObject* object) {
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
bool PhysicsWorld::checkCollision(PhysicsObject* object, bool sendMessage) {
	//built upon assumption that no object is larger than half the size of a chunk.
	
	bool result = false;

	Vec3<unsigned int> index = positionToIndex(object->getPosition());
	std::list<unsigned int> possibleX;
	std::list<unsigned int> possibleY;
	std::list<unsigned int> possibleZ;

	unsigned int x = index.getX();
	unsigned int y = index.getY();
	unsigned int z = index.getZ();

	if (x == 0) {
		possibleX.push_back(0);
		possibleX.push_back(1);
	}
	else if (x == chunks - 1) {
		possibleX.push_back(chunks - 2);
		possibleX.push_back(chunks - 1);
	}
	else {
		possibleX.push_back(x - 1);
		possibleX.push_back(x);
		possibleX.push_back(x + 1);
	}

	if (y == 0) {
		possibleY.push_back(0);
		possibleY.push_back(1);
	}
	else if (y == chunks - 1) {
		possibleY.push_back(chunks - 2);
		possibleY.push_back(chunks - 1);
	}
	else {
		possibleY.push_back(y - 1);
		possibleY.push_back(y);
		possibleY.push_back(y + 1);
	}

	if (z == 0) {
		possibleZ.push_back(0);
		possibleZ.push_back(1);
	}
	else if (z == chunks - 1) {
		possibleZ.push_back(chunks - 2);
		possibleZ.push_back(chunks - 1);
	}
	else {
		possibleZ.push_back(z - 1);
		possibleZ.push_back(z);
		possibleZ.push_back(z + 1);
	}

	for (auto X : possibleX) {
		for (auto Y : possibleY) {
			for (auto Z : possibleZ) {
				for (auto physObj : space[X][Y][Z]) {
					if (object != physObj) {
						if (object->collide(physObj, sendMessage)) {
							result = true;
						}
					}
				}
			}
		}
	}
	return result;
}