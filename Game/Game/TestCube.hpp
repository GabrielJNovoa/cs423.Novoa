#pragma once
//sfml

//stl

//other


class TestCube : virtual public GameObject, virtual public GraphicsObject, virtual public PhysicsObject
{
private:
	Vec3<float> origin;
	float dir = 0;
public:
	TestCube() {
		identifier = "testCube";

		//Collider newCollider(this,Collider::ORTHOBOX,40,40,40);
		collider = new Collider;
		collider->setParent(this);
		collider->setType(Collider::ORTHOBOX);
		collider->setDepth(40);
		collider->setWidth(40);
		collider->setHeight(40);

		Primitive prim1;
		Primitive prim2;
		Primitive prim3;
		Primitive prim4;
		Primitive prim5;
		Primitive prim6;
		prim1.setTextureId(0);
		prim2.setTextureId(1);
		prim3.setTextureId(2);
		prim4.setTextureId(3);
		prim5.setTextureId(4);
		prim6.setTextureId(4);

        prim1.addVertex(-20, -20, -20, 0, 0);
		prim1.addVertex(-20, 20, -20, 1, 0);
		prim1.addVertex(-20, -20, 20, 0, 1);
		prim1.addVertex(-20, -20, 20, 0, 1);
		prim1.addVertex(-20, 20, -20, 1, 0);
		prim1.addVertex(-20, 20, 20, 1, 1);

		prim2.addVertex(20, -20, -20, 0, 0);
		prim2.addVertex(20, 20, -20, 1, 0);
		prim2.addVertex(20, -20, 20, 0, 1);
		prim2.addVertex(20, -20, 20, 0, 1);
		prim2.addVertex(20, 20, -20, 1, 0);
		prim2.addVertex(20, 20, 20, 1, 1);

		prim3.addVertex(-20, -20, -20, 0, 0);
		prim3.addVertex(20, -20, -20, 1, 0);
		prim3.addVertex(-20, -20, 20, 0, 1);
		prim3.addVertex(-20, -20, 20, 0, 1);
		prim3.addVertex(20, -20, -20, 1, 0);
		prim3.addVertex(20, -20, 20, 1, 1);

		prim4.addVertex(-20, 20, -20, 0, 0);
		prim4.addVertex(20, 20, -20, 1, 0);
		prim4.addVertex(-20, 20, 20, 0, 1);
		prim4.addVertex(-20, 20, 20, 0, 1);
		prim4.addVertex(20, 20, -20, 1, 0);
		prim4.addVertex(20, 20, 20, 1, 1);

		prim5.addVertex(-20, -20, -20, 0, 0);
		prim5.addVertex(20, -20, -20, 1, 0);
		prim5.addVertex(-20, 20, -20, 0, 1);
		prim5.addVertex(-20, 20, -20, 0, 1);
		prim5.addVertex(20, -20, -20, 1, 0);
		prim5.addVertex(20, 20, -20, 1, 1);

		prim5.addVertex(-20, -20, 20, 0, 0);
		prim5.addVertex(20, -20, 20, 1, 0);
		prim5.addVertex(-20, 20, 20, 0, 1);
		prim5.addVertex(-20, 20, 20, 0, 1);
		prim5.addVertex(20, -20, 20, 1, 0);
		prim5.addVertex(20, 20, 20, 1, 1);

		mesh.push_back(prim1);
		mesh.push_back(prim2);
		mesh.push_back(prim3);
		mesh.push_back(prim4);
		mesh.push_back(prim5);
		mesh.push_back(prim6);
	}
	void preTick() {}
	void physicsTick() {
		Collision col;
		while (!collisionStack.empty()) {
			col = collisionStack.top();
			collisionStack.pop();
			std::cout << "testCube:\n";
			col.print();
		}
	}
	void postTick() {}
};

