#include "shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexFilename, const char* fragmentFilename)
{
    std::string vertexSource;
    std::string fragmentSource;
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;

    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vertexShaderFile.open(vertexFilename);
        std::ostringstream vertexShaderStream;
        vertexShaderStream << vertexShaderFile.rdbuf();
        vertexShaderFile.close();
        vertexSource = vertexShaderStream.str();

        fragmentShaderFile.open(fragmentFilename);
        std::ostringstream fragmentShaderStream;
        fragmentShaderStream << fragmentShaderFile.rdbuf();
        fragmentShaderFile.close();
        fragmentSource = fragmentShaderStream.str();
    }
    catch (const std::ifstream::failure& e)
    {
        std::cerr << "Error: Shader source file reading failed\n" << e.what() << std::endl;
    }

    GLint success;
    const GLsizei INFO_LOG_SIZE = 512;
    GLchar infoLog[INFO_LOG_SIZE]{};

    const GLchar* vertexSourceCode = vertexSource.c_str();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSourceCode, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, INFO_LOG_SIZE, NULL, infoLog);
        std::cerr << "Error: Vertex shader compilation failed\n" << infoLog << std::endl;
    }

    const GLchar* fragmentSourceCode = fragmentSource.c_str();
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSourceCode, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, INFO_LOG_SIZE, NULL, infoLog);
        std::cerr << "Error: Fragment shader compilation failed\n" << infoLog << std::endl;
    }

    _id = glCreateProgram();
    glAttachShader(_id, vertexShader);
    glAttachShader(_id, fragmentShader);
    glLinkProgram(_id);

    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(_id, INFO_LOG_SIZE, NULL, infoLog);
        std::cerr << "Error: Program linking failed\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(_id);
}

void Shader::id(GLuint id)
{
    _id = id;
}

GLuint Shader::id() const
{
    return _id;
}

void Shader::setUniformInt(const char* name, GLint value)
{
    glUniform1i(glGetUniformLocation(_id, name), value);
}

void Shader::setUniformFloat(const char* name, GLfloat value)
{
    glUniform1f(glGetUniformLocation(_id, name), value);
}

void Shader::use()
{
    glUseProgram(_id);
}
