#pragma once

#include"globalDefine.h"

namespace gg {

	class Material
	{

	public:
		vmath::vec3 material;
		float shininess;
		float strength;

		Material(
			vmath::vec3 _material = vmath::vec3(0.9f, 0.9f, 0.9f),
			float _shininess = 40.0f,
			float _strength = 20.0f
		)
			:
			material(_material),
			shininess(_shininess),
			strength(_strength)
		{}
		virtual ~Material() {}

	};

}

