#pragma once
//sfml

//stl

//other
#include "Vec3.hpp"
#include "PrimBundle.hpp"

class Primitive
{
private:
	unsigned int textureId;
	unsigned int size = 0;
	float* vertices = nullptr;
public:

	Primitive() {}

	void setTextureId(unsigned int newId) {
		textureId = newId;
	}
	void addVertex(float x, float y, float z, float u, float v) {
		size += 1;
		float* tmp = new float[size * 5];
		for (unsigned int i = 0; i < (size-1)*5; i++) {
			tmp[i] = vertices[i];
		}
		delete[] vertices;
		vertices = tmp;

		vertices[size * 5 - 5] = x; //convert to open gl coordinates
		vertices[size * 5 - 4] = y;
		vertices[size * 5 - 3] = z;
		vertices[size * 5 - 2] = u;
		vertices[size * 5 - 1] = v;
	}
	void addVertex(Vec3<float> pos, float u, float v) {
		addVertex(pos.getX(), pos.getY(), pos.getZ(), u, v);
	}
	
	PrimBundle readData() {
		PrimBundle out;
		out.count = size;
		out.texId = textureId;
		out.vertices = vertices;
		return out;
	}

	Primitive(const Primitive& other) {
		textureId = other.textureId;
		size = other.size;
		vertices = new float[size * 5];
		for (unsigned int i = 0; i < size * 5; i++) {
			vertices[i] = other.vertices[i];
		}
	}

	Primitive& operator=(const Primitive& other) {
		textureId = other.textureId;
		size = other.size;

		delete[] vertices;

		vertices = new float[size * 5];
		for (unsigned int i = 0; i < size * 5; i++) {
			vertices[i] = other.vertices[i];
		}
	}

	~Primitive() {
		delete[] vertices;
	}
};

