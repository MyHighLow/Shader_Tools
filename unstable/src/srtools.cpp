#include "srtools.h"

namespace srt {

	void print_info_log(GLuint obj) {
		int log_size = 0;
		int bytes_written = 0;
		glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &log_size);
		if (!log_size) return;
		char *infoLog = new char[log_size];
		glGetProgramInfoLog(obj, log_size, &bytes_written, infoLog);
		std::cerr << infoLog << std::endl;
		delete [] infoLog;
	};

	// ShaderDescriptor
	bool ShaderDescriptor::compile() {
		std::ifstream is(this->path.c_str(), std::ios::in|std::ios::binary|std::ios::ate);
		if (!is.is_open()) {
			std::cerr << "Unable to open file " << this->path << std::endl;
			return false;
		}
		long size = is.tellg();
		char *buffer = new char[size+1];
		is.seekg(0, std::ios::beg);
		is.read (buffer, size);
		is.close();
		buffer[size] = 0;

		this->handle = glCreateShader(this->type);
		glShaderSource(this->handle, 1, (const GLchar**)&buffer, NULL);
		glCompileShader(this->handle);
		std::cerr << "info log for " << this->path << std::endl;
		srt::print_info_log(this->handle);
		delete [] buffer;
		return true;
	};

	// ShaderProgramDescriptor
	ShaderProgramDescriptor::ShaderProgramDescriptor(std::string folder, SHADER_TYPE included_shaders) : included_shaders{included_shaders} {
		if (folder[folder.length()-1] != '/') {
			folder.push_back('/');
		};

		if (this->included_shaders & VERTEX_SHADER) {
			//printf("vert.glsl\n");
			std::string vpath = folder + "vert.glsl";
			std::ifstream vfs(vpath.c_str());
			this->vertex_shader_descriptor = ShaderDescriptor{GL_VERTEX_SHADER, vpath};
			vfs.close();
		};

		if (this->included_shaders & GEOMETRY_SHADER) {
			//printf("geo.glsl\n");
			std::string gpath = folder + "geo.glsl";
			std::ifstream gfs(gpath.c_str());
			this->geometry_shader_descriptor = ShaderDescriptor{GL_GEOMETRY_SHADER, gpath};
			gfs.close();
		};

		if (this->included_shaders & FRAGMENT_SHADER) {
			//printf("frag.glsl\n");
			std::string fpath = folder + "frag.glsl";
			std::ifstream ffs(fpath.c_str());
			this->fragment_shader_descriptor = ShaderDescriptor{GL_FRAGMENT_SHADER, fpath};
			ffs.close();
		};

		if (this->included_shaders & COMPUTE_SHADER) {
			//printf("comp.glsl\n");
			std::string cpath = folder + "comp.glsl";
			std::ifstream cfs(cpath.c_str());
			this->compute_shader_descriptor = ShaderDescriptor{GL_COMPUTE_SHADER, cpath};
			cfs.close();
		};
	};

	void ShaderProgramDescriptor::compile() {
		if (this->included_shaders & srt::VERTEX_SHADER) {
			this->vertex_shader_descriptor.compile();
		};
		if (this->included_shaders & srt::FRAGMENT_SHADER) {
			this->fragment_shader_descriptor.compile();
		};
		if (this->included_shaders & srt::GEOMETRY_SHADER) {
			this->geometry_shader_descriptor.compile();
		};
		if (this->included_shaders & srt::COMPUTE_SHADER) {
			this->compute_shader_descriptor.compile();
		};
	};

	void ShaderProgramDescriptor::link() {
		this->program_handle = glCreateProgram();
		if (this->included_shaders & srt::VERTEX_SHADER) {
			glAttachShader(this->program_handle, this->vertex_shader_descriptor.handle);
		};
		if (this->included_shaders & srt::FRAGMENT_SHADER) {
			glAttachShader(this->program_handle, this->fragment_shader_descriptor.handle);
		};
		if (this->included_shaders & srt::GEOMETRY_SHADER) {
			glAttachShader(this->program_handle, this->geometry_shader_descriptor.handle);
		};
		if (this->included_shaders & srt::COMPUTE_SHADER) {
			glAttachShader(this->program_handle, this->compute_shader_descriptor.handle);
		};
		glLinkProgram(this->program_handle);
		std::cerr << "info log for the linked program" << std::endl;
		srt::print_info_log(this->program_handle);
	};

	void ShaderProgramDescriptor::use() {
		glUseProgram(this->program_handle);
	};

	GLuint ShaderProgramDescriptor::uniform(const char *name) {
		return glGetUniformLocation(this->program_handle, name);
	};

	GLuint ShaderProgramDescriptor::attribute(const char *name) {
		return glGetAttribLocation(this->program_handle, name);
	};



	void ShaderProgramDescriptor::EZAttribPointer(const char *AttributeName, const int NumComponents, const int Stride, const int Offset) {
		GLuint id = this->attribute(AttributeName);
		glEnableVertexAttribArray(id);
		glVertexAttribPointer(id, NumComponents, GL_FLOAT, GL_FALSE, Stride, (const void*)Offset);
	};
	
	

};