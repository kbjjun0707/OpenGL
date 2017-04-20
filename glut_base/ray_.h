#pragma once

#include <glm\fwd.hpp>

namespace jun {

	class Ray {

	public:
		float	m_O[3];
		float	m_D[3];

		Ray();
		Ray(const float *o, const float *d);
		Ray(float ox, float oy, float oz, float dx, float dy, float dz);
		Ray(const glm::fvec3 &o, const glm::fvec3 &d);
		Ray(const Ray &r);
				
		static Ray calcRay(const int x, const int y);
		static float *pickObjdMove(const float *p_PreO, const float *p_PosO, const float *p_CameraPos, const float *p_ObjPos = nullptr);
	};

}