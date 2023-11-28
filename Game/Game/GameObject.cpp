#pragma once
#include "GameObject.h"
//sfml

//stl

//other


void GameObject::setParentWorld(GameWorld* newParentWorld) {
	parentWorld = newParentWorld;
}

void GameObject::destroy() {
	destroyed = true;
}

bool GameObject::exists() {
	return !destroyed;
}

Vec3<float> GameObject::getPosition() {
	return position;
}
void GameObject::setPosition(Vec3<float> newPosition) {
	position = newPosition;
}
void GameObject::setPosition(float newX, float newY, float newZ) {
	Vec3<float> newPosition(newX, newY, newZ);
	setPosition(newPosition);
}
Rotation<float> GameObject::getRotation() {
	return rotation;
}
void GameObject::setRotation(Rotation<float> newRotation) {
	rotation = newRotation;
}
