#pragma comment(lib, "opengl32.lib")
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

namespace RunGame {
    // �ؽ�ó ���� ����
    GLuint textures[2];
    int textureWidths[2];
    int textureHeights[2];

    // BMP ������ �ε��ϰ� �ؽ�ó�� ��ȯ�ϴ� �Լ�
    GLuint loadBMPTexture(const char* filename, int& width, int& height) {
        GLuint textureID;
        unsigned char* imageData;
        FILE* file;
        unsigned int dataPos;
        unsigned int imageSize;
        unsigned char* buffer;

        // BMP ���� ����
        fopen_s(&file,filename, "rb");
        if (!file) {
            std::cout << "Could not open file: " << filename << std::endl;
            return 0;
        }

        // BMP ���� ��� �б�
        unsigned char header[54];
        if (fread(header, 1, 54, file) != 54) {
            std::cout << "Invalid BMP file: " << filename << std::endl;
            fclose(file);
            return 0;
        }

        // BMP ������ ��ȿ�� �˻�
        if (header[0] != 'B' || header[1] != 'M') {
            std::cout << "Invalid BMP file: " << filename << std::endl;
            fclose(file);
            return 0;
        }

        // BMP ���Ͽ��� �̹��� ������ ��ġ, ũ�� �б�
        dataPos = *(int*)&(header[0x0A]);
        imageSize = *(int*)&(header[0x22]);

        // �̹��� ������ ũ�⸦ �����ϰ� �޸� �Ҵ�
        if (imageSize == 0) imageSize = (header[0x16] << 16) | header[0x15]; // BMP ���� ũ��� ��ü
        if (dataPos == 0) dataPos = 54;
        imageData = new unsigned char[imageSize];

        // �̹��� ������ �б�
        fread(imageData, 1, imageSize, file);

        // BMP ���� �ݱ�
        fclose(file);

        // BMP ������ ���� ����
        width = (header[0x12] << 24) | (header[0x11] << 16) | (header[0x10] << 8) | header[0x0F];
        height = (header[0x16] << 24) | (header[0x15] << 16) | (header[0x14] << 8) | header[0x13];

        // OpenGL �ؽ�ó ���� �� ���ε�
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // �ؽ�ó �Ķ���� ����
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // �ؽ�ó ������ ����
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);

        // �ؽ�ó ���� �Ϸ�
        glBindTexture(GL_TEXTURE_2D, 0);

        // �޸� ����
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

        // �ؽ�ó �ε� �� ũ�� ����
        /*for (int i = 0; i < numTextures; i++) {
            textures[i] = loadBMPTexture(bmpFiles[i], textureWidths[i], textureHeights[i]);
        }*/
        textures[0] = loadBMPTexture(bmpFiles[0], textureWidths[0], textureHeights[0]);
    }
}
