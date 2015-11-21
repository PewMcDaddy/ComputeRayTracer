#ifndef _NUANCEURCALC_H_
#define _NUANCEURCALC_H_
#include "Nuanceur.h"
#include <GL/glew.h>

class NuanceurCalc : public Nuanceur
{
public:
	NuanceurCalc();
	~NuanceurCalc();

	void compiler(const char* sourceNC);

	void initialiser(const char* nc);

private:
	GLuint calc_{ 0 };
};

#endif // _NUANCEURCALC_H_