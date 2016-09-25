//about keyboard:
#include<stdlib.h>
#include"globalDefine.h"
#include"PerspectiveCamera.h"

namespace gg {

	bool Wdown = false;
	bool Ddown = false;
	bool Sdown = false;
	bool Adown = false;
	bool UPdown = false;
	bool DOWNdown = false;
	bool RIGHTdown = false;
	bool LEFTdown = false;

	void myKeyboard(unsigned char _c, int _x, int _y) {
		switch (_c) {
		case 'w':
			Wdown = true; break;
		case 's':
			Sdown = true; break;
		case 'a':
			Adown = true; break;
		case 'd':
			Ddown = true; break;
		default: 
			break;
		}
	}

	void myKeyboardUp(unsigned char _c, int _x, int _y) {
		if (_c == 27)
			exit(0);
		switch (_c) {
		case 'w':
			Wdown = false; break;
		case 's':
			Sdown = false; break;
		case 'a':
			Adown = false; break;
		case 'd':
			Ddown = false; break;
		default:
			break;
		}
	}

	void mySpecial(int _k, int _x, int _y) {
		switch (_k) {
		case GLUT_KEY_UP:
			UPdown = true; break;
		case GLUT_KEY_DOWN:
			DOWNdown = true; break;
		case GLUT_KEY_RIGHT:
			RIGHTdown = true; break;
		case GLUT_KEY_LEFT:
			LEFTdown = true; break;
		}
	}

	void mySpecialUp(int _k, int _x, int _y) {
		switch (_k) {
		case GLUT_KEY_UP:
			UPdown = false; break;
		case GLUT_KEY_DOWN:
			DOWNdown = false; break;
		case GLUT_KEY_RIGHT:
			RIGHTdown = false; break;
		case GLUT_KEY_LEFT:
			LEFTdown = false; break;
		}
	}

	void idle() {
		if (UPdown == true)
			activeCamera->verticalRotate(0.05f);
		if (DOWNdown == true)
			activeCamera->verticalRotate(-0.05f);
		if (LEFTdown == true)
			activeCamera->horizontalRotate(0.05f);
		if (RIGHTdown == true)
			activeCamera->horizontalRotate(-0.05f);
		if (Wdown == true)
			activeCamera->fowardMove(0.05f);
		if (Sdown == true)
			activeCamera->fowardMove(-0.05f);
		if (Ddown == true)
			activeCamera->horizontalMove(0.05f);
		if (Adown == true)
			activeCamera->horizontalMove(-0.05f);
	}

}