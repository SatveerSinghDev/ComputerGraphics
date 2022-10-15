#include <iostream>
#include <math.h>
#include <GL/glut.h>
using namespace std;
struct point{
	double x;
	double y;
};
point P[4];
	
void BezierCurve(point P[4])
{
	
		double x = 0.0,y = 0.0;
		for (double t = 0.0; t <=1.0; t += 0.0005 )
		{
			x = P[0].x * pow((1 - t),3) + P[1].x * ((3 * t)*(pow((1 - t),2)))
				+ P[2].x * ((3 * pow(t,2))*(1 - t)) + P[3].x * (pow(t,3));
			y = P[0].y * pow((1 - t),3) + P[1].y * ((3 * t)*(pow((1 - t),2)))
				+ P[2].y * ((3 * pow(t,2))*(1 - t)) + P[3].y * (pow(t,3));

			glVertex2d(x,y);
			cout<<"\tx:"<<x<<"\ty:"<<y;
			cout<<endl;
		}
		
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity(); 

	glPointSize(1.0);
	glBegin(GL_POINTS);
		BezierCurve(P);
	glEnd(); 
	
	glutSwapBuffers(); 
}
void reshape(int width,int height) 
{
	glViewport(2,2,(GLsizei)width,(GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	gluOrtho2D(-10,10,-10,10);
	glMatrixMode(GL_MODELVIEW);
	
}

void init()
{
	glClearColor(1.0,0.0,0,1.0);
}

int main(int argc,char** argv)
{
	cout<<"Enter Vertices:\n";
	
	for (int i = 0; i <4 ; i++)
	{
		cout<<endl;
		cout<<"\tx:";	cin>>P[i].x;
		cout<<"\ty:";	cin>>P[i].y;
	}
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(200,100);
	glutInitWindowSize(500,500);
	
	glutCreateWindow("Window 1");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape); 
	init() ;
	glutMainLoop();
}



