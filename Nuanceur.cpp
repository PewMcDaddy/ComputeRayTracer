#include "Nuanceur.h"

Nuanceur::Nuanceur(){} // TODO NuanceurInterface
Nuanceur::~Nuanceur(){}// TODO NuanceurInterface

// TODO virtual void compiler()
// compiler appelle compilerNormale( const char* sourceNS, const char* sourceNF) pour un programme régulier
// et appelle compilerCompute(cons char* sourceCS) pour un compute shader.
void Nuanceur::compiler(){}

void Nuanceur::activer(){}// TODO NuanceurInterface
void Nuanceur::desactiver(){}// TODO NuanceurInterface

void Nuanceur::passerUniforme(const std::string nom, int valeurEntiere)
{
	glUniform1i(glGetUniformLocation(programme_, nom.c_str()), valeurEntiere);
}

void Nuanceur::passerUniforme(const std::string nom, float valeurFlottante)
{
	glUniform1f(glGetUniformLocation(programme_, nom.c_str()), valeurFlottante);
}

std::string Nuanceur::getProgramInfo(GLuint poignee)
{
	// Obtain lenght of the log
	int logLength;
	glGetShaderiv(poignee, GL_INFO_LOG_LENGTH, &logLength);

	// Read log into null-terminated buffer
	char* logText = new char[logLength + 1];
	int charsWritten = 0;
	glGetShaderInfoLog(poignee, logLength, &charsWritten, logText);

	// Return a string constructed from the buffer.
	std::string logString{ logText };
	delete[] logText;
	return std::move(logString);
}

