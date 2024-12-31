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
    // Get the value of the uniform with the given name in this shader program.
    GLfloat getUniformFloat(const char* name) const;
    // Get the value of the uniform with the given name in this shader program.
    glm::vec2 getUniformVec2(const char* name) const;
    // Get the value of the uniform with the given name in this shader program.
    glm::vec3 getUniformVec3(const char* name) const;
    // Get the value of the uniform with the given name in this shader program.
    glm::vec4 getUniformVec4(const char* name) const;
    // Get the value of the uniform with the given name in this shader program.
    glm::mat2 getUniformMat2(const char* name) const;
    // Get the value of the uniform with the given name in this shader program.
    glm::mat3 getUniformMat3(const char* name) const;
    // Get the value of the uniform with the given name in this shader program.
    glm::mat4 getUniformMat4(const char* name) const;

    // Set the value of the uniform with the given name in this shader program.
    // Requires using this shader program.
    void setUniformInt(const char* name, GLint value);
    // Set the value of the uniform with the given name in this shader program.
    // Requires using this shader program.
    void setUniformFloat(const char* name, GLfloat value);
    // Set the value of the uniform with the given name in this shader program.
    // Requires using this shader program.
    void setUniformVec2(const char* name, const glm::vec2& vec);
    // Set the value of the uniform with the given name in this shader program.
    // Requires using this shader program.
    void setUniformVec2(const char* name, GLfloat x, GLfloat y);
    // Set the value of the uniform with the given name in this shader program.
    // Requires using this shader program.
    void setUniformVec3(const char* name, const glm::vec3& vec);
    // Set the value of the uniform with the given name in this shader program.
    // Requires using this shader program.
    void setUniformVec3(const char* name, GLfloat x, GLfloat y, GLfloat z);
    // Set the value of the uniform with the given name in this shader program.
    // Requires using this shader program.
    void setUniformVec4(const char* name, const glm::vec4& vec);
    // Set the value of the uniform with the given name in this shader program.
    // Requires using this shader program.
    void setUniformVec4(const char* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    // Set the value of the uniform with the given name in this shader program.
    // Requires using this shader program.
    void setUniformMat2(const char* name, const glm::mat2& mat);
    // Set the value of the uniform with the given name in this shader program.
    // Requires using this shader program.
    void setUniformMat3(const char* name, const glm::mat3& mat);
    // Set the value of the uniform with the given name in this shader program.
    // Requires using this shader program.
    void setUniformMat4(const char* name, const glm::mat4& mat);

  private:
    GLuint _id;
};
