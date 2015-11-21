#ifndef _NUANCEUR_H_
#define _NUANCEUR_H_
#include <GL/glew.h>
#include <string>

// TODO NuanceurInterface
class Nuanceur
{
public:
	Nuanceur(); // TODO NuanceurInterface
	virtual ~Nuanceur();// TODO NuanceurInterface

	virtual void activer();// TODO NuanceurInterface
	virtual void desactiver();// TODO NuanceurInterface

	void passerUniforme(const std::string, int valeurEntiere);// TODO NuanceurInterface
	void passerUniforme(const std::string, float valeurFlottante);// TODO NuanceurInterface

	std::string getProgramInfo(GLuint poignee);// TODO NuanceurInterface

protected:
	GLuint programme_{ 0 };
};



#endif // _NUANCEUR_H_