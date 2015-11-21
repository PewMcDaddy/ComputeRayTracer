#include "Projection.h"
#include <GL/glew.h>

void Projection::definir(double aspect)
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 60.0, aspect , 0.1, 100.0 );
}