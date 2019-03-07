#include "pch.h"
#include "Scene.h"

Scene::Scene() {
	for (int i = 0; i < NUM_OBJECTS; i++)
		objects[i] = NULL;
	for (int i = 0; i < NUM_LIGHTS; i++)
		lights[i] = NULL;
}

void Scene::render()
{
	// Render loop
}