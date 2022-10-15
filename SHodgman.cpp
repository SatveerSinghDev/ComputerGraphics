#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
using namespace std;
float xPos=-10;

struct point {
	int x;
	int y;
	point(){
		x = 1;
		y = 1;
	}
	point(int x1,int y1){
		x = x1;	
		y = y1;
	}
};

struct upoint{
	int i;
	point x;
	upoint(int index,point x1){
		i = index;
		x = x1;
	}
};

vector<int> rm;
vector<upoint> ins;
vector<point> p;
vector<point> initP;

point boundary[4];

const string boundType[4] = {"LEFT","RIGHT","TOP","BOTTOM"};


bool dup(point x)		//for duplicate
{
	for(point t : p)
		if(t.x == x.x && t.y == x.y)
			return true;
	
	return false;
}
void update()			//update clipping
{
	for(int t : rm){
		p.erase(p.begin() + t);
	}	
	for(upoint t : ins){
		if(!dup(t.x)) 
			p.insert(p.begin() + t.i,t.x);
	}
	ins.clear();
	rm.clear();
}
void show()
{
	
	for(point t : p){
		glVertex2i(t.x+200,t.y);
	}
	glVertex2i(p[0].x+200,p[0].y);	
}
void showInit()
{
	for(point t : initP){
		glVertex2i(t.x,t.y);
	}
	glVertex2i(initP[0].x,initP[0].y);

}
void showBound(int shift)
{
	for (int i = 0; i <4; i++)
		glVertex2i(boundary[i].x + shift,boundary[i].y);
}
bool inside(point p,int xmin,int ymin,int xmax,int ymax,string edge)
{
	if(edge == "LEFT"){
		if(p.x < xmin)
			return false;
	}
	else if (edge == "RIGHT"){
		if(p.x > xmax )
			return false;
	}
	else if (edge == "TOP"){
		if(p.y > ymax)
			return false;

	}
	else if (edge == "BOTTOM"){
		if(p.y < ymin)
			return false;
	}
	return true;
	
}
point intercept(int xmin,int ymin,int xmax,int ymax,point p1,point p2,string edge)
{
	int x0 = p1.x,
		y0 = p1.y,
		x1 = p2.x,
		y1 = p2.y;
	int x = 0,y = 0;
	if(edge == "LEFT")
	{
		x = xmin;
		y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
		return point(x,y);
	}
	else if(edge == "RIGHT")
	{
		y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
		x = xmax;		
		return point(x,y);	
	}
	else if(edge == "TOP")
	{
		x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
		y = ymax;
		return point(x,y);
	}
	else
	{
		x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
		y = ymin;
		return point(x,y);
	}
}
void SH(int xmin,int ymin,int xmax,int ymax,string edge)
{		
		int n = p.size();
		for (int i = 0,j = 1; i < n; i++,j++)
		{
			if(j == n)
				j = 0;
				
			if(edge == "LEFT"){
				if(inside(p[i],xmin,ymin,xmax,ymax,edge)){
					if(( inside(p[j],xmin,ymin,xmax,ymax,edge)));
					else
					{
						
						if(j<i)
							p.push_back(intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge));
						else
							ins.push_back(upoint(j,intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge)));
						
					}
				}else
					if(inside(p[j],xmin,ymin,xmax,ymax,edge))
					{	
						
						ins.push_back(upoint(i,intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge)));
						rm.push_back(i);
					}	
			}
			if(edge == "RIGHT"){
				if(inside(p[i],xmin,ymin,xmax,ymax,edge)){
					if(( inside(p[j],xmin,ymin,xmax,ymax,edge)));
					else
					{
						
						if(j<i)
							p.push_back(intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge));
						else
							ins.push_back(upoint(j,intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge)));
						
					}
				}else
					if(inside(p[j],xmin,ymin,xmax,ymax,edge))
					{	
						//cout<<"\nelse if1\n";
						ins.push_back(upoint(i	,intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge)));
						rm.push_back(i);
					}	
			}
			if(edge == "TOP"){
				
				if(inside(p[i],xmin,ymin,xmax,ymax,edge)){
					if(( inside(p[j],xmin,ymin,xmax,ymax,edge)));
					else
					{
						
						if(j<i)
							p.push_back(intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge));
						else
							ins.push_back(upoint(j,intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge)));
						
					}
				}else
					if(inside(p[j],xmin,ymin,xmax,ymax,edge))
					{	
						
						ins.push_back(upoint(i	,intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge)));
						rm.push_back(i);
					}	
			}
			if(edge == "BOTTOM"){
				if(inside(p[i],xmin,ymin,xmax,ymax,edge)){
					if(( inside(p[j],xmin,ymin,xmax,ymax,edge)));
					else
					{
						cout<<"\nelse1\n";
						if(j<i)
							p.push_back(intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge));
						else
							ins.push_back(upoint(j,intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge)));
						
					}
				}else
					if(inside(p[j],xmin,ymin,xmax,ymax,edge))
					{	
						
						cout<<"\nelse if1\n";
						ins.push_back(upoint(i	,intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge)));
						rm.push_back(i);
					}	
			}
			
		}
		update();
		
	

}
void SHCheck()
{
	
	int xmin = boundary[0].x,
		ymin = boundary[0].y,
		xmax = boundary[2].x,
		ymax = boundary[1].y;

	for( auto s:boundType)
		SH(xmin,ymin,xmax,ymax,s);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity(); 

	glPointSize(10.0);
	glBegin(GL_POLYGON);
		showInit();
	glEnd(); 

	glBegin(GL_POLYGON);
		show();
	glEnd(); 

	glBegin(GL_LINE_LOOP);
		glColor3i(0,0,0);
		showBound(0);
	glEnd(); 

	glBegin(GL_LINE_LOOP);
		glColor3i(0,0,0);
		showBound(200);
	glEnd(); 

	
	
	glutSwapBuffers(); 
}
void reshape(int width,int height)
{
	
	glViewport(2,2,(GLsizei)width,(GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	int plane = 500;
	gluOrtho2D(0,plane,0,plane);
	glMatrixMode(GL_MODELVIEW);
	
}
void init()
{
	glClearColor(1.0,0.0,0,1.0);
}
int main(int argc,char** argv)
{
	p.push_back(point(100,150));
	p.push_back(point(200,250));
	p.push_back(point(300,200));
	
	boundary[0] = point(150,150);
	boundary[1] = point(150,200);
	boundary[2] = point(200,200);
	boundary[3] = point(200,150);
	
	

	
	initP = p;
	SHCheck();
	
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


