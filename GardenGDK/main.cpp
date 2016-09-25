#include"gardenGDK.h"

#include"LoadShaders.h"
#include"vapp.h"
#include"vutils.h"
#include"vbm.h"

using namespace vmath;
using namespace std;
using namespace gg;

ObjFile* teapot;
PerspectiveCamera* camera;
PointLight* light0;
DirectionalLight* light1;
DirectionalLight* light2;
SpotLight* pLight1;
HemisphereLight* hlight;

float screenWidth = 512.0f;
float screenHeight = 512.0f;

void init() {

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "teapot_vs.shader" },
		{ GL_FRAGMENT_SHADER,"garden_fs.shader" },
		{ GL_NONE,NULL },
	};

	program = LoadShaders(shaders);
	glUseProgram(program);

	gardenInit();//call it after shader setting

	Material teapotMaterial(vec3(0.9f, 0.3f, 0.1f), 20.0f, 0.5f);
	teapot = createObjFile(string("C:\\teapot2.obj"), teapotMaterial);

	camera = createPerspectiveCamera(
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 0.0f, -1.0f),
		vec3(0.0f, 1.0f, 0.0f),
		-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 500.0f
	);

	defaultLight->setInactive();//do no use the default light here.
	
	hlight = createHemisphereLight(vec3(0.0f,1.0f,0.0f),vec3(0.6f,0.6f,0.6f),vec3(0.0f,0.0f,0.0f));
	hlight->setActive();

	light0 = createPointLight();
	light0->setActive();

	teapot->multiMatrix(rotate(30.0f, vec3(1.0f, 0.0f, 0.0f)));
	teapot->multiMatrix(translate(vec3(5.0f, 0.0f, 0.0f)));
	teapot->multiMatrix(translate(vec3(5.0f,-30.0f,-120.0f)));

	camera->setActive();//gardenGDK has a default camera. we do not use it now.
	releaseCamera(defaultCamera);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	camera->setActive();
	teapot->draw();
	
	glFlush();

}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	screenHeight = (float)h;
	screenWidth = (float)w;
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA);

	glutInitWindowSize(512, 512);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(argv[0]);

	glewExperimental = GL_TRUE;
	if (glewInit()) {
		std::cerr << "Unable to initialize GLEW" << endl;
		exit(EXIT_FAILURE);
	}

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	init();

	glutKeyboardFunc(myKeyboard);
	glutKeyboardUpFunc(myKeyboardUp);
	glutSpecialFunc(mySpecial);
	glutSpecialUpFunc(mySpecialUp);
	glutIdleFunc(idle);

	glutMainLoop();

	gardenRelease();
}