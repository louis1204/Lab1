#ifndef _CUBE_H_
#define _CUBE_H_

#include "Matrix4.h"

class Cube
{
  protected:
    Matrix4 matrix;                 // model matrix
    double angle;                   // rotation angle [degrees]
	double angleZ;

  public:
    Cube();   // Constructor
    Matrix4& getMatrix();
    void spin(double);      // spin cube [degrees]
	void Keyboard(unsigned char key, int x, int y);
	double getAngle();
	void setAngle(double);
	void offsetX(double);
	void identity();
	void rotateZ(double deg);
};

class Window	  // output window related routines
{
  public:
    static int width, height; 	            // window size

    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
};

#endif

