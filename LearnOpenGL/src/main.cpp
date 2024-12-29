#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

#include "shader.h"

const unsigned int DEFAULT_WIDTH = 800;
const unsigned int DEFAULT_HEIGHT = 600;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Error: Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Error: Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    Shader shader("main.vert", "main.frag");

    // Vertex data layout
    // +-----------------+-----------------------------+
    // | Position (vec3) |  Texture coordinates (vec2) |
    // +-----------------+-----------------------------+
    // clang-format off
    const GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,   0.5f, 1.0f,
    };
    const GLuint indices[] = {
        0, 1, 2,
    };
    const GLfloat textureCoordinates[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.5f, 1.0f,
    };
    // clang-format on

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))
    );
    glEnableVertexAttribArray(1);

    int width, height, colorChannelCount;
    stbi_set_flip_vertically_on_load(1);
    auto data = stbi_load("container.jpg", &width, &height, &colorChannelCount, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (data != NULL)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Error: Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        double timeValue = glfwGetTime();
        glm::mat4 transform = glm::mat4(1.0f);
        transform =
            glm::rotate(transform, static_cast<float>(timeValue), glm::vec3(0.0f, 0.0f, 1.0f));
        shader.use();
        shader.setUniformMat4("transform", transform);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }
}
