#include "openglwidget_.h"

#include <Windows.h>

//#include <gl\glut.h>
#include <gl\gl.h>
#pragma comment(lib, "opengl32.lib")
//#include <gl\glu.h>
//#pragma comment(lib, "glu32.lib")

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

	m_Objs.push_back(new jun::TeapotObject());
	m_Objs.push_back(new jun::SphereObject(2, 0, 0, 1));

	m_Collis.push_back(new jun::SphereCollision(1.5));
	m_Collis.push_back(new jun::SphereCollision(2, 0, 0, 1.05));

	m_IsColli.push_back(false);
	m_IsColli.push_back(false);
	
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
	
	for (auto it : m_Objs) {
		if (it != nullptr) {
			glColor3f(1, 1, 1);
			it->draw(jun::Object::DRAWMODE::SOLID);
		}
	}
	for (int i = 0; i < m_Collis.size(); i++) {
		if (m_Collis[i] != nullptr) {
			if (m_IsColli[i] && m_MouseDown[0])
				glColor3f(0, 0.8, 0);
			else
				glColor3f(0.8, 0, 0);
			m_Collis[i]->draw();
		}
	}


}

void OpenglWidgetClass::timerEvent(QTimerEvent * e) {

	update();
}

void OpenglWidgetClass::wheelEvent(QWheelEvent * e) {

}

void OpenglWidgetClass::mousePressEvent(QMouseEvent * e) {
	glm::fvec3 campos;
	switch (e->button()) {
	case Qt::LeftButton:
		m_MouseDown[0] = true;
		m_PressPnt = e->pos();

		m_Cams[m_CamIdx].getPos(campos);
		m_CamRay = jun::Ray::calcRay(m_Viewport, m_ProjectionMat*m_LookAtMat*m_ModelMat, campos, m_PressPnt.x(), m_PressPnt.y());

		for (int i = 0; i < m_Collis.size(); i++) {
			m_IsColli[i] = jun::collision::detect(m_CamRay, *(jun::SphereCollision *)m_Collis[i]);
		}



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
