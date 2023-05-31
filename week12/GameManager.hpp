#pragma once
#include <iostream>

namespace RunGame {
	class GameManager {
	public:
		int GameState;
		int score;
		// 0:���� ��ŸƮ, 1:�� ����, 2:���� ����
		enum GameState {
			GameStart,
			inGame,
			GameOver
		};
		GameManager() {
			GameState = GameStart;
			score = 0;
		}
		~GameManager() {

		}

		void Zeroscore() {
			score = 0;
		}

		void Upscore() {
			score += 100;
		}

		void showScore() {
			std::cout << score << "���Դϴ�." << std::endl;
		}

		void GameState_Start() {
			GameState = GameStart;
		}
		void GameState_inGame() {
			GameState = inGame;
		}
		void GameState_Over() {
			GameState = GameOver;
		}
	};
}