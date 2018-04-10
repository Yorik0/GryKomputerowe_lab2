#pragma once

#include "SceneObject.h"

// Przyk³ad obiektu sceny dziedzicz¹cej po klasie SceneObject - w tym wypadku sfera

class Sphere : public SceneObject
{
public:
	Sphere(void);
	~Sphere(void);

	void Render();
	void Update();

	vec3 color;
	float radius;
};

