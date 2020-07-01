#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>

#include <camera/Camera.h>

const float PI = 3.14159265;
const uint WIDTH = 1000;
const uint HEIGHT = 1000;

Camera* camera;

// Drawing routine
void drawScene(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera->translation();
	gluLookAt(camera->getX(), camera->getY(), camera->getZ(), camera->getSightX(), camera->getSightY(), camera->getSightZ(), 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	float R = 20.0; // Radius of helix.
	float t; // Angle parameter.

	glBegin(GL_LINE_STRIP);
	for (t = -10 * PI; t <= 10 * PI; t += PI / 20.0)
		glVertex3f(R * cos(t), t, R * sin(t));
	glEnd();

	glFlush();
	glutPostRedisplay();
}

// Initialization routine.
void setup(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h) {
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10.0, 10.0, -10.0, 10.0, 20.0, 400.0);
// 	gluPerspective(45, float(WIDTH)/float(HEIGHT), 1, 10*sqrt(pow(ocean->get_ly(), 2) + pow(ocean->get_lx(), 2)));
}

// Keyboard input processing routine.
void keyDown(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	}
	camera->setKeyboard(key, true);
}

void keyUp(unsigned char key, int x, int y) {
	camera->setKeyboard(key, false);
}

void mouseControl(int x, int y) {
	camera->rotation(x, y);
	if (x >= WIDTH || x <= 0 || y >= HEIGHT || y <= 0) {
		glutWarpPointer(WIDTH / 2, HEIGHT / 2);
		camera->setMouse(WIDTH / 2, HEIGHT / 2);
	}
}

// Main routine.
int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitContextVersion(1, 3); // Use OpenGL 1.3
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	// Use this, so it'll work on Mesa having a different "Max compat profile version (e.g 3.0)"
	// than "Max core profile version (e.g 4.5)" when glxinfo is run:
	// glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Cubico");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardUpFunc(keyUp);
	glutKeyboardFunc(keyDown);
	glutPassiveMotionFunc(mouseControl);

	camera = new Camera {Camera::KEYBOARD::QWERTY, -30, 10, -50, 4 * PI / 7, PI / 4, 0.01, 0.1, WIDTH, HEIGHT};

	glewInit();
	setup();

	glutMainLoop();

	delete camera;
}
