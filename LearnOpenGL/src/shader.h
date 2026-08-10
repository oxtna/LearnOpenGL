#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader
{
  public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    // Make OpenGL use the shader program represented by this object.
    void use();

    // ID given by OpenGL for this program object.
    GLuint id() const;

    // Get the value of the uniform with the given name in this shader program.
    GLint getUniformInt(const std::string& name) const;
    GLfloat getUniformFloat(const std::string& name) const;
    glm::vec2 getUniformVec2(const std::string& name) const;
    glm::vec3 getUniformVec3(const std::string& name) const;
    glm::vec4 getUniformVec4(const std::string& name) const;
    glm::mat2 getUniformMat2(const std::string& name) const;
    glm::mat3 getUniformMat3(const std::string& name) const;
    glm::mat4 getUniformMat4(const std::string& name) const;

    // Set the value of the uniform with the given name in this shader program.
    // Requires using this shader program.
    void setUniformInt(const std::string& name, GLint value);
    void setUniformFloat(const std::string& name, GLfloat value);
    void setUniformVec2(const std::string& name, const glm::vec2& vec);
    void setUniformVec2(const std::string& name, GLfloat x, GLfloat y);
    void setUniformVec3(const std::string& name, const glm::vec3& vec);
    void setUniformVec3(const std::string& name, GLfloat x, GLfloat y, GLfloat z);
    void setUniformVec4(const std::string& name, const glm::vec4& vec);
    void setUniformVec4(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void setUniformMat2(const std::string& name, const glm::mat2& mat);
    void setUniformMat3(const std::string& name, const glm::mat3& mat);
    void setUniformMat4(const std::string& name, const glm::mat4& mat);

  private:
    GLuint _id;
};
