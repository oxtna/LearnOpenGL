#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
  public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    // Make OpenGL use the shader program represented by this object.
    void use();

    // ID given by OpenGL after creating the shader program.
    GLuint id() const;

    // Get the value of the uniform with the given name in this shader program.
    GLint getUniformInt(const char* name) const;
    GLfloat getUniformFloat(const char* name) const;
    glm::vec2 getUniformVec2(const char* name) const;
    glm::vec3 getUniformVec3(const char* name) const;
    glm::vec4 getUniformVec4(const char* name) const;
    glm::mat2 getUniformMat2(const char* name) const;
    glm::mat3 getUniformMat3(const char* name) const;
    glm::mat4 getUniformMat4(const char* name) const;

    // Set the value of the uniform with the given name in this shader program.
    // Requires using this shader program.
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

  private:
    GLuint _id;
};
