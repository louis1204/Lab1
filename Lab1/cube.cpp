#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include "cube.h"
#include "Matrix4.h"
#include<vector>

using namespace std;

static Cube cube;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

static Matrix4 rotZ = Matrix4(1,0,0,0,
							  0,1,0,0,
							  0,0,1,0,
							  0,0,0,1);
static Matrix4 rotY = Matrix4(1,0,0,0,
							  0,1,0,0,
							  0,0,1,0,
							  0,0,0,1);
static Matrix4 transZ = Matrix4(1,0,0,0,
							  0,1,0,0,
							  0,0,1,0,
							  0,0,0,1);
static Matrix4 transX = Matrix4(1,0,0,0,
							  0,1,0,0,
							  0,0,1,0,
							  0,0,0,1);
static Matrix4 transY = Matrix4(1,0,0,0,
							  0,1,0,0,
							  0,0,1,0,
							  0,0,0,1);
static Matrix4 scaleM = Matrix4(1,0,0,0,
							  0,1,0,0,
							  0,0,1,0,
							  0,0,0,1);
static double spinVal = 0.001;
static double r = 0;
static double g = 255;
static double b = 0;

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback(void)
{
	cube.spin(spinVal);     // rotate cube; if it spins too fast try 0.001
	displayCallback();		// call display routine to re-draw cube
}

//----------------------------------------------------------------------------
// Callback method called when window is resized.
void Window::reshapeCallback(int w, int h)
{
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0); // set perspective projection viewing frustum
  glTranslatef(0, 0, -20);
  glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called when window readraw is necessary or
// when glutPostRedisplay() was called.
void Window::displayCallback(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);

	cube.getMatrix().transpose();
	glLoadMatrixd(cube.getMatrix().getPointer());	//updates the matrix
	cube.getMatrix().transpose();

	// Draw sides of cube in object coordinate system:
	glBegin(GL_QUADS);
    glColor3f(r, g, b);

    // Draw front face:
	glNormal3f(0.0, 0.0, 1.0);   
    glVertex3f(-5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0,  5.0);
    glVertex3f( 5.0, -5.0,  5.0);
    glVertex3f(-5.0, -5.0,  5.0);
    
    // Draw left side:
	glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-5.0,  5.0,  5.0);
    glVertex3f(-5.0,  5.0, -5.0);
    glVertex3f(-5.0, -5.0, -5.0);
    glVertex3f(-5.0, -5.0,  5.0);
    
    // Draw right side:
	glNormal3f(1.0, 0.0, 0.0);
    glVertex3f( 5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0, -5.0);
    glVertex3f( 5.0, -5.0, -5.0);
    glVertex3f( 5.0, -5.0,  5.0);
  
    // Draw back face:
	glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-5.0,  5.0, -5.0);
    glVertex3f( 5.0,  5.0, -5.0);
    glVertex3f( 5.0, -5.0, -5.0);
    glVertex3f(-5.0, -5.0, -5.0);
  
    // Draw top side:
	glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0, -5.0);
    glVertex3f(-5.0,  5.0, -5.0);
  
    // Draw bottom side:
	glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-5.0, -5.0, -5.0);
    glVertex3f( 5.0, -5.0, -5.0);
    glVertex3f( 5.0, -5.0,  5.0);
    glVertex3f(-5.0, -5.0,  5.0);
	glEnd();
  
	glFlush();  
	glutSwapBuffers();
}

Cube::Cube()
{
  angle = 0.0;
  angleZ = 0.0;
}

Matrix4& Cube::getMatrix()
{
  return matrix;
}

void Cube::spin(double deg)
{
  angle += deg;
  if (angle > 360.0 || angle < -360.0) 
	  angle = 0.0;

  Matrix4 transformationM = Matrix4(1,0,0,0,
						 0,1,0,0,
						 0,0,1,0,
						 0,0,0,1);
  transformationM.multiply(transX);
  transformationM.multiply(transY);
  transformationM.multiply(transZ);
  rotY.rotateY(angle);
  transformationM.multiply(rotY);
  //matrix.setRotateY(angle, cube.getMatrix());
  //matrix.add(rotY);

  transformationM.multiply(rotZ);

  transformationM.multiply(scaleM);
  matrix = transformationM;
}

void Cube::rotateZ(double deg)
{
	angleZ += deg;
	if (angleZ > 360.0 || angleZ < -360.0) 
	  angleZ = 0.0;

	rotZ.rotateZ(angleZ);
}

double Cube::getAngle()
{
	return cube.angle;
}

void Cube::setAngle(double angle)
{
	cube.angle = angle;
}

void Cube::offsetX(double offset)
{
	cube.matrix.translate("x", offset);
}

void Cube::identity()
{
	cube.matrix.identity();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:             // ESCAPE key
			exit (0);
			break;
		case 'c':
			spinVal = spinVal * -1;
			cube.getMatrix().print();
			break;
		case 'Y':
			{
				transY.translate("y",1);
				cube.getMatrix().print();
				break;
			}
		case 'y':
			{
				transY.translate("y",-1);
				cube.getMatrix().print();
				break;
			}
		case 'X':
			{
				transX.translate("x",1);
				cube.getMatrix().print();
				break;
			}
		case 'x':
			{
				transX.translate("x",-1);
				cube.getMatrix().print();
				break;
			}
		case 'Z':
			{
				transZ.translate("z",1);
				cube.getMatrix().print();
				break;
			}
		case 'z':
			{
				transZ.translate("z",-1);
				cube.getMatrix().print();
				break;
			}
		case 'r':
			cube.identity();
			rotZ.identity();
			transX.identity();
			transY.identity();
			transZ.identity();
			scaleM.identity();
			r=0;
			g=255;
			b=0;
			cube.getMatrix().print();
			break;
		case 'a':
			{
				cube.rotateZ(3.14/(180));
				cube.getMatrix().print();
				break;
			}
		case 's':
			{
				scaleM.scale(0.9);
				cube.getMatrix().print();
				break;
			}
		case 'S':
			{
				scaleM.scale(1.1);
				cube.getMatrix().print();
				break;
			}
		case '1':
			r = 255;
			g = 0;
			b = 0;
			break;
		case '2':
			r = 0;
			g = 255;
			b = 0;
			break;
		case '3':
			r = 0;
			g = 0;
			b = 255;
			break;
		case '4':
			r = 255;
			g = 255;
			b = 0;
			break;
	}	
}

int main(int argc, char *argv[])
{
  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {100.0};
  float position[]  = {0.0, 10.0, 1.0, 0.0};	// lightsource position
  
  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(Window::width, Window::height);      // set initial window size
  glutCreateWindow("OpenGL Cube for CSE167");    	      // open window and set window title

  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
  glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
  glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
  glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
  glShadeModel(GL_SMOOTH);             	      // set shading to smooth
  glMatrixMode(GL_PROJECTION); 
  

  // Generate material properties:
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  
  // Generate light source:
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
  // Install callback functions:
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
  glutIdleFunc(Window::idleCallback);
  glutKeyboardFunc (Keyboard);
  // Initialize cube matrix:
  cube.getMatrix().identity();
    
  glutMainLoop();
  return 0;
}

