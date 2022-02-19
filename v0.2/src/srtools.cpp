#include "srtools.h"

Shader Shader::FromFile(const char *FilePath, const GLenum Type, bool Verbose /* = false */) {
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
		if (Verbose) {
			std::cerr << "info log for " << FilePath << std::endl;
			// srt::print_info_log(ret.Handle);
		};

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

ShaderProgram ShaderProgram::FromShaders(std::initializer_list<Shader> Shaders, bool Verbose /* = false */) {
	ShaderProgram ret = {.Shaders = Shaders};
	ret.Handle = glCreateProgram();
	
	for (Shader i : ret.Shaders) {
		glAttachShader(ret.Handle, i.Handle);
	};
	std::cout << "\n";
	glLinkProgram(ret.Handle); /**/

	// print info log
	if (Verbose) {
		std::cerr << "info log for the linked program" << std::endl;
		int log_size = 0;
		int bytes_written = 0;
		glGetProgramiv(ret.Handle, GL_INFO_LOG_LENGTH, &log_size);
		if (log_size){
			char *infoLog = new char[log_size];
			glGetProgramInfoLog(ret.Handle, log_size, &bytes_written, infoLog);
			std::cerr << infoLog << std::endl;
			delete [] infoLog;
		} else {
			std::cout << "\tNo Log\n";
		};
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

int ShaderProgram::ParseSize(std::string s) {
	if (s.compare("float") == 0) {
		return 4;
	} else
	if (s.compare("int") == 0) {
		return 4;
	};
	std::cout << "ShaderProgram::ParseSize(s) error - invalid type\n";
	return -1;
};

GLenum ShaderProgram::ParseGLenum(std::string s) {
	if (s.compare("float") == 0) {
		return GL_FLOAT;
	} else
	if (s.compare("int") == 0) {
		return GL_INT;
	}
	return 0;
	std::cout << "ShaderProgram::ParseGLenum(s) error - invalid type\n";
};

void ShaderProgram::JsonAttribPointers(const char *JsonFilePath, bool Verbose /* = false */) {
	// load attributes into an ordered json object
	std::ifstream f(JsonFilePath);
	nlohmann::ordered_json j;
	f >> j;
	nlohmann::ordered_json attributes_in = j["in"];

	// determine cumulative size of the vertex (for stride)
	int vertex_size = 0;
	for (auto it = attributes_in.begin(); it != attributes_in.end(); ++it) {
		int size = ShaderProgram::ParseSize(it->at("type"));
		vertex_size += size * it->at("components");
	};

	int offset = 0;
	for (auto it = attributes_in.begin(); it != attributes_in.end(); ++it) {
		std::string name = it->at("name");
		GLuint id = this->Attribute(name.c_str());
		glEnableVertexAttribArray(id);
		glVertexAttribPointer(id, it->at("components"), ShaderProgram::ParseGLenum(it->at("type")), GL_FALSE, vertex_size, (const void*)offset);
		if (Verbose) {
			std::cout << "glVertexAttribPointer(" << id <<", " << it->at("components") << ", " << ShaderProgram::ParseGLenum(it->at("type")) << ", GL_FALSE, " << vertex_size<< ", " << offset << ")\n";
		};
		offset += ShaderProgram::ParseSize(it->at("type")) * it->at("components");
	};
};
