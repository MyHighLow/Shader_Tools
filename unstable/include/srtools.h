#ifndef SRTOOLS_HEADER
#define SRTOOLS_HEADER

#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <iostream>
#include <fstream>
#include <cmath>

/*
	shader tools
		utilities for interacting with shaders
*/

/*
	GLenum shaderType:	* GL_COMPUTE_SHADER
						* GL_VERTEX_SHADER
						  GL_TESS_CONTROL_SHADER
						  GL_TESS_EVALUATION_SHADER
						* GL_GEOMETRY_SHADER
						* GL_FRAGMENT_SHADER

					* supported
*/

namespace srt {

	// shader-type bitmask
	typedef uint8_t SHADER_TYPE;
	const SHADER_TYPE VERTEX_SHADER = 0b00000001;
	const SHADER_TYPE VERT_SHADER = 0b00000001;
	const SHADER_TYPE V_SHADER = 0b00000001;
	
	const SHADER_TYPE GEOMETRY_SHADER = 0b00000010;
	const SHADER_TYPE GEO_SHADER = 0b00000010;
	const SHADER_TYPE G_SHADER = 0b00000010;

	const SHADER_TYPE FRAGMENT_SHADER = 0b00000100;
	const SHADER_TYPE FRAG_SHADER = 0b00000100;
	const SHADER_TYPE F_SHADER = 0b00000100;

	const SHADER_TYPE COMPUTE_SHADER = 0b00001000;
	const SHADER_TYPE COMP_SHADER = 0b00001000;
	const SHADER_TYPE C_SHADER = 0b00001000;

	// functions
	void print_info_log(GLuint obj);

	// shader descriptor
	struct ShaderDescriptor {
		GLenum type;			// needs to be specified
		std::string path;		// needs to be specified
		GLuint handle;

		// constructor
		// (just initialize type and path manually)

		// functions
		bool compile();
	};

	// shader program descriptor
	struct ShaderProgramDescriptor {
		SHADER_TYPE included_shaders; /* bitmask of SHADER_TYPEs */
		struct ShaderDescriptor vertex_shader_descriptor;
		struct ShaderDescriptor fragment_shader_descriptor;
		struct ShaderDescriptor geometry_shader_descriptor;
		struct ShaderDescriptor compute_shader_descriptor;
		GLuint program_handle;

		// constructor
		ShaderProgramDescriptor(std::string folder, SHADER_TYPE included_shaders);

		// functions
		void compile();
		void link();
		void use();
		GLuint uniform(const char *name);
		GLuint attribute(const char *name);

		void EZAttribPointer(const char *AttributeName, const int NumComponents, const int Stride, int Offset); // assumes type : GL_FLOAT, normalized : GL_FALSE

	};


};


#endif
