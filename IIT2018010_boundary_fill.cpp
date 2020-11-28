// organize and stay in moment --- Abhinav-IIITA
/*
 Write a program to draw a user defined pentagon and fill it using the following algorithms:
          a) flood fill   b)boundary fill
       Input for the pentagon has to be acquired using mouse click events, i.e. write and register a call back for mouse click. 
	   In the call back record position(x,y) for every click and draw a pentagon after five clicks. There after flood fill it.
*/
#ifdef APPLE
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <cmath>

// setting the window size

int ww=1200;
int wh=1200;
int first=0;

// set color values to fill

float bgCol[3] = {0.6, 0.2,0.1};
float intCol[3] = {1.0,1.0,1.0};
float fillCol[3] = {0.3,0.1,0.4};


// disply the screen

void display()
{
    glClearColor(1.0,0.0,0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

// define pouints for 2-d input
typedef struct{
   float x;
   float y;
 }Point2D;

// get all five points

Point2D p1,p2,p3,p4,p5;


// draw the required polygon

void drawpolygon(Point2D pt1,Point2D pt2,Point2D pt3,Point2D pt4, Point2D pt5)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
            glVertex2i(pt1.x,pt1.y);
            glVertex2i(pt2.x,pt2.y);
            glVertex2i(pt3.x,pt3.y);
            glVertex2i(pt4.x,pt4.y);
            glVertex2i(pt5.x,pt5.y);
        glEnd();
        glFlush();
}


// set the color of pixel

void setPixel(int pointx, int pointy, float f[3])
      {
             glBegin(GL_POINTS);
                  glColor3fv(f);
                  glVertex2i(pointx,pointy);
             glEnd();
             glFlush();
      }

// get the color of pixel

void getPixel(int x, int y, float pixels[3])
{
   glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,pixels);
}


// fill the area


void boundaryFill8(int x, int y,float oldcolor[3],float newcolor[3]) 
{ 
    float color[3];
    getPixel(x,y,color);
    
    // check requirements

    if(color[0]==oldcolor[0] && (color[1])==oldcolor[1] && (color[2])==oldcolor[2])
    {
            // set new color
             setPixel(x,y,newcolor);

             // go for neighbours
            boundaryFill8(x + 1, y, fill_color, boundary_color); 
            boundaryFill8(x, y + 1, fill_color, boundary_color); 
            boundaryFill8(x - 1, y, fill_color, boundary_color); 
            boundaryFill8(x, y - 1, fill_color, boundary_color); 
            boundaryFill8(x - 1, y - 1, fill_color, boundary_color); 
            boundaryFill8(x - 1, y + 1, fill_color, boundary_color); 
            boundaryFill8(x + 1, y - 1, fill_color, boundary_color); 
            boundaryFill8(x + 1, y + 1, fill_color, boundary_color); 
    } 
} 

// get clicks from mouse

void mouse(int btn, int state,int x,int y)
{
    if(btn==GLUT_LEFT_BUTTON)
        if(state==GLUT_DOWN)
        {
            switch(first)
            {
                case 0:
                    p1.x=x;
                    p1.y=(wh-y);
                    first=1;
                    break;

                case 1:
                    p2.x=x;
                    p2.y=wh-y;
                    first=2;
                    break;
                case 2:
                    p3.x=x;
                    p3.y=wh-y;
                    first=3;
                    break;
                case 3:
                    p4.x=x;
                    p4.y=wh-y;
                    first=4;
                    break;
                case 4:
                    p5.x=x;
                    p5.y=wh-y;
                    first=0;

                    // after all clicks draw the polygon and fill the boundary

                    drawpolygon(p1,p2,p3,p4,p5);

                    int xi = (p1.x+p2.x+p3.x+p4.x+p5.x)/5;
                    int yi = (p1.y+p2.y+p3.y+p4.y+p5.y)/5;

                    boundaryFill8(xi,yi,intCol,fillCol);
            }
        }

}

int main(int argc,char *argv[])
{
    glutInit( & argc, argv );
    glutInitWindowSize(ww,wh);
    // create window
    glutCreateWindow("assignment");
    gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);
    glutDisplayFunc(display);
    // get the mouse function
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
