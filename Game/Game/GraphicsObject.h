#pragma once
//sfml

//stl
#include <vector>
//other
#include "GameObject.h"
#include "Primitive.hpp"
#include "Drawable.hpp"

class GraphicsObject : virtual public GameObject
{
protected:
	std::vector<Primitive> mesh;
public:
	Drawable* drawTick();
	void addPrimitive(Primitive newPrimitive);
};

