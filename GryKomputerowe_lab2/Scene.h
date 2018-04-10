#pragma once

// Klasa odpowiedzialna za obs�ug� sceny i nale��cych do niej element�w (kamera, obiekty)

class Scene
{
public:
	Scene(void);
	~Scene(void);

	void Render();
	void Update();

	void AddObject(SceneObject* object);

private:

	std::vector<SceneObject*> sceneObjects;
};

