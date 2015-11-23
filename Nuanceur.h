#ifndef _NUANCEUR_H_
#define _NUANCEUR_H_
#include <GL/glew.h>
#include <string>


class Nuanceur
{
public:
	Nuanceur();
	virtual ~Nuanceur();

	virtual void activer();
	virtual void desactiver();

	void passerUniforme(const std::string, int valeurEntiere);
	void passerUniforme(const std::string, float valeurFlottante);

	std::string getProgramInfo(GLuint poignee);
	GLuint programme_{ 0 };
protected:

};



#endif // _NUANCEUR_H_