#version 430


uniform float xCam;
uniform float yCam;
uniform float zCam;

writeonly uniform image2D outputTexture;

uniform int M;
uniform int N;

uniform float indiceBloc;

uniform int nbRebonds;
uniform int miroir;

struct Intersect{
	float t;
	vec3 n;
	bool l;
	int numPlane;
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

	float t = -1;
	vec3 n = vec3(0,0,0);
	bool l = false;

	if(r.direction[i] != 0)
	{
		float tInter = (center[i] - r.origin[i])/r.direction[i];
		if(tInter > 0)
		{
			vec3 interPoint = r.origin + tInter*r.direction;
			if(abs(center[j] - interPoint[j]) < jDim && abs(center[k] - interPoint[k]) < kDim)
			{
				n[i] = 1;
				t = tInter;
				if(jDim - abs(center[j] - interPoint[j]) < 0.08 || kDim - abs(center[k] - interPoint[k]) < 0.08)
					l = true;
			}
		}
	}

	Intersect inter;
	inter.t = t;
	inter.n = n;
	inter.l = l;
	inter.numPlane = -1;

	return inter;
}

Intersect intersectPlane(Ray r, int numPlane)
{
	Intersect inter;
	inter.t = -1;
	inter.n = vec3(0,0,0);
	inter.l = false;
	inter.numPlane = numPlane;

	vec3 rt = vec3(3.5,3.5,12.5);
	float ltx = 3.5;
	float lty = 3.5;
	float ltz = 7.5;


	vec3 rm = vec3(3.5,4.0,14.5);

	float lmx = 0.5;
	float lmy = 1.0;
	float lmz = 2.5;

	vec3 center;

	switch(numPlane)
	{
		case 1:
			center = rt - vec3(ltx,0,0);
			inter = findIntersect(r, center,0, lty,ltz);
			inter.numPlane = numPlane;
			break;
		case 2:
			center = rt + vec3(ltx,0,0);
			inter = findIntersect(r, center,0, lty,ltz);
			inter.numPlane = numPlane;
			break;
		case 3: 
	    	// Plan y = ...
	    	center = rt + vec3(0,lty,0);
			inter = findIntersect(r, center,1, ltz,ltx);
	    	inter.numPlane = numPlane;
	    	break;
	    case 4:
	    	// Plan y = ...
	    	center = rt - vec3(0,lty,0);
			inter = findIntersect(r, center,1, ltz,ltx);
	    	inter.numPlane = numPlane;
	    	break;
	    case 5: 
	    	// Plan z = ...
	    	center = rt - vec3(0,0,ltz);
			inter = findIntersect(r, center,2, ltx,lty);
	    	inter.numPlane = numPlane;
	    	break;
	    case 6:
	    	// Plan z = ...
	    	center = rt + vec3(0,0,ltz);
			inter = findIntersect(r, center,2, ltx,lty);
	    	inter.numPlane = numPlane;
	    	break;
		
		case 7: // Plan x = 3
			center = rm - vec3(lmx,0,0);
			inter = findIntersect(r, center,0, lmy,lmz);
			inter.numPlane = numPlane;
			break;
		case 8: // Plan x = 4
			center = rm + vec3(lmx,0,0);
			inter = findIntersect(r, center,0, lmy,lmz);
			inter.numPlane = numPlane;
			break;
		case 9 :
	    	// Plan y = 3
	    	center = rm - vec3(0,lmy,0);
			inter = findIntersect(r, center,1, lmz,lmx);
	    	inter.numPlane = numPlane;
	    	break;
	    case 10 :
	    	// Play y = 5
	    	center = rm + vec3(0,lmy,0);
			inter = findIntersect(r, center,1, lmz,lmx);
	    	inter.numPlane = numPlane;
	    	break;
	    case 11 :
	    	// Plan z = 12
	    	center = rm - vec3(0,0,lmz);
			inter = findIntersect(r, center,2, lmx,lmy);
	    	inter.numPlane = numPlane;
	    	break;
	    case 12 :
	    	// Plan z = 17
	    	center = rm + vec3(0,0,lmz);
			inter = findIntersect(r, center,2, lmx,lmy);
	    	inter.numPlane = numPlane;
	    	break;
	}
	
	return inter;
}


Intersect findFirstIntersect(Ray r)
{
	Intersect firstInter, inter;
	firstInter.t = 10000;
	firstInter.n = vec3(1,1,1);
	firstInter.numPlane = -1;
	firstInter.l = false;
	inter = firstInter;
	for(int i = 1; i <=12; i++)
	{
		inter = intersectPlane(r,i);
		if(inter.t > 0 && inter.t < firstInter.t)
		{
			firstInter = inter;
		}
	}
	return firstInter;
}

