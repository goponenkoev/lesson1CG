//Jeff Chastine
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL/GLAux.h>
#include <iostream>

using namespace std;
GLsizei Height, Width;
unsigned int photo_tex;
AUX_RGBImageRec* photo_image;

unsigned int torus_tex;
AUX_RGBImageRec* torus_image;

void changeViewPort(int width, int height)
{
	if (height == 0)									
	{
		height = 1;										
	}
	glViewport(0, 0, width, height);
}

GLvoid Draw(GLvoid)									
{
	// Dodecahedron
	glPushMatrix();		
	glTranslatef(-0.7f, 0.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);			
	glColor3f(0.7f, 0.25f, 0.55f);				
	glScalef(0.1,0.1,0.14);
	glutWireDodecahedron();							
	glPopMatrix();	
	// Dodecahedron
	glPushMatrix();		
	glTranslatef(0.5f, 0.0f, 0.0f);
	glRotatef(60.0f, 0.0f, 0.0f, 1.0f);			
	glColor3f(1.0f, 0.0f, 0.9f);	
	glutWireCone(0.1f,0.5f,45.0f,10.0f);							
	glPopMatrix();	
	// Torus
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, photo_tex );
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidTorus(0.08f, 0.3f, 45.0f, 10.f);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	// Teapot
	glBindTexture(GL_TEXTURE_2D, torus_tex );
	glPushMatrix();	
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidTeapot(0.1f);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	//drawTorus();
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Draw();
	glutSwapBuffers();
}

int main(int argc, char* argv[]) {

	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Hello, GL");

	photo_image = auxDIBImageLoad("E://5.bmp");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &photo_tex);
	glBindTexture(GL_TEXTURE_2D, photo_tex );
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 
		photo_image->sizeX,
		photo_image->sizeY,
		0, GL_RGB, GL_UNSIGNED_BYTE,
		photo_image->data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	torus_image = auxDIBImageLoad("E://7.bmp");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &torus_tex);
	glBindTexture(GL_TEXTURE_2D, torus_tex );
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 
		torus_image->sizeX,
		torus_image->sizeY,
		0, GL_RGB, GL_UNSIGNED_BYTE,
		torus_image->data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glutReshapeFunc(changeViewPort);
	glutDisplayFunc(render);
	GLenum err = glewInit();

	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}

	glutMainLoop();
	return 0;
}