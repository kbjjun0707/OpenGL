#include "ray_.h"

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <Windows.h>

#include <gl\GL.h>


jun::Ray::Ray() {
	memset(m_O, 0, sizeof(m_O));
	memset(m_D, 0, sizeof(m_D));
	m_D[2] = -1;
}

jun::Ray::Ray(const float * o, const float * d) {
	m_O[0] = o[0];
	m_O[1] = o[1];
	m_O[2] = o[2];

	m_D[0] = d[0];
	m_D[1] = d[1];
	m_D[2] = d[2];
}

jun::Ray::Ray(float ox, float oy, float oz, float dx, float dy, float dz) {
	m_O[0] = ox;
	m_O[1] = oy;
	m_O[2] = oz;

	m_D[0] = dx;
	m_D[1] = dy;
	m_D[2] = dz;
}

jun::Ray::Ray(const glm::fvec3 & o, const glm::fvec3 & d) {
	memcpy(this->m_O, glm::value_ptr(o), sizeof(this->m_O));
	memcpy(this->m_D, glm::value_ptr(d), sizeof(this->m_D));	
}

jun::Ray::Ray(const Ray & r) {
	memcpy(this->m_O, r.m_O, sizeof(this->m_O));
	memcpy(this->m_D, r.m_D, sizeof(this->m_D));
}

jun::Ray jun::Ray::calcRay(const int x, const int y) {
	int viewPort[4];
	float proj[16], model[16];

	glGetIntegerv(GL_VIEWPORT, viewPort);
	glGetFloatv(GL_PROJECTION_MATRIX, proj);
	glGetFloatv(GL_MODELVIEW_MATRIX, model);

	float _x = (2.0*x) / viewPort[2] - 1.0f;
	float _y = 1.0f - (2.0*y) / viewPort[3];

	glm::fvec4 pO = { _x, _y, -1, 1 };
	glm::fvec4 pD = { _x, _y,  1, 1 };

	glm::mat4 projection = glm::make_mat4(proj);
	glm::mat4 modelview = glm::make_mat4(model);

	pO = glm::inverse(modelview)*glm::inverse(projection)*pO;
	pD = glm::inverse(modelview)*glm::inverse(projection)*pD;

	pO /= pO[3];
	pD /= pD[3];
	pD -= pO;

	pD = glm::normalize(pD);

	return Ray(pO[0], pO[1], pO[2],
		pD[0], pD[1], pD[2]);
}

float * jun::Ray::pickObjdMove(const float * p_PreO, const float * p_PosO, 
	const float * p_CameraPos, const float * p_ObjPos, float *dst) {

	glm::fvec3 K(p_CameraPos[0], p_CameraPos[1], p_CameraPos[2]);
	glm::fvec3 C(p_ObjPos[0], p_ObjPos[1], p_ObjPos[2]);
	glm::fvec3 preO(p_PreO[0], p_PreO[1], p_PreO[2]),
		posO(p_PosO[0], p_PosO[1], p_PosO[2]);
	if (preO == posO) {
		float res[3] = { 0 };
		return res;
	}
	glm::fvec3 move(posO - preO);
	glm::fvec3 A(preO - C), B(posO - C);
	glm::fvec3 a(preO - K), b(posO - K);

	float s1 = sqrt((a[1] * b[2] - b[1] * a[2])*(a[1] * b[2] - b[1] * a[2])
		+ (b[0] * a[2] - a[0] * b[2])*(b[0] * a[2] - a[0] * b[2])
		+ (a[0] * b[1] - b[0] * a[1])*(a[0] * b[1] - b[0] * a[1]));
	float s2 = sqrt((A[1] * B[2] - B[1] * A[2])*(A[1] * B[2] - B[1] * A[2])
		+ (B[0] * A[2] - A[0] * B[2])*(B[0] * A[2] - A[0] * B[2])
		+ (A[0] * B[1] - B[0] * A[1])*(A[0] * B[1] - B[0] * A[1]));

	float ratio = s2 / s1;

	move *= ratio;

	memcpy(dst, glm::value_ptr(move), sizeof(float) * 3);

	return glm::value_ptr(move);
}
