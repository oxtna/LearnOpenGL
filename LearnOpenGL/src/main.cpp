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

#include "time.h"
#include "camera.h"
#include "shader.h"

constexpr unsigned int DEFAULT_WIDTH = 800;
constexpr unsigned int DEFAULT_HEIGHT = 600;

bool mousePressed = false;
double lastMouseX = 0.0;
double lastMouseY = 0.0;

Camera camera(
    glm::vec3(0.0f, 0.0f, 3.0f), Camera::DefaultWorldUp, Camera::DefaultYaw,
    Camera::DefaultPitch, Camera::DefaultFieldOfView
);

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers);
void cursorPosCallback(GLFWwindow* window, double xPosition, double yPosition);
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void processInput(GLFWwindow* window);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window =
        glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Error: Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, scrollCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Error: Failed to initialize GLAD\n";
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader shader("main.vert", "main.frag");

    // Vertex data layout
    // +-----------------+-----------------------------+
    // | Position (vec3) |  Texture coordinates (vec2) |
    // +-----------------+-----------------------------+
    // clang-format off
    GLfloat vertices[] = {
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,

         0.5f,  0.5f,  0.5f,   0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f, 1.0f,

         0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f,

         0.5f, -0.5f,  0.5f,   0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,   1.0f, 1.0f,
    };
    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,
        
        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20,
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
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            width,
            height,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            data
        );
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Error: Failed to load texture\n";
    }

    stbi_image_free(data);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Time::update();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(
            model, Time::time() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f)
        );
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(
            glm::radians(camera.fieldOfView()),
            static_cast<float>(DEFAULT_WIDTH) / static_cast<float>(DEFAULT_HEIGHT),
            0.1f,
            100.0f
        );
        shader.use();
        shader.setUniformMat4("model", model);
        shader.setUniformMat4("view", view);
        shader.setUniformMat4("projection", projection);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(
            GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0
        );

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            mousePressed = true;
        }
        else
        {
            mousePressed = false;
        }
    }
}

void cursorPosCallback(GLFWwindow* window, double xPosition, double yPosition)
{
    if (mousePressed)
    {
        float deltaX = static_cast<float>(lastMouseX - xPosition);
        float deltaY = static_cast<float>(yPosition - lastMouseY);
        deltaX *= camera.Sensitivity;
        deltaY *= camera.Sensitivity;
        camera.rotate(deltaX, deltaY);
    }
    lastMouseX = xPosition;
    lastMouseY = yPosition;
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    camera.fieldOfView(camera.fieldOfView() - static_cast<float>(yOffset));
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.translate(camera.front() * camera.Speed * Time::deltaTime());
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.translate(-camera.front() * camera.Speed * Time::deltaTime());
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.translate(-camera.right() * camera.Speed * Time::deltaTime());
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.translate(camera.right() * camera.Speed * Time::deltaTime());
    }
}
