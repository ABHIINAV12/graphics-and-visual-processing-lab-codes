// IIT2018010 -- Abhinav Batta
/*
 Write a program to render an animated swing. On mouse click event, it should start to swing and gradually 
 reduce it speed to zero(use timer). 
 Try to make it  as realistic as possible.
*/

#include <stdio.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>


// set parameters
int direction=0;
float angle = 0.0;
bool pause = false;
int maxAngle=-40;


// function to rotate around a line

void rotate_around_line(GLdouble x0, GLdouble y0, GLdouble z0, GLdouble u1, GLdouble u2, GLdouble u3, GLdouble kut)
{
    double vek[3] = { u1 - x0, u2 - y0, u3 - z0 };


    glTranslatef(x0, y0, z0);
    glRotatef(-kut, vek[0], vek[1], vek[2]);
    glTranslatef(-x0, -y0, -z0);
}

// function to animate the swing

void animate(int a){
    if(direction!=-1){
        glutPostRedisplay();
        glutTimerFunc(10, animate, 1);
    }
}

// function to draw the swing

void drawSwing()
{
    glColor3f(1.0, 0.0, 1.0);
    glLineWidth(5.0);

    // Draw the ropes
    glBegin(GL_LINES);
    glVertex3d(-20, 30, 0);
    glVertex3d(-20, -30, 0);
    glVertex3d(20, 30, 0);
    glVertex3d(20, -30, 0);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);

    //Draw the top of the seat
    glBegin(GL_QUADS);
    glVertex3d(-20, -33, -10);
    glVertex3d(20, -33, -10);
    glVertex3d(20, -33, 10);
    glVertex3d(-20, -33, 10);

    glVertex3d(-20, -30, -10);
    glVertex3d(20, -30, -10);
    glVertex3d(20, -30, 10);
    glVertex3d(-20, -30, 10);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);

    // Draw the sides of the seat
    glBegin(GL_QUAD_STRIP);
    glVertex3d(20, -30, -10);
    glVertex3d(20, -33, -10);
    glVertex3d(-20, -30, -10);
    glVertex3d(-20, -33, -10);
    glVertex3d(-20, -30, 10);
    glVertex3d(-20, -33, 10);
    glVertex3d(20, -30, 10);
    glVertex3d(20, -33, 10);
    glVertex3d(20, -30, -10);
    glVertex3d(20, -33, -10);

    glEnd();
}

// function to draw the bar

void drawBar()
{
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 0.0);

    // Bottom
    glVertex3d(-50, 30, -1);
    glVertex3d(50, 30, -1);
    glVertex3d(50, 30, 1);
    glVertex3d(-50, 30, 1);
    
    // Top
    glVertex3d(-50, 33, -1);
    glVertex3d(50, 33, -1);
    glVertex3d(50, 33, 1);
    glVertex3d(-50, 33, 1);

    glColor3f(1.0, 0.65, 0.0);

    // Front
    glVertex3d(-50, 33, 1);
    glVertex3d(-50, 30, 1);
    glVertex3d(50, 30, 1);
    glVertex3d(50, 33, 1);
    // Back
    glVertex3d(50, 33, -1);
    glVertex3d(50, 30, -1);
    glVertex3d(-50, 30, -1);
    glVertex3d(-50, 33, -1);

    glColor3f(1.0, 0.0, 0.0);

    // Left
    glVertex3d(-50, 33, -1);
    glVertex3d(-50, 30, -1);
    glVertex3d(-50, 30, 1);
    glVertex3d(-50, 33, 1);
    // Right
    glVertex3d(50, 33, 1);
    glVertex3d(50, 30, 1);
    glVertex3d(50, 30, -1);
    glVertex3d(50, 33, -1);
    glEnd();
}

// finally display all stuff


static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Rotate the bar and swing
    glRotatef(60.0, 0.0, 1.0, 0.0);

    // Draw the bar
    drawBar();

    // Translate and rotate the swing to make it swing
    glTranslatef(0.0, 30.0, 0.0);
    glRotatef(angle, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -30.0, 0.0);

    // Draw the swing
    drawSwing();

    glFlush();
    glutSwapBuffers();

    // Make the it swing back or forth depending upon direction
    if (direction == 1){
        angle++;
    }
    else
        angle--;

    // Change the direction if max angle is reached
    if(abs(maxAngle)<2)
        direction=-1;
    else if (angle == maxAngle)
    {
        direction =direction^ 1;
        if(maxAngle<0){
            maxAngle=-1*maxAngle -2;
        }
        else if(maxAngle>0){
            maxAngle=-1*maxAngle+2;
        }
    }

}

// to resize the board as it swings

static void resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -150.0, 150.0);
    display();
}

int main(int argc, char *argv[])
{

    
    glutInit(&argc, argv);
    glutInitWindowSize(740, 580);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Swing");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    
    glClearColor(1, 1, 1, 1);
    glutTimerFunc(10, animate, 1);
    glutMainLoop();


    return EXIT_SUCCESS;
}
