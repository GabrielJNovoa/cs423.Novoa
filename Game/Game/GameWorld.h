#pragma once
//sfml
#include <SFML/Graphics.hpp>
//stl
#include <list>
#include <vector>
#include <stack>
#include <iostream>
//other
#include "GameObject.h"
#include "GraphicsObject.h"
#include "InputObject.h"
#include "PhysicsObject.h"
#include "GraphicsWorld.h"
#include "PhysicsWorld.h"
#include "InputWorld.h"


class GameObject;

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
	GameWorld(sf::Window* newWindow, unsigned int physicsWorldSize, unsigned int physicsWorldChunks);
	void setCamera(GameObject* newCamera);
	void addGameObject(GameObject* newObject);
	void addInputObject(InputObject* newObject);
	void addPhysicsObject(PhysicsObject* newObject);
	void addGraphicsObject(GraphicsObject* newObject);
	void tick(sf::Window& window);
	void inputTick();
	void preTick();
	void postTick();
	void physicsTick();
	void drawTick();
	void processEvents();
	void setWindow(sf::Window* win);
	void loadTexture(std::string path);
	GraphicsWorld& getGraphicsWorld();
};

