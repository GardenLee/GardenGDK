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

		//ˮƽ��ת��constUpVecΪ�ᣬ���ἴ�������ʱ�����upVec���Ҳ���ı�
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

		//��ֱ��ת��rightVecΪ��
		vmath::mat4 rotateMatrix(vmath::rotate(_angle, rightVec));

		vmath::vec3 _towardsVec = vmath::vec3(rotateMatrix * vmath::vec4(towardsVec, 1.0f));
		vmath::vec3 _upVec = vmath::vec3(rotateMatrix * vmath::vec4(upVec, 1.0f));

		//��������ܵ�������������������ܶ����ţ��������ҵߵ�
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
