#pragma 
#pragma comment(lib, "opengl32.lib")
#include <vector>
#include <chrono>
#include <thread>
#include <cmath>
#include "Object.hpp"
#include "texturemappin.hpp"

#define FPS_30 1/30.f 
#define FPS_60 1/60.f
#define FPS_144 1/144.f

using namespace std;

namespace RunGame {
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
		std::vector<Object> v;
		bool initcheck;
	public:
		int GameState; // 0:게임 스타트, 1:인 게임, 2:게임 오버
		SceneManager() {
			this->width = 1366;
			this->height = 768;
			this->GameState = GameStart;
			this->initcheck = true;
		}

		void GameStart_init() {
			this->initcheck = false;
		}
		void GameStart_Update() {
			if (this->initcheck == true) { GameStart_init(); }
			//윗줄은 init 확인용
			if (k_Space == true || k_Enter == true) {
				this->GameState = inGame;
				this->initcheck = true;
			}
		}
		void GameStart_Render() {
			glBindTexture(GL_TEXTURE_2D, textures[0]);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 0);
				glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 0);
				glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 0);
				glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, 0);
			glEnd();
		}
		void inGame_init() {
			this->initcheck = false;
		}
		void inGame_Update() {
			if (initcheck == true) { inGame_init(); }
			//윗줄은 init 확인용
			if (this->initcheck == true) { GameStart_init(); }
			//윗줄은 init 확인용
			if (k_Space == true || k_Enter == true) {
				this->GameState = GameOver;
				this->initcheck = true;
			}
		}
		void inGame_Render() {

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