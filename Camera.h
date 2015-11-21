#ifndef _CAMERA_H_
#define _CAMERA_H_

#define MAXPHI 89
#define MINPHI -89
#define MINTHETA -180
#define MAXTHETA 180

class Camera
{
public:
	Camera(double, double, double);	
	void definir(); // TODO Send Position to compute shader
	void incrementerTheta(double deltaAngle);
	void incrementerPhi(double deltaAngle);

	bool modeLookAt_;
	double theta_;
	double phi_;
	double dist_;

	// Nuanceur* computeProg

};

#endif // _CAMERA_H_

