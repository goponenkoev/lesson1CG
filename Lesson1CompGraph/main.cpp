//Jeff Chastine
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

using namespace std;
GLsizei Height, Width;

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
	// Teapot
	glPushMatrix();	
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.55f);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glutSolidTeapot(0.1f);
	glPopMatrix();
	// Torus
	glPushMatrix();	
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.55f);
	glutWireTorus(0.08f, 0.3f, 45.0f, 10.f);
	glPopMatrix();
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