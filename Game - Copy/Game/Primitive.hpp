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

class Primitive
{
private:
	unsigned int textureId;
	unsigned int size = 0;
	GLfloat* vertices = nullptr;
public:
	void setTextureId(unsigned int newId) {
		textureId = newId;
	}
	void addVertex(float x, float y, float z, float u, float v) {
		size += 1;
		GLfloat* tmp = new GLfloat[size * 5];
		for (int i = 0; i < (size-1)*5; i++) {
			tmp[i] = vertices[i];
		}
		delete[] vertices;
		vertices = tmp;

		vertices[size * 5 - 5] = x;
		vertices[size * 5 - 4] = y;
		vertices[size * 5 - 3] = z;
		vertices[size * 5 - 2] = u;
		vertices[size * 5 - 1] = v;
	}
	void addVertex(Vec3<float> pos, float u, float v) {
		addVertex(pos.getX(), pos.getY(), pos.getZ(), u, v);
	}
	
	GraphicsWorld::PrimBundle readData() {
		GraphicsWorld::PrimBundle out;
		out.count = size;
		out.texId = textureId;
		out.vertices = vertices;
	}

	~Primitive() {
		delete[] vertices;
	}
};

