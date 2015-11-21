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
	NuanceurReg();
	~NuanceurReg();

	void compiler( const char* sourceNS, const char* sourceNF);

	void initialiser( const char* ns, const char* nf);

private:
	
	struct Poignees{
		GLuint sommets_{0};
		GLuint fragments_{0};
	} poignees;
};



#endif // _NUANCEURREG_H_