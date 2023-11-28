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

// positive x is forwards
// positive y is left
// positive z is up

template <typename T>
class Vec3
{
private:
	T x = 0;
	T y = 0;
	T z = 0;
public:
	Vec3() {};
	Vec3(T newX, T newY, T newZ) : x(newX), y(newY), z(newZ) {}

	void set(T newX, T newY, T newZ) {
		x = newX;
		y = newY;
		z = newZ;
	}

	void setX(T newX) {
		x = newX;
	}
	void setY(T newY) {
		y = newY;
	}
	void setZ(T newZ) {
		z = newZ;
	}

	T getX() const {
		return x;
	}
	T getY() const {
		return y;
	}
	T getZ() const {
		return z;
	}

	float magnitude() const {
		return sqrt(x * x + y * y + z * z);
	}

	bool isZero() const {
		return (x == 0 && y == 0 && z == 0);
	}

	Vec3<T> normalized() const {
		Vec3<T> tmp(x, y, z);
		float mag = magnitude();
		if (mag == 0) {
			return tmp * mag;
		}
		else {
			return tmp * (1 / mag);
		}
	}

	void normalize() {
		float mag = 1 / magnitude();
		x *= mag;
		y *= mag;
		z *= mag;
	}

	Vec3<T> operator+(Vec3<T> const& other) {
		Vec3<T> tmp(x + other.getX(), y + other.getY(), z + other.getZ());
		return tmp;
	}
	Vec3<T> operator-(Vec3<T> const& other) {
		Vec3<T> tmp(x - other.getX(), y - other.getY(), z - other.getZ());
		return tmp;
	}

	T dot(Vec3<T> const& other) const {
		return x * other.getX() + y * other.getY() + z * other.getZ();
	}
	Vec3<T> cross(Vec3<T> const& other) const {
		Vec3<T> tmp(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.z);
		return tmp;
	}
	T angleBetween(Vec3<T> const other) const {
		return acos(dot(other) / (magnitude() * other.magnitude()));
	}
	Vec3<T> rotateAround(Vec3<T> const& other, float const angle) {
		Vec3<T> o;
		o = other.normalized();
		T s = sin(angle);
		T c = cos(angle);

		Vec3<T> A(
			1 + (1 - c) * (-(o.z * o.z) - (o.y * o.y)),
			-s * o.z + (1 - c) * (o.x * o.y),
			s * o.y + (1 - c) * (o.x * o.z)
		);
		Vec3<T> B(
			s * o.z + (1 - c) * (o.x * o.y),
			1 + (1 - c) * (-(o.z * o.z) - (o.x * o.x)),
			-s * o.x + (1 - c) * (o.y * o.z)
		);
		Vec3<T> C(
			-s * o.y + (1 - c) * (o.x * o.z),
			s * o.x + (1 - c) * (o.y * o.z),
			1 + (1 - c) * (-(o.x * o.x) - (o.y * o.y))
		);

		Vec3<T> out(dot(A), dot(B), dot(C));
		return out;		
	}

	template <typename S>
	Vec3<T> operator*(S const& other) {
		Vec3<T> tmp(x * other, y * other, z * other);
		return tmp;
	}

	std::string toString() {
		return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
	}
};

