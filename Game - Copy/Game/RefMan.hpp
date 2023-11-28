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

template <typename T>
class RefMan
{
private:
	T* target = nullptr;
	unsigned int refCount = 0;

	RefMan(T* newTarget) {
		target = newTarget;
	};

	void decreaseRefCount() {
		refCount -= 1;
		if (refCount <= 0) {
			delete target;
			delete this;
		}
	}

	RefMan(const RefMan<T>& other) = delete;
	RefMan(RefMan<T>&& other) = delete;

	RefMan<T>& operator=(const RefMan<T>& other) = delete;
	RefMan<T>& operator=(const RefMan<T>&& other) = delete;

	~RefMan() {};
public:
	class Ref {
	private:
		RefMan<T>* parent = nullptr;
		Ref(RefMan<T>* newParent) {
			parent = newParent;
			newParent->refCount += 1;
		};
	public:
		Ref() {}

		Ref(const Ref& other) {
			parent = other.parent;
			if (parent != nullptr) {
				parent->refCount += 1;
			}
		};

		Ref& operator=(const Ref& other) {
			if (parent != nullptr) {
				parent->decreaseRefCount();
			}
			parent = other.parent;
			if (parent != nullptr) {
				parent->refCount += 1;
			}
			return *this;
		}

		bool exists() {
			return parent->exists();
		}

		T& operator*() {
			return *(parent->target);
		}

		bool operator==(const Ref& other) {
			return parent == other.parent;
		}

		~Ref() {
			if (parent != nullptr) {
				parent->decreaseRefCount();
			}
		}

		friend class RefMan;
	};

	static RefMan<T>* makeRefMan(T* newTarget) {
		return new RefMan<T>(newTarget);
	}

	Ref makeRef() {
		Ref out(this);
		return out;
	}

	void disconnect() {
		target = nullptr;
		if (refCount <= 0 && target == nullptr) {
			delete this;
		}
	}

	bool exists() {
		return target != nullptr;
	}

	unsigned int getRefCount() {
		return refCount;
	}

	void debugSelfDestructDoNotUse() {
		delete this;
	}
	void debugTargetDestructDoNotUse() {
		delete this;
	}
};

