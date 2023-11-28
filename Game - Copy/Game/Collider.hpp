#pragma once
#include "Vec3.hpp"

class Collider
{
private:
	Vec3<double> position;
public:
	enum type {
		sphere,
		triangle
	};
};

