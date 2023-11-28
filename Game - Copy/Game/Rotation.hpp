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
class Rotation
{
private:
	Vec3<T> forward;
	Vec3<T> up;
public:
	Rotation() {
		forward.setX(1);
		up.setY(1);
	};

	static Rotation<T> RightTurn(T angle) {
		Rotation<T> tmp;
		Vec3<T> newForward(cos(-angle), sin(-angle), 0);
		tmp.setForward(newForward);

		return tmp;
	}
	static Rotation<T> upTurn(T angle) {
		Rotation<T> tmp;

		Vec3<T> newForward(cos(angle), 0, sin(angle));
		Vec3<T> newUp(cos(angle + std::numbers::pi / 2), 0, sin(angle + std::numbers::pi / 2));

		tmp.setForward(newForward);
		tmp.setUp(newUp);

		return tmp;
	}
	static Rotation<T> rightRoll(T angle) {
		Rotation<T> tmp;

		Vec3<T> newUp(0, sin(-angle), cos(-angle));
		tmp.setUp(newUp);

		return tmp;
	}
	static Rotation<T> identity() {
		Rotation<T> tmp;
		return tmp;
	}

	void setForward(Vec3<T> &newForward) {
		forward = newForward.normalized();
	}
	void setUp(Vec3<T> &newUp) {
		up = newUp.normalized();
	}

	Vec3<T> getForward() const {
		return forward;
	}
	Vec3<T> getUp() const {
		return up;
	}

	Vec3<T> axisToForward() const { //gets the axis you rotate around by angleToForward() to get to the forward vector
		Vec3<T> f(1, 0, 0);
		Vec3<T> u(0, 0, 1);
		Vec3<T> k = forward.cross(f);
		T angle = forward.angleBetween(f);
		if (k.isZero()) {
			k.setZ(1); //makes k (0,1,0) since forward must be (-1,0,0)
		}
		return k;
	}
	T angleToForward() const {
		Vec3<T> f(1, 0, 0);
		return forward.angleBetween(f);
	}
	T angleToUp() const {
		Vec3<T> f(1, 0, 0);
		Vec3<T> u(0, 0, 1);
		return up.angleBetween(u.rotateAround(axisToForward(),angleToForward()));
	}

	Rotation<T> operator* (Rotation<T> const& other) {
		Vec3<T> f(1, 0, 0);
		Vec3<T> u(0, 0, 1);
		Vec3<T> k = forward.cross(f);
		T angle = forward.angleBetween(f);
		if (k.isZero()) {
			k.setZ(1); //makes k (0,1,0) since forward must be (-1,0,0)
		}

		Rotation<T> out;
		
		T a = up.rotateAround(k, angle).angleBetween(u);

		out.forward = other.getForward().rotateAround(f, a).rotateAround(k, -angle);
		out.up = other.getUp().rotateAround(f, a).rotateAround(k, -angle);
		
		return out;
	}
};

