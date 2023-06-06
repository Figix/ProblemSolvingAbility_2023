#pragma once
#pragma comment(lib, "opengl32.lib")
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

GLuint textures[1];  // 텍스처 배열 크기 수정

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
        imageSize = width * height * 3;  // 수정: 이미지 크기 계산
    if (dataPos == 0)
        dataPos = 54;

    imageData = new unsigned char[imageSize];
    fread(imageData, 1, imageSize, file);
    fclose(file);

    width = *(int*)&(header[0x12]);  // 수정: 이미지 폭 읽기
    height = *(int*)&(header[0x16]);  // 수정: 이미지 높이 읽기

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // 수정: 선형 필터링 사용
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // 수정: 선형 필터링 사용

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);  // 수정: 픽셀 형식 변경

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