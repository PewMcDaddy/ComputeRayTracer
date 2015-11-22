#include "NuanceurCalc.h"
#include <string>
#include <iostream>
#include <fstream>


char* lireNuanceur(const char* path);

NuanceurCalc::NuanceurCalc()
{
	calc_ = 0;
}

NuanceurCalc::~NuanceurCalc(){};


void NuanceurCalc::compiler(const char* sourceNC)
{
	// Assign handles for the program and shaders
	programme_ = glCreateProgram();
	calc_ = glCreateShader(GL_COMPUTE_SHADER);

	// Load and compile the compute shader
	glShaderSource(calc_, 1, &sourceNC, NULL);
	glCompileShader(calc_);

	// Attach the shaders to the program
	glAttachShader(programme_, calc_);

	// Link the program. (not sure what this does.)
	glLinkProgram(programme_);

	// Show information log of both shaders.
	std::cout << getProgramInfo(calc_) << std::endl;
}

std::string lireNuanceurCalc(const char* path)
{
	std::string fileText;
	std::string ligne;

	std::ifstream fin;
	fin.open(path);

	getline(fin, ligne);
	while (!fin.fail())
	{
		fileText += ligne + '\n';
		getline(fin, ligne);
	}

	// std::cout << fileText << std::endl;

	// Return the source code of the shader
	return fileText;
}

void NuanceurCalc::initialiser(const char* nc)
{
	// Read files into buffers
	std::string sourceNC = lireNuanceurCalc(nc);

	// Send source to GPU and compile
	compiler(sourceNC.c_str());
}
