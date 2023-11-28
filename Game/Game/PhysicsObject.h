#pragma once
//sfml

//stl
#include <stack>
//other
#include "GameObject.h"
#include "PhysicsWorld.h"
#include "Collider.h"

class Collider;
class PhysicsWorld;

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
	Collider *collider = nullptr;
	PhysicsWorld* home = nullptr;
public:
	PhysicsObject();
	void receiveCollision(PhysicsObject* otherObject, std::string otherIdentifier, Vec3<float> otherPosition);
	virtual void physicsTick() = 0;
	std::string getIdentifier();
	void setHome(PhysicsWorld* newHome);
	bool checkCollision(bool sendMessage);
	Collider* getCollider();
	void updatePosition(Vec3<float> newPosition, Vec3<float> oldPosition);
	bool collide(PhysicsObject* other, bool sendMessage);
};

