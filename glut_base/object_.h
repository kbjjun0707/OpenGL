#pragma once

#include "transform_.h"

namespace jun {

	namespace objects {

		const enum DRAWMODE {
			WIRE = 1, SOLID = 2
		};

	}
	
	class Object : public Transform {
	public:
		Object();
		virtual void draw(int mode = 1);
	};


	class SphereObject : public Object {
		float m_Radius;

	public:
		SphereObject(float r = 0.5f);
		SphereObject(float *pos, float r);
		SphereObject(glm::fvec3 pos, float r);
		SphereObject(float x, float y, float z, float r);

		virtual void draw(int mode = 1);

		float getRadius();
		void setRadius(const float &r);
	};


}