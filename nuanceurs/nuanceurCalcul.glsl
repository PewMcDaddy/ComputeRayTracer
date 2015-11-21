#version 430
#define FAR_CLIP 1000.0f

uniform float xCam;
uniform float yCam;
uniform float zCam;

writeonly uniform image2D outputTexture;

struct Intersect{
	float t;
	vec3 n;
	bool l;
};

struct Ray{
	vec3 origin;
	vec3 direction;
};

Intersect findIntersect(Ray r, vec3 center,int axis, float jDim, float kDim)
{
	int i = axis;
	int j = (axis + 1)%3;
	int k = (axis + 2)%3;
	Intersect inter;
	inter.t = 1.0f;
	inter.n = vec3(1.0f,1.0f,1.0f);
	bool l = true;

	return inter;
}


void main()
{
	int i;i = i+1;
}