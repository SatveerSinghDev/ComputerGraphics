#include <GL/glut.h>
float xx = 0, yy = 0; 

//user key-pressing function
void Key(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_UP:
			yy++;
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
			yy--;
			glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT:
			xx--;
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			xx++;
			glutPostRedisplay();
			break;
			default:break;
	}
}
//display function according to key press
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 2, 4);
	
	glBegin(GL_QUADS);
	glVertex2f(300+xx, 200+yy);
	glVertex2f(400+xx, 200+yy);
	glVertex2f(400+xx, 300+yy);
	glVertex2f(300+xx, 300+yy);
	glEnd();
	
	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(700, 70);
	glutCreateWindow("Square Moving");
	
	glutDisplayFunc(display);
	
	glClearColor(0, 0, 0, 0);
	gluOrtho2D(0.0, 400, 0.0, 400);
	glutSpecialFunc(Key);
	
	glutMainLoop();
	
	return 0;
}


