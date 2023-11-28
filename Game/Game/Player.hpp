#pragma once
//sfml

//stl

//other
#include "GameObject.h"
#include "PhysicsObject.h"
#include "Collider.h"

class Player : virtual public GameObject, virtual public InputObject, virtual public PhysicsObject
{
private:
	sf::Event ev;
	sf::Window* window;
	Vec3<float> steeringVector;
	Vec3<float> velocity;
	float acceleration = 0.03;
	float deceleration = 0.1;
	float rotationSpeed = 0.002;
	float rollSpeed = 0.1;
	float rollMomentum = 0;

	// positive x is forwards
	// positive y is left
	// positive z is up
	//w = 22, a = 0, s = 18, d = 3
	void handleInputs() {
		int mult = 0;
		sf::Vector2i centerMouse;
		centerMouse.x = window->getSize().x / 2;
		centerMouse.y = window->getSize().y / 2;

		while (!eventStack.empty()) {
			mult = 0;
			ev = eventStack.top();
			eventStack.pop();

			switch (ev.type) {
			case sf::Event::MouseMoved:
				std::cout << ev.mouseMove.y - centerMouse.y << "\n";
				std::cout << ev.mouseMove.x - centerMouse.x << "\n";
				rotation.pitchUp(-(ev.mouseMove.y - centerMouse.y) * rotationSpeed);
				rotation.yawRight((ev.mouseMove.x - centerMouse.x) * rotationSpeed);

				sf::Mouse::setPosition(centerMouse, *window);

				break;
			case sf::Event::KeyPressed:
				mult = 1;
				break; 
			case sf::Event::KeyReleased:
				mult = -1;
				break;
			}

			std::cout << ev.key.scancode << "\n";
			if (mult != 0) {
				switch (ev.key.scancode) {
				case 22: //w
					steeringVector.setX(mult + steeringVector.getX());
					break;
				case 0: //a
					steeringVector.setY(mult + steeringVector.getY());
					break;
				case 40: //space
					steeringVector.setZ(mult + steeringVector.getZ());
					break;
				case 18: //s
					steeringVector.setX(-mult + steeringVector.getX());
					break;
				case 3: //s
					steeringVector.setY(-mult + steeringVector.getY());
					break;
				case 128: //lshift
					steeringVector.setZ(-mult + steeringVector.getZ());
					break;
				case sf::Keyboard::Q: //left roll
					rollMomentum -= mult;
					break;
				case sf::Keyboard::E: //right roll
					rollMomentum += mult;
					break;
				}
			}
		}
	}

public:
	Player() {
		eventTypes = { sf::Event::KeyPressed,sf::Event::KeyReleased, sf::Event::MouseMoved };
		identifier = "player";

		//Collider newCollider(this, Collider::SPHERE,20);
		collider = new Collider;
		collider->setParent(this);
		collider->setType(Collider::SPHERE);
		collider->setRadius(5);
	}

	void setWindow(sf::Window* win) {
		window = win;
	}

	void preTick() {}
	void physicsTick() {
		Collision col;
		while (!collisionStack.empty()) {
			col = collisionStack.top();
			collisionStack.pop();
			std::cout << "player:\n";
			col.print();
		}
	}
	void postTick() {
		Vec3<float> oldPosition = position;
		handleInputs();

		rotation.rollRight(rollMomentum*rollSpeed);

		velocity = velocity + (rotation.rotateVector(steeringVector) * acceleration);
		velocity = velocity * (1 - deceleration);

		if (moveStep(position + velocity.xComponent(), 10)) {
			velocity.setX(0);
		}
		if (moveStep(position + velocity.yComponent(), 10)) {
			velocity.setY(0);
		}
		if (moveStep(position + velocity.zComponent(), 10)) {
			velocity.setZ(0);
		}
	}

	bool moveStep(Vec3<float> targetPosition, int steps) {
		Vec3<float> prevPos = position;
		Vec3<float> direction = (targetPosition - position).normalized();
		float stepDistance = (targetPosition - position).magnitude();

		for (int i = 0; i < steps; i++) {
			prevPos = position;
			position = position + direction * stepDistance;
			updatePosition(position,prevPos);
			if (checkCollision(false)) {
				updatePosition(prevPos, position);
				position = prevPos;
				return true;
			}
		}

		return false;
	}
};

