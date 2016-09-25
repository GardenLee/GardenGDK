#include"Object.h"
#include<list>
using namespace std;

namespace gg {

	int Object::idIndex = 1;

	Object::~Object() {}

	void releaseObject(Object* _obj) {
		if (_obj == NULL) return;

		for (list<Object*>::iterator ite = allObjects.begin();
			ite != allObjects.end();

			)
		{
			if (*ite == _obj) {
				ite = allObjects.erase(ite);
				break;
			}
			else
				ite++;
		}

		delete _obj;
		_obj->id = -1;
	}

}