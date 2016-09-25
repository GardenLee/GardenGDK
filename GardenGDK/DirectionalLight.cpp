#include "DirectionalLight.h"
#include "SpotLight.h"

using namespace std;

namespace gg {

	DirectionalLight* createDirectionalLight(
		vmath::vec3 _lightFrom,
		vmath::vec3 _lightTo,
		vmath::vec3 _color,
		vmath::vec3 _ambient
	) {
		DirectionalLight* light = new DirectionalLight(_lightFrom, _lightTo, _color, _ambient);
		allLights.push_back(light);

		return light;
	}

	DirectionalLight* createDirectionalLight(const DirectionalLight& _rhs) {
		DirectionalLight* light = new DirectionalLight(_rhs);

		allLights.push_back(light);
		return light;
	}

	int DirectionalLight::setActive()
	{
		if (getId() == -1) return -1;
		if (index != -1) return index;//if already has a sit

		index = -1;
		for (int i = 0; i < MaxLights; i++) {
			if (lightsArray[i].isEnabled == 0) {
				index = i;
				lightsArray[i].isEnabled = 1;
				lightsArray[i].isDirectional = 1;
				lightsArray[i].ambient = ambient;
				lightsArray[i].color = color;
				lightsArray[i].lightFrom = lightFrom;
				lightsArray[i].lightTo = lightTo;
				break;
			}
		}
		if (index != -1) {//find a sit
			uniformLightProperties(index);//put data of this sit into shader
		}

		return index;
	}

	int DirectionalLight::setInactive()
	{
		if (getId() == -1) return -2;//pointer is invalid
		if (index == -1) return -1;//has no sit

		lightsArray[index].isEnabled = 0;
		lightsArray[index].isDirectional = 0;
		uniformLightProperties(index);//put data of this sit into shader

		index = -1;
		return 0;//success
	}

}
