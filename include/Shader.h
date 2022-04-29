/* Shader Abstraction */

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
    void Bind() { glUseProgram(program); }
    void Unbind() { glUseProgram(0); }

    // Set uniform named name
    void SetUniform(const std::string &name, const glm::mat4 &mat);
    void SetUniform(const std::string &name, const glm::vec3 &vec);
    void SetUniform(const std::string &name, const int i);

    // Get uniform named name location
    GLint GetUniformLocation(const std::string &name);
    // Set program
    void SetProgram(GLuint prog) { program = prog; }

    // Cleans memory
    void Destroy() { glDeleteProgram(program); }
};
