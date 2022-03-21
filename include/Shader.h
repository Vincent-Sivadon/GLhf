#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <glad/glad.h>

#include <glm/glm.hpp>

class Shader
{
private:
    // Shader program
    GLuint program;

    // Get uniform named name location
    GLint getUniformLocation(const std::string &name);

public:
    Shader() {}
    // Shader program creation from files (vertex, fragment)
    Shader(const char *vertexPath, const char *fragmentPath);
    // Shader program creation from shader files (vertex, fragment, tessellation control, tesselation evaluation)
    Shader(const char *vertexPath,
           const char *fragmentPath,
           const char *tessControlPath,
           const char *tessEvalPath);
    // Delete shader program memory
    ~Shader(){};

    // Bind the shader program
    void bind() { glUseProgram(program); }
    void unbind() { glUseProgram(0); }

    // Set uniform named name to mat
    void SetUniform(const std::string &name, const glm::mat4 &mat);

    // Cleans memory
    void destroy() { glDeleteProgram(program); }
};
