#include "transform_.h"

#include <glm\gtc\type_ptr.hpp>
#include <stdio.h>

jun::Transform::Transform(const glm::fvec3 &p_Pos) {
	m_Pos.x = p_Pos.x;
	m_Pos.y = p_Pos.y;
	m_Pos.z = p_Pos.z;
}

jun::Transform::Transform(const float * p_Pos) {
	m_Pos.x = p_Pos[0];
	m_Pos.y = p_Pos[1];
	m_Pos.z = p_Pos[2];
}

jun::Transform::Transform(float x, float y, float z) {
	m_Pos.x = x;
	m_Pos.y = y;
	m_Pos.z = z;
}

void jun::Transform::translate(const glm::fvec3 & t) {
	m_Pos.x += t.x;
	m_Pos.y += t.y;
	m_Pos.z += t.z;
}

void jun::Transform::translate(float x, float y, float z) {
	m_Pos.x += x;
	m_Pos.y += y;
	m_Pos.z += z;
}

void jun::Transform::translate(float * t) {
	m_Pos.x += t[0];
	m_Pos.y += t[1];
	m_Pos.z += t[2];
}

void jun::Transform::setPosition(float x, float y, float z) {
	m_Pos.x = x;
	m_Pos.y = y;
	m_Pos.z = z;
}

void jun::Transform::setPosition(const float * pos) {
	m_Pos.x = pos[0];
	m_Pos.y = pos[1];
	m_Pos.z = pos[2];
}

void jun::Transform::setPosition(const glm::fvec3 & pos) {
	m_Pos.x = pos.x;
	m_Pos.y = pos.y;
	m_Pos.z = pos.z;
}

void jun::Transform::rotate(float degree, glm::fvec3 axis) {
	m_Quaternion = glm::rotate(m_Quaternion, glm::radians(degree), axis);
}

void jun::Transform::rotate(float degree, 
	float axisX, float axisY, float axisZ) {
	m_Quaternion = glm::rotate(m_Quaternion, glm::radians(degree),
		glm::fvec3(axisX, axisY, axisZ));
}

void jun::Transform::rotate(float degree, float * axis) {
	m_Quaternion = glm::rotate(m_Quaternion, glm::radians(degree),
		glm::fvec3(axis[0], axis[1], axis[2]));
}

void jun::Transform::setRotate(float degree, glm::fvec3 axis) {

	m_Quaternion = glm::angleAxis(glm::radians(degree), axis);
}

void jun::Transform::setRotate(float degree, 
	float axisX, float axisY, float axisZ) {

	m_Quaternion = glm::angleAxis(glm::radians(degree),
		glm::fvec3(axisX, axisY, axisZ));
}

void jun::Transform::setRotate(float degree, float * axis) {

	m_Quaternion = glm::angleAxis(glm::radians(degree),
		glm::fvec3(axis[0], axis[1], axis[2]));
}

void jun::Transform::getQuaternion(float *dst) {
	memcpy(dst, glm::value_ptr(m_Quaternion), sizeof(float) * 4);
}

void jun::Transform::getPos(float *dst) {
	memcpy(dst, glm::value_ptr(m_Pos), sizeof(float) * 3);
}

