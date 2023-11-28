#pragma once
#include "GraphicsObject.h"

Drawable* GraphicsObject::drawTick() {
	Drawable* out = new Drawable;
	out->rotation = rotation;
	out->translation = position;
	out->count = mesh.size();
	out->primBundles = new PrimBundle[mesh.size()];

	if (mesh.size() != 0) {
		for (int i = 0; i < mesh.size(); i++) {
			out->primBundles[i] = mesh[i].readData();
		}
	}

	return out;
}

void GraphicsObject::addPrimitive(Primitive newPrimitive) {
	mesh.push_back(newPrimitive);
}

