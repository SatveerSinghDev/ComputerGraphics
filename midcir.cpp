#include <GL/glut.h>
#include <stdio.h>
void circle() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0);
	float r = 100;
	float x = 0, y = r;
	float p = 1 - r;
	glBegin(GL_POINTS);

	while (x != y) 
	{
		
		x++;
		if (p < 0) {
		   p += 2 * (x + 1) + 1;
		}
		  else {
		   y--;
		   p += 2 * (x + 1) + 1 - 2 * (y - 1);
		}
		glVertex2i(x, y);
		glVertex2i(-x, y);
		glVertex2i(x, -y);
		glVertex2i(-x, -y);

		glVertex2i(y, x);
		glVertex2i(-y, x);
		glVertex2i(y, -x);
		glVertex2i(-y, -x);

	 }
	 glEnd();
	
	 glFlush();
}
int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 600);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Line Draw OpenGL");

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-250, 250, -250, 250);
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, 500, 500);

	glutDisplayFunc(circle);
	glutMainLoop();
	return 0;
}
