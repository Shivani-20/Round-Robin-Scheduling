#include <glut.h>
#include <stdio.h>
#include<conio.h>
#include<string.h>


using namespace std;

int arrival[8] = { 0 }, i = 0, j = -90, burst[8],burst1[8], p = 0, l = -90, TQ = 0, np; int i1 = 0, i2 = 0, h = 1, h1 = 1; 
int ready[40][3]; int finished[30]; int comp_time[8],tat[8],wt[8];

void myKey(unsigned char key, int x, int y);
void arri(unsigned char key, int x, int y);
void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GLUT_SINGLE | GLUT_RGB);
	glLoadIdentity();
	glOrtho(-90.0, 100.0, -15.0, 100.0, 0.0, 1.0);

}
void renderbitmap(float x, float y, void *font, char *string)
{
	char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);
}
//to reset no. of processes
void reset(unsigned char key, int x, int y)
{
	if ((key == 'r') || (key == 'R'))
	{
		glRasterPos2f(20,90);//same line
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, key);
        glutKeyboardFunc(myKey);
	}
}
void displayText1(float x, float y, char *string) {
	char * ch;

	glColor3f(0.1f, 0.1f, 0.1f);
	glRasterPos2f(x, y);

	for (ch = string; *ch; ch++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)*ch);
	}
}
void displayText(float x, float y, char *string) {
	char * ch;

	glColor3f(0.1f, 0.1f, 0.1f);
	glRasterPos2f(x, y);

	for (ch = string; *ch; ch++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)*ch);
	}
}
void calculation()
{
	int b; char buf[100] = { 0 }; char buf1[100] = { 0 };

	for (int b1 = 0; b1 < 30; b1++)
	{
		//process numbers
		finished[b1] = -1;

	}
	for (b = 1; b <= np; b++)
	{

		finished[b] = b;

	}


	
	int y = 1; int y1 = 1;
	int c; int i = 1;
	int p = np + 1;
	int sum = 0;
	while (true)
	{
		c = burst[y];
		if (c <= TQ)
		{
			burst[y] = 0;
			ready[i][0] = y;
			ready[i][1] = c;
			sum = sum + c;
			ready[i][2] = sum;
			++i;
			y = finished[++y1];
			if (y == -1)
				break;
		}
		else
		{
			burst[y] = burst[y] - TQ;
			ready[i][0] = y;
			ready[i][1] = TQ;
			sum = sum + TQ;
			ready[i][2] = sum;
			++i;
			finished[p] = y;
			++p;
			y = finished[++y1];
		}
	}
	int w; int a = -64;  b = 5;
	for (int j = 1; j < i; j++)
	{
		w = ready[j][1];
		if (ready[j][2] >9)
			b = 6;

		if (j % 2 == 0)
		{
			glColor3f(0.0f, 0.0f, 0.0f);
			glRecti(a, 13, (b*w) + a, 16);

		}
		else
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glRecti(a, 13, (b*w) + a, 16);

		}
		glRasterPos2f((a + (a + (b*w))) / 2, 10);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 48 + ready[j][0]);


		a = (b*w) + a;

	}
	glColor3f(0.1f, 0.1f, 0.1f);
	sprintf_s(buf, "---process numbers");

	renderbitmap(70, 10, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	int h = 1;
	while (h <= np)
	{
		int max = 0;
		for (int y = 1; y < i; y++)
		{
			if ((ready[y][2] >= max)&&(ready[y][0]==h))
				max = ready[y][2];
		}
		
		comp_time[h] = max;
		
		++h;



	}
	int sum1 = 0, sum2 = 0;float avg1,avg2;
	
	for (int h = 1; h <= np; h++)
	{
		tat[h] = comp_time[h] - arrival[h];
		wt[h] = tat[h] - burst1[h];
		sum1 = sum1 + tat[h];
		
		sum2 = sum2 + wt[h];
	
	
	}
	
	avg1 = (float)sum1 / np;
	avg2 = (float)sum2 / np;

	sprintf_s(buf, "average turn-around time:");

	renderbitmap(-90, 4, GLUT_BITMAP_TIMES_ROMAN_24, buf);

	snprintf(buf, 100, "FPS: %.1f", avg1);
	displayText(-50, 4, buf);
	


	sprintf_s(buf1, "average waiting time:");

	renderbitmap(-90, 0, GLUT_BITMAP_TIMES_ROMAN_24, buf1);
	snprintf(buf1, 100, "FPS: %.1f", avg2);
	displayText1(-50, 0, buf1);


}
//for final output in the next page
void result()
{
	glColor3f(0.f, 0.f, 0.f);
	
	int w = 0,w1; int q = 0; int y = 0;
	while (w <= 25)
	{
		w1 = w;
		while (w1 > 9)
		{
			y = w1 / 10;
			glRasterPos2f(-65 + q, 20);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 48 + y);

			w1 = w1 % 10;
			++q;
		}
		glRasterPos2f(-65 + q, 20);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 48 + w1);
		q = q + 5;
		++w;
	}
		glBegin(GL_LINES);
		glVertex2d(-64,18);
		glVertex2d(77,18);
		glEnd();
		calculation();
	
}
//for time quantum
void time_q(unsigned char key, int x, int y)
{
	char buf[100] = { 0 };
	glColor3f(0.f, 0.f, 0.f);
	if ((key == '1') || (key == '2') || (key == '3'))
	{
		glRasterPos2f(-16, 30); // jumb to next line
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, key);
		TQ = key - '0';

	}
	if (key == 'E')
	{
		
		
		sprintf_s(buf, "GANTT CHART:");

		renderbitmap(-90, 20, GLUT_BITMAP_TIMES_ROMAN_24, buf);
		result();
		
	}

}

