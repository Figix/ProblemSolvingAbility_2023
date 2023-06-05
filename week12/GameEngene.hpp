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
		//input과 이벤트를 관리하기 위한 callback함수들
		static void error_callback(int error, const char* description)
		{
			fputs(description, stderr);
		}
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{

			//GLFW_PRESS(do), GLFW_REPEAT(ing), GLFW_RELEASE(end), GLFW_KEY_UNKNOWN(none)
			// esc를 통해 게임 종료 확인
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

			//아래는 예시용으로 작성함
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
			//그래픽 관련 데이터들을 디바이스(그래픽에서는 출력 장치)를 매핑(연결해주는)것
			//지정한 윈도우 창 기준으로 그리기 위한 메소드
			glfwSetKeyCallback(window, key_callback);
			//key입력 이벤트 받는 메소드

			/*-----------------------------------------------------------------------------------------------------------*/
			//이 곳에서 텍스쳐 매핑할 것들 처리하기
			/*init_texture_GameStart();
			init_texture_GameOver();*/
			initialize_texture();
			/*-----------------------------------------------------------------------------------------------------------*/

			//게임 상대 관리에서 시작을 정리하는 단계
			sm = new SceneManager();
		}
		void Update(GLFWwindow* window) {
			//게임 스테이트 관리 및 연산 처리
			startRenderTimePoint = chrono::system_clock::now();
			if (sm->GameState == GameStart) {
				sm->GameStart_Update();
				cout << "0업데이트" << endl;
			}
			else if(sm->GameState == inGame) {
				sm->inGame_Update();
				cout << "1업데이트" << endl;
			}
			else if (sm->GameState == GameOver) {
				sm->GameOver_Update();
				cout << "2업데이트" << endl;
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
				cout << "0렌더" << endl;
			}
			else if (sm->GameState == inGame) {
				sm->inGame_Render();
				cout << "1렌더" << endl;
			}
			else if (sm->GameState == GameOver) {
				sm->GameOver_Render();
				cout << "2렌더" << endl;
			}
			glfwSwapBuffers(window);
			//렌더링이 오래걸릴 경우 다 못칠하니 미리 칠해두고 그것을 현재있는것과 바꿈
			glfwPollEvents();
			//이벤트에서 중복된 이벤트들을 정리해서 전달해주는 것
			//함수가 실행되는 순간마다 전달받는다.

			renderDuration = chrono::system_clock::now() - startRenderTimePoint;
			sleeptime = (int)((FPS_30-renderDuration.count()) * 1000);

			this_thread::sleep_for(chrono::milliseconds(sleeptime));
			if (sleeptime == 0) { cout << "프레임 방어 실패 중" << endl; }

			//현재 30FPS 기준으로 돌고 있음
			//FPS_30에서 FPS_60으로 바꾸면 60FPS로 변경가능;
		}
		void Release(GLFWwindow* window) {
			glfwDestroyWindow(window);
			glfwTerminate();
			std::exit(EXIT_SUCCESS);
		}

		//충돌 확인하는 함수
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