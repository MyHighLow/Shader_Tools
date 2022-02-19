#ifndef SRTOOLS_HEADER
#define SRTOOLS_HEADER

#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

struct Shader {
	GLuint Handle; 
	GLenum Type;

	static Shader FromFile(const char *FilePath, const GLenum Type);
	static Shader FromSource(const char *Source, const GLenum Type);
};

struct ShaderProgram {
	std::vector<Shader> Shaders;
	GLuint Handle;

	static ShaderProgram FromShaders(const Shader Shaders...);

	void Use();
	GLuint Uniform(const char *Name);
	GLuint Attribute(const char *Name);
	void EasyAttribPointer(const char *AttributeName, const int NumComponents, const int Stride, const int Offset);


};





#endif
