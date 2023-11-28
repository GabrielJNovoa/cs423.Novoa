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

//class GraphicsObject;
class GraphicsWorld
{
private:
	std::list<RefMan<GraphicsObject>::Ref> inhabitants;
	std::vector<sf::Texture> textures;
public:

	GraphicsWorld() {}

	struct PrimBundle {
		unsigned int texId;
		unsigned int count;
		GLfloat* vertices;
	};
	struct Drawable {
		Vec3<float> toForward;
		float forwardAngle;
		Vec3<float> toUp;
		float upAngle;
		Vec3<float> translation;
		unsigned int count;
		PrimBundle* primBundles;

		~Drawable() {
			delete[] primBundles;
		}
	};

	void addGraphicsObject(RefMan<GraphicsObject>::Ref newObject) {
		inhabitants.push_back(newObject);
	}

	void drawTick(sf::Window& window, RefMan<GameObject>::Ref camera) {
		window.setActive();
		Rotation<float> rot = (*camera).getRotation();
		Vec3<float> k = rot.axisToForward();
		Vec3<float> f = rot.getForward();
		Vec3<float> pos = (*camera).getPosition();

		glMatrixMode(GL_MODELVIEW);
		//prepare camera matrix. will need coordinate conversion
		glLoadIdentity();
		glTranslatef(-pos.getX(), -pos.getY(), -pos.getZ());
		glRotatef(rot.angleToForward(), k.getX(), k.getY(), k.getZ());
		glRotatef(rot.angleToUp(), f.getX(), f.getY(), f.getZ());
		glPushMatrix(); //save matrix

		Drawable* current = nullptr;

		for (auto i = inhabitants.begin(); i != inhabitants.end(); i++) {
			if ((*i).exists()) {
				current = (*(*i)).drawTick();
				glTranslatef(-current->translation.getX(), -current->translation.getY(), -current->translation.getZ());
				glRotatef(current->forwardAngle, current->toForward.getX(), current->toForward.getY(), current->toForward.getZ());
				glRotatef(current->upAngle, current->toUp.getX(), current->toUp.getY(), current->toUp.getZ());
				glTranslatef(current->translation.getX(), current->translation.getY(), current->translation.getZ());

				for (int j = 0; j < current->count; j++) {
					sf::Texture::bind(&textures[current->primBundles[j].texId]);
					glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), current->primBundles[j].vertices);
					glVertexPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), current->primBundles[j].vertices + 3);
					glDrawArrays(GL_TRIANGLES, 0, current->primBundles[j].count);
				}

				delete current;

				glPopMatrix();
				glPushMatrix();
			}
			else {
				inhabitants.erase(i);
			}
		}

		glPopMatrix();
	}

	void loadTexture(std::string path) {
		sf::Texture tex;
		tex.loadFromFile(path);
		textures.push_back(tex);
	}
};

