#include "object_.h"

#include <gl\glut.h>



jun::Object::Object() {
}

void jun::Object::draw(int mode) {
}



jun::SphereObject::SphereObject(float r) {
	m_Radius = r;
}

jun::SphereObject::SphereObject(float * pos, float r) {
	m_Radius = r;

	this->setPosition(pos);
}

jun::SphereObject::SphereObject(glm::fvec3 pos, float r) {
	m_Radius = r;
	this->setPosition(pos);
}

jun::SphereObject::SphereObject(float x, float y, float z, float r) {
	m_Radius = r;
	this->setPosition(x, y, z);
}

void jun::SphereObject::draw(int mode) {
	glPushMatrix(); {
		glTranslatef(this->m_Pos[0], this->m_Pos[1], this->m_Pos[2]);
		switch (mode) {
		case objects::DRAWMODE::WIRE:
			glutWireSphere(m_Radius, 20, 20);
			break;

		case objects::DRAWMODE::SOLID:
			glutSolidSphere(m_Radius, 20, 20);
			break;
		}
	}glPopMatrix();
}

float jun::SphereObject::getRadius() {
	return m_Radius;
}

void jun::SphereObject::setRadius(const float & r) {
	m_Radius = r;
}

