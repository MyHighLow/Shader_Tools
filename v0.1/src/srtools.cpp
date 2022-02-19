#include "srtools.h"

Shader Shader::FromFile(const char *FilePath, const GLenum Type) {
	Shader ret = {.Type = Type};
	// open file stream
	std::ifstream is(FilePath, std::ios::in|std::ios::binary|std::ios::ate);
	if (!is.is_open()) {
		std::cerr << "Unable to open file " << FilePath << std::endl;
		return ret;
	}
	// read from file
	long size = is.tellg();
	char *buffer = new char[size+1];
	is.seekg(0, std::ios::beg);
	is.read (buffer, size);
	is.close();
	buffer[size] = 0;
	// compile shader
	ret.Handle = glCreateShader(Type);
	glShaderSource(ret.Handle, 1, (const GLchar**)&buffer, NULL);
	glCompileShader(ret.Handle);
	// output results
		// std::cerr << "info log for " << FilePath << std::endl;
		// srt::print_info_log(ret.Handle);
	// cleanup
	delete [] buffer;
	return ret;
};

Shader Shader::FromSource(const char *Source, const GLenum Type) {
	Shader ret = {.Type = Type};
	// compile shader
	ret.Handle = glCreateShader(Type);
	glShaderSource(ret.Handle, 1, (const GLchar**)&Source, NULL);
	glCompileShader(ret.Handle);
	// output results
		// std::cerr << "info log for " << FilePath << std::endl;
		// srt::print_info_log(ret.Handle);
	// cleanup
	return ret;
};

ShaderProgram ShaderProgram::FromShaders(const Shader Shaders...) {
	ShaderProgram ret = {.Shaders = {Shaders}};
	ret.Handle = glCreateProgram();
	
	for (Shader i : ret.Shaders) {
		glAttachShader(ret.Handle, i.Handle);
	};
	return ret;
};

void ShaderProgram::Use() {
	glUseProgram(this->Handle);
};

GLuint ShaderProgram::Uniform(const char *name) {
	return glGetUniformLocation(this->Handle, name);
};

GLuint ShaderProgram::Attribute(const char *name) {
	return glGetAttribLocation(this->Handle, name);
};

void ShaderProgram::EasyAttribPointer(const char *AttributeName, const int NumComponents, const int Stride, const int Offset) {
	GLuint id = this->Attribute(AttributeName);
	glEnableVertexAttribArray(id);
	glVertexAttribPointer(id, NumComponents, GL_FLOAT, GL_FALSE, Stride, (const void*)Offset);
};

