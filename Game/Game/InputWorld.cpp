#pragma once
#include "InputWorld.h"
//sfml

//stl

//other


void InputWorld::addInputObject(InputObject* newObject) {
	std::list<sf::Event::EventType> events = newObject->getEvents();
	for (const auto& ev : events) {
		eventsByType[ev].push_back(newObject);
	}
}
void InputWorld::inputTick() { //clean out deleted objects
	for (auto& ls : eventsByType) {
		for (auto i = ls.begin(); i != ls.end(); i++) {
			if (!(*i)->exists()) {
				ls.erase(i);
			}
		}
	}
}
void InputWorld::receiveInputs(sf::Event& event) {
	for (auto& i : eventsByType[event.type]) {
		i->receiveEvent(event);
	}
}