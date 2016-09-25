#pragma once
#include"globalDefine.h"

namespace gg {

	class Camera
	{
	private:

		vmath::vec3 towardsVec;
		vmath::vec3 rightVec;
		vmath::vec3 upVec;
		vmath::vec3 constUpVec;

	protected:

		vmath::vec3 position;
		vmath::vec3 up;
		vmath::vec3 center;

		int id;
		static int idIndex;
		
	public:
		virtual void setActive() = 0;

		//gardenGDK gives flexibility, but donot courage users to use follow functions:
		vmath::vec3 getPosition() {
			return position;
		}
		void setPosition(vmath::vec3 _pos) {
			position = _pos;
		}
		void setUp(vmath::vec3 _up) {
			up = _up;
		}
		void setCenter(vmath::vec3 _center) {
			center = _center;
		}
		//

		int getId() {
			return id;
		}

		Camera(vmath::vec3 _position, vmath::vec3 _center, vmath::vec3 _up);

		Camera(const Camera& _rhs) :
			position(_rhs.position),
			up(_rhs.up),
			center(_rhs.center)
			//...
		{
			id = idIndex++;
		}

		virtual ~Camera() = 0;

		virtual void fowardMove(float _dis);
		virtual void horizontalMove(float _dis);
		virtual void verticalRotate(float _angle);
		virtual void horizontalRotate(float _angle);

		friend void releaseCamera(Camera* _cam);

	};


}

