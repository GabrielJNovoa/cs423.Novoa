#ifndef MASTERINCLUDE
#define MASTERINCLUDE
#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include <numbers>
#include <list>
#include <array>
#include <vector>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <SFML/Graphics.hpp>
#define GLAD_GL_IMPLEMENTATION
#include <gl/GL.h>

#include "Collider.hpp"
#include "GameObject.hpp"
#include "GameWorld.hpp"
#include "GraphicsObject.hpp"
#include "GraphicsWorld.hpp"
#include "InputObject.hpp"
#include "InputWorld.hpp"
#include "PhysicsObject.hpp"
#include "PhysicsWorld.hpp"
#include "Primitive.hpp"
#include "RefMan.hpp"
#include "Rotation.hpp"
#include "Vec3.hpp"
#endif // !MASTERINCLUDE

class GameWorld
{
private:
	std::list<RefMan<GameObject>::Ref> inhabitants;
	PhysicsWorld physicsWorld;
	InputWorld inputWorld;
	GraphicsWorld graphicsWorld;
	RefMan<GameObject>::Ref camera;
	sf::Event event;
public:
	
	GameWorld() {}

	void setCamera(RefMan<GameObject>::Ref newCamera) {
		camera = newCamera;
	}

	void addGameObject(RefMan<GameObject>::Ref newObject) {
		inhabitants.push_back(newObject);
	}

	void addInputObject(RefMan<InputObject>::Ref newObject) {
		inputWorld.addInputObject(newObject);
	}

	void addPhysicsObject(RefMan<PhysicsObject>::Ref newObject) {
		physicsWorld.addPhysicsObject(newObject);
	}

	void addGraphicsObject(RefMan<GraphicsObject>::Ref newObject) {
		graphicsWorld.addGraphicsObject(newObject);
	}

	void tick(sf::Window& window) {
		preTick();
		physicsTick();
		postTick();
		drawTick(window);
	}
	void preTick() {
		for (auto i = inhabitants.begin(); i != inhabitants.end(); i++) {
			if ((*i).exists()) {
				(*(*i)).preTick();
			}
			else {
				inhabitants.erase(i);
			}
		}
	}
	void postTick() {
		for (auto i = inhabitants.begin(); i != inhabitants.end(); i++) {
			if ((*i).exists()) {
				(*(*i)).postTick();
			}
			else {
				inhabitants.erase(i);
			}
		}
	}
	void physicsTick() {
		physicsWorld.physicsTick();
	}

	void drawTick(sf::Window& window) {
		graphicsWorld.drawTick(window, camera);
	}

	void processEvents(sf::Window& window) {
		while (window.pollEvent(event)) {
			
			inputWorld.inputStep(event);
			
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
	}

	GraphicsWorld& getGraphicsWorld() {
		return graphicsWorld;
	}
};

