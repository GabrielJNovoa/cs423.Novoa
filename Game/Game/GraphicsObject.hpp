#pragma once
//sfml

//stl
#include <vector>
//other
#include "Primitive.hpp"
#include "GraphicsWorld.hpp"
#include "Vec3.hpp"
#include "Rotation.hpp"
#include "PrimBundle.hpp"
#include "Drawable.hpp"

class GraphicsObject : virtual public GameObject
{
protected:
	std::vector<Primitive> mesh;
public:
	Drawable* drawTick() {
		Drawable* out = new Drawable;
		out->rotation = rotation;
		out->translation = position;
		out->count = mesh.size();
		out->primBundles = new PrimBundle[mesh.size()];

		if (mesh.size() != 0) {
			for (int i = 0; i < mesh.size(); i++) {
				out->primBundles[i] = mesh[i].readData();
			}
		}

		return out;
	}

	void addPrimitive(Primitive newPrimitive) {
		mesh.push_back(newPrimitive);
	}
};

