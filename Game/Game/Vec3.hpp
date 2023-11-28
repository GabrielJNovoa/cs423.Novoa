#pragma once
//sfml

//stl
#include <numbers>
#include <cmath>
#include <string>
//other


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

	Vec3<T> xComponent() {
		Vec3<float> out(x, 0, 0);
		return out;
	}
	Vec3<T> yComponent() {
		Vec3<float> out(0, y, 0);
		return out;
	}
	Vec3<T> zComponent() {
		Vec3<float> out(0, 0, z);
		return out;
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
		Vec3<T> v(x, y, z);
		v.normalize();

		T s = sin(angle);
		T c = cos(angle);

		Vec3<T> A(
			c + o.x * o.x * (1 - c),
			o.x * o.y * (1 - c) - o.z * s,
			o.x * o.z * (1 - c) + o.y * s
		);
		Vec3<T> B(
			o.y * o.x * (1 - c) + o.z * s,
			c + o.y * o.y * (1 - c),
			o.y * o.z * (1 - c) - o.x * s
		);
		Vec3<T> C(
			o.z * o.x * (1 - c) - o.y * s,
			o.z * o.y * (1 - c) + o.x * s,
			c + o.z * o.z * (1 - c)
		);

		Vec3<T> out(v.dot(A), v.dot(B), v.dot(C));
		v = v * magnitude();
		return out;		
	}
	T distance(Vec3<T>& other) {
		return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z));
	}

	template <typename S>
	Vec3<T> operator*(S const& other) {
		Vec3<T> tmp(x * other, y * other, z * other);
		return tmp;
	}

	std::string toString() {
		return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
	}

	Vec3<T> toOpenGl() {
		Vec3<T> out(-y, z, -x);
		return out;
	}
};

