#pragma once

// Klasa opisuj�ca tr�jwymiarowy wektor.
// S�u�y do przetrzymywania pozycji oraz kierunk�w obiekt�w sceny i kamery.
// Powinno si� rozbudowa� t� klas� o funkcje obs�uguj�c� operacje na wektorach.
// Polecana alternatywa - GLM.

class vec3
{
public:
	vec3(void);
	vec3(float x, float y, float z);
	~vec3(void);

	float x, y, z;
};

