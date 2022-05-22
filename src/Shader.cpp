/* Shader Class Abstraction */

#include "Shader.h"

#include <GL/glext.h>
#include <glm/gtc/type_ptr.hpp>

namespace GLhf
{

    // Convert text from a file to a string
    std::string readFile(const char *file_path)
    {
        std::string content;
        std::ifstream file_stream(file_path, std::ios::in);

        if (!file_stream.is_open())
        {
            std::cerr << "Could not read file " << file_path << ". File does not exist." << std::endl;
            return "";
        }

        std::string line = "";
        while (!file_stream.eof())
        {
            std::getline(file_stream, line);
            content.append(line + "\n");
        }

        file_stream.close();
        return content;
    }

    // Shader program_ creation from files (vertex, fragment)
    void Shader::Create(const char *vertex_shader_name, const char *fragment_shader_name)
    {
        // Change "texture.vs" to "../resources/texture.vs"
        // --------------------------------------------------------------
        char vertex_shader_path[100];
        char fragment_shader_path[100];
        const std::string directory_path("../resources/shaders/");
        const std::string new_vertex_path(directory_path + vertex_shader_name);
        strcpy(vertex_shader_path, new_vertex_path.c_str());
        const std::string new_fragment_path = directory_path + fragment_shader_name;
        strcpy(fragment_shader_path, new_fragment_path.c_str());
        
        // Read shader files
        // -----------------
        std::string vertex_shader_str = readFile(vertex_shader_path);
        std::string fragment_shader_str = readFile(fragment_shader_path);

        // Type conversion
        // ---------------
        const char *vertex_shader_src = vertex_shader_str.c_str();
        const char *fragment_shader_src = fragment_shader_str.c_str();

        // Create shaders
        // --------------
        GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

        // Compile vertex shader
        // ---------------------
        glShaderSource(vertex_shader, 1, &vertex_shader_src, NULL);
        glCompileShader(vertex_shader);

        // Compile fragment shader
        // -----------------------
        glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);
        glCompileShader(fragment_shader);

        // Create final shader program_
        // ---------------------------
        program_ = glCreateProgram(); // must be != 0
        glAttachShader(program_, vertex_shader);
        glAttachShader(program_, fragment_shader);
        glLinkProgram(program_);

        // Delete shaders
        // --------------
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }

    // Shader program_ creation from shader files (vertex, fragment, tessellation control, tesselation evaluation)
    void Shader::Create(const char *vertex_path,
                const char *fragment_path,
                const char *tessellation_control_path,
                const char *tessellation_evaluation_path)
    {
        // Read shader files
        std::string vertex_shader_str = readFile(vertex_path);
        std::string fragment_shader_str = readFile(fragment_path);
        std::string tessellation_control_shader_str = readFile(tessellation_control_path);
        std::string tessellation_evaluation_shader_str = readFile(tessellation_evaluation_path);

        // Type conversion
        const char *vertex_shader_src = vertex_shader_str.c_str();
        const char *fragment_shader_src = fragment_shader_str.c_str();
        const char *tessellation_control_shader_src = tessellation_control_shader_str.c_str();
        const char *tessellation_evaluation_shader_src = tessellation_evaluation_shader_str.c_str();

        // Create shaders
        GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        GLuint tessellation_control_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
        GLuint tessellation_evaluation_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);

        // Compile vertex shader
        glShaderSource(vertex_shader, 1, &vertex_shader_src, NULL);
        glCompileShader(vertex_shader);

        // Compile fragment shader
        glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);
        glCompileShader(fragment_shader);

        // Compile tessellation control shader
        glShaderSource(tessellation_control_shader, 1, &tessellation_control_shader_src, NULL);
        glCompileShader(tessellation_control_shader);

        // Compile tessellation evaluation shader
        glShaderSource(tessellation_evaluation_shader, 1, &tessellation_evaluation_shader_src, NULL);
        glCompileShader(tessellation_evaluation_shader);

        // Create final shader program_
        program_ = glCreateProgram();
        glAttachShader(program_, vertex_shader);
        glAttachShader(program_, fragment_shader);
        glAttachShader(program_, tessellation_control_shader);
        glAttachShader(program_, tessellation_evaluation_shader);
        glLinkProgram(program_);

        // Delete shaders
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        glDeleteShader(tessellation_control_shader);
        glDeleteShader(tessellation_evaluation_shader);
    }

    // Get uniform named name location
    GLint Shader::GetUniformLocation(const std::string &name)
    {
        return glGetUniformLocation(program_, name.c_str());
    }

    // Set uniform named name to mat
    void Shader::SetUniform(const std::string &name, const glm::mat4 &mat)
    {
        GLint location = GetUniformLocation(name);
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
    }

    void Shader::SetUniform(const std::string &name, const glm::vec3 &vec)
    {
        GLint location = GetUniformLocation(name);
        glUniform3fv(location, 1, glm::value_ptr(vec));
    }

    void Shader::SetUniform(const std::string &name, const int i)
    {
        GLint location = GetUniformLocation(name);
        glUniform1i(location, i);
    }

}