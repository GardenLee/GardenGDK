#pragma once

#ifndef DRAWINGOBJECT_H
#define DRAWINGOBJECT_H

//objects can be drawed on the screen. 

#include "Object.h"

#include<vector>
#include<algorithm>

namespace gg {
	class DrawingObject :
		public Object
	{
	public:

		virtual ~DrawingObject() = 0;

		virtual void draw() = 0;

	protected:
		vmath::mat4 modelMatrix;

		std::vector<float> vertices;
		std::vector<float> normals;

		Material material;

		DrawingObject(Material _material = Material()) :Object() {
			modelMatrix = vmath::translate(vmath::vec3(0.0f, 0.0f, 0.0f));
			material = _material;
		};

		DrawingObject(const DrawingObject& _obj) :Object(_obj){
			modelMatrix = _obj.modelMatrix;
			vertices.resize(_obj.vertices.size());
			normals.resize(_obj.normals.size());
			std::copy(_obj.vertices.begin(), _obj.vertices.end(), vertices.begin());
			std::copy(_obj.normals.begin(), _obj.normals.end(), normals.begin());
			material = _obj.material;
		}

	};

}




#endif