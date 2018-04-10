#pragma once

// Klasa opisuj¹ca trójwymiarowy wektor.
// S³u¿y do przetrzymywania pozycji oraz kierunków obiektów sceny i kamery.
// Powinno siê rozbudowaæ t¹ klasê o funkcje obs³uguj¹c¹ operacje na wektorach.
// Polecana alternatywa - GLM.

class vec3
{
public:
	vec3(void);
	vec3(float x, float y, float z);
	~vec3(void);

	float x, y, z;
};

