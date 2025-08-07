#include "shader.h"
#include <glm/gtc/type_ptr.hpp>
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

#ifdef _DEBUG
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
#endif

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
#ifdef _DEBUG
        std::cerr << "Error: Shader source file reading failed\n"
                  << e.what() << '\n';
#endif
    }

#ifdef _DEBUG
    GLint success;
    constexpr GLsizei INFO_LOG_SIZE = 512;
    GLchar infoLog[INFO_LOG_SIZE]{};
#endif

    const GLchar* vertexSourceCode = vertexSource.c_str();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSourceCode, NULL);
    glCompileShader(vertexShader);

#ifdef _DEBUG
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, INFO_LOG_SIZE, NULL, infoLog);
        std::cerr << "Error: Vertex shader compilation failed\n" << infoLog << '\n';
    }
#endif

    const GLchar* fragmentSourceCode = fragmentSource.c_str();
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSourceCode, NULL);
    glCompileShader(fragmentShader);

#ifdef _DEBUG
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, INFO_LOG_SIZE, NULL, infoLog);
        std::cerr << "Error: Fragment shader compilation failed\n"
                  << infoLog << '\n';
    }
#endif

    _id = glCreateProgram();
    glAttachShader(_id, vertexShader);
    glAttachShader(_id, fragmentShader);
    glLinkProgram(_id);

#ifdef _DEBUG
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(_id, INFO_LOG_SIZE, NULL, infoLog);
        std::cerr << "Error: Program linking failed\n" << infoLog << '\n';
    }
#endif

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(_id);
}

void Shader::use()
{
    glUseProgram(_id);
}

GLuint Shader::id() const
{
    return _id;
}

GLint Shader::getUniformInt(const char* name) const
{
    GLint value;
    glGetUniformiv(_id, glGetUniformLocation(_id, name), &value);
    return value;
}

GLfloat Shader::getUniformFloat(const char* name) const
{
    GLfloat value;
    glGetUniformfv(_id, glGetUniformLocation(_id, name), &value);
    return value;
}

glm::vec2 Shader::getUniformVec2(const char* name) const
{
    glm::vec2 value;
    glGetnUniformfv(_id, glGetUniformLocation(_id, name), 2, glm::value_ptr(value));
    return value;
}

glm::vec3 Shader::getUniformVec3(const char* name) const
{
    glm::vec3 value;
    glGetnUniformfv(_id, glGetUniformLocation(_id, name), 2, glm::value_ptr(value));
    return value;
}

glm::vec4 Shader::getUniformVec4(const char* name) const
{
    glm::vec4 value;
    glGetnUniformfv(_id, glGetUniformLocation(_id, name), 2, glm::value_ptr(value));
    return value;
}

glm::mat2 Shader::getUniformMat2(const char* name) const
{
    glm::mat2 value;
    glGetnUniformfv(_id, glGetUniformLocation(_id, name), 2, glm::value_ptr(value));
    return value;
}

glm::mat3 Shader::getUniformMat3(const char* name) const
{
    glm::mat3 value;
    glGetnUniformfv(_id, glGetUniformLocation(_id, name), 2, glm::value_ptr(value));
    return value;
}

glm::mat4 Shader::getUniformMat4(const char* name) const
{
    glm::mat4 value;
    glGetnUniformfv(_id, glGetUniformLocation(_id, name), 2, glm::value_ptr(value));
    return value;
}

void Shader::setUniformInt(const char* name, GLint value)
{
    glUniform1i(glGetUniformLocation(_id, name), value);
}

void Shader::setUniformFloat(const char* name, GLfloat value)
{
    glUniform1f(glGetUniformLocation(_id, name), value);
}

void Shader::setUniformVec2(const char* name, const glm::vec2& vec)
{
    glUniform2fv(glGetUniformLocation(_id, name), 1, glm::value_ptr(vec));
}

void Shader::setUniformVec2(const char* name, GLfloat x, GLfloat y)
{
    glUniform2f(glGetUniformLocation(_id, name), x, y);
}

void Shader::setUniformVec3(const char* name, const glm::vec3& vec)
{
    glUniform3fv(glGetUniformLocation(_id, name), 1, glm::value_ptr(vec));
}

void Shader::setUniformVec3(const char* name, GLfloat x, GLfloat y, GLfloat z)
{
    glUniform3f(glGetUniformLocation(_id, name), x, y, z);
}

void Shader::setUniformVec4(const char* name, const glm::vec4& vec)
{
    glUniform4fv(glGetUniformLocation(_id, name), 1, glm::value_ptr(vec));
}

void Shader::setUniformVec4(
    const char* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w
)
{
    glUniform4f(glGetUniformLocation(_id, name), x, y, z, w);
}

void Shader::setUniformMat2(const char* name, const glm::mat2& mat)
{
    glUniformMatrix2fv(
        glGetUniformLocation(_id, name), 1, GL_FALSE, glm::value_ptr(mat)
    );
}

void Shader::setUniformMat3(const char* name, const glm::mat3& mat)
{
    glUniformMatrix3fv(
        glGetUniformLocation(_id, name), 1, GL_FALSE, glm::value_ptr(mat)
    );
}

void Shader::setUniformMat4(const char* name, const glm::mat4& mat)
{
    glUniformMatrix4fv(
        glGetUniformLocation(_id, name), 1, GL_FALSE, glm::value_ptr(mat)
    );
}
