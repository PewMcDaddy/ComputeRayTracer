#ifndef _NUANCEUR_H_
#define _NUANCEUR_H_
#include <GL/glew.h>
#include <string>

// TODO NuanceurInterface
class NuanceurInterface
{
public:
	NuanceurInterface(); // TODO NuanceurInterface
	virtual ~NuanceurInterface() = 0;// TODO NuanceurInterface

	// TODO virtual void compiler()
	// compiler appelle compilerNormale( const char* sourceNS, const char* sourceNF) pour un programme régulier
	// et appelle compilerCompute(cons char* sourceCS) pour un compute shader.
	virtual void compiler();

	virtual void activer();// TODO NuanceurInterface
	virtual void desactiver();// TODO NuanceurInterface

	void passerUniforme(const std::string, int valeurEntiere);// TODO NuanceurInterface
	void passerUniforme(const std::string, float valeurFlottante);// TODO NuanceurInterface

	std::string getProgramInfo(GLuint poignee);// TODO NuanceurInterface

private:

};



#endif // _NUANCEUR_H_