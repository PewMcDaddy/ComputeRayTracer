// les étudiants peuvent utiliser l'exemple du cours pour démarrer:
//    http://www.cours.polymtl.ca/inf2705/nuanceurs/exempleSimple/


#version 120
#define M_PI_2  (1.57079632679489661923)  // PI/2

uniform sampler2D laTexture;
uniform float T = 2.0;
uniform float alpha, invAlpha, z_0;
varying vec4 mcPosition;
uniform int Npredivide;
uniform float t;

struct polarVec
{
	float r;
	float theta;
};

vec2 multiply(vec2 texCoord, float period)
{
	return vec2(0.5,0.5) + period*(texCoord - vec2(0.5,0.5));
}

vec2 divide(vec2 texCoord, float period)
{
	return vec2(0.5,0.5) + (texCoord - vec2(0.5,0.5))/(pow(period,Npredivide));
}
vec2 complexMultiply(vec2 z1, vec2 z2)
{
	return vec2(z1.x*z2.x - z1.y*z2.y , z1.x*z2.y + z1.y*z2.x);
}
vec2 complexInvert(vec2 z)
{
	float invR2 = 1/(z.x*z.x + z.y*z.y);
	return vec2(invR2*z.x, -invR2*z.y);
}
vec2 complexExponentiate(float r, float theta, float c, float d)
{
	// float lnrd = log(r)*beta.y; // 0
	// float rc = pow(r,beta.x); //   1
	// float thetad = theta*beta.y;// 0
	// float ethd = exp(-theta*beta.y);// 1
	// vec2 z1 = vec2(rc*cos(lnrd),rc*sin(lnrd));
	// vec2 z2 = vec2(ethd*cos(thetad), ethd*sin(thetad));
	// return complexMultiply(z1,z2);
	float arg = c*theta + 0.5*d*log(r*r);
	return pow(r*r, c*0.5)*exp(-d*theta)*vec2(cos(arg),sin(arg));

}

vec2 z1surBeta(float r, float theta, vec2 beta)
{
	vec2 invBeta = complexInvert(beta);
	return complexExponentiate(r,theta,invBeta.x, invBeta.y);
}
void main( void )
{
	// vec2 texCoord = gl_TexCoord[0].st;
	// vec2 ES_coords = (texCoord - vec2(0.5,0.5))*2.0;
	// float r = length(ES_coords);
	// float newR = pow(r,alpha)*alpha;
	// vec2 newES_coord = newR/r*ES_coords;
	// vec2 newTexCoord = (newES_coord/2) + vec2(0.5,0.5);

	float r_cone = pow(pow(z_0 - mcPosition.z,2) + pow(mcPosition.x,2) + pow(mcPosition.y,2),0.5);
	float r_m = pow(alpha*r_cone,invAlpha);
	float theta_m = acos(mcPosition.x/length(mcPosition.xy));
	if(mcPosition.y < 0) theta_m = -theta_m;

	vec2 temp1 = vec2(log(T),4*M_PI_2);
	vec2 temp2 = vec2(0.0, 4*M_PI_2);
	vec2 beta = (1-t)*vec2(1.0,0.0) + t*complexMultiply(temp2,complexInvert(temp1));
	vec2 transform1 = z1surBeta(r_m, theta_m,beta);

	vec2 transform2 = r_m * mcPosition.xy / length(mcPosition.xy);
	// transform est dans le carré [-1,1]


	vec2 newTexCoord = vec2(0.5,0.5) + 0.5*transform1;


	vec2 texCoord = divide(newTexCoord,T);
	int iter = 0;
	vec4 textureColor = texture2D( laTexture, texCoord.st );
	while(textureColor.g > 0.99 && textureColor.r < 0.01 && textureColor.b < 0.01 && ++iter < 30)
	{
		texCoord = multiply(texCoord,T);
		textureColor = texture2D( laTexture, texCoord.st );
	}
	if(iter >= 29) discard;

	gl_FragColor = textureColor;
}
