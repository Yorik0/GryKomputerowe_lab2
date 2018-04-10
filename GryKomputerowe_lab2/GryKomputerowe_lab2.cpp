#include "stdafx.h"
#include "math.h"
#include "windows.h"

// Deklaracje funkcji u¿ywanych jako obs³uga zdarzeñ GLUT-a.
void OnRender();
void OnReshape(int, int);
void OnKeyPress(unsigned char, int, int);
void OnKeyDown(unsigned char, int, int);
void OnKeyUp(unsigned char, int, int);
void OnTimer(int);

// Struktura pozwalaj¹ca na przechowanie aktualnego stanu kamery.
// Struktura powinna dziedziczyæ po klasie SceneObject, ale dla u³atwienia w ramach dzisiejszych zajêæ zostanie zaimplementowana osobno.
struct SCameraState {
	vec3 pos; // pozycja kamery
	vec3 dir; // kierunek patrzenia (wektor jednostkowy)
	float speed; // mno¿nik zmian pozycji - "szybkoœæ" ruchów kamery
};

// Zmienna przechowuj¹ca aktualny stan kamery. Powinno siê "w³o¿yæ ten obiekt do sceny za pomoc¹ metody AddObject().
SCameraState player;

//sila bezwladnosc
float camera_force = 0;

// Deklaracja sceny.
Scene scene;

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 360);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("Gry Komputerowe: Lab 2");

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutTimerFunc(17, OnTimer, 0);

	glEnable(GL_DEPTH_TEST);
	

	// Inicjalizacja parametrów kamery:
	player.pos.x = 0.0f;
	player.pos.y = 1.75f;
	player.pos.z = 0.0f;

	player.dir.x = 0.0f;
	player.dir.y = 0.0f;
	player.dir.z = -1.0f;

	player.speed = .1f;

	// Dodanie do sceny siatki stu kolorowych sfer.
	for (int ix = -5; ix <= 5; ix+=1) {
		for (int iz = -5; iz <= 5; iz+=1) {

			Sphere* sphere = new Sphere();

			sphere->pos.x = (float) ix;
			sphere->pos.y = 1.0f;
			sphere->pos.z = (float) iz;

			sphere->color.x = .5f + .1f * ix;
			sphere->color.y = .5f - .1f * iz;
			sphere->color.z = 0.0f;

			sphere->radius = 0.05f;

			scene.AddObject(sphere);
		}
	}

	glutMainLoop();

	return 0;
}

// Tablica przechowuj¹ca stan klawiszy w formie flag, indeksowana wg kodów ASCII.
bool keystate[256];

// Obs³uga zdarzenia, gdy zostanie wciœniêty klawisz - zdarzenie nieoodporne na repetycjê klawiszy.
void OnKeyPress(unsigned char key, int x, int y) {
	printf("KeyPress: %c\n", key);
	if (!keystate[key]) {
		OnKeyDown(key, x, y); // Emulacja zdarzenia zwi¹zanego z pojedynczym wciœniêciem klawisza
	}
	keystate[key] = true;


}

// Obs³uga naszego w³asnego zdarzenia, gdy zostanie po raz pierwszy wciœniêty klawisz - zdarzenie odporne na repetycjê.
void OnKeyDown(unsigned char key, int x, int y) {
	//printf("KeyDown: %c\n", key);
	if (key == 27) { // ESC - wyjœcie
		glutLeaveMainLoop();
	}
}

// Obs³uga zdarzenia puszczenia klawisza.
void OnKeyUp(unsigned char key, int x, int y) {
	printf("KeyUp: %c\n", key);
	keystate[key] = false;

	if (key == 'w')
	{
		while (player.speed >= 0)
		{
			//Sleep(4);
			player.pos.x += player.dir.x * player.speed;
			player.pos.y += player.dir.y * player.speed;
			player.pos.z += player.dir.z * player.speed;
			player.speed -= 0.01f;
			//printf("speed: %f\n", player.speed);
			Sleep(4);
		}
		player.speed = 0.1f;
	}
}

// Aktualizacja stanu gry - wywo³ywana za poœrednictwem zdarzenia-timera.
void OnTimer(int id) {

	if (keystate['w']) {
		//while (player.speed > 0)
		//{
			player.pos.x += player.dir.x * player.speed;
			player.pos.y += player.dir.y * player.speed;
			player.pos.z += player.dir.z * player.speed;
			//player.speed -= 0.001f;
			//printf("speed: %f\n", player.speed);
		//}		
		//player.speed = 0.1f;
	}
	if (keystate['s']) {
		player.pos.x -= player.dir.x * player.speed;
		player.pos.y -= player.dir.y * player.speed;
		player.pos.z -= player.dir.z * player.speed;
	}
	if (keystate['a']) {
		player.pos.x += player.dir.z * player.speed;
		//player.pos.y -= player.dir.y * player.speed;
		player.pos.z -= player.dir.x * player.speed;
	}
	if (keystate['d']) {
		player.pos.x -= player.dir.z * player.speed;
		//player.pos.y -= player.dir.y * player.speed;
		player.pos.z += player.dir.x * player.speed;
	}
	if (keystate['q']) {

		float alfa = atan2(player.dir.z, player.dir.x);
		alfa -= 0.1f;
		player.dir.x = cos(alfa);
		player.dir.z = sin(alfa);

	}
	if (keystate['e']) {
		float alfa = atan2(player.dir.z, player.dir.x);
		alfa += 0.1f;
		player.dir.x = cos(alfa);
		player.dir.z = sin(alfa);
	}
	// Aktualizacja ca³ej sceny
	scene.Update();

	// Chcemy, by ta funkcja wywolala sie ponownie za 17ms.
	glutTimerFunc(17, OnTimer, 0);
}

void OnRender() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Ustawienie kamery na podstawie jej stanu przechowywanego w zmiennej player.
	gluLookAt(
		player.pos.x, player.pos.y, player.pos.z, // Pozycja kamery
		player.pos.x + player.dir.x, player.pos.y + player.dir.y, player.pos.z + player.dir.z, // Punkt na ktory patrzy kamera (pozycja + kierunek)
		0.0f, 1.0f, 0.0f // Wektor wyznaczajacy pion
	);

	// Rendering ca³ej sceny
	scene.Render();

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();

}

void OnReshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, (float) width / height, .01f, 100.0f);
}
