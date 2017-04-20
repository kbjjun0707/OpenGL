#include "glutmanager.h"
#include "camera_.h"
#include "ray_.h"
#include "collision_.h"
#include "object_.h"

#include <Windows.h>

#include <gl\glut.h>
#include <gl\GLU.h>
#include <gl\GL.h>

#include <vector>
#include <iostream>

#include <glm\gtc\type_ptr.hpp>

int g_WinId;
int g_WinWidth, g_WinHeight, g_WinPosX, g_WinPosY;

bool		g_MouseDown[3] = { 0 };
int			g_PressX = 0, g_PressY = 0;
jun::Ray	g_MouseRay;


int g_CamIdx;									// ī�޶� ��ȣ
std::vector<jun::Camera> g_Cams;				// ī�޶��
std::vector<jun::Collision_Base *> g_Collis;	// �浹ü��
std::vector<jun::Object *> g_Objects;
int g_PickIdx;


void jun::init(char * windowName, int posX, int posY, int x, int y) {
	g_WinPosX = posX; g_WinPosY = posY;
	g_WinWidth = x, g_WinHeight = y;

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(g_WinPosX, g_WinPosY);
	glutInitWindowSize(g_WinWidth, g_WinHeight);
	g_WinId = glutCreateWindow(windowName);
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	g_Cams.push_back(jun::Camera(0, 0, 10));
	g_CamIdx = 0;

	g_Objects.push_back(new jun::SphereObject(1));
	g_Collis.push_back(new jun::SphereCollision(1));
	g_PickIdx = -1;
}

void jun::run() {
	/*
	�Է� -> ó��(�Է��� �����͸� ��� �������) -> ������Ʈ
	(ó�� ���(�̵�, ȸ�� ��) ������ ����) -> ������
	������ ���� �� ���̴�.
	*/
	// ������ âũ�⺯ȭ�� ����
	glutReshapeFunc(reshape);

	// ���콺 Ű���� �⺻ �Է� ���� (�� ����)
	glutMouseFunc(onMouseClick);
	glutMotionFunc(onMouseMotion);
	glutKeyboardFunc(onKeyBoard);
	
	// ������Ʈ
	glutIdleFunc(idle);

	// ȭ�� ���(������)
	glutDisplayFunc(display);

	// glut �Լ��� �ݺ�
	glutMainLoop();
}


void jun::reshape(int x, int y) {
	g_WinWidth = x; g_WinHeight = y;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, x, y);
	gluPerspective(45, (double)g_WinWidth / g_WinHeight, 0.1f, 10000.f);
}

void jun::onMouseClick(int bnt, int state, int x, int y) {
	switch (bnt) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			g_MouseDown[0] = true;
			g_PressX = x; g_PressY = y;
			g_MouseRay = jun::Ray::calcRay(x, y);
			bool find = false;
			for (int i = 0; !find && i < g_Collis.size(); i++) {
				if (g_Collis[i] == nullptr) continue;
				switch (g_Collis[i]->type()) {
				case jun::collision::TYPE::SPHERE:
					if (jun::collision::detect(g_MouseRay, *(jun::SphereCollision *)g_Collis[i])) {
						g_PickIdx = i;
						find = true;
					}
					break;
				case jun::collision::TYPE::QUAD:
					break;
				}
			}

		} else if (state == GLUT_UP) {
			g_MouseDown[0] = false;
			g_PickIdx = -1;
		}
		break;
	default:
		break;
	}
}

void jun::onMouseMotion(int x, int y) {
	if (g_MouseDown[0] && g_PickIdx >= 0) {
		jun::Ray pre = g_MouseRay;
		g_MouseRay = jun::Ray::calcRay(x, y);

		float objPos[3], camPos[3];
		g_Objects[g_PickIdx]->getPos(objPos);
		g_Cams[g_CamIdx].getPos(camPos);

		float *m = jun::Ray::pickObjdMove(pre.m_O, g_MouseRay.m_O, camPos, objPos);
		float move[3] = { m[0], m[1], m[2] };

		g_Objects[g_PickIdx]->translate(move);
		g_Collis[g_PickIdx]->translate(move);
	}
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
	g_Cams[g_CamIdx].getCamMat(CamMat);
	glMultMatrixf(CamMat);

	glPushMatrix(); {				// ��ü ������ �κ�
		
		for (int i = 0; i < g_Collis.size(); i++) {
			if (i == g_PickIdx) {
				glColor3f(0, 1, 0);
			} else {
				glColor3f(1, 0, 0);
			}
			g_Objects[i]->draw();
		}	
		

	}glPopMatrix();

	glutSwapBuffers();
}

