#include"globalDefine.h"
#include"PerspectiveCamera.h"
#include"ObjFile.h"
#include"DirectionalLight.h"
#include<iostream>
#include<string>

#pragma comment(lib,"legacy_stdio_definitions.lib")

#if _MSC_VER>=1900
#include "stdio.h" 
_ACRTIMP_ALT FILE* __cdecl __acrt_iob_func(unsigned);
#ifdef __cplusplus 
extern "C"
#endif 
FILE* __cdecl __iob_func(unsigned i) {
	return __acrt_iob_func(i);
}
#endif /* _MSC_VER>=1900 */


using namespace vmath;
using namespace std;

//define all global variables. globalDefine.h externs these variables.

namespace gg {
	//matrixs location:
	GLuint program;
	GLint modelMatrixLoc;
	GLint projectionMatrixLoc;
	GLint viewMatrixLoc;

	GLint ambientLoc;
	GLint lightColorLoc;
	GLint lightDirectionLoc;
	GLint eyePosLoc;
	GLint shininessLoc;
	GLint strengthLoc;
	GLint lightFromLoc;
	GLint lightToLoc;
	GLint materialLoc;
	GLint lightsArrayLoc;

	list<Object*> allObjects;
	list<Camera*> allCameras;
	list<Light*> allLights;

	Camera* activeCamera;

	PerspectiveCamera* defaultCamera;
	DirectionalLight* defaultLight;

	LightProperties lightsArray[MaxLights];

	void uniformLightProperties(int i, GLuint _program) {
		GLint loc = -1;
		char tmp[50];

		sprintf(tmp, "lightsArray[%d].isEnabled", i);
		loc = glGetUniformLocation(_program, tmp);
		glUniform1i(loc, lightsArray[i].isEnabled);

		sprintf(tmp, "lightsArray[%d].isPoint", i);
		loc = glGetUniformLocation(_program, tmp);
		glUniform1i(loc, lightsArray[i].isPoint);

		sprintf(tmp, "lightsArray[%d].isSpot", i);
		loc = glGetUniformLocation(_program, tmp);
		glUniform1i(loc, lightsArray[i].isSpot);

		sprintf(tmp, "lightsArray[%d].isDirectional", i);
		loc = glGetUniformLocation(_program, tmp);
		glUniform1i(loc, lightsArray[i].isDirectional);

		sprintf(tmp, "lightsArray[%d].isHemisphere", i);
		loc = glGetUniformLocation(_program, tmp);
		glUniform1i(loc, lightsArray[i].isHemisphere);

		sprintf(tmp, "lightsArray[%d].ambient", i);
		loc = glGetUniformLocation(_program, tmp);
		glUniform3fv(loc, 1, lightsArray[i].ambient);

		sprintf(tmp, "lightsArray[%d].color", i);
		loc = glGetUniformLocation(_program, tmp);
		glUniform3fv(loc, 1, lightsArray[i].color);

		sprintf(tmp, "lightsArray[%d].position", i);
		loc = glGetUniformLocation(_program, tmp);
		glUniform3fv(loc, 1, lightsArray[i].position);

		sprintf(tmp, "lightsArray[%d].coneCenter", i);
		loc = glGetUniformLocation(_program, tmp);
		glUniform3fv(loc, 1, lightsArray[i].coneCenter);

		sprintf(tmp, "lightsArray[%d].lightFrom", i);
		loc = glGetUniformLocation(_program, tmp);
		glUniform3fv(loc, 1, lightsArray[i].lightFrom);

		sprintf(tmp, "lightsArray[%d].lightTo", i);
		loc = glGetUniformLocation(_program, tmp);
		glUniform3fv(loc, 1, lightsArray[i].lightTo);

		sprintf(tmp, "lightsArray[%d].spotCosCutoff", i);
		loc = glGetUniformLocation(_program, tmp);
		glUniform1f(loc, lightsArray[i].spotCosCutoff);

		sprintf(tmp, "lightsArray[%d].spotExponent", i);
		loc = glGetUniformLocation(_program, tmp);
		glUniform1f(loc, lightsArray[i].spotExponent);

		sprintf(tmp, "lightsArray[%d].constantAttenuation", i);
		loc = glGetUniformLocation(_program, tmp);
		glUniform1f(loc, lightsArray[i].constantAttenuation);

		sprintf(tmp, "lightsArray[%d].linearAttenuation", i);
		loc = glGetUniformLocation(_program, tmp);
		glUniform1f(loc, lightsArray[i].linearAttenuation);

		sprintf(tmp, "lightsArray[%d].quadraticAttenuation", i);
		loc = glGetUniformLocation(_program, tmp);
		glUniform1f(loc, lightsArray[i].quadraticAttenuation);
	}

	void gardenInit() {//this function should be called after glUseProgram()

		for (int i = 0; i < MaxLights; i++) {
			lightsArray[i].isEnabled = false;
		}

		modelMatrixLoc = glGetUniformLocation(program, "model_matrix");
		projectionMatrixLoc = glGetUniformLocation(program, "projection_matrix");
		viewMatrixLoc = glGetUniformLocation(program, "view_matrix");

		lightsArrayLoc = glGetUniformLocation(program, "lightsArray");

		shininessLoc = glGetUniformLocation(program, "shininess");
		strengthLoc = glGetUniformLocation(program, "strength");
		materialLoc = glGetUniformLocation(program, "material");

		//default camera:
		defaultCamera = createPerspectiveCamera(
			vec3(0.0f, 0.0f, 1.0f),
			vec3(0.0f, 0.0f, -1.0f),
			vec3(0.0f, 1.0f, 0.0f),
			-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 300.0f
		);
		defaultCamera->setActive();

		//default light:
		defaultLight = createDirectionalLight();
		defaultLight->setActive();

		//TODO: init others

	}

	void gardenRelease() {
		//release all new objects
		
		int objectCount = allObjects.size();
		for (list<Object*>::iterator ite = allObjects.begin();
			ite!=allObjects.end();
			ite++
			) {
			delete *ite;
			*ite = NULL;
		}
		allObjects.clear();

		int cameraCount = allCameras.size();
		for (list<Camera*>::iterator ite = allCameras.begin();
			ite != allCameras.end();
			ite++
			) {
			delete *ite;
			*ite = NULL;
		}
		allCameras.clear();

		int lightCount = allLights.size();
		for (list<Light*>::iterator ite = allLights.begin();
			ite != allLights.end();
			ite++
			) {
			(*ite)->setInactive();
			delete *ite;
			*ite = NULL;
		}
		allLights.clear();

		cout << objectCount << " objects have been released." << endl;
		cout << cameraCount << " cameras have been released." << endl;
		cout << lightCount << " lights have been released." << endl;
	}

	Object* findObject(int id) {
		for (list<Object*>::iterator ite;
			ite != allObjects.end();
			ite++) {
			if ((*ite)->getId() == id) {
				return *ite;
			}
		}
		return NULL;
	}

	Light* findLight(int id) {
		for (list<Light*>::iterator ite;
			ite != allLights.end();
			ite++) {
			if ((*ite)->getId() == id) {
				return *ite;
			}
		}
		return NULL;
	}

	Camera* findCamera(int id) {
		for (list<Camera*>::iterator ite;
			ite != allCameras.end();
			ite++) {
			if ((*ite)->getId() == id) {
				return *ite;
			}
		}
		return NULL;
	}

}