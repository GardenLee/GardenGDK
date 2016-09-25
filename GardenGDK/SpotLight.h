#pragma once
#include "Light.h"

namespace gg {

	class SpotLight :
		public Light
	{
	private:

		SpotLight() {}

	protected:

		SpotLight(
			vmath::vec3 _position,
			vmath::vec3 _coneCenter,
			vmath::vec3 _color,
			vmath::vec3 _ambient,
			float _spotCos,
			float _spotExp,
			float _c,
			float _l,
			float _q
		) :
			Light(),
			ambient(_ambient),
			color(_color),
			position(_position),
			coneCenter(_coneCenter),
			spotCosCutoff(_spotCos),
			spotExponent(_spotExp),
			constantAttenuation(_c),
			linearAttenuation(_l),
			quadraticAttenuation(_q)
		{}

		SpotLight(const SpotLight& _rhs) :
			Light(_rhs),
			ambient(_rhs.ambient),
			color(_rhs.color),
			position(_rhs.position),
			coneCenter(_rhs.coneCenter),
			spotCosCutoff(_rhs.spotCosCutoff),
			spotExponent(_rhs.spotExponent),
			constantAttenuation(_rhs.constantAttenuation),
			linearAttenuation(_rhs.linearAttenuation),
			quadraticAttenuation(_rhs.quadraticAttenuation)
		{}

		virtual ~SpotLight() {}

	public:

		vmath::vec3 ambient;
		vmath::vec3 color;
		vmath::vec3 position;
		vmath::vec3 coneCenter;
		float spotCosCutoff;
		float spotExponent;
		float constantAttenuation;
		float linearAttenuation;
		float quadraticAttenuation;
		
		virtual int setActive();
		virtual int setInactive();

		friend SpotLight* createSpotLight(
			vmath::vec3 _position = vmath::vec3(0.0f, 0.0f, 0.0f),
			vmath::vec3 _coneCenter = vmath::vec3(0.0f, 0.0f, -1.0f),
			vmath::vec3 _color = vmath::vec3(0.9f, 0.9f, 0.9f),
			vmath::vec3 _ambient = vmath::vec3(0.2f, 0.2f, 0.2f),
			float _spotCosCutoff = 0.6f,
			float _spotExponent = 5.0f,
			float _c = 1.0f,
			float _l = 0.001f,
			float _q = 0.000001f
		);
		friend SpotLight* createSpotLight(const SpotLight& _rhs);
		friend void releaseLight(Light* _light);
		
	};

}

