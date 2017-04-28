#ifndef OBJECT__H
#define OBJECT__H


#include "transform_.h"

namespace jun {
			
	class Object : public Transform {
	protected:
		float m_Scale;
	public:
		Object(float *pos);
		Object(const glm::fvec3 &pos);
		Object(float x = 0, float y = 0, float z = 0);

		virtual void draw(int mode = 1) = 0;

		void setScale(float scale);

		const enum DRAWMODE {
			WIRE = 1, SOLID = 2
		};
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


	class TeapotObject : public Object {		
	public:
		TeapotObject(float *pos);
		TeapotObject(const glm::fvec3 &pos);
		TeapotObject(float x = 0, float y = 0, float z = 0);

		virtual void draw(int mode = 1);
	};



}

#endif // !OBJECT__H