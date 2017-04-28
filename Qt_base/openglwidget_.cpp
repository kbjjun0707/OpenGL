#include "openglwidget_.h"

#include <Windows.h>

#include <gl\glut.h>
#include <gl\gl.h>
#pragma comment(lib, "opengl32.lib")
#include <gl\glu.h>
#pragma comment(lib, "glu32.lib")

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <qdebug.h>


OpenglWidgetClass::OpenglWidgetClass(QWidget* parent) : QOpenGLWidget(parent) {

}

OpenglWidgetClass::~OpenglWidgetClass() {

}

void OpenglWidgetClass::initializeGL() {
	initializeOpenGLFunctions();
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	m_Cams.push_back(jun::Camera(0, 0, 10));
	m_CamIdx = 0;
	memset(m_MouseDown, 0, sizeof(m_MouseDown));

	m_ProjectionMat = glm::mat4(1.0);
	
	startTimer(40);
}

void OpenglWidgetClass::resizeGL(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	m_Viewport = { 0, 0, w, h };
		
	m_ProjectionMat = glm::perspective<float>(45, (float)w / h, 0.1, 10000);
	
}

void OpenglWidgetClass::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	m_Cams[m_CamIdx].getCamMat(m_LookAtMat);
	glMultMatrixf(glm::value_ptr(m_ProjectionMat*m_LookAtMat*m_ModelMat));

	glPushMatrix(); {
		glutSolidTeapot(1);

	}glPopMatrix();

}

void OpenglWidgetClass::timerEvent(QTimerEvent * e) {

	update();
}

void OpenglWidgetClass::wheelEvent(QWheelEvent * e) {

}

void OpenglWidgetClass::mousePressEvent(QMouseEvent * e) {
	switch (e->button()) {
	case Qt::LeftButton:
		m_MouseDown[0] = true;
		m_PressPnt = e->pos();
		break;
	default:
		break;
	}
}

void OpenglWidgetClass::mouseMoveEvent(QMouseEvent * e) {
	if (m_MouseDown[0]) {
		
	}
}

void OpenglWidgetClass::mouseReleaseEvent(QMouseEvent * e) {
	switch (e->button()) {
	case Qt::LeftButton:
		m_MouseDown[0] = false;
		break;
	default:
		break;
	}

}
