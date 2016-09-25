#pragma once
#include "Light.h"

namespace gg {

	class PointLight :
		public Light
	{
	private:

		PointLight() {}

	protected:

		PointLight(
			vmath::vec3 _position,
			vmath::vec3 _color,
			vmath::vec3 _ambient,
			float _constantAttenuation,
			float _linearAttenuation,
			float _quadraticAttenuation
		) :
			Light(),
			ambient(_ambient),
			color(_color),
			position(_position),
			constantAttenuation(_constantAttenuation),
			linearAttenuation(_linearAttenuation),
			quadraticAttenuation(_quadraticAttenuation)
		{}

		PointLight(const PointLight& _rhs) :Light(_rhs) {
			ambient = _rhs.ambient;
			color = _rhs.color;
			position = _rhs.position;
			constantAttenuation = _rhs.constantAttenuation;
			linearAttenuation = _rhs.linearAttenuation;
			quadraticAttenuation = _rhs.quadraticAttenuation;
		}

		virtual ~PointLight() {};

	public:

		vmath::vec3 ambient;
		vmath::vec3 color;
		vmath::vec3 position;
		float constantAttenuation;
		float linearAttenuation;
		float quadraticAttenuation;

		virtual int setActive();
		virtual int setInactive();

		friend PointLight* createPointLight(
			vmath::vec3 _position = vmath::vec3(0.0f, 0.0f, 0.0f),
			vmath::vec3 _color = vmath::vec3(0.9f, 0.9f, 0.9f),
			vmath::vec3 _ambient = vmath::vec3(0.2f, 0.2f, 0.2f),
			float _c = 1.0f,
			float _l = 0.001f,
			float _q = 0.00001f
		);
		friend PointLight* createPointLight(const PointLight& _rhs);
		friend void releaseLight(Light* _light);
	};

}

