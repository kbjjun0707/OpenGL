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


void jun::init(char * windowName, int posX, int posY, int x, int y) {
	m_WinPosX = posX; m_WinPosY = posY;
	m_WinWidth = x, m_WinHeight = y;

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(m_WinPosX, m_WinPosY);
	glutInitWindowSize(m_WinWidth, m_WinHeight);
	m_WinId = glutCreateWindow(windowName);
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	m_Cams.push_back(jun::Camera(0, 0, 20));
	m_CamIdx = 0;
}

void jun::run() {
	/*
	입력 -> 처리(입력한 데이터를 어떻게 사용할지) -> 업데이트
	(처리 결과 이동, 회전 등의 움직임 적용) -> 렌더링
	순으로 진행 할 것이다.
	*/
	// 윈도우 창크기변화에 반응
	glutReshapeFunc(reshape);

	// 마우스 키보드 기본 입력 반응 (더 있음)
	glutMouseFunc(onMouseClick);
	glutKeyboardFunc(onKeyBoard);

	// 업데이트
	glutIdleFunc(idle);

	// 화면 출력(렌더링)
	glutDisplayFunc(display);

	// glut 함수들 반복
	glutMainLoop();
}


void jun::reshape(int x, int y) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, x, y);
	gluPerspective(45, (double)m_WinWidth / m_WinHeight, 0.1f, 10000.f);
}

void jun::onMouseClick(int bnt, int state, int x, int y) {
}

void jun::onKeyBoard(unsigned char key, int x, int y) {
}



void jun::idle() {


	glutPostRedisplay();
}

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

