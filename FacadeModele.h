#define LARGEUR_INITIALE 900
#define HAUTEUR_INITIALE 600
#include <GL/glew.h>
#include "Projection.h"
#include "Camera.h"
#include "NuanceurReg.h"

#define NUANCEUR FacadeModele::obtenirInstance()->obtenirNuanceur()


class ArbreRenduINF2705;
class SceneTP3;
class FacadeModele
{
public:
	static FacadeModele* obtenirInstance();
	static void libererInstance();
	FacadeModele();
	~FacadeModele();

	void initialiser();

	void redimensionnement( GLsizei w, GLsizei h );
	void afficherScene();

	void clavier( unsigned char touche, int x, int y );
	void clavierSpecial( int touche, int x, int y );
	void sourisClic( int button, int state, int CurseurX, int curseurY );
	void sourisMouvement( int CurseurX, int curseurY );

	void setFeneID(GLuint ID);
	Nuanceur* obtenirNuanceur(){return prog_;};

private:
	Projection* projection_; // TODO GONE or change to orthographic
	Camera* camera_; 
	SceneTP3* scene_;
	Nuanceur* prog_;

	struct G{
		GLuint largeur_;
		GLuint hauteur_;
		GLuint feneID_;
		bool modePlein_;
	}g;

	struct Curseur{
		int dernierX_;
		int dernierY_;
	}curseur;
	int nPredivide{3};

	static FacadeModele* instance_;

};

