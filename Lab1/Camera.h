#pragma once
#include "Vector3.h"
#include "Matrix4.h"
#include <GL/glut.h>

class Camera
{
	protected:
		Vector3 e;	//center of projection
		Vector3 d;	//object looking at
		Vector3 up;	//(unit?) vector looking up
		Matrix4 c;	//internal camera matrix
	public:
		Camera();
		Camera(Vector3 e, Vector3 d, Vector3 up);
		~Camera(void);
		GLdouble* getGLMatrix();
};

