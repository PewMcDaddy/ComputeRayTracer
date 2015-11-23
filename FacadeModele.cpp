#include "FacadeModele.h"
#ifndef GLUT_WHEEL_UP
#  define GLUT_WHEEL_UP   4  
#  define GLUT_WHEEL_DOWN 3  
#endif
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "SceneTP3.h"
#include "NuanceurCalc.h"

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
			camera_->dist_ += 1;
			std::cout << camera_->dist_ << std::endl;
		}
		else  // WHEEL_UP
		if (camera_->dist_ > 1){
			camera_->dist_ -= 1;
			std::cout << camera_->dist_ << std::endl;
		}
		glutPostRedisplay();
	}
}


void FacadeModele::sourisMouvement( int curseurX, int curseurY )
{
	int deltaX = curseurX - curseur.dernierX_;
	int deltaY = curseurY - curseur.dernierY_;
	
	camera_->incrementerTheta( -deltaX / 100.0);

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
	//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

	//projection_->definir((GLdouble)g.largeur_ / (GLdouble)g.hauteur_);

	GLuint texHandle;
	glGenTextures(1, &texHandle);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texHandle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, g.largeur_, g.hauteur_, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, NULL);
	glBindImageTexture(0, texHandle, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);

	progCalc_->activer();
	progCalc_->passerUniforme("M",(int) g.hauteur_);
	progCalc_->passerUniforme("N",(int) g.largeur_);
	camera_->definir();

	progCalc_->passerUniforme("outputTexture", 0);
	glDispatchCompute(g.largeur_ /16 + 1, g.hauteur_/16 + 1 , 1);
	GLenum e = glGetError();
	if (e != GL_NO_ERROR) {
		std::cout << "ERROR MOFO" << gluErrorString(e) << e << std::endl;
	}

	progReg_->activer();
	// ============================================================================================


	GLuint renderHandle = progReg_->programme_;
	glUniform1i(glGetUniformLocation(renderHandle, "srcTex"), 0);
	
	
	GLuint vertArray;
	glGenVertexArrays(1, &vertArray);
	glBindVertexArray(vertArray);

	GLuint posBuf;
	glGenBuffers(1, &posBuf);
	glBindBuffer(GL_ARRAY_BUFFER, posBuf);
	float data[] = {
		-1.0f, -1.0f,
		-1.0f, 1.0f,
		1.0f, -1.0f,
		1.0f, 1.0f
	};


	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 8, data, GL_STREAM_DRAW);
	GLint posPtr = glGetAttribLocation(renderHandle, "pos");
	glVertexAttribPointer(posPtr, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posPtr);


	// ============================================================================================
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

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
	// glEnable(GL_DEPTH_TEST);
	projection_ = new Projection();

	g.modePlein_ = true;

	progReg_ = new NuanceurReg();
	// charger les nuanceurs
	const char *ns = "nuanceurs/nuanceurSommets.glsl";
	const char *nf = "nuanceurs/nuanceurFragments.glsl";
	progReg_->initialiser( ns, nf );

	progCalc_ = new NuanceurCalc();
	// const char *nc = "nuanceurs/dude.glsl";
	const char *nc = "nuanceurs/nuanceurCalcul.glsl";
	progCalc_->initialiser(nc);

	camera_ = new Camera(5.0, 0.0, 1.0,progCalc_); // TODO Give it the computeShader 


}
