# Shader Tools
This C++ library is intended to be used in conjunction with OpenGL.

## Version Notes

v0.1 - BROKEN work (doesn't link programs inside ShaderProgram::FromShaders() )

v0.2 - added support for creating attribpointers from json files. Note - there are minimal checks for validity of json files
	Actually works now (shaders are linked inside of ShaderProgram::FromShaders() )