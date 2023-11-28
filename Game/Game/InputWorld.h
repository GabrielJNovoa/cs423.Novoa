#pragma once
//sfml
#include <SFML/Window.hpp>
//stl
#include <vector>
#include <list>
#include <array>
//other
#include "InputObject.h"

class InputWorld
{
private:
	std::array<std::list<InputObject*>, sf::Event::Count> eventsByType;
public:
	void addInputObject(InputObject* newObject);
	void inputTick();
	void receiveInputs(sf::Event& event);
};

