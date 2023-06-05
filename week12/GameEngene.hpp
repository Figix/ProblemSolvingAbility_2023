#pragma once
#pragma comment(lib, "opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <cmath>
#include "GameManager.hpp"
#include "Object.hpp"
#include "Scene.hpp"
#include "texturemappin.hpp"
//#include "EnemyManager.hpp"
//#include "Player.hpp"
//#include "Texturemapping.hpp"

#define VK_S 0x53
#define VK_A 0x41
#define FPS_30 1/30.f 
#define FPS_60 1/60.f
#define FPS_144 1/144.f

using namespace std;
namespace RunGame {

	class GameLoop {
	private:
		chrono::system_clock::time_point startRenderTimePoint;
		chrono::duration<double> renderDuration;
		int sleeptime;
		SceneManager* sm;
	public:
		GameLoop() {}
		~GameLoop() {}
		//input�� �̺�Ʈ�� �����ϱ� ���� callback�Լ���
		static void error_callback(int error, const char* description)
		{
			fputs(description, stderr);
		}
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{

			//GLFW_PRESS(do), GLFW_REPEAT(ing), GLFW_RELEASE(end), GLFW_KEY_UNKNOWN(none)
			// esc�� ���� ���� ���� Ȯ��
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
				glfwSetWindowShouldClose(window, GL_TRUE);

			if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {k_Space = true;}
			else {k_Space = false;}

			if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) { k_Enter = true; }
			else { k_Enter = false; }
			
			if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) { k_Rarrow = true; }
			else { k_Rarrow = false; }
			
			if (key == GLFW_KEY_UP && action == GLFW_PRESS) { k_Uarrow = true; }
			else { k_Uarrow = false; }
			
			if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) { k_Larrow = true; }
			else { k_Larrow = false; }

			if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) { k_Darrow = true; }
			else { k_Darrow = false; }

			//�Ʒ��� ���ÿ����� �ۼ���
			/*if (key == GLFW_KEY_S && action == GLFW_PRESS) { pressS = true; }
			else { pressS = false; }*/
		}
		void Run()
		{
			GLFWwindow* window;
			glfwSetErrorCallback(error_callback);
			
			if (!glfwInit())
			{
				std::exit(EXIT_FAILURE);
			}
			window = glfwCreateWindow(1366, 768, "Running Box", NULL, NULL);

			Initialize(window);

			while (!glfwWindowShouldClose(window))
			{
				Update(window);
				Render(window);

			}
			Release(window);
		}
		void Initialize(GLFWwindow* window) {
			if (!window) {
				glfwTerminate();
				std::exit(EXIT_FAILURE);
			}
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glfwMakeContextCurrent(window);
			//�׷��� ���� �����͵��� ����̽�(�׷��ȿ����� ��� ��ġ)�� ����(�������ִ�)��
			//������ ������ â �������� �׸��� ���� �޼ҵ�
			glfwSetKeyCallback(window, key_callback);
			//key�Է� �̺�Ʈ �޴� �޼ҵ�

			/*-----------------------------------------------------------------------------------------------------------*/
			//�� ������ �ؽ��� ������ �͵� ó���ϱ�
			/*init_texture_GameStart();
			init_texture_GameOver();*/
			initialize_texture();
			/*-----------------------------------------------------------------------------------------------------------*/

			//���� ��� �������� ������ �����ϴ� �ܰ�
			sm = new SceneManager();
		}
		void Update(GLFWwindow* window) {
			//���� ������Ʈ ���� �� ���� ó��
			startRenderTimePoint = chrono::system_clock::now();
			if (sm->GameState == GameStart) {
				sm->GameStart_Update();
				cout << "0������Ʈ" << endl;
			}
			else if(sm->GameState == inGame) {
				sm->inGame_Update();
				cout << "1������Ʈ" << endl;
			}
			else if (sm->GameState == GameOver) {
				sm->GameOver_Update();
				cout << "2������Ʈ" << endl;
			}
		}
		void Render(GLFWwindow* window) {
			float ratio;
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);
			ratio = width / (float)height;


			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);


			glFlush();
			glDisable(GL_TEXTURE_2D);
			glFinish();

			if (sm->GameState == GameStart) {
				sm->GameStart_Render();
				cout << "0����" << endl;
			}
			else if (sm->GameState == inGame) {
				sm->inGame_Render();
				cout << "1����" << endl;
			}
			else if (sm->GameState == GameOver) {
				sm->GameOver_Render();
				cout << "2����" << endl;
			}
			glfwSwapBuffers(window);
			//�������� �����ɸ� ��� �� ��ĥ�ϴ� �̸� ĥ�صΰ� �װ��� �����ִ°Ͱ� �ٲ�
			glfwPollEvents();
			//�̺�Ʈ���� �ߺ��� �̺�Ʈ���� �����ؼ� �������ִ� ��
			//�Լ��� ����Ǵ� �������� ���޹޴´�.

			renderDuration = chrono::system_clock::now() - startRenderTimePoint;
			sleeptime = (int)((FPS_30-renderDuration.count()) * 1000);

			this_thread::sleep_for(chrono::milliseconds(sleeptime));
			if (sleeptime == 0) { cout << "������ ��� ���� ��" << endl; }

			//���� 30FPS �������� ���� ����
			//FPS_30���� FPS_60���� �ٲٸ� 60FPS�� ���氡��;
		}
		void Release(GLFWwindow* window) {
			glfwDestroyWindow(window);
			glfwTerminate();
			std::exit(EXIT_SUCCESS);
		}

		//�浹 Ȯ���ϴ� �Լ�
		/*bool isCollision() {
			for (int i = 0; i < 3; i++) {
				if (fabs(PL->x - EM->E[i].x) < (PL->size / 2) + (EM->E[i].size / 16)) {
					if (fabs(PL->y - EM->E[i].y) < (PL->size / 2) + (EM->E[i].size / 2)) {
						return true;
					}
				}
			}
			return false;
		}*/

		/*void DrawGameStart() {
			glColor4f(0.25, 0.25, 0.25, 1);
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
			glBindTexture(GL_TEXTURE_2D, textGameStart);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 0);
			glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 0);
			glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 0);
			glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, 0);
			glEnd();
		}
		void DrawGameOver() {
			glColor4f(0.5, 0.5, 0.5, 1);
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
			glBindTexture(GL_TEXTURE_2D, textGameOver);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 0);
			glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 0);
			glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 0);
			glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, 0);
			glEnd();
		}*/
	};
}