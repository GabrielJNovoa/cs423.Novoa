#pragma once
#include "GameWorld.h"
//sfml

//stl

//other

GameWorld::GameWorld(sf::Window* newWindow, unsigned int physicsWorldSize, unsigned int physicsWorldChunks) {
	physicsWorld.createWorld(physicsWorldSize, physicsWorldChunks);
	window = newWindow;
}
void GameWorld::setCamera(GameObject* newCamera) {
	camera = newCamera;
}
void GameWorld::addGameObject(GameObject* newObject) {
	newObject->setParentWorld(this);
	inhabitants.push_back(newObject);
}
void GameWorld::addInputObject(InputObject* newObject) {
	inputWorld.addInputObject(newObject);
}
void GameWorld::addPhysicsObject(PhysicsObject* newObject) {
	physicsWorld.addPhysicsObject(newObject);
}
void GameWorld::addGraphicsObject(GraphicsObject* newObject) {
	graphicsWorld.addGraphicsObject(newObject);
}
void GameWorld::tick(sf::Window& window) {
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
void GameWorld::inputTick() {
	inputWorld.inputTick();
}
void GameWorld::preTick() {
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
void GameWorld::postTick() {
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
void GameWorld::physicsTick() {
	physicsWorld.physicsTick();
}
void GameWorld::drawTick() {
	if (camera != nullptr) {
		if (camera->exists()) {
			graphicsWorld.drawTick(*window, camera);
		}
	}
}
void GameWorld::processEvents() {
	while (window->pollEvent(event)) {

		inputWorld.receiveInputs(event);

		switch (event.type) {
		case sf::Event::Closed:
			window->close();
			break;
		}
	}
}
void GameWorld::setWindow(sf::Window* win) {
	window = win;
}
void GameWorld::loadTexture(std::string path) {
	graphicsWorld.loadTexture(path);
}
GraphicsWorld& GameWorld::getGraphicsWorld() {
	return graphicsWorld;
}

