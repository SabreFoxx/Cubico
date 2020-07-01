#include <GL/glew.h>
#include <GL/freeglut.h>

#include <polyvox/CubicSurfaceExtractor.h>
#include <polyvox/MarchingCubesSurfaceExtractor.h>
#include <polyvox/Mesh.h>
#include <polyvox/RawVolume.h>

#include <camera/Camera.h>

const float PI = 3.14159265;
const uint WIDTH = 500;
const uint HEIGHT = 500;

Camera* camera;

// Vertex co-ordinate vectors.
static float vertices[] = {
	10.00000, 10.00000, -10.00000,
	10.00000, -10.00000, -10.00000,
	10.00000, 10.00000, 10.00000,
	10.00000, -10.00000, 10.00000,
	-10.00000, 10.00000, -10.00000,
	-10.00000, -10.00000, -10.00000,
	-10.00000, 10.00000, 10.00000,
	-10.00000, -10.00000, 10.00000
};

static unsigned int indices[] = { 5, 3, 1, 3, 8, 4, 7, 6, 8, 2, 8, 6, 1, 4, 2, 5, 2, 6, 5, 7, 3, 3, 7, 8, 7, 5, 6, 2, 4, 8, 1, 3, 4, 5, 1, 2 };

// Drawing routine
void drawScene(void) {
	static int positions[] = {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33};
	static int vertices[] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera->translation();
	gluLookAt(camera->getX(), camera->getY(), camera->getZ(), camera->getSightX(), camera->getSightY(), camera->getSightZ(), 0, 1, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
// 	glDrawArrays(GL_TRIANGLES, 0, 3);
// 	glMultiDrawArrays(GL_TRIANGLES, positions, vertices, 12);

	glFlush();
	glutPostRedisplay();
}

// Initialization routine.
void setup(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
}

// OpenGL window reshape routine.
void resize(int w, int h) {
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10.0, 10.0, -10.0, 10.0, 20.0, 400.0);
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
	glutMotionFunc(mouseControl);

	camera = new Camera {Camera::KEYBOARD::QWERTY, -30, 10, -50, 4 * PI / 7, PI / 4, 0.001, 0.1, WIDTH, HEIGHT};

	glewInit();
	setup();

	glutMainLoop();

	delete camera;
}

