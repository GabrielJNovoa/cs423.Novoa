#pragma once
#include "Collider.h"
//sfml

//stl

//other

Collider::Collider() {}
void Collider::setRadius(float newRadius) {
	radius = newRadius;
}
void Collider::setDepth(float newDepth) {
	boxDepth = newDepth;
}
void Collider::setWidth(float newWidth) {
	boxWidth = newWidth;
}
void Collider::setHeight(float newHeight) {
	boxHeight = newHeight;
}
void Collider::setParent(PhysicsObject* newParent) {
	parent = newParent;
}
void Collider::setType(int newType) {
	ColliderType = newType;
}
bool Collider::collide(Collider& other, bool sendMessage) {
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
bool Collider::sphereToSphere(Collider& self, Collider& other, bool sendMessage) {

	Vec3<float> selfPos = self.parent->getPosition();
	Vec3<float> otherPos = other.parent->getPosition();

	//simple distance check
	if (selfPos.distance(otherPos) < (self.radius + other.radius)) {
		if (sendMessage) {
			self.parent->receiveCollision(other.parent, other.parent->getIdentifier(), otherPos);
			other.parent->receiveCollision(self.parent, self.parent->getIdentifier(), selfPos);
		}
		return true;
	}
	return false;
}
bool Collider::boxToBox(Collider& self, Collider& other, bool sendMessage) {

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
		minX1 <= maxX2 &&
		maxX1 >= minX2 &&
		minY1 <= maxY2 &&
		maxY1 >= minY2 &&
		minZ1 <= maxZ2 &&
		maxZ1 >= minZ2
		) {
		if (sendMessage) {
			self.parent->receiveCollision(other.parent, other.parent->getIdentifier(), otherPos);
			other.parent->receiveCollision(self.parent, self.parent->getIdentifier(), selfPos);
		}
		return true;
	}
	return false;
}
bool Collider::sphereToBox(Collider& self, Collider& other, bool sendMessage) {
	Vec3<float> selfPos = self.parent->getPosition();
	float rad = self.radius;

	Vec3<float> otherPos = other.parent->getPosition();
	float minX = otherPos.getX() - (other.boxDepth / 2);
	float maxX = otherPos.getX() + (other.boxDepth / 2);
	float minY = otherPos.getY() - (other.boxWidth / 2);
	float maxY = otherPos.getY() + (other.boxWidth / 2);
	float minZ = otherPos.getZ() - (other.boxHeight / 2);
	float maxZ = otherPos.getZ() + (other.boxHeight / 2);

	Vec3<float> p(
		std::clamp(selfPos.getX(), minX, maxX),
		std::clamp(selfPos.getY(), minY, maxY),
		std::clamp(selfPos.getZ(), minZ, maxZ)
		);

	//simple distance check
	if (selfPos.distance(p) < (self.radius)) {
		if (sendMessage) {
			self.parent->receiveCollision(other.parent, other.parent->getIdentifier(), otherPos);
			other.parent->receiveCollision(self.parent, self.parent->getIdentifier(), selfPos);
		}
		return true;
	}
	return false;
}