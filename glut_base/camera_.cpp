#include "camera_.h"

#include <glm\gtc\type_ptr.hpp>
#include <iostream>

jun::Camera::Camera(const glm::fvec3 & p_Pos) : Transform(p_Pos) {
}

jun::Camera::Camera(const float * p_Pos) : Transform(p_Pos) {
}

jun::Camera::Camera(float x, float y, float z) : Transform (x, y, z) {
}

void jun::Camera::getCamMat(float * dst) {
	float target[3] = { 0 }, up[3] = { 0 };
	getTarget(target); getUp(up);

	glm::mat4 resMat = glm::lookAt(
		m_Pos,
		glm::make_vec3<float>(target),
		glm::make_vec3<float>(up)
	);

	memcpy(dst, glm::value_ptr(resMat), sizeof(float) * 16);
}

void jun::Camera::getTarget(float *dst) {
	glm::fvec3 res(0, 0, -1);
	res = glm::rotate(m_Quaternion, res);
	res += m_Pos;
	
	memcpy(dst, glm::value_ptr(res), sizeof(float) * 3);
}

void jun::Camera::getFront(float * dst) {
	glm::fvec3 res(0, 0, -1);
	res = glm::rotate(m_Quaternion, res);

	memcpy(dst, glm::value_ptr(res), sizeof(float) * 3);
}

void jun::Camera::getUp(float *dst) {
	glm::fvec3 res(0, 1, 0);
	res = glm::rotate(m_Quaternion, res);

	memcpy(dst, glm::value_ptr(res), sizeof(float) * 3);
}
