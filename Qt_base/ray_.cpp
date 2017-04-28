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

jun::Ray jun::Ray::calcRay(const float camX, const float camY, const float camZ, const int x, const int y) {
	int viewPort[4];
	float proj[16], model[16];

	glGetIntegerv(GL_VIEWPORT, viewPort);
	glGetFloatv(GL_PROJECTION_MATRIX, proj);
	glGetFloatv(GL_MODELVIEW_MATRIX, model);

	float _x = (2.0*x) / viewPort[2] - 1.0f;
	float _y = 1.0f - (2.0*y) / viewPort[3];

	glm::fvec4 pO = { camX, camY, camZ, 1 };
	glm::fvec4 pD = { _x, _y, -1, 1 };

	glm::mat4 projection = glm::make_mat4(proj);
	glm::mat4 modelview = glm::make_mat4(model);

	pD = glm::inverse(modelview)*glm::inverse(projection)*pD;

	pD /= pD[3];
	pD -= pO;

	pD = glm::normalize(pD);

	return Ray(pO, pD);
}

jun::Ray jun::Ray::calcRay(const float * viewport, const float * MVP, float camX, float camY, float camZ, int x, int y) {
	float _x = (2.0*x) / viewport[2] - 1.0f;
	float _y = 1.0f - (2.0*y) / viewport[3];

	glm::fvec4 pO = { camX, camY, camZ, 1 };
	glm::fvec4 pD = { _x, _y, -1, 1 };

	pD = glm::inverse(glm::make_mat4(MVP))*pD;
	pD /= pD[3];
	pD -= pO;

	pD = glm::normalize(pD);

	return Ray(pO, pD);
}

jun::Ray jun::Ray::calcRay(const glm::fvec4 & viewport, 
	const glm::mat4 & MVP, const glm::fvec3 & camposition, int x, int y) {
	float _x = (2.0*x) / viewport[2] - 1.0f;
	float _y = 1.0f - (2.0*y) / viewport[3];

	glm::fvec4 pO = { camposition[0], camposition[1], camposition[2], 1 };
	glm::fvec4 pD = { _x, _y, -1, 1 };

	pD = glm::inverse(MVP)*pD;
	pD /= pD[3];
	pD -= pO;

	pD = glm::normalize(pD);

	return Ray(pO, pD);
}

float * jun::Ray::pickObjdMove(const float * p_PreO, const float * p_PosO, 
	const float * p_CameraPos, const float * p_ObjPos) {

	glm::fvec3 K(p_CameraPos[0], p_CameraPos[1], p_CameraPos[2]);
	glm::fvec3 C;
	if (p_ObjPos == nullptr) {
		C = K;
	} else {
		C[0] = p_ObjPos[0];
		C[1] = p_ObjPos[1];
		C[2] = p_ObjPos[2];
	}
	glm::fvec3	preO(p_PreO[0], p_PreO[1], p_PreO[2]),
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

	return glm::value_ptr(move);
}

float * jun::Ray::pickObjdMove(int p_PreX, int p_PreY, int p_PosX, int p_PosY, const float * p_CameraPos, const float * p_ObjPos) {
	int viewPort[4];
	float proj[16], model[16];

	glGetIntegerv(GL_VIEWPORT, viewPort);
	glGetFloatv(GL_PROJECTION_MATRIX, proj);
	glGetFloatv(GL_MODELVIEW_MATRIX, model);

	float _x1 = (2.0*p_PreX) / viewPort[2] - 1.0f;
	float _y1 = 1.0f - (2.0*p_PreY) / viewPort[3];

	float _x2 = (2.0*p_PosX) / viewPort[2] - 1.0f;
	float _y2 = 1.0f - (2.0*p_PosY) / viewPort[3];

	glm::fvec4 pre = { _x1, _y1, -1, 1 };
	glm::fvec4 pos = { _x2, _y2, -1, 1 };

	glm::mat4 projection = glm::make_mat4(proj);
	glm::mat4 modelview = glm::make_mat4(model);

	pre = glm::inverse(modelview)*glm::inverse(projection)*pre;
	pos = glm::inverse(modelview)*glm::inverse(projection)*pos;

	pre /= pre[3];
	pos /= pos[3];
	
	return pickObjdMove(glm::value_ptr(pre), glm::value_ptr(pos), p_CameraPos, p_ObjPos);
}