#pragma once
#pragma comment(lib, "opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

static GLuint textures[7];

GLuint loadTexture(const char* filename, int& width, int& height) {
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filename, &width, &height, nullptr, STBI_rgb_alpha);
    if (!data) {
        std::cerr << "Failed to load image: " << filename << std::endl;
        return 0;
    }
    cout << filename << endl;
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

    return texture;
}

void initialize_texture() {
    string imageFiles[7] = {
        "GameStart.png",
        "GameEnd.png",
        "s1Among.png",
        "s2Among.png",
        "s3Among.png",
        "s4Among.png",
        "s5Among.png"
    };

    for (int i = 0; i < 7; i++) {
        int width = 1366, height = 768;
        textures[i] = loadTexture(imageFiles[i].c_str(), width, height);
    }
}