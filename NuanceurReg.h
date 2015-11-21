#ifndef _NUANCEURREG_H_
#define _NUANCEURREG_H_
#include "Nuanceur.h"
#include <stdio.h>
#include <iostream>
#include <GL/glew.h>

// TODO NuanceurInterface
class NuanceurReg: public Nuanceur
{
public:
	NuanceurReg(); // TODO NuanceurInterface
	~NuanceurReg();// TODO NuanceurInterface

	// TODO virtual void compiler()
	// compiler appelle compilerNormale( const char* sourceNS, const char* sourceNF) pour un programme régulier
	// et appelle compilerCompute(cons char* sourceCS) pour un compute shader.
	void compiler( const char* sourceNS, const char* sourceNF);

	// TODO Même chose pour initialiser()
	void initialiser( const char* ns, const char* nf);

	void activer();// TODO NuanceurInterface
	void desactiver();// TODO NuanceurInterface

private:
	
	struct Poignees{
		GLuint sommets_{0};
		GLuint fragments_{0};
	} poignees;
};



#endif // _NUANCEUR_H_