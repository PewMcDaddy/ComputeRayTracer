#include "Camera.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <GL/glew.h>
#define DEG2RAD(a) ((a) * M_PI / 180.0)
#define RAD2DEG(a) ((a) * 180.0 / M_PI)
#define CLIP(a,min,max) ( (a < min) ? min : ((a > max) ? max : a) )

Camera::Camera(double dist, double theta, double phi)
{
	dist_ = dist;
	theta_ = theta;
	phi_ = phi;
	modeLookAt_ = true;
}

void Camera::definir()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (0)
		gluLookAt(dist_*sin(theta_)*sin(phi_), dist_*cos(theta_)*sin(phi_), dist_*cos(phi_), 0, 0, 0, 0, 0, 1);
	else
	{
		glTranslatef(0, 0, -dist_);
		glRotatef(-RAD2DEG(phi_), 1.0, 0.0, 0.0);
		glRotatef(180 + RAD2DEG(theta_), 0.0, 0.0, 1.0);
	}
}


void Camera::incrementerTheta(double deltaAngle)
{
	theta_ += deltaAngle;
}

void Camera::incrementerPhi(double deltaAngle)
{
	phi_ += deltaAngle;
	phi_ = CLIP(phi_,MINPHI,MAXPHI);
}

