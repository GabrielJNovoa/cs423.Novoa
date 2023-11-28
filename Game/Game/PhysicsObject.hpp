#pragma once
//sfml

//stl
#include <list>
#include <string>
#include <stack>
//other
#include "GameObject.h"
#include "Vec3.hpp"
#include "Collider.hpp"

class PhysicsObject : virtual public GameObject
{
protected:
	struct Collision {
		PhysicsObject* object = nullptr;
		std::string identifier = "";
		Vec3<float> position;

		void print() {
			std::cout << "object: " << object << "\n";
			std::cout << "identifier: " << identifier << "\n";
			std::cout << "position: " << position.toString() << "\n\n";
		}
	};
	std::string identifier;
	std::stack<Collision> collisionStack;
	Collider collider;

public:
	PhysicsObject() {}
	void receiveCollision(PhysicsObject* otherObject, std::string otherIdentifier, Vec3<float> otherPosition) {
		Collision col;
		col.object = otherObject;
		col.identifier = otherIdentifier;
		col.position = otherPosition;
		collisionStack.push(col);
	}

	virtual void physicsTick() = 0;

	std::string getIdentifier() {
		return identifier;
	}
};

