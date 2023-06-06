#pragma once
#pragma comment(lib, "opengl32.lib")
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

GLuint textures[1];  // �ؽ�ó �迭 ũ�� ����

GLuint loadBMPTexture(const char* filename, int& width, int& height) {
    GLuint textureID;
    unsigned char* imageData;
    FILE* file;

    fopen_s(&file, filename, "rb");
    if (!file) {
        std::cout << "Could not open file: " << filename << std::endl;
        return 0;
    }

    unsigned char header[54];
    if (fread(header, 1, 54, file) != 54) {
        std::cout << "Invalid BMP file: " << filename << std::endl;
        fclose(file);
        return 0;
    }

    if (header[0] != 'B' || header[1] != 'M') {
        std::cout << "Invalid BMP file: " << filename << std::endl;
        fclose(file);
        return 0;
    }

    int dataPos = *(int*)&(header[0x0A]);
    int imageSize = *(int*)&(header[0x22]);

    if (imageSize == 0)
        imageSize = width * height * 3;  // ����: �̹��� ũ�� ���
    if (dataPos == 0)
        dataPos = 54;

    imageData = new unsigned char[imageSize];
    fread(imageData, 1, imageSize, file);
    fclose(file);

    width = *(int*)&(header[0x12]);  // ����: �̹��� �� �б�
    height = *(int*)&(header[0x16]);  // ����: �̹��� ���� �б�

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // ����: ���� ���͸� ���
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // ����: ���� ���͸� ���

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);  // ����: �ȼ� ���� ����

    glBindTexture(GL_TEXTURE_2D, 0);

    delete[] imageData;

    return textureID;
}

void initialize_texture() {
    const char* bmpFiles[1] = {
       "GameSTART_1.bmp"
    };

    int textureWidths[1];
    int textureHeights[1];

    for (int i = 0; i < 1; i++) {
        textures[i] = loadBMPTexture(bmpFiles[i], textureWidths[i], textureHeights[i]);
    }
}