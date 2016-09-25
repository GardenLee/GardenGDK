#pragma once

#ifndef OBJFILE_H
#define OBJFILE_H

#include "DrawingObject.h"
#include<string>

namespace gg {

	//how to use:
	//use createObjFile() create a object,
	//use multiMatrix() to add translate(or rotate) on it,
	//than use draw() to draw it.

	class ObjFile :
		public DrawingObject
	{
	private:
		std::string fileName;
		std::vector<unsigned int> indices;
		std::vector<float> readingNormals;

		GLfloat* abuf;
		GLuint* ebuf;

		GLuint vao;
		GLuint vbo;
		GLuint ebo;

		GLint indicesCount;
		GLint verticesCount;

		enum { bufLen = 10000 };

		void transpose(int, int);	
		//TODO:
		//operator delete in private

	protected:

		ObjFile() {};
		ObjFile(std::string, Material _material);//read obj file and put data into vectors
		ObjFile(const ObjFile& _obj);//read data from _obj. vao, vbo, attribPointer also be set already
		bool readFile();

		virtual ~ObjFile();
		void operator delete(void* p) { free(p); p = NULL; };

	public:

		virtual void draw();
		virtual void multiMatrix(vmath::mat4);

		//factory:
		friend ObjFile* createObjFile(std::string _fileName, Material _material = Material());
		friend ObjFile* createObjFile(const ObjFile& _obj);
		friend void releaseObject(Object* _obj);

	};

}
#endif