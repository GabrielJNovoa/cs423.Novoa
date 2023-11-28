#pragma once
#include "GraphicsWorld.h"

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

#ifndef GLAD_GL_IMPLEMENTATION
#define GLAD_GL_IMPLEMENTATION
#endif
#include <gl/GL.h>
#include <SFML/Graphics.hpp>

//sfml

//stl

//other

GraphicsWorld::GraphicsWorld() {}
void GraphicsWorld::addGraphicsObject(GraphicsObject* newObject) {
	inhabitants.push_back(newObject);
}
void GraphicsWorld::drawTick(sf::Window& window, GameObject* camera) {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	window.setActive(true);
	Rotation<float> cameraRot = camera->getRotation();
	Vec3<float> cameraPos = camera->getPosition();

	float radToDeg = 180 / std::numbers::pi;

	glMatrixMode(GL_MODELVIEW);
	//prepare camera matrix. will need coordinate conversion
	glPushMatrix();
	float* matrix = new float[16];
	Vec3<float> row;

	float coordinateConversion[] = {
		0, 0,-1, 0,
	   -1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 0, 1
	};

	Drawable* current = nullptr;
	for (auto i = inhabitants.begin(); i != inhabitants.end(); i++) {
		if ((*i)->exists()) {

			current = (*i)->drawTick();
			glLoadIdentity();
			glMultMatrixf(coordinateConversion);

			row = cameraRot.getRow(0);
			matrix[0] = row.getX();
			matrix[1] = row.getY();
			matrix[2] = row.getZ();
			matrix[3] = 0;
			row = cameraRot.getRow(1);
			matrix[4] = row.getX();
			matrix[5] = row.getY();
			matrix[6] = row.getZ();
			matrix[7] = 0;
			row = cameraRot.getRow(2);
			matrix[8] = row.getX();
			matrix[9] = row.getY();
			matrix[10] = row.getZ();
			matrix[11] = 0;

			matrix[12] = 0;
			matrix[13] = 0;
			matrix[14] = 0;
			matrix[15] = 1;

			glMultMatrixf(matrix);

			glTranslatef(-cameraPos.getX(), -cameraPos.getY(), -cameraPos.getZ());
			glTranslatef(current->translation.getX(), current->translation.getY(), current->translation.getZ());

			row = current->rotation.getRow(0);
			matrix[0] = row.getX();
			matrix[4] = row.getY();
			matrix[8] = row.getZ();
			matrix[12] = 0;
			row = current->rotation.getRow(1);
			matrix[1] = row.getX();
			matrix[5] = row.getY();
			matrix[9] = row.getZ();
			matrix[13] = 0;
			row = current->rotation.getRow(2);
			matrix[2] = row.getX();
			matrix[6] = row.getY();
			matrix[10] = row.getZ();
			matrix[14] = 0;

			matrix[3] = 0;
			matrix[7] = 0;
			matrix[11] = 0;
			matrix[15] = 1;

			glMultMatrixf(matrix);

			for (unsigned int j = 0; j < current->count; j++) {
				glEnable(GL_TEXTURE_2D);
				sf::Texture::bind(&textures[current->primBundles[j].texId]);
				glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), current->primBundles[j].vertices);
				glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), current->primBundles[j].vertices + 3);
				glDrawArrays(GL_TRIANGLES, 0, current->primBundles[j].count);
			}

			delete current;
		}
		else {
			inhabitants.erase(i);
		}
	}
	delete[] matrix;
	glPopMatrix();

}
void GraphicsWorld::loadTexture(std::string path) {
	sf::Texture tex;
	tex.loadFromFile(path);
	textures.push_back(tex);
}

