#pragma once
#include "Light.h"

namespace gg {

	class HemisphereLight :
		public Light
	{
	private:


	protected:

		HemisphereLight(
			vmath::vec3 _direct, 
			vmath::vec3 _skyColor, 
			vmath::vec3 _groundColor
		) :
			Light(), 
			direction(_direct),
			skyColor(_skyColor),
			groundColor(_groundColor)
		{}

		HemisphereLight(const HemisphereLight& _rhs) :
			Light(_rhs),
			direction(_rhs.direction),
			skyColor(_rhs.skyColor),
			groundColor(_rhs.groundColor)
		{}

		virtual ~HemisphereLight() {}

	public:

		vmath::vec3 direction;
		vmath::vec3 skyColor;
		vmath::vec3 groundColor;

		virtual int setActive();
		virtual int setInactive();

		friend HemisphereLight* createHemisphereLight(
			vmath::vec3 _direct = vmath::vec3(0.0f, 1.0f, 0.0f),
			vmath::vec3 _skyColor = vmath::vec3(1.0f, 1.0f, 1.0f),
			vmath::vec3 _groundColor = vmath::vec3(0.0f, 0.0f, 0.0f)
		);
		friend HemisphereLight* createHemisphereLight(const HemisphereLight& _rhs);
		
		friend void releaseLight(Light* _light);

	};

}

