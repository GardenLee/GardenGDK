#include "PerspectiveCamera.h"
using namespace std;

namespace gg {

	PerspectiveCamera* createPerspectiveCamera(
		vmath::vec3 _position,
		vmath::vec3 _center,
		vmath::vec3 _up,
		float _left, float _right,
		float _bottom, float _top,
		float __near, float __far
	) {
		PerspectiveCamera* cam = new PerspectiveCamera(
			_position,
			_center,
			_up,
			_left, _right,
			_bottom, _top,
			__near, __far);
		allCameras.push_back(cam);

		return cam;
	}

	PerspectiveCamera * createPerspectiveCamera(const PerspectiveCamera & rhs)
	{
		PerspectiveCamera* cam = new PerspectiveCamera(rhs);
		allCameras.push_back(cam);
		return cam;
	}

	void PerspectiveCamera::setActive() {
		if (id == -1) return;//TODO: report error

		vmath::mat4 projectionMatrix(vmath::frustum(left, right, bottom, top, _near, _far));
		vmath::mat4 viewMatrix(vmath::lookat(position, center, up));

		glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, projectionMatrix);
		glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, viewMatrix);
		
		//when use view_matrix, eyePos always be zero :)
		//glUniform3fv(eyePosLoc, 1, position);
		if (eyePosLoc != -1)
			glUniform3fv(eyePosLoc, 1, position);

		activeCamera = this;
	};

}
