#pragma once
//sfml

//stl
#include <algorithm>
//other
#include "Vec3.hpp"
#include "GameObject.h"
#include "PhysicsObject.h"

class PhysicsObject;

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
	Collider();
	void setRadius(float newRadius);
	void setDepth(float newDepth);
	void setWidth(float newWidth);
	void setHeight(float newHeight);
	void setParent(PhysicsObject* newParent);
	void setType(int newType);
	enum Type {
		SPHERE,
		ORTHOBOX
	};
	bool collide(Collider& other, bool sendMessage);
	bool sphereToSphere(Collider& self, Collider& other, bool sendMessage);
	bool boxToBox(Collider& self, Collider& other, bool sendMessage);
	bool sphereToBox(Collider& self, Collider& other, bool sendMessage);
};