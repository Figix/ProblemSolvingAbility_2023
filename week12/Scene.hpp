#pragma 
#pragma comment(lib, "opengl32.lib")
#include <vector>
#include <chrono>
#include <thread>
#include <cmath>
#include <iostream> 
#include "Object.hpp"
#include "texturemappin.hpp"


#define FPS_30 1/30.f 
#define FPS_60 1/60.f
#define FPS_144 1/144.f

using namespace std;

namespace RunGame {
	static bool isSpacePressed;
	static bool k_Space;
	static bool k_Enter;
	static bool k_Uarrow;
	static bool k_Rarrow;
	static bool k_Darrow;
	static bool k_Larrow;

	enum GameState {
		GameStart,
		inGame,
		GameOver
	};

	class SceneManager {
	private:
		int width, height;
		bool initcheck;
		int framecount;
		bool pressed_GameStart;

		Player *player = new Player(-0.8, -0.77, 0.2, 1.0);
		Ground* ground1 = new Ground(0, -0.9, 2.1, 0.1);
		Ground* ground2 = new Ground(2, -0.9, 2.1, 0.1);
		Cloud* cloud1 = new Cloud(0.8, 0.5, 0.3, 1);
		Cloud* cloud2 = new Cloud(-0.2, 0.3, 0.44, 1);
		Cloud* cloud3 = new Cloud(0.2, 0.75, 0.2, 1);
		Sun* sun = new Sun(1, 0.65, 0.25, 1);
	public:
		int GameState; // 0:게임 스타트, 1:인 게임, 2:게임 오버
		SceneManager() {
			this->width = 1366;
			this->height = 768;
			this->GameState = GameStart;
			this->initcheck = true;
			this->framecount = 0;
		}

		void GameStart_init() {
			this->initcheck = false;
		}
		void GameStart_Update() {
			if (this->initcheck == true) { GameStart_init(); }
			//윗줄은 init 확인용
			if (isSpacePressed == true && this->GameState == GameStart) {
				this->GameState = inGame;
				this->initcheck = true;
				isSpacePressed = false;
			}
		}
		void GameStart_Render() {
			glBindTexture(GL_TEXTURE_2D, textures[0]);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f);glVertex2f(-0.5f, -0.5f);
				glTexCoord2f(1.0f, 0.0f);glVertex2f(0.5f, -0.5f);
				glTexCoord2f(1.0f, 1.0f);glVertex2f(0.5f, 0.5f);
				glTexCoord2f(0.0f, 1.0f);glVertex2f(-0.5f, 0.5f);
			glEnd();
		}

		void inGame_init() {
			this->initcheck = false;
			cout << "test" << endl;
			cout << "x : " << player->x<<",y : "<<player->y << ",ratio : " << player->ratio<<",size : "<<player->size<<endl;
			framecount = 0;
		}
		void inGame_Update() {
			if (initcheck == true) { inGame_init(); }
			//윗줄은 init 확인용
			if (this->initcheck == true) { GameStart_init(); }
			//윗줄은 init 확인용
			if (isSpacePressed == true && this->GameState == inGame) {
				player->jump();
				isSpacePressed = false;
			}

			framecount++;
			if (framecount == 30) {
				ground1->speedup();
				ground2->speedup();
				framecount = 0;
			}
			else if (framecount == 15) {
				cloud1->speedup();
				cloud2->speedup();
				cloud3->speedup();
				sun->speedup();
			}
			ground1->move();
			ground2->move();
			cloud1->move();
			cloud2->move();
			cloud3->move();
			sun->move();
			player->gravity();
		}
		void inGame_Render() {
			ground1->Draw();
			ground2->Draw();
			sun->Draw();
			cloud1->Draw();
			cloud2->Draw();
			cloud3->Draw();

			player->Draw();
		}

		void GameOver_init() {
			this->initcheck = false;
		}
		void GameOver_Update() {
			if (initcheck == true) { GameOver_init(); }
			//윗줄은 init 확인용
			if (this->initcheck == true) { GameStart_init(); }
			//윗줄은 init 확인용
			if (k_Space == true || k_Enter == true) {
				this->GameState = GameStart;
				this->initcheck = true;
			}
		}
		void GameOver_Render() {
			glColor4f(0.5, 0.5, 0.5, 1);
			//glEnable(GL_TEXTURE_2D);
			//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
			//glBindTexture(GL_TEXTURE_2D, textGameStart);
			glBegin(GL_QUADS);
			//glTexCoord2f(0.0, 0.0); 
			glVertex3f(-1.0, -1.0, 0);
			//glTexCoord2f(1.0, 0.0); 
			glVertex3f(1.0, -1.0, 0);
			//glTexCoord2f(1.0, 1.0);
			glVertex3f(1.0, 1.0, 0);
			//glTexCoord2f(0.0, 1.0); 
			glVertex3f(-1.0, 1.0, 0);
			glEnd();
		}

	};
}