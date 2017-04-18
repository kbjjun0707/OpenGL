#pragma once

#include "transform_.h"

namespace jun {

	/*
	카메라의 기본 정보
		Pos = { 0, 0, 0 }
		Up = { 0, 1, 0 }, Dir = { 0, 0, -1 }
	*/
	class Camera : public Transform {

	public:
		Camera(const glm::fvec3 &p_Pos);
		Camera(const float *p_Pos);
		Camera(float x = 0, float y = 0, float z = 0);

		// 4x4 matrix
		void getCamMat(float *dst);
		// point3
		void getTarget(float *dst);
		// vec3 (target - pos)
		void getDir(float *dst);
		// vec3
		void getUp(float *dst);
	};

}