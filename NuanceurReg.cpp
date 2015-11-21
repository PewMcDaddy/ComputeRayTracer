#include "NuanceurReg.h"
#include <string>

NuanceurReg::NuanceurReg()
{
	poignees.sommets_ = 0;
	poignees.fragments_ = 0;
}

NuanceurReg::~NuanceurReg(){};

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

void NuanceurReg::compiler(const char* sourceNS, const char* sourceNF)
{
	// Assign handles for the program and shaders
	programme_ = glCreateProgram();
	poignees.sommets_ = glCreateShader(GL_VERTEX_SHADER);
	poignees.fragments_ = glCreateShader(GL_FRAGMENT_SHADER);

	// Load and compile the vertex shader
	glShaderSource( poignees.sommets_, 1, &sourceNS, NULL);
	glCompileShader( poignees.sommets_ );

	// Load and compile the fragment shader
	glShaderSource( poignees.fragments_, 1, &sourceNF, NULL);
	glCompileShader( poignees.fragments_ );

	// Attach the shaders to the program
	glAttachShader( programme_, poignees.sommets_);
	glAttachShader( programme_, poignees.fragments_);

	// Link the program. (not sure what this does.)
	glLinkProgram(programme_);

	// Show information log of both shaders.
	std::cout << getProgramInfo(poignees.sommets_) << std::endl;
	std::cout << getProgramInfo(poignees.fragments_) << std::endl;
}



void NuanceurReg::initialiser(const char* ns, const char* nf)
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


void NuanceurReg::activer()
{
	glUseProgram(programme_);
}
void NuanceurReg::desactiver()
{
	glUseProgram(0);
}