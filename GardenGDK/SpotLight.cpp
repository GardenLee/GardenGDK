#include "SpotLight.h"

namespace gg {

	SpotLight * createSpotLight(
		vmath::vec3 _position,
		vmath::vec3 _coneCenter,
		vmath::vec3 _color,
		vmath::vec3 _ambient,
		float _spotCosCutoff,
		float _spotExponent,
		float _c, float _l, float _q
	) {
		SpotLight* light = new SpotLight(
			_position, _coneCenter, _color, _ambient,
			_spotCosCutoff, _spotExponent, _c, _l, _q
		);

		allLights.push_back(light);
		return light;
	}

	SpotLight * createSpotLight(const SpotLight & _rhs)
	{
		SpotLight* light = new SpotLight(_rhs);

		allLights.push_back(light);
		return light;
	}

	int SpotLight::setActive()
	{
		if (index != -1) return index;

		index = -1;
		for (int i = 0; i < MaxLights; i++) {
			if (lightsArray[i].isEnabled == 0) {
				index = i;
				lightsArray[i].isEnabled = 1;
				lightsArray[i].isSpot = 1;
				lightsArray[i].ambient = ambient;
				lightsArray[i].color = color;
				lightsArray[i].position = position;
				lightsArray[i].coneCenter = coneCenter;
				lightsArray[i].spotCosCutoff = spotCosCutoff;
				lightsArray[i].spotExponent = spotExponent;
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

	int SpotLight::setInactive()
	{
		if (getId() == -1) return -2;
		if (index == -1) return -1;

		lightsArray[index].isEnabled = 0;
		lightsArray[index].isSpot = 0;
		uniformLightProperties(index);

		index = -1;
		return 0;
	}

}
