#pragma once

// Klasa abstrakcyjna opisuj�ca obiekt sceny. Wszystkie klasy obiekt�w sceny (np. sfery, �ciany, gracz itd.) powinny po tej klasie dziedziczy�.

class SceneObject
{
public:
	SceneObject(void);
	~SceneObject(void);

	vec3 pos;

	virtual void Render() = 0;
	virtual void Update() = 0;
};

