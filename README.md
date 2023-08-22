# Shader Tools
This C++ library is intended to be used in conjunction with OpenGL. Streamlines shader compilation and linking. Includes some common shaders as well for ease-of-access.

## Version Notes

Added support for creating attribpointers from json files. Note - there are minimal checks for validity of json files. Shaders are now linked inside of ShaderProgram::FromShaders()
