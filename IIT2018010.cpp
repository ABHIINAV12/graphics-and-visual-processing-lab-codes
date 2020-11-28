// load liberaries
/*
 WAP a program to draw two cones(see attch. image) connected along their tips and rotating along the line passing through their tips.
     hint: use glutWireCone function to daw the cone. use transformation  mechanism provided by opengl to make transformations.
*/
#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;

// define global variables

GLfloat xRotate, yRotate, zRotate1, zRotate2;

// initialization

void init(void)
{
glClearColor (0.0, 0.0, 0.0, 0.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
}

// draw cones

void Cone(void) 
{ 

  // set the global variables
  GLdouble base=1;
  GLdouble height=1.5;
  GLint slices =20;
  GLint stacks =20;
  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  // describe translation of first cone, its color and all that
  glTranslatef(0.0,1.5,-4.5);
  glColor3f(0.0,1.0,1.0); 
  glRotatef(xRotate,1.0,0.0,0.0);
  glRotatef(yRotate,0.0,1.0,0.0);
  glRotatef(zRotate1,0.0,0.0,1.0);
  glScalef(1.0,1.0,1.0);
  // draw the first cone
  glutWireCone(base,height,slices,stacks);
  glLoadIdentity();
  glTranslatef(0.0,-1.5,-4.5);
  glColor3f(0.0,1.0,1.0); 
  glRotatef(yRotate,0.0,1.0,0.0);
  // the axis of rotation of second cone with respect to first cone -1 to x and z axis
  glRotatef(-1*xRotate,1.0,0.0,0.0);
  glRotatef(-1*zRotate2,0.0,0.0,1.0);
  glScalef(1.0,1.0,1.0);
  // draw second cone
  glutWireCone(base,height,slices,stacks);
  glFlush();

} 

void reshapeCone(int x, int y)
{
  if (y == 0 || x == 0) return;
  glMatrixMode(GL_PROJECTION);  
  glLoadIdentity();

  gluPerspective(70.0,(GLdouble)x/(GLdouble)y,0.5,20.0);

  glViewport(0,0,x,y);  
}

void idleCone(void)
{
 
  zRotate1 += 0.1;
  zRotate2 += 0.1;
  Cone();
}

int main(int argc, char **argv){
// set up the window 
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(1280, 720);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Cone Rotate");
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  xRotate=90;
  glClearColor(0.0,0.0,0.0,0.0);
  glutDisplayFunc(Cone);
  glutReshapeFunc(reshapeCone);
  glutIdleFunc(idleCone);
  glutMainLoop();
  return  0;
}
