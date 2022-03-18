#include "Shader.h"

#include <GL/glext.h>
#include <glm/gtc/type_ptr.hpp>

// Convert text from a file to a string
std::string readFile(const char *filePath)
{
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream.is_open())
    {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

// Shader program creation from files (vertex, fragment)
Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    // Read shader files
    std::string vertexShaderStr = readFile(vertexPath);
    std::string fragmentShaderStr = readFile(fragmentPath);

    // Type conversion
    const char *vertexShaderSrc = vertexShaderStr.c_str();
    const char *fragmentShaderSrc = fragmentShaderStr.c_str();

    // Create shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Compile vertex shader
    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);

    // Compile fragment shader
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);

    // Create final shader program
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// Shader program creation from shader files (vertex, fragment, tessellation control, tesselation evaluation)
Shader::Shader(const char *vertexPath,
               const char *fragmentPath,
               const char *tessControlPath,
               const char *tessEvalPath)
{
    // Read shader files
    std::string vertexShaderStr = readFile(vertexPath);
    std::string fragmentShaderStr = readFile(fragmentPath);
    std::string tessControlShaderStr = readFile(tessControlPath);
    std::string tessEvalShaderStr = readFile(tessEvalPath);

    // Type conversion
    const char *vertexShaderSrc = vertexShaderStr.c_str();
    const char *fragmentShaderSrc = fragmentShaderStr.c_str();
    const char *tessControlShaderSrc = tessControlShaderStr.c_str();
    const char *tessEvalShaderSrc = tessEvalShaderStr.c_str();

    // Create shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint tessControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
    GLuint tessEvalShader = glCreateShader(GL_TESS_EVALUATION_SHADER);

    // Compile vertex shader
    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);

    // Compile fragment shader
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);

    // Compile tessellation control shader
    glShaderSource(tessControlShader, 1, &tessControlShaderSrc, NULL);
    glCompileShader(tessControlShader);

    // Compile tessellation evaluation shader
    glShaderSource(tessEvalShader, 1, &tessEvalShaderSrc, NULL);
    glCompileShader(tessEvalShader);

    // Create final shader program
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glAttachShader(program, tessControlShader);
    glAttachShader(program, tessEvalShader);
    glLinkProgram(program);

    // Delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(tessControlShader);
    glDeleteShader(tessEvalShader);
}

Shader::~Shader()
{
    glDeleteProgram(program);
}

// Get uniform named name location
GLint Shader::getUniformLocation(const std::string &name)
{
    return glGetUniformLocation(program, name.c_str());
}

// Set uniform named name to mat
void Shader::SetUniform(const std::string &name, const glm::mat4 &mat)
{
    GLint location = getUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}
