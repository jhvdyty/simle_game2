#ifndef CHARACTER_H
#define CHARACTER_H

#include <glad/glad.h> 

#include <string> 
#include <fstream> 
#include <sstream> 
#include <iostream> 

#include "shader.h"
#include "stb_image.h"
#include "collide.h"

#include <GLFW/glfw3.h> 

class Character {
private:
    float x, y;
    float speed;
    float width, height;
    unsigned int VAO, VBO, EBO;
    unsigned int texture1, texture2;
    Shader shader;
    Collide& obj;

    unsigned int loadTexture(const char* path) {
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;
        unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        return textureID;
    }

public:
    Character(float startX, float startY, float characterWidth, float characterHeight, float moveSpeed,
        const char* vertexPath, const char* fragmentPath,
        const char* texturePath1, const char* texturePath2,
        Collide& collideObj)
        : x(startX), y(startY), width(characterWidth), height(characterHeight), speed(moveSpeed),
        shader(vertexPath, fragmentPath), obj(collideObj) {
        setupMesh();
        texture1 = loadTexture(texturePath1);
        texture2 = loadTexture(texturePath2);
    }

    bool isColliding(float newX, float newY) {
        // Check if the new position of the character overlaps with the object
        if (newX + width / 2 >= obj.getX() - obj.getWidth() / 2 && newX - width / 2 <= obj.getX() + obj.getWidth() / 2) {
            if (newY + height / 2 >= obj.getY() - obj.getHeight() / 2 && newY - height / 2 <= obj.getY() + obj.getHeight() / 2) {
                return true; // Collision detected
            }
        }
        return false; // No collision
    }


    void setupMesh() {
        float vertices[] = {
            // Positions                    // Colors           // Texture Coords
             width / 2,  height / 2, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
             width / 2, -height / 2, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
            -width / 2, -height / 2, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
            -width / 2,  height / 2, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
        };

        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    void move(float dx, float dy) {
        float newX = x + dx;
        float newY = y + dy;

        // Check for collision with the object
        if (isColliding(newX, newY)) {
            return;
        }
        x = newX;
        y = newY;
    }

    void draw(float mixValue) {
        shader.Use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        shader.setInt("ourTexture1", 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        shader.setInt("ourTexture2", 1);

        glUniform1f(glGetUniformLocation(shader.Program, "mixValue"), mixValue);
        glUniform1f(glGetUniformLocation(shader.Program, "x_mov"), x);
        glUniform1f(glGetUniformLocation(shader.Program, "y_mov"), y);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void processInput(GLFWwindow* window, float deltaTime) {
        float movement = speed * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            move(-movement, 0);
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            move(movement, 0);
        }
        move(0, -movement);
    }

    ~Character() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }





};




#endif