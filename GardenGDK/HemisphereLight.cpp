#include "HemisphereLight.h"

using namespace vmath;

namespace gg {

	HemisphereLight * createHemisphereLight(
		vmath::vec3 _direct,
		vmath::vec3 _skyColor,
		vmath::vec3 _groundColor
	) {
		HemisphereLight* light = new HemisphereLight(_direct, _skyColor, _groundColor);

		allLights.push_back(light);
		return light;
	}

	HemisphereLight* createHemisphereLight(const HemisphereLight& _rhs) {
		HemisphereLight* light = new HemisphereLight(_rhs);

		allLights.push_back(light);
		return light;
	}

	int HemisphereLight::setActive()
	{
		if (getId() == -1) return -1;
		if (index != -1) return index;//if already has a sit

		index = -1;
		for (int i = 0; i < MaxLights; i++) {
			if (lightsArray[i].isEnabled == 0) {
				index = i;
				lightsArray[i].isEnabled = 1;
				lightsArray[i].isHemisphere = 1;
				lightsArray[i].color = skyColor;
				lightsArray[i].ambient = groundColor;
				lightsArray[i].lightFrom = direction;
				lightsArray[i].lightTo = vec3(0.0f);
				break;
			}
		}
		if (index != -1) {//find a sit
			uniformLightProperties(index);//put data of this sit into shader
		}

		return index;
	}

	int HemisphereLight::setInactive()
	{
		if (getId() == -1) return -2;//pointer is invalid
		if (index == -1) return -1;//has no sit

		lightsArray[index].isEnabled = 0;
		lightsArray[index].isHemisphere = 0;
		uniformLightProperties(index);//put data of this sit into shader

		index = -1;
		return 0;//success
	}

}