vec4 planeColor(int numPlane)
{
	vec4 color;
	switch(numPlane)
	{
		case 7:
			color = vec4(1,0,0,1); // Rouge
			break;
		case 8:
			color = vec4(0,1,1,1); // Cyan
			break;
		case 9:
			color = vec4(0,1,0,1); // Verte
			break;
		case 10:
			color = vec4(1,1,0,1); // Jaune
			break;
		case 11:
			color = vec4(0,0,1,1); // Bleu
			break;
		case 12:
			color = vec4(1,0,1,1); // Magenta
			break;
	}
	return color;
}

vec3 reflectPhil(vec3 d, vec3 n)
{
	return d - 2*dot(d,n)*n;
}

vec3 refract(vec3 d, vec3 n, float indice1, float indice2)
{
	vec3 z = (indice1 / indice2) * (d - dot(d,n)*n);
	if(dot(n,d) > 0)
		return z + sqrt(1-length(z)*length(z)) * n;
	else
		return z - sqrt(1-length(z)*length(z)) * n;
}

bool totalInternalReflection(vec3 d, vec3 n, float indAir, float indBloc, int nRebound)
{
	float incident;
	float transmitted;

	if(nRebound == 0)
	{
		incident = indAir;
		transmitted = indBloc;
	}
	else
	{
		incident = indBloc;
		transmitted = indAir;
	}

	if(incident < transmitted)
		return false;

	float theta = acos(abs(dot(n,normalize(d))));
	float critical = asin(transmitted/incident);
	if(theta > critical)
		return true;

	return false;
}

vec4 RecCastRay(Ray r, float indAir, float indBloc, bool withLine, int nRebound, int nRefract)
{
	if(nRefract > 1 || nRebound > 20)
	{
		return vec4(1,1,1,1);
	}


for(int rebond = 0; rebond <= nbRebonds ; rebond++)
{

	Intersect inter = findFirstIntersect(r);

	if(7 <= inter.numPlane && inter.numPlane <= 12)
	{
		return planeColor(inter.numPlane);
	}
	else if(1 <= inter.numPlane && inter.numPlane <= 6)
	{
		
		if(withLine && inter.l && rebond < 2)
			return vec4(0,0,0,1);

		vec3 point = r.origin + inter.t * r.direction;
		bool reflInt = true;
		reflInt = totalInternalReflection(r.direction,inter.n,indAir,indBloc,rebond);
		if(reflInt || (rebond > 0 && miroir ==1))
		{
			r.direction = reflectPhil(r.direction, inter.n);
			r.origin = point + 0.0001*r.direction;
		}
		else
		{
			r.direction = refract(r.direction, inter.n,indAir,indBloc);
			r.origin = point + 0.0001*r.direction;;
		}
	}
	else
	{
		return vec4(1,1,1,1);
	}

}


	return vec4(1,1,1,1);

}



vec4 castRay(vec3 obs, vec3 point, float indAir, float indBloc, bool withLine)
{
	Ray r;
	r.origin = obs;
	r.direction = normalize(point - obs);

	return RecCastRay(r, indAir, indBloc, withLine, 0, 0);
	return vec4(0.0,0.0,1.0,0.0);
}

vec3 pixelToPoint(int X, int Y, vec3 center, vec3 normal, int M, int N, float W, float H)
{
	vec3 point = vec3(1,1,1);
	vec3 uDirection = normalize(cross(vec3(0,0,1),normal));
	vec3 vDirection = normalize(cross(normal,uDirection));

	float u = W*(X - N/2.0f)/N;
	float v = H*(Y - M/2.0f)/M;

	point = center + u*uDirection + v*vDirection;

	return point;
}


layout (local_size_x = 16, local_size_y = 16, local_size_z = 1) in;


void main()
{

	vec4 couleur = vec4(1.0,0.0,1.0,1.0);
	
	int i = int(gl_GlobalInvocationID.x);
	int j = int(gl_GlobalInvocationID.y);
	vec3 center = vec3(3.5,3.5,12.0);

	vec3 cam = vec3(xCam,yCam,zCam) + center;
	// cam = vec3(-10,3.5,15);
	// // 

	vec3 normal = -normalize(center - cam);
	// 

	center = cam - 1 * normal;
	vec3 point = pixelToPoint(i,j,center,normal,M,N,1,float(M)/float(N));
	// 
	couleur = castRay(cam,point,1.0,indiceBloc,true);
	//couleur = vec4(sin(float(i)/10.0),cos(float(j)/10),0,1);
	imageStore(outputTexture,ivec2(i,j),couleur);
}