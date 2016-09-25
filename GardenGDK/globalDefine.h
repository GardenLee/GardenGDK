#pragma once

//this header used by gardenGDK inters. all gardenGDK classes will include this header.
//this header just used by gardenGDK itself. 

#ifndef GLOBALDEFINE_H
#define GLOBALDEFINE_H

#include"vgl.h"
#include"vmath.h"
#include"Camera.h"
#include"Object.h"
#include"Material.h"
#include"Light.h"
#include<iostream>
#include<stdlib.h>
#include<list>


namespace gg {
	enum { inPositionPos, inNormalPos };

	class Object;
	class Camera;
	class Light;

	extern GLuint program;
	extern GLint modelMatrixLoc;
	extern GLint projectionMatrixLoc;
	extern GLint viewMatrixLoc;

	extern GLint ambientLoc;
	extern GLint lightColorLoc;
	extern GLint lightDirectionLoc;
	extern GLint eyePosLoc;
	extern GLint shininessLoc;
	extern GLint strengthLoc;
	extern GLint lightFromLoc;
	extern GLint lightToLoc;
	extern GLint materialLoc;

	extern std::list<Object*> allObjects;
	extern std::list<Camera*> allCameras;
	extern std::list<Light*> allLights;

	extern Camera* activeCamera;

	struct LightProperties
	{
		int isEnabled;
		int isPoint;
		int isSpot;
		int isDirectional;
		int isHemisphere;
		vmath::vec3 ambient;
		vmath::vec3 color;
		vmath::vec3 position;
		vmath::vec3 coneCenter;
		vmath::vec3 lightFrom;
		vmath::vec3 lightTo;
		float spotCosCutoff;
		float spotExponent;
		float constantAttenuation;
		float linearAttenuation;
		float quadraticAttenuation;

		LightProperties() {
			isEnabled = 0;
			isPoint = 0;
			isSpot = 0;
			isDirectional = 0;
			isHemisphere = 0;
		}
	};
	const int MaxLights = 12;
	extern LightProperties lightsArray[];

	void gardenInit();
	void gardenRelease();
	void uniformLightProperties(int, GLuint = program);

}

#endif