/*
Work in 2D.  Write a function to draw a curve(L,B) using bezier algorithm. 
4 control points will be (0,0), (B+B/2,L/4), (B+B/2,3*L/4), (0,L). This would look like half petal of a flower.
    2. Use transformation to create a full petal.
    3. use transformation to create a flower with six petals.
    4. Use transformation to create a set of 10 random sized, random located flowers.
*/

#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#define MAX_CPTS  25
#define PI 3.14


GLfloat cpts[MAX_CPTS][3];
int xyzt = 0;
static int x_len = 500, y_len = 500;
float l, b;
int maxx_len, maxy_len;
int count = 0;

float scale = 1;

void point_adding(float l, float b) {

	cpts[xyzt][0] = (l * scale) / maxy_len;
	cpts[xyzt][1] = (b*scale) / maxx_len;
	cpts[xyzt][2] = 0.0;
	xyzt++;
}

void aip() {
	point_adding(0, 0);
	point_adding(b + b / 2, l / 4);
	point_adding(b + b / 2, 3 * (l / 4));
	point_adding(0, l);
}
void curve_drawing()
{
	int i;
	for (i = 0; i < xyzt - 3; i += 3)
	{
		/* draw the curve using OpenGL evaluators */

		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, cpts[i]);
		glMapGrid1f(30, 0.0, 1.0);
		glEvalMesh1(GL_LINE, 0, 30);
	}
	glFlush();
}


void petal_adding() {
	glPushMatrix();
	glScalef(-1, 1, 1);
	curve_drawing();
	glPopMatrix();
	curve_drawing();
}

float getter_rad(float degree) {
	return (degree * PI) / 180;
}

void petal_addingAtAngele(float angle) {
	//float angle = getter_rad(degree);
	glPushMatrix();
	glRotatef(angle, 0, 0, 1);
	petal_adding();
	glPopMatrix();
}


void draw_flwr(int n) {
	int angle = 0;
	int delta_angle = (360.0) / n;

	for (int i = 0; i < n; i++) {
		petal_addingAtAngele(angle + i * delta_angle);
	}
}


void display()
{
	int i, upper = .5, lower = 0;
	glClear(GL_COLOR_BUFFER_BIT);

	for (int j = 0; j < 3; j++)
	{
		glBegin(GL_POINTS);
		for (i = 0; i < xyzt; i++)
		{
			glVertex3fv(cpts[i]);
		}

		glEnd();
		draw_flwr(6);

		glTranslatef(-.5, 0, 0);
	}
	for (int j = 0; j < 3; j++)
	{
		glBegin(GL_POINTS);
		for (i = 0; i < xyzt; i++)
		{
			glVertex3fv(cpts[i]);
		}

		glEnd();
		draw_flwr(6);

		glTranslatef(.5, .5, 0);
	}
	for (int j = 0; j < 3; j++)
	{
		glBegin(GL_POINTS);
		for (i = 0; i < xyzt; i++)
		{
			glVertex3fv(cpts[i]);
		}

		glEnd();
		draw_flwr(6);

		glTranslatef(-.5, -.5, 0);
	}

	glFlush();
}

void reshape(int w, int h)
{
	x_len = w;
	y_len = h;

	maxx_len = w > h ? w : h;
	maxy_len = maxx_len;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);

	xyzt = 0;
	aip();
	glutPostRedisplay();
}



void addReflection() {

}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q': case 'Q':
		exit(0);
		break;
	case 'c': case 'C':
		xyzt = 0;
		glutPostRedisplay();
		break;
	case 'r': case 'R':
		aip();
		addReflection();
		glutPostRedisplay();
		break;
	case 'd': case 'D':
		curve_drawing();
		break;
	case 'i': case 'I':
		scale = scale * 2;
		xyzt = 0;
		aip();
		addReflection();
		glutPostRedisplay();
		curve_drawing();
		break;

	case 'o': case 'O':
		scale = scale / 2;
		xyzt = 0;
		aip();
		addReflection();
		glutPostRedisplay();
		curve_drawing();
		break;
	}
}

int main(int argc, char **argv)
{

	printf("Enter the value of L and B");
	scanf("%f %f", &l, &b);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(x_len, y_len);
	glutCreateWindow("curves");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(5.0);
	glEnable(GL_MAP1_VERTEX_3);
	glutMainLoop();
}
