// 	les étudiants peuvent utiliser l'exemple du cours pour démarrer:
//    http://www.cours.polymtl.ca/inf2705/nuanceurs/exempleSimple/

#version 110

#define M_PI_2  (1.57079632679489661923)  // PI/2

varying vec4 positionRelative;
varying vec4 mcPosition;

void main( void )
{
	// transformation standard du sommet (ModelView et Projection)
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
	mcPosition = gl_Vertex;

	// Transmission de la couleur au nuanceur de fragments.
	gl_FrontColor = gl_Color;
	gl_BackColor = gl_Color;

	// Sauvegarder gl_vertex dans une variable "varying" custom pour pouvoir 
	// l'utiliser dans le nuanceur de fragments.
	positionRelative = gl_Vertex;

	// Pour garder le clip plane
	gl_ClipVertex = gl_ModelViewMatrix * gl_Vertex;
	gl_TexCoord[0] = gl_MultiTexCoord0;
}
