/* Link the libraries code-wise. */
#ifdef _MSC_VER
#	pragma comment(lib, "OpenGL32.lib")
#	pragma comment(lib, "GLu32.lib")

#	pragma comment(lib, "SDL.lib")
#	pragma comment(lib, "SDLmain.lib")
#	pragma comment(lib, "SDL_image.lib")
#endif //_MSC_VER

#include <string>
#include <cmath>
#include <GL/glut.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>

#define PI 3.141592653589793

unsigned Textures[3];
unsigned BoxList(0);					//Added!

										/* These will define the player's position and view angle. */
double X(0.0), Y(0.0), Z(0.0);
double ViewAngleHor(0.0), ViewAngleVer(0.0);

GLboolean moving;
//int X = 400;
//int Y = 300;

void
InitFishs(void)
{

}
void
Animate() {
	return;
}
void
Init(void){
GLfloat light_position[] = { 0,50,-100,1 };
GLfloat ambient[] = { 0.2,0.2,0.2,1 };
GLfloat diffuse[] = { 0.8,0.8,0.8,1 };
GLfloat specular[] = { 1,0.6,0.6,1 };
glLightfv(GL_LIGHT1, GL_POSITION, light_position);
glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
glEnable(GL_LIGHTING); glEnable(GL_LIGHT1);
glClearColor(0.3, 0.4, 0.8, 0.1);
glShadeModel(GL_SMOOTH);
}

void
Reshape(int width, int height)//<----no use so far
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(400.0, 2.0, 10000.0, 400000.0);
	glMatrixMode(GL_MODELVIEW);
}


/* ARGSUSED1 */
void
Key(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:           /* Esc will quit */
		exit(1);
		break;
	case ' ':          /* space will advance frame */
		if (!moving) {
			Animate();
		}
	}
}



void
Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	GLfloat tp_ambient[] = { 0.05,0.05,0.05,1 };
	GLfloat tp_diffuse[] = { 0.7,0.3,1,1 };
	GLfloat tp_specular[] = { 0.6,0.6,0.6,1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tp_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tp_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tp_specular);
	glutSolidTeapot(0.2);
	glFlush();
}

void
Visible(int state)
{
	if (state == GLUT_VISIBLE) {
		if (moving)
			glutIdleFunc(Animate);
	}
	else {
		if (moving)
			glutIdleFunc(NULL);
	}
}

void
menuSelect(int value)
{
	switch (value) {
	case 1:
		//X = 500;
		//Y = 250;
		break;
	case 2:
		//X = 400;
		//Y = 300;
		break;
	case 3:
		exit(0);
		break;
	}
}

int
main(int argc, char **argv)
{
	glutInitWindowSize(400, 300);//<--------------This design doesnt work
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("CG-Project");
	Init();
	glutDisplayFunc(Display);
	//glutReshapeFunc(Reshape);
	glutKeyboardFunc(Key);
	moving = GL_TRUE;
	glutIdleFunc(Animate);
	glutVisibilityFunc(Visible);
	glutCreateMenu(menuSelect);//<-----------pop up menu.
	glutAddMenuEntry("500X250", 1);
	glutAddMenuEntry("400X300", 2);
	glutAddMenuEntry("Quit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;             /* ANSI C requires main to return int. */
}
