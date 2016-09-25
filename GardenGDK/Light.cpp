#include "Light.h"
#include<list>
#include "HemisphereLight.h"
using namespace std;

namespace gg {

	int Light::idIndex = 1;

	Light::~Light()
	{
	}

	void releaseLight(Light* _light) {

		if (_light == NULL) return;

		_light->setInactive();

		for (list<Light*>::iterator ite = allLights.begin();
			ite != allLights.end();
			)
		{
			if (*ite == _light) {
				allLights.erase(ite);
				break;
			}
			else ite++;
		}

		
		delete _light;
		_light->id = -1;
	}

}
