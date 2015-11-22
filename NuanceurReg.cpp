#include "NuanceurReg.h"
#include <string>
#include <iostream>
#include <fstream>

std::string lireNuanceurReg(const char* path)
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

NuanceurReg::NuanceurReg()
{
	poignees.sommets_ = 0;
	poignees.fragments_ = 0;
}

NuanceurReg::~NuanceurReg(){};


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
	std::string sourceNS = lireNuanceurReg(ns);
	std::string sourceNF = lireNuanceurReg(nf);
	
	// Send source to GPU and compile
	compiler( sourceNS.c_str() , sourceNF.c_str() );
}

