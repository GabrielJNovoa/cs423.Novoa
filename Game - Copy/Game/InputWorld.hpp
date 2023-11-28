#ifndef MASTERINCLUDE
#define MASTERINCLUDE
#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include <numbers>
#include <list>
#include <array>
#include <vector>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <SFML/Graphics.hpp>
#define GLAD_GL_IMPLEMENTATION
#include <gl/GL.h>

#include "Collider.hpp"
#include "GameObject.hpp"
#include "GameWorld.hpp"
#include "GraphicsObject.hpp"
#include "GraphicsWorld.hpp"
#include "InputObject.hpp"
#include "InputWorld.hpp"
#include "PhysicsObject.hpp"
#include "PhysicsWorld.hpp"
#include "Primitive.hpp"
#include "RefMan.hpp"
#include "Rotation.hpp"
#include "Vec3.hpp"
#endif // !MASTERINCLUDE

class InputWorld
{
private:
	std::list<RefMan<InputObject>::Ref> inhabitants;
	std::array<std::list<RefMan<InputObject>::Ref>,sf::Event::Count> eventsByType;
public:
	void addInputObject(RefMan<InputObject>::Ref newObject) {
		inhabitants.push_back(newObject);
	}
	void inputStep(sf::Event& event) {
		for (auto i = eventsByType[event.type].begin() ; i != eventsByType[event.type].end() ; i++) {
			if ((*i).exists()) {
				(*(*i)).receiveEvent(event);
			}
			else {
				eventsByType[event.type].erase(i);
			}
		}
	}
};

