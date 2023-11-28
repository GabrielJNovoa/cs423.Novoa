#pragma once
//sfml
#include <SFML/Window.hpp>
//stl
#include <list>
#include <stack>
//other
#include "GameObject.h"


class InputObject : virtual public GameObject
{
protected:
	std::list<sf::Event::EventType> eventTypes;
	std::stack<sf::Event> eventStack;
public:
	std::list<sf::Event::EventType> getEvents();
	void receiveEvent(sf::Event& newEvent);
};
