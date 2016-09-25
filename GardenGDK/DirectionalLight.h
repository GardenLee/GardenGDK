#pragma once

#include "Light.h"

namespace gg {
	class DirectionalLight :
		public Light
	{
	private:

		DirectionalLight() {}

	protected:

		DirectionalLight(
			vmath::vec3 _lightFrom,
			vmath::vec3 _lightTo,
			vmath::vec3 _color,
			vmath::vec3 _ambient
		) :
			Light(),
			ambient(_ambient),
			color(_color),
			lightFrom(_lightFrom),
			lightTo(_lightTo) {}

		DirectionalLight(const DirectionalLight& _rhs) :Light(_rhs) {
			ambient = _rhs.ambient;
			color = _rhs.color;
			lightFrom = _rhs.lightFrom;
			lightTo = _rhs.lightTo;
		}

		virtual ~DirectionalLight() {};

	public:

		vmath::vec3 ambient;
		vmath::vec3 color;
		vmath::vec3 lightFrom;
		vmath::vec3 lightTo;

		virtual int setActive();
		virtual int setInactive();

		friend DirectionalLight* createDirectionalLight(
			vmath::vec3 _lightFrom = vmath::vec3(0.0f, 0.0f, 0.0f),
			vmath::vec3 _lightTo = vmath::vec3(0.0f, 0.0f, -1.0f),
			vmath::vec3 _color = vmath::vec3(0.9f, 0.9f, 0.9f),
			vmath::vec3 _ambient = vmath::vec3(0.2f, 0.2f, 0.2f)
		);
		friend DirectionalLight* createDirectionalLight(const DirectionalLight& _rhs);
		friend void releaseLight(Light* _light);

	};

}

