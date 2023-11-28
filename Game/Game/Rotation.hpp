#pragma once
//sfml

//stl
#include <string>
#include <iostream>
//other
#include "Vec3.hpp"


// positive x is forwards
// positive y is left
// positive z is up
template <typename T>
class Rotation
{
private:
	Vec3<T> A;
	Vec3<T> B;
	Vec3<T> C;
public:
	Rotation() {
		A.set(1, 0, 0);
		B.set(0, 1, 0);
		C.set(0, 0, 1);
	}
	void pitchUp(T angle) {
		Vec3<T> X(cos(angle), 0, sin(angle));
		Vec3<T> Y(0, 1, 0);
		Vec3<T> Z(-sin(angle), 0, cos(angle));

		Vec3<T> newA(A.dot(X), A.dot(Y), A.dot(Z));
		Vec3<T> newB(B.dot(X), B.dot(Y), B.dot(Z));
		Vec3<T> newC(C.dot(X), C.dot(Y), C.dot(Z));

		A = newA;
		B = newB;
		C = newC;
	}
	void yawRight(T angle) {
		Vec3<T> X(cos(angle), -sin(angle), 0);
		Vec3<T> Y(sin(angle), cos(angle), 0);
		Vec3<T> Z(0, 0, 1);

		Vec3<T> newA(A.dot(X), A.dot(Y), A.dot(Z));
		Vec3<T> newB(B.dot(X), B.dot(Y), B.dot(Z));
		Vec3<T> newC(C.dot(X), C.dot(Y), C.dot(Z));

		A = newA;
		B = newB;
		C = newC;
	}
	void rollRight(T angle) {
		Vec3<T> X(1, 0, 0);
		Vec3<T> Y(0, cos(angle), sin(angle));
		Vec3<T> Z(0, -sin(angle), cos(angle));

		Vec3<T> newA(A.dot(X), A.dot(Y), A.dot(Z));
		Vec3<T> newB(B.dot(X), B.dot(Y), B.dot(Z));
		Vec3<T> newC(C.dot(X), C.dot(Y), C.dot(Z));

		A = newA;
		B = newB;
		C = newC;
	}

	Vec3<T> rotateVector(Vec3<T> vec) {
		Vec3<T> out(vec.dot(A), vec.dot(B), vec.dot(C));
		return out;
	}

	Vec3<T> getRow(int i) {
		if (i == 0) {
			return A;
		}
		if (i == 1) {
			return B;
		}
		if (i == 2) {
			return C;
		}
	}

	void print() {
		std::cout << A.toString() << "\n";
		std::cout << B.toString() << "\n";
		std::cout << C.toString() << "\n\n";
	}
};

