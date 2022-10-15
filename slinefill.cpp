#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
 void move (int a) ;
void output(int x, int y, char *string)
{
  int len, i;
  glColor3f(0,0,0);                                                    
  glRasterPos2f(x, y);                                                
  len = (int) strlen(string);                                        
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);    
                                                                  
  }
}

int le[500], re[500], flag=0 ,m,i;
int t=0;

	void init()
	{	glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		gluOrtho2D(0, 500, 0, 500);
	}


	void edge(int x0, int y0, int x1, int y1)
	{
		if (y1<y0)
		{
			int tmp;
			tmp = y1;
			y1 = y0;
			y0 = tmp;
			tmp = x1;
			x1 = x0;
			x0 = tmp;
		}
		int x = x0;
		m = (y1 - y0) / (x1 - x0);
		for (int i = y0; i<y1; i++)
		{
			if (x<le[i])
				le[i] = x;
			if (x>re[i])
				re[i] = x;
			x += (1 / m);
		}
	}

	void display()
	{
		output(0,450,"Polygon filling will start in 3,2,1..");
		glColor3f(0, 0, 1);
		glBegin(GL_LINE_LOOP);
		glVertex2f(200, 100);
		glVertex2f(100, 200);
		glVertex2f(200, 300);
		glVertex2f(300, 200);
		glEnd();
			
				if (le[t] < re[t])
				{
					for (int j = le[t]; j < re[t]; j++)
					{
						glColor3f(1, 0, 0);
						glBegin(GL_POINTS);
						glVertex2f(j, t);
						glEnd();
					}
				}
		glFlush();
	}

	int main(int argc, char **argv)
	{

			for (int i = 0; i<500; i++)
		{
			le[i] = 500;
			re[i] = 0;
		} 
		
		edge(200, 100, 100, 200);
		edge(100, 200, 200, 300);
		edge(200, 300, 300, 200);
		edge(300, 200, 200, 100);
		
		glutInit(&argc, argv);
		glutInitWindowPosition(300, 100);
		glutInitWindowSize(500, 500);
		glutCreateWindow("scan line");
		init();

		glutDisplayFunc(display);
		    glutTimerFunc(0,move,0);

		glutMainLoop();
	}

void move (int a)
	{
		glutPostRedisplay(); 
		glutTimerFunc(1000/60,move,0);
              if(t<500)
              t++;   
	}
