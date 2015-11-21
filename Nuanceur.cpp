#include "NuanceurReg.h"
#include <string>

Nuanceur::Nuanceur()
{
	poignees.programme_ = 0;
	poignees.sommets_ = 0;
	poignees.fragments_ = 0;
}

char* lireNuanceur( const char* path)
{
	// Safety check
	if(path == 0) return 0;

	// Open the file for reading
	FILE* file = fopen(path, "r");

	// Determine the length of the file and return to the start
	fseek(file, 0, SEEK_END);
	int fsize = ftell(file);
	fseek(file, 0, SEEK_SET);

	// Read the file into a null-terminated buffer
	char* fileText = new char[fsize + 1];
	fread(fileText, fsize, 1, file);
	fileText[fsize] = 0;

	// Return the source code of the shader
	return fileText;
}

void Nuanceur::compiler(const char* sourceNS, const char* sourceNF)
{
	// Assign handles for the program and shaders
	poignees.programme_ = glCreateProgram();
	poignees.sommets_ = glCreateShader(GL_VERTEX_SHADER);
	poignees.fragments_ = glCreateShader(GL_FRAGMENT_SHADER);

	// Load and compile the vertex shader
	glShaderSource( poignees.sommets_, 1, &sourceNS, NULL);
	glCompileShader( poignees.sommets_ );

	// Load and compile the fragment shader
	glShaderSource( poignees.fragments_, 1, &sourceNF, NULL);
	glCompileShader( poignees.fragments_ );

	// Attach the shaders to the program
	glAttachShader( poignees.programme_, poignees.sommets_);
	glAttachShader( poignees.programme_, poignees.fragments_);

	// Link the program. (not sure what this does.)
	glLinkProgram(poignees.programme_);

	// Show information log of both shaders.
	std::cout << getProgramInfo(poignees.sommets_) << std::endl;
	std::cout << getProgramInfo(poignees.fragments_) << std::endl;
}

std::string Nuanceur::getProgramInfo(GLuint poignee)
{
	// Obtain lenght of the log
	int logLength;
	glGetShaderiv( poignee , GL_INFO_LOG_LENGTH , &logLength );

	// Read log into null-terminated buffer
	char* logText = new char[logLength + 1];
	int charsWritten = 0;
	glGetShaderInfoLog( poignee , logLength , &charsWritten, logText );

	// Return a string constructed from the buffer.
	std::string logString{logText};
	delete[] logText;
	return std::move( logString );
}

void Nuanceur::initialiser(const char* ns, const char* nf)
{
	// Read files into buffers
	char* sourceNS = lireNuanceur(ns);
	char* sourceNF = lireNuanceur(nf);
	
	// Send source to GPU and compile
	compiler( sourceNS , sourceNF );

	// Free the source code buffers.
	delete[] sourceNF;
	delete[] sourceNS;
	sourceNF = sourceNS = 0;
}


void Nuanceur::activer()
{
	glUseProgram(poignees.programme_);
}
void Nuanceur::desactiver()
{
	glUseProgram(0);
}

void Nuanceur::passerUniforme(const std::string nom, int valeurEntiere)
{
	glUniform1i(glGetUniformLocation(poignees.programme_, nom.c_str()), valeurEntiere);
}
void Nuanceur::passerUniforme(const std::string nom, float valeurFlottante)
{
	glUniform1f(glGetUniformLocation(poignees.programme_, nom.c_str()), valeurFlottante);
}