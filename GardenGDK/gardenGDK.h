#pragma once
//this head file includes all headers of gardenGDK.
//users can use gardenGDK including this header.
//global defines for users should be declared here, not in globalDefine.h.

#ifndef GARDENGDK_H
#define GARDENGDK_H

#include"ObjFile.h"
#include"PerspectiveCamera.h"
#include"Material.h"
#include"DirectionalLight.h"
#include"PointLight.h"
#include"SpotLight.h"
#include"HemisphereLight.h"
#include<iostream>

namespace gg {
	void idle();
	void mySpecialUp(int _k, int _x, int _y);
	void mySpecial(int _k, int _x, int _y);
	void myKeyboardUp(unsigned char _c, int _x, int _y);
	void myKeyboard(unsigned char _c, int _x, int _y);

	Object* findObject(int id);
	Light* findLight(int id);
	Camera* findCamera(int id);

	extern PerspectiveCamera* defaultCamera;
	extern DirectionalLight* defaultLight;


	void getError() {
		using namespace std;
		GLenum error = glGetError();
		switch (error) {
		case GL_INVALID_ENUM:cout << "GL_INVALID_ENUM" << endl; break;
		case GL_INVALID_OPERATION:cout << "GL_INVALID_OPERATION" << endl; break;
		case GL_OUT_OF_MEMORY:cout << "GL_OUT_OF_MEMORY" << endl; break;
			cout << "unknown error" << endl; break;
		}
	}
}

#endif