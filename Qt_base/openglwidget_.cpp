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
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	m_Cams.push_back(jun::Camera(0, 0, 10));
	m_CamIdx = 0;
	m_PickIdx = -1;
	m_Objects.push_back(new jun::SphereObject(1));
	m_Collis.push_back(new jun::SphereCollision(1.2));
	memset(m_MouseDown, 0, sizeof(m_MouseDown));

	startTimer(40);
}

void OpenglWidgetClass::resizeGL(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	gluPerspective(45, (float)w / h, 0.1, 10000);

}

void OpenglWidgetClass::paintGL() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float CamMat[16] = { 0 };
	m_Cams[m_CamIdx].getCamMat(CamMat);
	glMultMatrixf(CamMat);

	glPushMatrix(); {

		for (int i = 0; i < m_Objects.size(); i++) {
			if (i == m_PickIdx) {
				glColor3f(0, 1, 0);
			} else {
				glColor3f(1, 0, 0);
			}
			m_Objects[i]->draw(jun::Object::DRAWMODE::SOLID);
			m_Collis[i]->draw();
		}

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
		m_CamRay = jun::Ray::calcRay(m_PressPnt.x(), m_PressPnt.y());
		for (int i = 0; !find && i < m_Collis.size(); i++) {
			if (m_Collis[i] == nullptr) continue;
			switch (m_Collis[i]->type()) {
			case jun::Collision_Base::TYPE::SPHERE:
				if (jun::Collision_Base::detect(m_CamRay, *(jun::SphereCollision *)m_Collis[i])) {
					m_PickIdx = i;
				}
				break;
			case jun::Collision_Base::TYPE::QUAD:
				break;
			}
		}
		break;
	default:
		break;
	}
	qDebug() << m_CamRay.m_O[0] << " " << m_CamRay.m_O[1] << " " << m_CamRay.m_O[2] << endl;
}

void OpenglWidgetClass::mouseMoveEvent(QMouseEvent * e) {
	if (m_MouseDown[0] && m_PickIdx >= 0) {
		jun::Ray pre = m_CamRay;
		m_CamRay = jun::Ray::calcRay(e->pos().x(), e->pos().y());

		float objPos[3], camPos[3];
		m_Objects[m_PickIdx]->getPos(objPos);
		m_Cams[m_CamIdx].getPos(camPos);

		float *m = jun::Ray::pickObjdMove(pre.m_O, m_CamRay.m_O, camPos, objPos);
		float move[3] = { m[0], m[1], m[2] };

		m_Objects[m_PickIdx]->translate(move);
		m_Collis[m_PickIdx]->translate(move);
	}


}

void OpenglWidgetClass::mouseReleaseEvent(QMouseEvent * e) {
	switch (e->button()) {
	case Qt::LeftButton:
		m_MouseDown[0] = false;
		m_PickIdx = -1;
		break;
	default:
		break;
	}

}
