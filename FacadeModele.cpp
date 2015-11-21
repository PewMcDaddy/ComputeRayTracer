#include "FacadeModele.h"
#ifndef GLUT_WHEEL_UP
#  define GLUT_WHEEL_UP   4  
#  define GLUT_WHEEL_DOWN 3  
#endif
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "SceneTP3.h"

FacadeModele* FacadeModele::instance_ = 0;

FacadeModele* FacadeModele::obtenirInstance()
{
	if (instance_ == 0)
		instance_ = new FacadeModele();

	return instance_;
}

void FacadeModele::libererInstance()
{
	delete instance_;
}

FacadeModele::FacadeModele()
{

}

FacadeModele::~FacadeModele()
{

}

void FacadeModele::clavier( unsigned char touche, int x, int y )
{
	switch ( touche )
	{
		case '\e': // escape
			glutDestroyWindow( g.feneID_ );
			exit( 0 );
			break;
		case '-':
		case '_':
				// Changer distance. 
				camera_->dist_ += 0.1;
			break;
		case '+':
		case '=':
			if ( camera_->dist_ > 1.0 )
				camera_->dist_ -= 0.1;
			break;
		//case 'r':
		//	initialiser();
		//	break;
		case 'l':
			camera_->modeLookAt_ = !camera_->modeLookAt_;
			break;
		case 'g':
			{
				g.modePlein_ = !g.modePlein_;
				if (g.modePlein_ == false)
					glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
				else
					glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			}
			break;
		case '[': break;
		case ']': break;

	}
	glutPostRedisplay();
}

void FacadeModele::sourisClic( int button, int state, int CurseurX, int curseurY )
{
	if ( state == GLUT_DOWN )
	{
		curseur.dernierX_ = CurseurX;
		curseur.dernierY_ = curseurY;
	}
	// Zoom avec la roulette
	if ((button == GLUT_WHEEL_DOWN) || (button == GLUT_WHEEL_UP)) 
    { 
		if ( button == GLUT_WHEEL_DOWN ){
			camera_->dist_ += .1;
		}
		else  // WHEEL_UP
		if (camera_->dist_ > 1)
				camera_->dist_ -= .1;
       glutPostRedisplay();
	}
}


void FacadeModele::sourisMouvement( int curseurX, int curseurY )
{
	int deltaX = curseurX - curseur.dernierX_;
	int deltaY = curseurY - curseur.dernierY_;
	
	camera_->incrementerTheta( deltaX / 100.0);

	camera_->incrementerPhi( deltaY / 100.0);
	
	curseur.dernierX_ = curseurX;
	curseur.dernierY_ = curseurY;
	
	glutPostRedisplay();
}


void FacadeModele::clavierSpecial( int touche, int x, int y )
{

}

void FacadeModele::redimensionnement( GLsizei w, GLsizei h )
{
	g.largeur_ = w;
	g.hauteur_ = h;
	glViewport( 0, 0, w, h );
	glutPostRedisplay();
}

void FacadeModele::afficherScene()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

	projection_->definir((GLdouble)g.largeur_ / (GLdouble)g.hauteur_);

	camera_->definir();

	scene_->dessiner();

	glutSwapBuffers();
}

void FacadeModele::setFeneID(GLuint ID)
{
	g.feneID_ = ID;
}

void FacadeModele::initialiser()
{
	glewInit();
	// donner la couleur de fond
	glClearColor( 0.2, 0.2, 0.2, 1.0 );
	
	// activer les etats openGL
	glEnable(GL_DEPTH_TEST);
	projection_ = new Projection();



	g.modePlein_ = true;

	prog_ = new Nuanceur();
	// charger les nuanceurs
	const char *ns = "nuanceurs/nuanceurSommets.glsl";
	const char *nf = "nuanceurs/nuanceurFragments.glsl";
	prog_->initialiser( ns, nf );

	scene_ = new SceneTP3(prog_);
	scene_->initialiser();
	camera_ = new Camera(5.0, 0.0, 1.0); // TODO Give it the computeShader 
}
