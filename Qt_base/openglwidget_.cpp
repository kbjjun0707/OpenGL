#include "openglwidget_.h"

#include <Windows.h>

#include <gl\gl.h>
#pragma comment(lib, "opengl32.lib")
#include <gl\glu.h>
#pragma comment(lib, "glu32.lib")

#include <qdebug.h>


OpenglWidgetClass::OpenglWidgetClass(QWidget* parent) : QOpenGLWidget(parent) {

}

OpenglWidgetClass::~OpenglWidgetClass() {

}

void OpenglWidgetClass::initializeGL() {
	initializeOpenGLFunctions();
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

}

void OpenglWidgetClass::resizeGL(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	gluPerspective(45, (float)w / h, 0.1, 10000);

}

void OpenglWidgetClass::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

	glPushMatrix(); {

		glBegin(GL_QUADS);
		glVertex3f(-1, -1, 0);
		glVertex3f(-1, 1, 0);
		glVertex3f(1, 1, 0);
		glVertex3f(1, -1, 0);
		glEnd();

	}glPopMatrix();
}

void OpenglWidgetClass::timerEvent(QTimerEvent * e) {

	update();
}

void OpenglWidgetClass::wheelEvent(QWheelEvent * e) {

}

void OpenglWidgetClass::mousePressEvent(QMouseEvent * e) {

}

void OpenglWidgetClass::mouseMoveEvent(QMouseEvent * e) {

}

void OpenglWidgetClass::mouseReleaseEvent(QMouseEvent * e) {

}
