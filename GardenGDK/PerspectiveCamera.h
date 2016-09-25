#pragma once
#include "Camera.h"

namespace gg {
	class PerspectiveCamera :
		public Camera
	{
	private:

		float left, right, bottom, top, _near, _far;

	protected:

		PerspectiveCamera(
			vmath::vec3 _position,
			vmath::vec3 _center,
			vmath::vec3 _up,
			float _left, float _right,
			float _bottom, float _top,
			float __near, float __far
		)
			:
			Camera(_position, _center, _up),
			left(_left), right(_right),
			bottom(_bottom), top(_top),
			_near(__near), _far(__far)
		{}

		PerspectiveCamera(const PerspectiveCamera& rhs):Camera(rhs) {
			left = rhs.left;
			right = rhs.right;
			bottom = rhs.bottom;
			top = rhs.top;
			_near = rhs._near;
			_far = rhs._far;
		}

		//do not allow call ~() initiatively
		virtual ~PerspectiveCamera() {};
		void operator delete(void* p) { free(p); };

	public:

		void resetPerspect(float _l, float _r, float _b, float _t, float _n, float _f) {
			left = _l; right = _r;
			bottom = _b; top = _t;
			_near = _n; _far = _f;
		}

		//factory:
		friend PerspectiveCamera* createPerspectiveCamera(
			vmath::vec3 _position,
			vmath::vec3 _center,
			vmath::vec3 _up,
			float _left, float _right,
			float _bottom, float _top,
			float __near, float __far
		);
		friend PerspectiveCamera* createPerspectiveCamera(const PerspectiveCamera& rhs);
		friend void releaseCamera(Camera* _cam);

		void setActive();

	};

}

