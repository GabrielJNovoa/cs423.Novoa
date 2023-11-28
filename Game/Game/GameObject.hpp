#pragma once
//other
#include "Vec3.hpp"
#include "Rotation.hpp"
#include "GameWorld.hpp"

class GameObject
{
private:

protected:
	Vec3<float> position;
	Rotation<float> rotation;
	bool destroyed = false;
	class GameWorld* parentWorld = nullptr;
public:

	virtual void preTick() = 0;
	virtual void postTick() = 0;

	void setParentWorld(GameWorld* newParentWorld) {
		parentWorld = newParentWorld;
	}

	void destroy() {
		destroyed = true;
	}

	bool exists() {
		return !destroyed;
	}

	Vec3<float> getPosition() {
		return position;
	}
	Rotation<float> getRotation() {
		return rotation;
	}
};

