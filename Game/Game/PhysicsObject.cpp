#pragma once
#include "PhysicsObject.h"
//sfml

//stl

//other

class Collider;

PhysicsObject::PhysicsObject() {}
void PhysicsObject::receiveCollision(PhysicsObject* otherObject, std::string otherIdentifier, Vec3<float> otherPosition) {
	Collision col;
	col.object = otherObject;
	col.identifier = otherIdentifier;
	col.position = otherPosition;
	collisionStack.push(col);
}
std::string PhysicsObject::getIdentifier() {
	return identifier;
}
void PhysicsObject::setHome(PhysicsWorld* newHome) {
	home = newHome;
}
bool PhysicsObject::checkCollision(bool sendMessage) {
	return (home->checkCollision(this, sendMessage));
}
Collider* PhysicsObject::getCollider() {
	return collider;
}
void PhysicsObject::updatePosition(Vec3<float> newPosition, Vec3<float> oldPosition) {
	home->updatePosition(newPosition, oldPosition, this);
}
bool PhysicsObject::collide(PhysicsObject* other, bool sendMessage) {
	return collider->collide(*(other->collider), sendMessage);
}
