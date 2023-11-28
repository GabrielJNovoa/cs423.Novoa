#pragma once
#include "GameObject.h"
#include <SFML/Window.hpp>
#include <stack>
#include <list>
class InputObject : virtual public GameObject
{
protected:
	std::list<sf::Event::EventType> eventTypes;
	std::stack<sf::Event> eventStack;
public:
	std::list<sf::Event::EventType> getEvents() {
		return eventTypes;
	}
	void receiveEvent(sf::Event& newEvent) {
		eventStack.push(newEvent);
	}
};
