#pragma once

// Klasa odpowiedzialna za obs³ugê sceny i nale¿¹cych do niej elementów (kamera, obiekty)

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

