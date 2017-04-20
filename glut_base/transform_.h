#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\quaternion.hpp>

namespace jun {

	class Transform {

	protected:
		glm::fvec3 m_Pos;
		glm::fquat m_Quaternion;
		
	public:
		Transform(const glm::fvec3 &p_Pos);
		Transform(const float *p_Pos);
		Transform(float x = 0, float y = 0, float z = 0);

		void translate(const glm::fvec3 &t);
		void translate(float x, float y, float z);
		void translate(float *t);

		void setPosition(const glm::fvec3 &pos);
		void setPosition(float x, float y, float z);
		void setPosition(const float *pos);

		void rotate(float degree, glm::fvec3 axis);
		void rotate(float degree, float axisX, float axisY, float axisZ);
		void rotate(float degree, float *axis);

		void setRotate(float degree, glm::fvec3 axis);
		void setRotate(float degree, float axisX, float axisY, float axisZ);
		void setRotate(float degree, float *axis);

		// float * {x, y, z, w}
		void getQuaternion(float *dst);
		// float *{x, y, z}
		void getPos(float *dst);
	};

	typedef Transform Transf;
}