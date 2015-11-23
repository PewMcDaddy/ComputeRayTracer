#include "Camera.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <GL/glew.h>
#define DEG2RAD(a) ((a) * M_PI / 180.0)
#define RAD2DEG(a) ((a) * 180.0 / M_PI)
#define CLIP(a,min,max) ( (a < min) ? min : ((a > max) ? max : a) )
#include "Nuanceur.h"

Camera::Camera(double dist, double theta, double phi, Nuanceur* progCalc)
{
	dist_ = dist;
	theta_ = theta;
	phi_ = phi;
	modeLookAt_ = true;
	progCalc_ = progCalc;
}

void Camera::definir()
{
	// TODO Calculer x,y,z selon phi,theta,dist et le point visé

	float xCam = -10;
	float yCam = -10;
	float zCam = 15;

	float r = dist_ * cos(phi_);
	zCam = dist_ * sin(phi_);
	xCam = r * cos(theta_);
	yCam = r * sin(theta_);




	progCalc_->passerUniforme("xCam", xCam);
	progCalc_->passerUniforme("yCam", yCam);
	progCalc_->passerUniforme("zCam", zCam);
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

