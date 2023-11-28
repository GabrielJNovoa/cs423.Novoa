#pragma once
//sfml
#include <SFML/Window/Event.hpp>
//stl
#include <list>
#include <array>
//other
#include "InputObject.hpp"

class InputWorld
{
private:
	std::array<std::list<InputObject*>,sf::Event::Count> eventsByType;
public:
	void addInputObject(InputObject* newObject) {
		std::list<sf::Event::EventType> events = newObject->getEvents();
		for (const auto& ev : events) {
			eventsByType[ev].push_back(newObject);
		}
	}

	void inputTick() { //clean out deleted objects
		for (auto& ls : eventsByType) {
			for (auto i = ls.begin() ; i != ls.end() ; i++) {
				if (!(*i)->exists()) {
					ls.erase(i);
				}
			}
		}
	}

	void receiveInputs(sf::Event& event) {
		for (auto& i : eventsByType[event.type]) {
			i->receiveEvent(event);
		}
	}
};

