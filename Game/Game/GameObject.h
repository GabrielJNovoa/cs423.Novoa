#pragma once
//sfml

//stl

//other
#include "Rotation.hpp"

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
	void setParentWorld(GameWorld* newParentWorld);
	void destroy();
	bool exists();
	Vec3<float> getPosition();
	void setPosition(Vec3<float> newPosition);
	void setPosition(float newX, float newY, float newZ);
	Rotation<float> getRotation();
	void setRotation(Rotation<float> newRotation);
};

