#include "PointLight.h"
#include<list>
using namespace std;

namespace gg {

	PointLight* createPointLight(
		vmath::vec3 _position,
		vmath::vec3 _color,
		vmath::vec3 _ambient,
		float _c,
		float _l,
		float _q
	) {
		PointLight* light = new PointLight(
			_position, _color, _ambient, _c, _l, _q
		);
		allLights.push_back(light);

		return light;
	}

	PointLight* createPointLight(const PointLight& _rhs) {
		PointLight* light = new PointLight(_rhs);

		allLights.push_back(light);
		return light;
	}

	int PointLight::setActive()
	{
		if (index != -1) return index;

		index = -1;
		for (int i = 0; i < MaxLights; i++) {
			if (lightsArray[i].isEnabled == 0) {
				index = i;
				lightsArray[i].isEnabled = 1;
				lightsArray[i].isPoint = 1;
				lightsArray[i].ambient = ambient;
				lightsArray[i].color = color;
				lightsArray[i].position = position;
				lightsArray[i].constantAttenuation = constantAttenuation;
				lightsArray[i].linearAttenuation = linearAttenuation;
				lightsArray[i].quadraticAttenuation = quadraticAttenuation;
				break;
			}
		}
		if (index != -1) {
			uniformLightProperties(index);
		}

		return index;
	}

	int PointLight::setInactive()
	{
		if (getId() == -1) return -2;
		if (index == -1) return -1;

		lightsArray[index].isEnabled = 0;
		lightsArray[index].isPoint = 0;
		uniformLightProperties(index);

		index = -1;
		return 0;
	}

}
