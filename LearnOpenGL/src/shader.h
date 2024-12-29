#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
  public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void id(GLuint id);
    GLuint id() const;

    void setUniformInt(const char* name, GLint value);
    void setUniformFloat(const char* name, GLfloat value);
    void setUniformVec2(const char* name, const glm::vec2& vec);
    void setUniformVec2(const char* name, GLfloat x, GLfloat y);
    void setUniformVec3(const char* name, const glm::vec3& vec);
    void setUniformVec3(const char* name, GLfloat x, GLfloat y, GLfloat z);
    void setUniformVec4(const char* name, const glm::vec4& vec);
    void setUniformVec4(const char* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void setUniformMat2(const char* name, const glm::mat2& mat);
    void setUniformMat3(const char* name, const glm::mat3& mat);
    void setUniformMat4(const char* name, const glm::mat4& mat);

    void use();

  private:
    GLuint _id;
};
