#pragma once
//sfml

//stl

//other
#include "GameObject.h"
#include "GraphicsObject.h"
#include "PhysicsObject.h"

class WallBlock : virtual public GameObject, virtual public GraphicsObject, virtual public PhysicsObject
{
private:
public:
	WallBlock() {
		identifier = "wall";

		//Collider newCollider(this,Collider::ORTHOBOX,40,40,40);
		collider = new Collider;
		collider->setParent(this);
		collider->setType(Collider::ORTHOBOX);
		collider->setDepth(40);
		collider->setWidth(40);
		collider->setHeight(40);

		Primitive prim;
		prim.setTextureId(0);

		prim.addVertex(-20, -20, -20, 0, 0);
		prim.addVertex(-20, 20, -20, 1, 0);
		prim.addVertex(-20, -20, 20, 0, 1);
		prim.addVertex(-20, -20, 20, 0, 1);
		prim.addVertex(-20, 20, -20, 1, 0);
		prim.addVertex(-20, 20, 20, 1, 1);

		prim.addVertex(20, -20, -20, 0, 0);
		prim.addVertex(20, 20, -20, 1, 0);
		prim.addVertex(20, -20, 20, 0, 1);
		prim.addVertex(20, -20, 20, 0, 1);
		prim.addVertex(20, 20, -20, 1, 0);
		prim.addVertex(20, 20, 20, 1, 1);

		prim.addVertex(-20, -20, -20, 0, 0);
		prim.addVertex(20, -20, -20, 1, 0);
		prim.addVertex(-20, -20, 20, 0, 1);
		prim.addVertex(-20, -20, 20, 0, 1);
		prim.addVertex(20, -20, -20, 1, 0);
		prim.addVertex(20, -20, 20, 1, 1);

		prim.addVertex(-20, 20, -20, 0, 0);
		prim.addVertex(20, 20, -20, 1, 0);
		prim.addVertex(-20, 20, 20, 0, 1);
		prim.addVertex(-20, 20, 20, 0, 1);
		prim.addVertex(20, 20, -20, 1, 0);
		prim.addVertex(20, 20, 20, 1, 1);

		prim.addVertex(-20, -20, -20, 0, 0);
		prim.addVertex(20, -20, -20, 1, 0);
		prim.addVertex(-20, 20, -20, 0, 1);
		prim.addVertex(-20, 20, -20, 0, 1);
		prim.addVertex(20, -20, -20, 1, 0);
		prim.addVertex(20, 20, -20, 1, 1);

		prim.addVertex(-20, -20, 20, 0, 0);
		prim.addVertex(20, -20, 20, 1, 0);
		prim.addVertex(-20, 20, 20, 0, 1);
		prim.addVertex(-20, 20, 20, 0, 1);
		prim.addVertex(20, -20, 20, 1, 0);
		prim.addVertex(20, 20, 20, 1, 1);

		mesh.push_back(prim);
	}
	void preTick() {}
	void physicsTick() {
		while (!collisionStack.empty()) {
			collisionStack.pop();
		}
	}
	void postTick() {}
};

