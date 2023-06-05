#pragma comment(lib, "opengl32.lib")
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

namespace RunGame {
    // 텍스처 변수 선언
    GLuint textures[2];
    int textureWidths[2];
    int textureHeights[2];

    // BMP 파일을 로드하고 텍스처로 변환하는 함수
    GLuint loadBMPTexture(const char* filename, int& width, int& height) {
        GLuint textureID;
        unsigned char* imageData;
        FILE* file;
        unsigned int dataPos;
        unsigned int imageSize;
        unsigned char* buffer;

        // BMP 파일 열기
        fopen_s(&file,filename, "rb");
        if (!file) {
            std::cout << "Could not open file: " << filename << std::endl;
            return 0;
        }

        // BMP 파일 헤더 읽기
        unsigned char header[54];
        if (fread(header, 1, 54, file) != 54) {
            std::cout << "Invalid BMP file: " << filename << std::endl;
            fclose(file);
            return 0;
        }

        // BMP 파일의 유효성 검사
        if (header[0] != 'B' || header[1] != 'M') {
            std::cout << "Invalid BMP file: " << filename << std::endl;
            fclose(file);
            return 0;
        }

        // BMP 파일에서 이미지 데이터 위치, 크기 읽기
        dataPos = *(int*)&(header[0x0A]);
        imageSize = *(int*)&(header[0x22]);

        // 이미지 데이터 크기를 조정하고 메모리 할당
        if (imageSize == 0) imageSize = (header[0x16] << 16) | header[0x15]; // BMP 파일 크기로 대체
        if (dataPos == 0) dataPos = 54;
        imageData = new unsigned char[imageSize];

        // 이미지 데이터 읽기
        fread(imageData, 1, imageSize, file);

        // BMP 파일 닫기
        fclose(file);

        // BMP 파일의 폭과 높이
        width = (header[0x12] << 24) | (header[0x11] << 16) | (header[0x10] << 8) | header[0x0F];
        height = (header[0x16] << 24) | (header[0x15] << 16) | (header[0x14] << 8) | header[0x13];

        // OpenGL 텍스처 생성 및 바인딩
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // 텍스처 파라미터 설정
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // 텍스처 데이터 전송
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);

        // 텍스처 생성 완료
        glBindTexture(GL_TEXTURE_2D, 0);

        // 메모리 해제
        delete[] imageData;

        return textureID;
    }

    void initialize_texture() {
        const char* bmpFiles[8] = {
           "GameSTART_1.bmp",
           "texture1.bmp",
           "texture2.bmp",
           "texture3.bmp",
           "texture4.bmp",
           "texture5.bmp",
           "texture6.bmp",
           "texture7.bmp"
        };

        // 텍스처 로드 및 크기 저장
        /*for (int i = 0; i < numTextures; i++) {
            textures[i] = loadBMPTexture(bmpFiles[i], textureWidths[i], textureHeights[i]);
        }*/
        textures[0] = loadBMPTexture(bmpFiles[0], textureWidths[0], textureHeights[0]);
    }
}
