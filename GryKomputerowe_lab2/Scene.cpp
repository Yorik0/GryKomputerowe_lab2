#include "stdafx.h"
#include "Scene.h"


Scene::Scene(void)
{
}


Scene::~Scene(void)
{
	for(unsigned int i = 0 ; i < sceneObjects.size() ; i++)
		delete sceneObjects[i];

	sceneObjects.clear();
}

// Dodawanie obiektu do sceny
void Scene::AddObject(SceneObject* object)
{
	sceneObjects.push_back(object);
}

// Renderowanie wszystkich obiektów na scenie
void Scene::Render()
{
	for(unsigned int i = 0 ; i < sceneObjects.size() ; i++)
		sceneObjects[i]->Render();
}

// Aktualizowanie wszystkich obiektów na scenie
void Scene::Update()
{
	for(unsigned int i = 0 ; i < sceneObjects.size() ; i++)
		sceneObjects[i]->Update();
}