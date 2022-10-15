#include <iostream>
#include <math.h>
#include <GL/glut.h>
#define M 20
#define N 20
using namespace std;
float xPos=-5;

double inputM[M][N]= { {5,-5,-5,5},{5,5,-5,-5},{1,1,1,1}} ;
double outputM[M][N];
double n = 0;
void show(double n)
{
	cout<<endl;
	double x = 0,y = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 3; j++)
			switch (j)
			{
				case 0:
					x = inputM[j][i];
					break;
				case 1:
					y = inputM[j][i];
					break;

				case 2:
					break;
			}		
		glVertex2i(x,y);
	}
}
void show2(double n)
{
	cout<<endl;
	double x = 0,y = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 3; j++)
			switch (j)
			{
				case 0:
					x = outputM[j][i];
					break;
				case 1:
					y = outputM[j][i];
					break;

				case 2:
					break;
			}		
		cout<<endl;
		glVertex2i(x,y);
	}
}
void matrixMul(double T[][N],double n1,double m1,double n,double m)
{
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < m ; k++)
		{
			double sum = 0;
			for (int j = 0; j < m ; j++)
			{
				
				sum += inputM[j][k] * T[i][j];
			}
			outputM[i][k] = sum;
		}
	}
}
void scaling(double n,double m,double dx,double dy)
{
	double S[M][N] = { {dx,0,0},
					{0,dy,0},
					{0,0,1}};
	
	matrixMul(S,3,3,n,m);
	show2(m);
}
void rotate(double n,double m,double theta)
{
	double R[M][N] = { {cos(theta),(-sin(theta)),0},
					{sin(theta),cos(theta),0},
					{0,0,1}};
	
	matrixMul(R,3,3,n,m);
	show2(m);

}
void translate(double n,double m,double dx,double dy)
{
	double T[M][N] = { {1,0,dx},
					{0,1,dy},
					{0,0,1}};
	
	matrixMul(T,3,3,n,m);
	show2(m);

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity(); 

	glPointSize(10.0);
	
	glBegin(GL_LINE_LOOP);
		show(n);	
	glEnd(); 
	
	glBegin(GL_LINE_LOOP);
		glColor3f(0,0,0);	
		rotate(3,n,0.52);
	glEnd(); 
	
	glBegin(GL_LINE_LOOP);
		glColor3f(0,0,1);	
		translate(3,n,2,2);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
		glColor3f(0,1,0);	
		scaling(3,n,2,2);
	glEnd(); 

	
	glutSwapBuffers(); 
}
void reshape(int width,int height)
{
	glViewport(2,2,(GLsizei)width,(GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	gluOrtho2D(-20,20,-20,20);
	glMatrixMode(GL_MODELVIEW);
	
}

void init()
{
	glClearColor(1.0,0.0,0,1.0);
}
int main(int argc,char** argv)
{
	n = 4;
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
