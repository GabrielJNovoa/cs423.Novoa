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

class GraphicsObject : virtual public GameObject
{
protected:
	std::vector<Primitive> mesh;
public:
	GraphicsWorld::Drawable* drawTick() {
		GraphicsWorld::Drawable* out = new GraphicsWorld::Drawable;
		out->toForward = rotation.axisToForward();
		out->forwardAngle = rotation.angleToForward();
		out->toUp = rotation.getForward();
		out->upAngle = rotation.angleToUp();
		out->translation = position;
		out->primBundles = new GraphicsWorld::PrimBundle[mesh.size()];

		for (int i = 0; i < mesh.size(); i++) {
			out->primBundles[i] = mesh[i].readData();
		}
	}
};

