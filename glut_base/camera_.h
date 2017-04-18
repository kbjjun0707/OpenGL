#pragma once

#include "transform_.h"

namespace jun {

	/*
	ī�޶��� �⺻ ����
		Pos = { 0, 0, 0 }
		Up = { 0, 1, 0 }, Dir = { 0, 0, -1 }
	*/
	class Camera : public Transform {

	public:
		Camera(const glm::fvec3 &p_Pos);
		Camera(const float *p_Pos);
		Camera(float x = 0, float y = 0, float z = 0);

		void getMat(float *dst);
		void getTarget(float *dst);
		void getUp(float *dst);
	};

}