#pragma once

#include <glad/glad.h>

class Shader
{
  public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void id(GLuint id);
    GLuint id() const;

    void setUniformInt(const char* name, GLint value);
    void setUniformFloat(const char* name, GLfloat value);

    void use();

  private:
    GLuint _id;
};
