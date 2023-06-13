#pragma 
#pragma comment(lib, "opengl32.lib")
#include <vector>
#include <chrono>
#include <thread>
#include <cmath>
#include <iostream> 
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <windows.h>
#include "Object.hpp"
#include "texturemappin.hpp"

#define FPS_30 1/30.f 
#define FPS_60 1/60.f
#define FPS_144 1/144.f

using namespace std;

namespace RunGame {
	static bool isSpacePressed;
	static bool isEnterPressed;

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
		bool isSTOP;
		int score;
		int drawindex;
		int drawcounter;

		Player *player = new Player();
		Ground* ground1 = new Ground();
		Ground* ground2 = new Ground();
		Cloud* cloud1 = new Cloud();
		Cloud* cloud2 = new Cloud();
		Cloud* cloud3 = new Cloud();
		Sun* sun = new Sun();
		Block* block[3];
	public:
		int GameState; // 0:게임 스타트, 1:인 게임, 2:게임 오버
		SceneManager() {
			this->width = 1366;
			this->height = 768;
			this->GameState = GameStart;
			this->initcheck = true;
			this->framecount = 0;

			for (int i = 0; i < 3; i++) {
				block[i] = new Block();
			}
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
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textures[0]);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);
			glEnd();
		}

		void inGame_init() {
			system("cls");
			this->initcheck = false;
			isSTOP = true;
			score = 0;

			player->set(-0.8, -0.77, 0.2, 1.0);
			ground1->set(0, -0.9, 2.1, 0.1);
			ground2->set(2, -0.9, 2.1, 0.1);
			cloud1->set(0.8, 0.5, 0.3, 1);
			cloud2->set(-0.2, 0.3, 0.44, 1);
			cloud3->set(0.2, 0.75, 0.2, 1);
			sun->set(1, 0.65, 0.25, 1);
			for (int i = 0; i < 3; i++) {
				block[i]->clear();
			}

			drawindex = 3;

			block[0]->setblock();
			framecount = 0;
		}
		void inGame_Update() {
			if (initcheck == true) { inGame_init(); }
			//윗줄은 init 확인용
			if (this->initcheck == true) { GameStart_init(); }
			//윗줄은 init 확인용
			if (isEnterPressed == true && this->GameState == inGame) {
				isSTOP=isSTOP ? false: true;
				isEnterPressed = false;
			}
			if (isSTOP) {
				if (isSpacePressed == true && this->GameState == inGame) {
					player->jump();
					isSpacePressed = false;
				}
				framecount++;
				if (framecount == 30) {
					ground1->speedup();
					ground2->speedup();
					block[0]->speedup();
					block[1]->speedup();
					block[2]->speedup();

					for (int i = 0; i < 3; i++) {
						if (block[i]->isusing == false) {
							block[i]->setblock();
							break;
						}
					}
					framecount = 0;
				}
				else if (framecount == 15) {
					cloud1->speedup();
					cloud2->speedup();
					cloud3->speedup();
					sun->speedup();
					score += 10;
				}
				if (framecount % 5 == 4) {
					drawindex++;
					if (drawindex == 7) {
						drawindex = 3;
					}
				}
				ground1->move();
				ground2->move();
				cloud1->move();
				cloud2->move();
				cloud3->move();
				sun->move();
				block[0]->move();
				block[1]->move();
				block[2]->move();
				player->gravity();
				for (int i = 0; i < 3; i++) {
					if (iscollision_AABB(player, block[i])) {
						this->initcheck = true;
						GameState = GameOver;
					}
				}
			}
			

		}
		void inGame_Render() {
			ground1->Draw();
			ground2->Draw();
			sun->Draw();
			cloud1->Draw();
			cloud2->Draw();
			cloud3->Draw();
			for (int i = 0; i < 3; i++) {
				if (block[i]->isusing) {
					block[i]->Draw();
				}
			}

			player->Draw(drawindex);
		}

		void GameOver_init() {
			this->initcheck = false;

			// inGame에서 했던 게임 정보를 저장함
			textwrite(score);
		}
		void GameOver_Update() {
			if (initcheck == true) { GameOver_init(); }
			//윗줄은 init 확인용
			if (this->initcheck == true) { GameStart_init(); }
			//윗줄은 init 확인용
			if (isSpacePressed == true && this->GameState == GameOver) {
				this->GameState = inGame;
				this->initcheck = true;
				isSpacePressed = false;
			}
		}
		void GameOver_Render() {
			glColor4f(0.5, 0.5, 0.5, 1);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textures[1]);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);
			glEnd();
		}

		bool iscollision_AABB(Player *p, Block *b)
		{
			//if (a.max.y < b.min.x || a.min.x > b.max.x)
			if ((p->x + (p->size / 2)) < (b->x - (b->size / 2)) || (p->x - (p->size / 2)) > (b->x + (b->size / 2))) {
				return false;
			}
			//if (a.max.y < b.min.y || a.min.y > b.max.y)
			if ((p->y + (p->size * p->ratio / 2)) < (b->y - (b->size * b->ratio / 2)) || (p->y - (p->size * p->ratio / 2)) > (b->y + (b->size * b->ratio / 2))) {
				return false;
			}
			return true;
		}

		struct UserData {
			std::string date;
			int score;
			int userNumber;
		};

		static bool compareByScore(const UserData& a, const UserData& b) {
			return a.score > b.score;
		}

		void textwrite(int SCORE) {
			std::time_t now = std::time(nullptr);
			std::tm currentTime;
			localtime_s(&currentTime, &now);

			std::ostringstream oss;
			std::string format = "%Y년 %m월 %d일 %H시 %M분 %S초";

			char currentTimeBuffer[100];
			std::strftime(currentTimeBuffer, sizeof(currentTimeBuffer), format.c_str(), &currentTime);

			std::string currentTimeString(currentTimeBuffer);

			srand((unsigned int)time(NULL));
			int user_number = rand() % 10000;

			std::ofstream file("record.txt", std::ios::app); // 파일을 추가 모드로 열기
			if (file.is_open()) {
				// 파일이 정상적으로 열렸을 때 내용 추가
				file << currentTimeString << "/ score : " << SCORE << "/ user_number : " << user_number << endl;
				file.close(); // 파일 닫기
			}
			else {
				std::cout << "파일을 열 수 없습니다." << std::endl;
			}

			sortScores("record.txt", "Rank.txt");

			std::ifstream file2("Rank.txt");

			if (file2.is_open()) {
				std::vector<std::string> lines;
				std::string line;
				while (std::getline(file2, line)) {
					lines.push_back(line);
				}

				file2.close();

				// 파일에서 읽은 모든 내용 출력
				for (const std::string& str : lines) {
					std::cout << str << std::endl;
				}
			}
			else {
				std::cout << "파일을 열 수 없습니다." << std::endl;
			}
		}

		void sortScores(const std::string& inputFileName, const std::string& outputFileName) {
			std::ifstream inputFile(inputFileName);
			std::vector<UserData> userDataList;

			if (inputFile.is_open()) {
				std::string line;
				while (std::getline(inputFile, line)) {
					std::string scoreStr = line.substr(line.find("score : ") + 8);
					int score = std::stoi(scoreStr);

					std::string userNumberStr = line.substr(line.find("user_number : ") + 14);
					int userNumber = std::stoi(userNumberStr);

					userDataList.push_back({ line, score, userNumber });
				}

				inputFile.close();

				std::sort(userDataList.begin(), userDataList.end(), compareByScore);

				std::ofstream outputFile(outputFileName);
				if (outputFile.is_open()) {
					for (const auto& userData : userDataList) {
						outputFile << userData.date << '\n';
					}
					outputFile.close();
				}
				else {
					std::cerr << "파일을 저장하는 데 실패했습니다." << std::endl;
				}
			}
			else {
				std::cerr << "파일을 열 수 없습니다." << std::endl;
			}
		}
	};
}