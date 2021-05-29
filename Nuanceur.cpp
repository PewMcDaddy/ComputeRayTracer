#include "Nuanceur.h"

Nuanceur::Nuanceur(){} // TODO NuanceurInterface
Nuanceur::~Nuanceur(){}// TODO NuanceurInterface

void Nuanceur::activer()
{
	glUseProgram(programme_);
}
void Nuanceur::desactiver()
{
	glUseProgram(0);
}

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
	return logString;
}