//for burst time
void burs(unsigned char key, int x, int y)
{
	glColor3f(0.f, 0.f, 0.f);
	char buf[100] = { 0 };
	char buf1[100] = { 0 };
	if ((key == '1') || (key == '2') || (key == '3') || (key == '4') || (key == '5')|| (key == '6') || (key == '7'))
	{
		glRasterPos2f(-60 + i2, 80); // jumb to next line
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, key);
		i2 = i2 + 4;
		burst[h1] = key - '0';
		burst1[h1] = key - '0';

		++h1;
	}
	else if (key == 'E')
	{
		sprintf_s(buf, "Now enter time quantum time: can be 1 or 2 or 3 seconds");

		renderbitmap(-90,30, GLUT_BITMAP_TIMES_ROMAN_24, buf);
		glutKeyboardFunc(time_q);
	}
	else
	{
		glColor3f(0.9f, 0.f, 0.1f);
		sprintf_s(buf1, "wrong:");

		renderbitmap(-60 + i2, 80, GLUT_BITMAP_TIMES_ROMAN_24, buf1);
		i2 = i2 + 9;
	
	}

}

//for arrival time 
void arri(unsigned char key, int x, int y)
{

	glColor3f(0.f, 0.f, 0.f);
	char buf[100] = { 0 };
	char buf1[100] = { 0 };

	if ((key == '1') || (key == '2') || (key == '3') || (key == '4') || (key == '5') || (key == '6') || (key == '7') || (key == '0'))
	{
		glRasterPos2f(-60 + i1, 85);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, key);
		i1 = i1 + 4;
		arrival[h] = key - '0';
		++h;

	}
	else if (key == 'E')
	{
	
		sprintf_s(buf, "Now enter burst time:");

		renderbitmap(-90, 80, GLUT_BITMAP_TIMES_ROMAN_24, buf);

		glutKeyboardFunc(burs);
	}
	else
	{
		glColor3f(0.9f, 0.f, 0.1f);
		sprintf_s(buf1, "wrong:");
		
		renderbitmap(-60+i1, 85, GLUT_BITMAP_TIMES_ROMAN_24, buf1);
		i1 = i1 + 9;
		
	}
}


//to enter no. of processes.
void myKey(unsigned char ke, int x, int y)
{
	glColor3f(0.f, 0.f, 0.f);
	char buf[100] = { 0 };
	char buf1[100] = { 0 };
	if ((ke == '1') || (ke == '2') || (ke == '3') || (ke == '4') || (ke == '5'))
	{
		glRasterPos2f(-60, 90);//same line
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ke);
		np = ke - '0';

		sprintf_s(buf, "Now enter arrival time:");

		renderbitmap(-90, 85, GLUT_BITMAP_TIMES_ROMAN_24, buf);

		
		
			glutKeyboardFunc(arri);
		
	}
	else
	{
		glColor3f(0.f, 0.2f, 0.5f);
		sprintf_s(buf1, "wrong input,press R/r to reset");
		renderbitmap(-40, 90, GLUT_BITMAP_TIMES_ROMAN_24, buf1);
		glutKeyboardFunc(reset);
	}
	
}

void introscreen()
{
	glColor3f(0.3f,0.1f, 0.8f);
	char buf[100] = { 0 };
	sprintf_s(buf, "Enter no. of processes:");
	renderbitmap(-90, 90, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	


	glColor3f(1.f, 0.f, 0.f);
	sprintf_s(buf, "Press E to run program for output");
	renderbitmap(-90, 70, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	sprintf_s(buf,"Press R to reset the program,only limited to process number");
	renderbitmap(-90, 65, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	glColor3f(1.f, 1.f, 0.f);
	sprintf_s(buf, "Constraints on input:");
	renderbitmap(-90, 55, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	glColor3f(0.5f, 0.0f, 0.2f);
	sprintf_s(buf, "1. Number of processes limited to 5");
	renderbitmap(-90, 50, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	sprintf_s(buf, "2. All processes must arrive before 7 sec");
	renderbitmap(-90, 45, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	sprintf_s(buf, "3. All processes can't have same arrival time and input should be in in ascending order");
	renderbitmap(-90, 40, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	sprintf_s(buf, "4. Burst time less than or equal to 7");
	renderbitmap(-90, 35, GLUT_BITMAP_TIMES_ROMAN_24, buf);

}

void display()
{

	introscreen();
	glFlush();
	glutPostRedisplay();

}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(30, 30);
	
	glutCreateWindow("Round robin scheduling");
	init();
	glClearColor(0.7,0.6,1,0);
	glutDisplayFunc(display);
	glutKeyboardFunc(myKey); // register the key handler.
	
	glutMainLoop();
	return 0;             /* ANSI C requires main to return int. */
}