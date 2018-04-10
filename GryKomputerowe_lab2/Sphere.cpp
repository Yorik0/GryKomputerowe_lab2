#include "stdafx.h"
#include "Sphere.h"


Sphere::Sphere(void)
{
}


Sphere::~Sphere(void)
{
}

void Sphere::Render()
{
	glColor3f(color.x, color.y, color.z);

	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		glutSolidSphere(radius, 24, 24);
	glPopMatrix();
}

void Sphere::Update()
{

}