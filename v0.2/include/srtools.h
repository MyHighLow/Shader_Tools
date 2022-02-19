#ifndef SRTOOLS_HEADER
#define SRTOOLS_HEADER

#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <initializer_list>

#include <json.hpp>

struct Shader {
	GLuint Handle; 
	GLenum Type;

	static Shader FromFile(const char *FilePath, const GLenum Type, bool Verbose = false);
	static Shader FromSource(const char *Source, const GLenum Type);
};

struct ShaderProgram {
	private:
		int ParseSize(std::string s);
		GLenum ParseGLenum(std::string s);

	public:
		std::vector<Shader> Shaders;
		GLuint Handle;

		// static ShaderProgram FromShaders(const Shader Shaders...);
		static ShaderProgram FromShaders(std::initializer_list<Shader> Shaders, bool Verbose = false);

		void Use();
		GLuint Uniform(const char *Name);
		GLuint Attribute(const char *Name);
		void EasyAttribPointer(const char *AttributeName, const int NumComponents, const int Stride, const int Offset);
		void JsonAttribPointers(const char *JsonFilePath, bool Verbose = false);

};





#endif
