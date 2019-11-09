#include "shader.h"
#include <fstream>

// Use either GL_FRAGMENT_SHADER or GL_VERTEX_SHADER
Shader::Shader(unsigned short shadertype) {
  _shaderType = shadertype;
  memset(_shaderSource, 0x00, MAX_SHADER_SIZE);
}

int Shader::loadShaderSource(const std::string path) {
  std::ifstream shaderFile;
  shaderFile.open(path);
  std::string source;
  std::string line;
  if (shaderFile.is_open()) {
    while(getline(shaderFile, line))
    {
      source += line + "\n";
    }

    const char * source_cstr = source.c_str();
    strcpy(_shaderSource, source_cstr);
    shaderFile.close();
    return 0;
  }
  else
  {
    std::cerr << "ERROR - Could not open shaderfile: " << path << std::endl;
  }
  return -1;
}

const unsigned short Shader::getShaderType() {
  return _shaderType;
}

const char * Shader::getShaderSource() {
  return _shaderSource;
}

GLuint Shader::compile() {
  GLuint s = glCreateShader(_shaderType);
  // Avoid const issues with a stack variable.
  const char * src = getShaderSource();
  glShaderSource(s, 1, &src, NULL);
  glCompileShader(s);
  return s;
}

