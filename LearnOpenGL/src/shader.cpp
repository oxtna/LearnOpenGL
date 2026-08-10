#include "shader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <logging/logs.h>
#include <format>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>

Shader::Shader(const std::string& vertexFilename, const std::string& fragmentFilename) : _id{}
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
        logging::error(std::format("Shader source file reading failed: {}", e.what()));
    }

    GLint success = GL_TRUE;
    GLsizei infoLogLength = 0;

    logging::debug(std::format("Creating and compiling vertex shader: {}", vertexFilename));
    const GLchar* vertexSourceCode = vertexSource.c_str();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (vertexShader == 0)
    {
        logging::error(std::format("Vertex shader creation failed: {}", glGetError()));
    }
    glShaderSource(vertexShader, 1, &vertexSourceCode, nullptr);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        logging::error(std::format("Vertex shader compilation failed: {}", vertexFilename));
    }

    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        std::string infoLog(infoLogLength, '\0');
        glGetShaderInfoLog(vertexShader, infoLogLength, nullptr, infoLog.data());
        logging::info(std::format("Vertex shader info log: {}", infoLog));
    }

    logging::debug(std::format("Creating and compiling fragment shader: {}", fragmentFilename));
    const GLchar* fragmentSourceCode = fragmentSource.c_str();
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (fragmentShader == 0)
    {
        logging::error(std::format("Fragment shader creation failed: {}", glGetError()));
    }
    glShaderSource(fragmentShader, 1, &fragmentSourceCode, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        logging::error(std::format("Fragment shader compilation failed: {}", fragmentFilename));
    }

    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        std::string infoLog(infoLogLength, '\0');
        glGetShaderInfoLog(fragmentShader, infoLogLength, nullptr, infoLog.data());
        logging::info(std::format("Fragment shader info log: {}", infoLog));
    }

    logging::debug("Creating program object and attaching compiled shaders to it");
    _id = glCreateProgram();
    if (_id == 0)
    {
        logging::error(std::format("Program object creation failed: {}", glGetError()));
    }
    glAttachShader(_id, vertexShader);
    glAttachShader(_id, fragmentShader);
    glLinkProgram(_id);

    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        logging::error(std::format("Program object linking failed: {}", glGetError()));
    }

    glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        std::string infoLog(infoLogLength, '\0');
        glGetProgramInfoLog(_id, infoLogLength, nullptr, infoLog.data());
        logging::info(std::format("Program object info log: {}", infoLog));
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    logging::debug(std::format("Created program object: {}", _id));
}

Shader::~Shader()
{
    logging::debug(std::format("Deleting program object: {}", _id));
    glDeleteProgram(_id);
}

Shader::Shader(Shader&& other) noexcept : _id{std::exchange(other._id, 0)}
{
}

Shader& Shader::operator=(Shader&& other) noexcept
{
    _id = std::exchange(other._id, 0);
    return *this;
}

void Shader::use()
{
    glUseProgram(_id);
}

GLuint Shader::id() const
{
    return _id;
}

GLint Shader::getUniformInt(const std::string& name) const
{
    GLint value;
    glGetUniformiv(_id, glGetUniformLocation(_id, name.c_str()), &value);
    return value;
}

GLfloat Shader::getUniformFloat(const std::string& name) const
{
    GLfloat value;
    glGetUniformfv(_id, glGetUniformLocation(_id, name.c_str()), &value);
    return value;
}

glm::vec2 Shader::getUniformVec2(const std::string& name) const
{
    glm::vec2 value;
    glGetnUniformfv(_id, glGetUniformLocation(_id, name.c_str()), 2, glm::value_ptr(value));
    return value;
}

glm::vec3 Shader::getUniformVec3(const std::string& name) const
{
    glm::vec3 value;
    glGetnUniformfv(_id, glGetUniformLocation(_id, name.c_str()), 2, glm::value_ptr(value));
    return value;
}

glm::vec4 Shader::getUniformVec4(const std::string& name) const
{
    glm::vec4 value;
    glGetnUniformfv(_id, glGetUniformLocation(_id, name.c_str()), 2, glm::value_ptr(value));
    return value;
}

glm::mat2 Shader::getUniformMat2(const std::string& name) const
{
    glm::mat2 value;
    glGetnUniformfv(_id, glGetUniformLocation(_id, name.c_str()), 2, glm::value_ptr(value));
    return value;
}

glm::mat3 Shader::getUniformMat3(const std::string& name) const
{
    glm::mat3 value;
    glGetnUniformfv(_id, glGetUniformLocation(_id, name.c_str()), 2, glm::value_ptr(value));
    return value;
}

glm::mat4 Shader::getUniformMat4(const std::string& name) const
{
    glm::mat4 value;
    glGetnUniformfv(_id, glGetUniformLocation(_id, name.c_str()), 2, glm::value_ptr(value));
    return value;
}

void Shader::setUniformInt(const std::string& name, GLint value)
{
    glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
}

void Shader::setUniformFloat(const std::string& name, GLfloat value)
{
    glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
}

void Shader::setUniformVec2(const std::string& name, const glm::vec2& vec)
{
    glUniform2fv(glGetUniformLocation(_id, name.c_str()), 1, glm::value_ptr(vec));
}

void Shader::setUniformVec2(const std::string& name, GLfloat x, GLfloat y)
{
    glUniform2f(glGetUniformLocation(_id, name.c_str()), x, y);
}

void Shader::setUniformVec3(const std::string& name, const glm::vec3& vec)
{
    glUniform3fv(glGetUniformLocation(_id, name.c_str()), 1, glm::value_ptr(vec));
}

void Shader::setUniformVec3(const std::string& name, GLfloat x, GLfloat y, GLfloat z)
{
    glUniform3f(glGetUniformLocation(_id, name.c_str()), x, y, z);
}

void Shader::setUniformVec4(const std::string& name, const glm::vec4& vec)
{
    glUniform4fv(glGetUniformLocation(_id, name.c_str()), 1, glm::value_ptr(vec));
}

void Shader::setUniformVec4(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    glUniform4f(glGetUniformLocation(_id, name.c_str()), x, y, z, w);
}

void Shader::setUniformMat2(const std::string& name, const glm::mat2& mat)
{
    glUniformMatrix2fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setUniformMat3(const std::string& name, const glm::mat3& mat)
{
    glUniformMatrix3fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setUniformMat4(const std::string& name, const glm::mat4& mat)
{
    glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}
