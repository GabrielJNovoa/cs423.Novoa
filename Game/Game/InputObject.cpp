#pragma once
#include "InputObject.h"
//sfml

//stl

//other


std::list<sf::Event::EventType> InputObject::getEvents() {
	return eventTypes;
}
void InputObject::receiveEvent(sf::Event& newEvent) {
	eventStack.push(newEvent);
}
