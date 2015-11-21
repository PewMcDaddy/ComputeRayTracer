#include <GL/glew.h>
#include <GL/glut.h>
#include "FacadeModele.h"

void afficherScene()									{FacadeModele::obtenirInstance()->afficherScene();}
void redimensionnement( GLsizei w, GLsizei h )			{FacadeModele::obtenirInstance()->redimensionnement( w, h );}
void clavier( unsigned char touche, int x, int y )		{FacadeModele::obtenirInstance()->clavier( touche, x, y );}
void clavierSpecial( int touche, int x, int y )			{FacadeModele::obtenirInstance()->clavierSpecial(  touche, x, y );}
void sourisMouvement( int x, int y )					{FacadeModele::obtenirInstance()->sourisMouvement( x, y );}
void sourisClic( int button, int state, int x, int y )	{FacadeModele::obtenirInstance()->sourisClic( button, state, x, y );}

int main( int argc, char *argv[] )
{	
	// initialisation de GLUT
	glutInit( &argc, argv );
	// paramétrage de l'affichage
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_STENCIL);
	// taille de la fenetre
	glutInitWindowSize( LARGEUR_INITIALE, HAUTEUR_INITIALE );
	// création de la fenêtre
	FacadeModele::obtenirInstance()->setFeneID(glutCreateWindow( "INF2705" ));
	FacadeModele::obtenirInstance()->initialiser();

	// référencement de la fonction de rappel pour l'affichage
	glutDisplayFunc( afficherScene );
	// référencement de la fonction de rappel pour le redimensionnement
	glutReshapeFunc( redimensionnement );
	// référencement de la fonction de gestion des touches
	glutKeyboardFunc( clavier );
	// référencement de la fonction de gestion des touches spéciales
	glutSpecialFunc( clavierSpecial );
	// référencement de la fonction de rappel pour le mouvement de la souris
	glutMotionFunc( sourisMouvement );
	// référencement de la fonction de rappel pour le clic de la souris
	glutMouseFunc( sourisClic );
	glutPostRedisplay();
	// boucle principale de gestion des evenements
	glutMainLoop();

	return EXIT_SUCCESS;

}

