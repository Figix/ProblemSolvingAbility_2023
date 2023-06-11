#pragma once
#pragma comment(lib, "opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

static GLuint textures[2];

GLuint loadTexture(const char* filename, int& width, int& height) {
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filename, &width, &height, nullptr, STBI_rgb_alpha);
    if (!data) {
        std::cerr << "Failed to load image: " << filename << std::endl;
        return 0;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

    return texture;
}

void initialize_texture() {
    string imageFiles[2] = {
        "GameStart.png",
        "GameEnd.png"
    };

    for (int i = 0; i < 2; i++) {
        int width = 1366, height = 768;
        textures[i] = loadTexture(imageFiles[i].c_str(), width, height);
    }
}