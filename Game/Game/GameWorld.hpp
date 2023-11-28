#pragma once
//stl
#include <list>
//other
#include "RefMan.hpp"
#include "GameObject.h"
#include "PhysicsWorld.h"
#include "InputWorld.hpp"
#include "GraphicsWorld.hpp"
#include "InputObject.hpp"
#include "PhysicsObject.h"
#include "GraphicsObject.h"

class GameWorld
{
private:
	sf::Window* window = nullptr;
	std::list<GameObject*> inhabitants;
	std::list<GameObject*> dyingInhabitants;
	std::list<GameObject*> deadInhabitants;
	PhysicsWorld physicsWorld;
	InputWorld inputWorld;
	GraphicsWorld graphicsWorld;
	GameObject* camera = nullptr;
	sf::Event event;
public:
	GameWorld(sf::Window* newWindow, unsigned int physicsWorldSize, unsigned int physicsWorldChunks) {
		physicsWorld.createWorld(physicsWorldSize, physicsWorldChunks);
		window = newWindow;
	}
	void setCamera(GameObject* newCamera) {
		camera = newCamera;
	}

	void addGameObject(GameObject* newObject) {
		newObject->setParentWorld(this);
		inhabitants.push_back(newObject);
	}

	void addInputObject(InputObject* newObject) {
		inputWorld.addInputObject(newObject);
	}

	void addPhysicsObject(PhysicsObject* newObject) {
		physicsWorld.addPhysicsObject(newObject);
	}

	void addGraphicsObject(GraphicsObject* newObject) {
		graphicsWorld.addGraphicsObject(newObject);
	}

	void tick(sf::Window& window) {
		inputTick();
		preTick();
		physicsTick();
		postTick();
		drawTick();

		for (auto i : deadInhabitants) {
			delete i;
		}
		deadInhabitants.clear();
		std::swap(deadInhabitants, dyingInhabitants);
	}

	void inputTick() {
		inputWorld.inputTick();
	}

	void preTick() {
		for (auto i = inhabitants.begin(); i != inhabitants.end(); i++) {
			if ((*i)->exists()) {
				(*(*i)).preTick();
			}
			else {
				dyingInhabitants.push_back(*i);
				inhabitants.erase(i);
			}
		}
	}
	void postTick() {
		for (auto i = inhabitants.begin(); i != inhabitants.end(); i++) {
			if ((*i)->exists()) {
				(*i)->postTick();
			}
			else {
				dyingInhabitants.push_back(*i);
				inhabitants.erase(i);
			}
		}
	}
	void physicsTick() {
		physicsWorld.physicsTick();
	}

	void drawTick() {
		if (camera!= nullptr) {
			if (camera->exists()) {
				graphicsWorld.drawTick(*window, camera);
			}
		}
	}

	void processEvents() {
		while (window->pollEvent(event)) {
			
			inputWorld.receiveInputs(event);
			
			switch (event.type) {
			case sf::Event::Closed:
				window->close();
				break;
			}
		}
	}

	void setWindow(sf::Window* win) {
		window = win;
	}

	void loadTexture(std::string path) {
		graphicsWorld.loadTexture(path);
	}

	GraphicsWorld& getGraphicsWorld() {
		return graphicsWorld;
	}
};

