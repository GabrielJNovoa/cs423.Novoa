#pragma once
#include "GameObject.hpp"
#include <SFML/Window.hpp>
#include <stack>
#include <list>
class InputObject : virtual public GameObject
{
protected:
	std::list<unsigned int> eventTypes;
	std::stack<sf::Event> eventStack;
public:
	std::list<unsigned int>& getEvents() {
		return eventTypes;
	}
	void receiveEvent(sf::Event& newEvent) {
		eventStack.push(newEvent);
	}
};
