#pragma once

// Klasa abstrakcyjna opisuj¹ca obiekt sceny. Wszystkie klasy obiektów sceny (np. sfery, œciany, gracz itd.) powinny po tej klasie dziedziczyæ.

class SceneObject
{
public:
	SceneObject(void);
	~SceneObject(void);

	vec3 pos;

	virtual void Render() = 0;
	virtual void Update() = 0;
};

