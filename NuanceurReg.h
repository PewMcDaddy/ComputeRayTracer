#ifndef _NUANCEUR_H_
#define _NUANCEUR_H_
#include <stdio.h>
#include <iostream>
#include <GL/glew.h>

// TODO NuanceurInterface
class Nuanceur
{
public:
	Nuanceur(); // TODO NuanceurInterface
	~Nuanceur();// TODO NuanceurInterface

	// TODO virtual void compiler()
	// compiler appelle compilerNormale( const char* sourceNS, const char* sourceNF) pour un programme régulier
	// et appelle compilerCompute(cons char* sourceCS) pour un compute shader.
	void compiler( const char* sourceNS, const char* sourceNF);

	// TODO Même chose pour initialiser()
	void initialiser( const char* ns, const char* nf);

	void activer();// TODO NuanceurInterface
	void desactiver();// TODO NuanceurInterface

	void passerUniforme(const std::string, int valeurEntiere);// TODO NuanceurInterface
	void passerUniforme(const std::string, float valeurFlottante);// TODO NuanceurInterface

	std::string getProgramInfo(GLuint poignee);// TODO NuanceurInterface

private:
	struct Poignees{
		GLuint programme_{0};
		GLuint sommets_{0};
		GLuint fragments_{0};
	} poignees;
};



#endif // _NUANCEUR_H_