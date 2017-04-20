#pragma once

#include "transform_.h"

namespace jun {

	class Ray;
	class SphereCollision;
	class Collision_Base;
	
	class Collision_Base : public Transform {
		int m_Type;

	public:
		Collision_Base(int type);

		int type();
		virtual void draw(int mode = 1) = 0;

		const enum TYPE {
			SPHERE = 1, QUAD = 2
		};
		const enum DRAWMODE {
			WIRE = 1, SOLID = 2
		};

		static bool detect(const Ray &r, SphereCollision &c);
	};


	class SphereCollision : public Collision_Base {
		float m_Radius;

	public:
		SphereCollision(float r = 0.5f);
		SphereCollision(float *pos, float r);
		SphereCollision(float x, float y, float z, float r);

		virtual void draw(int mode = 1);

		float getRadius();
		void setRadius(const float &r);
	};

}

