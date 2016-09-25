#include "Camera.h"
#include<list>
using namespace std;

namespace gg {

	int Camera::idIndex = 1;

	Camera::Camera(vmath::vec3 _position, vmath::vec3 _center, vmath::vec3 _up)
	{
		id = idIndex++;

		position = _position;
		center = _center;
		up = _up;

		towardsVec = center - position;
		upVec = up;
		rightVec = vmath::cross(towardsVec, upVec);
		constUpVec = upVec;
	}

	void Camera::horizontalRotate(float _angle) {

		//水平旋转以constUpVec为轴，该轴即构造相机时传入的upVec，且不会改变
		vmath::mat4 rotateMatrix(vmath::rotate(_angle, constUpVec));

		towardsVec = vmath::vec3(rotateMatrix * vmath::vec4(towardsVec, 1.0f));
		upVec = vmath::vec3(rotateMatrix * vmath::vec4(upVec, 1.0f));
		rightVec = vmath::vec3(rotateMatrix * vmath::vec4(rightVec, 1.0f));
		//rightVec = vmath::cross(towardsVec, upVec);

		center = position + towardsVec;
		up = upVec;

		glutPostRedisplay();
	}

	void Camera::verticalRotate(float _angle) {

		//竖直旋转以rightVec为轴
		vmath::mat4 rotateMatrix(vmath::rotate(_angle, rightVec));

		vmath::vec3 _towardsVec = vmath::vec3(rotateMatrix * vmath::vec4(towardsVec, 1.0f));
		vmath::vec3 _upVec = vmath::vec3(rotateMatrix * vmath::vec4(upVec, 1.0f));

		//摄像机不能倒过来，倒过来将引起很多困扰，比如左右颠倒
		if (_upVec[1] > 0.1) {
			towardsVec = _towardsVec;
			upVec = _upVec;

			center = position + towardsVec;
			up = upVec;
		}

		glutPostRedisplay();
	}

	void Camera::horizontalMove(float _dis) {

		vmath::vec3 movingVec = vmath::normalize(rightVec);
		position = position + _dis * movingVec;

		center = position + towardsVec;

		glutPostRedisplay();
	}

	void Camera::fowardMove(float _dis) {

		vmath::vec3 movingVec = vmath::normalize(towardsVec);
		position = position + _dis * movingVec;

		center = position + towardsVec;

		glutPostRedisplay();
	}

	Camera::~Camera()
	{
	}

	void releaseCamera(Camera* _cam) {
		if (activeCamera == _cam)
			return;//you can not release the active camera

		for (list<Camera*>::iterator ite = allCameras.begin();
			ite != allCameras.end();

			) {
			if (*ite == _cam) {
				ite = allCameras.erase(ite);
				break;
			}
			else
				ite++;
		}

		delete _cam;
		_cam->id = -1;
	}

}
