#include "ObjFile.h"
#include<sstream>
#include<fstream>
using namespace std;

namespace gg {

	ObjFile::ObjFile(string _fileName, Material _material) :
		DrawingObject(_material),
		fileName(_fileName) {}

	ObjFile::ObjFile(const ObjFile& _obj) :DrawingObject(_obj) {
		fileName = _obj.fileName;
		indices.resize(_obj.indices.size());
		std::copy(_obj.indices.begin(), _obj.indices.end(), indices.begin());
		readingNormals.clear();

		indicesCount = indices.size();
		verticesCount = vertices.size();

		abuf = new float[2 * verticesCount];
		ebuf = new unsigned int[indicesCount];
		for (int i = 0; i < verticesCount; i++)
			abuf[i] = vertices[i];
		for (int i = 0; i < verticesCount; i++)
			abuf[i + verticesCount] = normals[i];
		for (int i = 0; i < indicesCount; i++)
			ebuf[i] = indices[i] - 1;

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(unsigned int), ebuf, GL_STATIC_DRAW);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 2 * verticesCount * sizeof(float), abuf, GL_STATIC_DRAW);

		glVertexAttribPointer(inPositionPos, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glVertexAttribPointer(inNormalPos, 3, GL_FLOAT, GL_FALSE, 0, (const void*)(verticesCount * sizeof(float)));
		glEnableVertexAttribArray(inPositionPos);
		glEnableVertexAttribArray(inNormalPos);

	}

	void ObjFile::transpose(int _resPos, int _decPos) {
		for (int i = 0; i < 3; i++) {
			normals[(_decPos - 1) * 3 + i] = readingNormals[(_resPos - 1) * 3 + i];
		}
	}

	bool ObjFile::readFile() {
		char ch;
		ifstream objFile;
		objFile.open(fileName);

		if (objFile.fail()) {
			cout << "file open fail" << endl;
			return false;
		}

		char* buf = new char[bufLen];
		while (objFile.getline(buf, bufLen)) {
			istringstream iss(buf);

			if (buf[0] == 'v'&&buf[1] != 'n') {
				float x, y, z;
				iss >> ch >> x >> y >> z;
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
			}

			else if (buf[0] == 'v'&&buf[1] == 'n') {
				float x, y, z;
				iss >> ch >> ch >> x >> y >> z;
				readingNormals.push_back(x);
				readingNormals.push_back(y);
				readingNormals.push_back(z);
			}

			else if (buf[0] == 'g') break;

			else continue;

		}

		if (vertices.size() != readingNormals.size()) {
			cout << "点数与法线数不匹配" << endl;
			return false;
		}

		normals.resize(readingNormals.size());


		while (objFile.getline(buf, bufLen)) {
			istringstream iss(buf);

			if (buf[0] == 'f') {
				unsigned int va, vb, vc, na, nb, nc;
				iss >> ch >> va >> ch >> ch >> na >> vb >>
					ch >> ch >> nb >> vc >> ch >> ch >> nc;
				indices.push_back(va);
				indices.push_back(vb);
				indices.push_back(vc);

				transpose(na, va);
				transpose(nb, vb);
				transpose(nc, vc);
			}

			else continue;
		}

		//data has already in vectors. now put them into vbo:
		indicesCount = indices.size();
		verticesCount = vertices.size();

		abuf = new float[2 * verticesCount];
		ebuf = new unsigned int[indicesCount];
		for (int i = 0; i < verticesCount; i++)
			abuf[i] = vertices[i];
		for (int i = 0; i < verticesCount; i++)
			abuf[i + verticesCount] = normals[i];
		for (int i = 0; i < indicesCount; i++)
			ebuf[i] = indices[i] - 1;

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(unsigned int), ebuf, GL_STATIC_DRAW);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 2 * verticesCount * sizeof(float), abuf, GL_STATIC_DRAW);

		glVertexAttribPointer(inPositionPos, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glVertexAttribPointer(inNormalPos, 3, GL_FLOAT, GL_FALSE, 0, (const void*)(verticesCount * sizeof(float)));
		glEnableVertexAttribArray(inPositionPos);
		glEnableVertexAttribArray(inNormalPos);

		return true;
	}

	void ObjFile::draw() {
		if (id == -1) return;

		glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrix);
		glUniform3fv(materialLoc, 1, material.material);
		glUniform1f(shininessLoc, material.shininess);
		glUniform1f(strengthLoc, material.strength);

		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);

	}

	void ObjFile::multiMatrix(vmath::mat4 _mat) {
		modelMatrix = _mat * modelMatrix;
	}

	ObjFile::~ObjFile()
	{
		vertices.clear();
		normals.clear();
		readingNormals.clear();
		if (abuf) delete[] abuf;
		if (ebuf) delete[] ebuf;
	}

	//factory creater:
	ObjFile* createObjFile(string _fileName, Material _material) {
		ObjFile* obj = new ObjFile(_fileName, _material);
		if (!obj->readFile()) {
			cout << "createObjFile() failed." << endl;
			return NULL;
		}

		allObjects.push_back(obj);
		return obj;
	}

	ObjFile * createObjFile(const ObjFile & _obj)
	{
		ObjFile* obj = new ObjFile(_obj);
		
		allObjects.push_back(obj);
		return obj;
	}

}
