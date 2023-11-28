#pragma once
//sfml

//stl
#include "Vec3.hpp"
//other
#include "PhysicsObject.h"

class Collider
{
private:
	PhysicsObject* parent = nullptr;
	int ColliderType = ORTHOBOX;

	float radius = 1;
	float boxDepth = 1; //x
	float boxWidth = 1; //y
	float boxHeight = 1;//z

public:
	Collider() {}
	Collider(PhysicsObject* setParent, int setType, float setRadius) {
		parent = setParent;
		ColliderType = setType;

		radius = setRadius;
	}
	Collider(PhysicsObject* setParent, int setType, float setDepth, float setWidth, float setHeight) {
		parent = setParent;
		ColliderType = setType;

		boxDepth = setDepth;
		boxWidth = setWidth;
		boxHeight = setHeight;
	}
	enum Type {
		SPHERE,
		ORTHOBOX
	};

	bool collide(Collider& other, bool sendMessage) {
		if (ColliderType == SPHERE) {
			if (other.ColliderType == SPHERE) {
				return sphereToSphere(*this, other, sendMessage);
			}
			else if (other.ColliderType == ORTHOBOX) {
				return sphereToBox(*this, other, sendMessage);
			}
		}
		else if (ColliderType == ORTHOBOX) {
			if (other.ColliderType == SPHERE) {
				return sphereToBox(other, *this, sendMessage);
			}
			else if (other.ColliderType == ORTHOBOX) {
				return boxToBox(*this, other, sendMessage);
			}
		}
	}

	bool sphereToSphere(Collider& self, Collider& other, bool sendMessage) {

		Vec3<float> selfPos = self.parent->getPosition();
		Vec3<float> otherPos = other.parent->getPosition();

		//simple distance check
		if (sqrt(selfPos.dot(selfPos) + otherPos.dot(otherPos)) < (self.radius + other.radius)) {
			if (sendMessage) {
				self.parent->receiveCollision(other.parent, other.parent->getIdentifier(), otherPos);
				other.parent->receiveCollision(self.parent, self.parent->getIdentifier(), selfPos);
			}
			return true;
		}
		return false;
	}

	bool boxToBox(Collider& self, Collider& other, bool sendMessage) {

		Vec3<float> selfPos = self.parent->getPosition();
		float minX1 = selfPos.getX() - (self.boxDepth / 2);
		float maxX1 = selfPos.getX() + (self.boxDepth / 2);
		float minY1 = selfPos.getY() - (self.boxWidth / 2);
		float maxY1 = selfPos.getY() + (self.boxWidth / 2);
		float minZ1 = selfPos.getZ() - (self.boxHeight / 2);
		float maxZ1 = selfPos.getZ() + (self.boxHeight / 2);

		Vec3<float> otherPos = other.parent->getPosition();
		float minX2 = otherPos.getX() - (other.boxDepth / 2);
		float maxX2 = otherPos.getX() + (other.boxDepth / 2);
		float minY2 = otherPos.getY() - (other.boxWidth / 2);
		float maxY2 = otherPos.getY() + (other.boxWidth / 2);
		float minZ2 = otherPos.getZ() - (other.boxHeight / 2);
		float maxZ2 = otherPos.getZ() + (other.boxHeight / 2);

		if ( //simple rectangle box
			((minX1 < minX2 < maxX1) || (minX1 < maxX2 < maxX1))&&
			((minY1 < minY2 < maxY1) || (minY1 < maxY2 < maxY1))&&
			((minZ1 < minZ2 < maxZ1) || (minZ1 < maxZ2 < maxZ1))
		) {
			if (sendMessage) {
				self.parent->receiveCollision(other.parent, other.parent->getIdentifier(), otherPos);
				other.parent->receiveCollision(self.parent, self.parent->getIdentifier(), selfPos);
			}
			return true;
		}
		return false;
	}

	bool sphereToBox(Collider& self, Collider& other, bool sendMessage) {
		Vec3<float> selfPos = self.parent->getPosition();
		float rad = self.radius;

		Vec3<float> otherPos = other.parent->getPosition();
		float minX = otherPos.getX() - (other.boxDepth / 2);
		float maxX = otherPos.getX() + (other.boxDepth / 2);
		float minY = otherPos.getY() - (other.boxWidth / 2);
		float maxY = otherPos.getY() + (other.boxWidth / 2);
		float minZ = otherPos.getZ() - (other.boxHeight / 2);
		float maxZ = otherPos.getZ() + (other.boxHeight / 2);

		//find nearest point on box
		float x = 0;
		float y = 0;
		float z = 0;

		if (selfPos.getX() > maxX) { x = maxX; }
		else if (selfPos.getX() < minX) { x = minX; }
		else { x = otherPos.getX(); }

		if (selfPos.getY() > maxY) { y = maxY; }
		else if (selfPos.getY() < minY) { y = minY; }
		else { y = otherPos.getY(); }

		if (selfPos.getZ() > maxZ) { z = maxZ; }
		else if (selfPos.getZ() < minZ) { z = minZ; }
		else { z = otherPos.getZ(); }

		Vec3<float> p(x, y, z);

		//simple distance check
		if (sqrt(selfPos.dot(selfPos) + p.dot(p)) < (self.radius)) {
			if (sendMessage) {
				self.parent->receiveCollision(other.parent, other.parent->getIdentifier(), otherPos);
				other.parent->receiveCollision(self.parent, self.parent->getIdentifier(), selfPos);
			}
			return true;
		}
		return false;
	}
};