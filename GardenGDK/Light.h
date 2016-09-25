#pragma once

#include"globalDefine.h"

namespace gg {

	class Light
	{
	protected:

		int index;
		int id;
		static int idIndex;

	public:

		Light() {
			index = -1;
			id = idIndex++;
		};

		Light(const Light& _rhs) {
			id = idIndex++;
			index = -1;
		}

		int getIndex() {
			return index;
		}

		int getId() {
			return id;
		}

		virtual int setActive() = 0;
		virtual int setInactive() = 0;
		virtual ~Light() = 0;

		friend void releaseLight(Light* _light);

	};

	
}

