#pragma once
//sfml

//stl

//other
#include "Rotation.hpp"

class Drawable
{
public:
	Rotation<float> rotation;
	Vec3<float> translation;
	unsigned int count;
	PrimBundle* primBundles;

	~Drawable() {
		delete[] primBundles;
	}
};

