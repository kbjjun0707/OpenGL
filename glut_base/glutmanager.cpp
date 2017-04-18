#include "glutmanager.h"
#include "camera_.h"

#include <Windows.h>

#include <gl\glut.h>
#include <gl\GLU.h>
#include <gl\GL.h>

#include <vector>

int m_WinId;
int m_WinWidth, m_WinHeight, m_WinPosX, m_WinPosY;

std::vector<jun::Camera> m_Cams;
int m_CamIdx;


void jun::display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float CamMat[16] = { 0 };
	m_Cams[m_CamIdx].getCamMat(CamMat);
	glMultMatrixf(CamMat);
	
	glutSolidTeapot(1);

	glutSwapBuffers();
}

void jun::reshape(int x, int y) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, x, y);
	gluPerspective(45, (double)m_WinWidth / m_WinHeight, 0.1f, 10000.f);
}

void jun::idle() {


	glutPostRedisplay();
}

void jun::init(char * windowName, int posX, int posY, int x, int y) {
	m_WinPosX = posX; m_WinPosY = posY;
	m_WinWidth = x, m_WinHeight = y;

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(m_WinPosX, m_WinPosY);
	glutInitWindowSize(m_WinWidth, m_WinHeight);
	m_WinId = glutCreateWindow(windowName);
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	m_Cams.push_back(jun::Camera(0,0,20));
	m_CamIdx = 0;
}

void jun::run() {
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutMainLoop();
}
