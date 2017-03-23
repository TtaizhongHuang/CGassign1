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
short r = 0;
short l = 0;
void re1(void);
void re2(void);
void light1(void);
void light2(void);
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
	


glEnable(GL_LIGHTING); 
light1();
//light2();

}

/*
* GrabTexObjFromFile
*	This function will use SDL to load the specified image, create an OpenGL
*	texture object from it and return the texture object number.
*/
GLuint GrabTexObjFromFile(const std::string& fileName)
{
	/* Use SDL_image to load the PNG image. */
	SDL_Surface *Image = IMG_Load(fileName.c_str());

	/* Image doesn't exist or failed loading? Return 0. */
	if (!Image)
		return 0;

	unsigned Object(0);

	/* Generate one texture (we're creating only one). */
	glGenTextures(1, &Object);

	/* Set that texture as current. */
	glBindTexture(GL_TEXTURE_2D, Object);

	/* You can use these values to specify mipmaps if you want to, such as 'GL_LINEAR_MIPMAP_LINEAR'. */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* We're setting textures to be repeated here. */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //NEW!
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //NEW!

																  /* Create the actual texture object. */
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Image->w, Image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, Image->pixels);

	/* Free the surface, we are finished with it. */
	SDL_FreeSurface(Image);

	return Object;
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
	GLfloat tp_ambient[] = { 0.4,0.4,0.4,1 };
	GLfloat tp_diffuse[] = { 0.2,0.2,0.2,1 };
	GLfloat tp_specular[] = { 0.2,0.2,0.2,1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tp_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tp_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tp_specular);
	glutSolidSphere(0.5, 100, 100);
	//glutSolidTeapot(0.2);
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
		glutIdleFunc(re1);

		break;
	case 2:
		glutIdleFunc(re2);

		break;
	case 3:
		glutIdleFunc(light1);

		break;
	case 4:
		glutIdleFunc(light2);

		break;
	case 5:
		exit(0);
		break;
	}
}
void
re1(void) {
	glutReshapeWindow(600, 600);
	r = 0;
}
void
re2(void) {
	glutReshapeWindow(300, 300);
	r = 1;
}
void
light1(void) {
	GLfloat light_position[] = { 300,50,-100,1 };
	GLfloat ambient[] = { 0.2,0.2,0.2,1 };
	GLfloat diffuse[] = { 0.8,0.8,0.8,1 };
	GLfloat specular[] = { 0.6,0.6,0.6,1 };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	glDisable(GL_LIGHT2);
	glEnable(GL_LIGHT1);
	glClearColor(0.3, 0.4, 0.8, 0.1);
	glShadeModel(GL_SMOOTH);
	glutDisplayFunc(Display);

}
void
light2(void) {
	GLfloat light_position2[] = { -150,90,-50,1 };
	GLfloat ambient2[] = { 0.4,0.3,0.3,1 };
	GLfloat diffuse2[] = { 0.6,0.6,0.6,1 };
	GLfloat specular2[] = { 0.8,0.5,0.5,1 };
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular2);

	glDisable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glClearColor(0.3, 0.4, 0.8, 0.1);
	glShadeModel(GL_SMOOTH);
	glutDisplayFunc(Display);

}

int
main(int argc, char **argv)
{
	glutInitWindowSize(600, 600);//<--------------This design doesnt work
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("CG-Project");
	Init();



	
	//glutReshapeFunc(Reshape);
	glutKeyboardFunc(Key);
	moving = GL_TRUE;
	glutIdleFunc(Animate);
	glutVisibilityFunc(Visible);
	glutCreateMenu(menuSelect);//<-----------pop up menu.
	glutAddMenuEntry("600X600", 1);
	glutAddMenuEntry("300X300", 2);
	glutAddMenuEntry("Light1", 3);
	glutAddMenuEntry("Light2", 4);
	glutAddMenuEntry("Quit", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;             /* ANSI C requires main to return int. */
}
