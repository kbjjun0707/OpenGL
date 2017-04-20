#include "collision_.h"
#include "ray_.h"

#include <gl\glut.h>

#include <glm\gtc\type_ptr.hpp>


bool jun::collision::detect(const Ray & r, SphereCollision & c) {
	float collPos[3] = { 0 };
	c.getPos(collPos);

	glm::fvec3 O(glm::make_vec3(r.m_O)), D(glm::make_vec3(r.m_D)), 
		C(glm::make_vec3(collPos));

	glm::fvec3 s = O - C;
	if ( (glm::dot(s, D)*glm::dot(s, D)) 
		- glm::dot(D, D)	*(glm::dot(s, s) - c.getRadius()*c.getRadius()) >= 0) {
		return true;
	}

	return false;
}



jun::Collision_Base::Collision_Base(int type) {
	m_Type = type;
}

int jun::Collision_Base::type() {
	return m_Type;
}



jun::SphereCollision::SphereCollision(float r) 
	: Collision_Base(collision::SPHERE) {
	m_Radius = r;
}

jun::SphereCollision::SphereCollision(float * pos, float r)
	: Collision_Base(collision::SPHERE) {
	m_Radius = r;
	
	m_Pos.x = pos[0];
	m_Pos.y = pos[1];
	m_Pos.z = pos[2];
}

jun::SphereCollision::SphereCollision(float x, float y, float z, float r)
	: Collision_Base(collision::SPHERE) {
	m_Radius = r;

	m_Pos.x = x;
	m_Pos.y = y;
	m_Pos.z = z;
}

void jun::SphereCollision::draw(int mode) {

	glColor3f(0, 0.8f, 0);
	glPushMatrix(); {
		glTranslatef(m_Pos[0], m_Pos[1], m_Pos[2]);
		switch (mode) {
		case collision::WIRE:
			glutWireSphere(m_Radius, 10, 15);
			break;
		case collision::SOLID:
			glutSolidSphere(m_Radius, 10, 15);
			break;
		default:
			break;
		}
	}glPopMatrix();

}

float jun::SphereCollision::getRadius() {
	return m_Radius;
}

void jun::SphereCollision::setRadius(const float & r) {
	m_Radius = r;
}
