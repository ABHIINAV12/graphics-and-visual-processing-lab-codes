// organize and stay in moment -- Abhinav IIITA
/*
 Write a program to extrude following 3D shapes from basic 2D shapes:
        A Cylinder of height (Y axis) 5H from a circle of radius R. 
		Calculate 48 points. At h=0H, 1H, 2H, 3H, 4H and 5H   for angle=0,45,90,135,180,225,270 and 315.
        Don't use inbuilt function to render the cylinder. Draw curved lines to connect the points. 
		Implement Curved line function of your own using bezier curves.
*/
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

#define PI 3.1415927

// function to draw curve

void drawCurve(float x0,float y0,float x1,float y1,float h0,float angle)
{
    glPushMatrix();
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);

    double x[]={x0,(x0+x1+0.05*(x0+x1>0?1:-1))/2,(x0+x1+0.05*(x0+x1>0?1:-1))/2,x1};
    double y[]={y0,(y0+y1+0.05*(y0+y1>0?1:-1))/2,(y0+y1+0.05*(y0+y1>0?1:-1))/2,y1};

	double xu = 0.0 , yu = 0.0, u = 0.0 ; 
	int i = 0 ; 
	for(u = 0.0 ; u <= 1.0 ; u += 0.0001) { 
		xu = pow(1-u,3)x[0]+3*u*pow(1-u,2)*x[1]+3*pow(u,2)(1-u)*x[2]+pow(u,3)*x[3]; 
		yu = pow(1-u,3)y[0]+3*u*pow(1-u,2)*y[1]+3*pow(u,2)(1-u)*y[2]+pow(u,3)*y[3]; 
        glVertex3f(xu,yu,h0);
	} 

    glEnd();
    glPopMatrix();
    glLineWidth(1.0);
}

void draw_cylinder(GLfloat radius,GLfloat height,GLubyte R,GLubyte G,GLubyte B){
    GLfloat x = 0.0;
    GLfloat y = 0.0;
    GLfloat angle = 0.0;
    GLfloat angle_stepsize = M_PI/4;
    glColor3ub(R-40,G-40,B-40);
    for (float h=0;h<height;h+=height/5){
        angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glBegin(GL_LINES);
            glVertex3f(x, y , h);
            glVertex3f(x, y , h+height/5);
            glEnd();
            angle = angle + angle_stepsize;
            drawCurve(x,y,radius * cos(angle),radius * sin(angle),h,PI/4);
        }
    }
    angle = 0.0;
    while( angle < 2*PI ) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        angle = angle + angle_stepsize;
        drawCurve(x,y,radius * cos(angle),radius * sin(angle),height,PI/4);
    }
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0,-0.4,-3.0);
    glRotatef(-40, 1.0, 0.0, 0.0);
    draw_cylinder(0.3, 1.0, 255, 160, 100);
    glFlush();
}

void reshape(int width, int height){
    if (width == 0 || height == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, (GLdouble)width/(GLdouble)height,0.6, 25.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, width, height);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,640);
    glutCreateWindow("TEST");
    glClearColor(0.0,0.0,0.0,0.0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
