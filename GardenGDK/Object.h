#pragma once

//the "basic-est" class. lots of classes will be derived from it.

/*
layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
*/


#ifndef OBJECT_H
#define OBJECT_H

#include"globalDefine.h"

namespace gg {

	class Object
	{
	public:

		virtual ~Object() = 0;

		int getId() {
			return id;
		}


	protected:
		Object() {
			id = idIndex++;

		};

		Object(const Object& _obj) {
			id = idIndex++;
		}

		int id;//unique index for every object
		static int idIndex;

		friend void releaseObject(Object* _obj);

	};



}

#endif
