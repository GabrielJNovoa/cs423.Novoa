#pragma once
//sfml
#include <SFML/Graphics.hpp>
//stl
#include <vector>
#include <numbers>
#include <list>
//other
#include "GameObject.h"
#include "GraphicsObject.h"
#include "Vec3.hpp"
#include "PrimBundle.hpp"
#include "Drawable.hpp"

class GraphicsWorld
{
private:
	std::list<GraphicsObject*> inhabitants;
	std::vector<sf::Texture> textures;
public:
	GraphicsWorld();
	void addGraphicsObject(GraphicsObject* newObject);
	void drawTick(sf::Window& window, GameObject* camera);
	void loadTexture(std::string path);
};

