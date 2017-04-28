#include "object_.h"

#include <gl\glut.h>
#include <glm\gtc\type_ptr.hpp>


jun::Object::Object(float *pos) 
	: Transform(pos), m_Scale(1.f) {
}

jun::Object::Object(const glm::fvec3 &pos) 
	: Transform(pos), m_Scale(1.f) {
}

jun::Object::Object(float x, float y, float z) 
	: Transform(x, y, z), m_Scale(1.f) {
}

void jun::Object::setScale(float scale) {
	m_Scale = scale;
}



jun::SphereObject::SphereObject(float r) 
	: Object(0, 0, 0) {
	m_Radius = r;
}

jun::SphereObject::SphereObject(float * pos, float r) 
	: Object(pos) {
	m_Radius = r;

	this->setPosition(pos);
}

jun::SphereObject::SphereObject(glm::fvec3 pos, float r) 
	: Object(pos) {
	m_Radius = r;
	this->setPosition(pos);
}

jun::SphereObject::SphereObject(float x, float y, float z, float r) 
	: Object(x,y,z) {
	m_Radius = r;
	this->setPosition(x, y, z);
}

void jun::SphereObject::draw(int mode) {
	glPushMatrix(); {
		glTranslatef(this->m_Pos[0], this->m_Pos[1], this->m_Pos[2]);
		switch (mode) {
		case Object::DRAWMODE::WIRE:
			glutWireSphere(m_Radius*m_Scale, 20, 20);
			break;

		case Object::DRAWMODE::SOLID:
			glutSolidSphere(m_Radius*m_Scale, 20, 20);
			break;
		}
	}glPopMatrix();
}

float jun::SphereObject::getRadius() {
	return m_Radius*m_Scale;
}

void jun::SphereObject::setRadius(const float & r) {
	m_Radius = r;
}



jun::TeapotObject::TeapotObject(float *pos) 
	: Object(pos){

}

jun::TeapotObject::TeapotObject(const glm::fvec3 &pos) 
	: Object(pos) {

}

jun::TeapotObject::TeapotObject(float x, float y, float z)
	: Object(x, y, z) {

}

void jun::TeapotObject::draw(int mode) {
	glPushMatrix(); {
		glTranslatef(this->m_Pos[0], this->m_Pos[1], this->m_Pos[2]);
		glm::mat4 rot = glm::toMat4(m_Quaternion);
		glMultMatrixf(glm::value_ptr(rot));
		switch (mode) {
		case Object::DRAWMODE::WIRE:
			glutWireTeapot(m_Scale);
			break;

		case Object::DRAWMODE::SOLID:
			glutSolidTeapot(m_Scale);
			break;
		}
	}glPopMatrix();
}