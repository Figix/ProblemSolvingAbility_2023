#pragma once
#pragma comment(lib, "opengl32.lib")
#include <GLFW/glfw3.h>

#define SR 16.0f/9.0f //ScreenRatio È­¸é ºñ 16:9

namespace RunGame {
	class Player {
	private:
		float gravityforce=0.05;
		float jumpforce=0;
	public:
		float x, y;
		float size;
		float ratio;

		//-0.8, -0.8, 0.2, 1.0

		Player() {
			x = -0.8f;
			y = -0.8f;
			size = 0.2f;
			ratio = 1.0f;
		}

		Player(float X, float Y, float SIZE, float RATIO) {
			x = X;
			y = Y;
			size = SIZE;
			ratio = RATIO*SR;
		}

		~Player() {

		}

		void Draw() {
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glBegin(GL_QUADS);
				glVertex2f(x - (size / 2), y - (size * ratio / 2));
				glVertex2f(x - (size / 2), y + (size * ratio / 2));
				glVertex2f(x + (size / 2), y + (size * ratio / 2));
				glVertex2f(x + (size / 2), y - (size * ratio / 2));
			glEnd();
		}

		void jump() { 
			if (jumpforce <= 0.05f) {
				jumpforce += 0.27f;
			}
		}

		void gravity() {
			jumpforce = jumpforce - (jumpforce / 25) - 0.0175f;
			y = y + jumpforce;
			y = y - gravityforce;
			if (y <= -0.77) {
				y = -0.77;
				jumpforce = 0.0f;
			}
			else if (y >= 0.77)
				y = 0.77;
		}
	};

	class Ground {
	private:
		float spd = -0.01;
	public:
		float x, y;
		float size;
		float ratio;

		//-0.8, -0.8, 0.2, 1.0

		Ground() {
			x = -0.8f;
			y = -0.8f;
			size = 0.2f;
			ratio = 1.0f;
		}

		Ground(float X, float Y, float SIZE, float RATIO) {
			x = X;
			y = Y;
			size = SIZE;
			ratio = RATIO * SR;
		}

		~Ground() {

		}

		void Draw() {
			glBegin(GL_QUADS);
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			glVertex2f(x - (size / 2), y - (size * ratio / 2));
			glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
			glVertex2f(x - (size / 2), y + (size * ratio / 2));
			glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
			glVertex2f(x + (size / 2), y + (size * ratio / 2));
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glVertex2f(x + (size / 2), y - (size * ratio / 2));
			glEnd();
		}

		void move() {
			x = x + spd;
			if (x <= -2.0f) {
				x = 2.0f;
			}
		}

		void speedup() {
			spd -= 0.01;
			if (spd <= -0.05f) {
				spd = -0.1f;
			}
		}
	};

	class Block {
	private:
		float spd=-0.01;
	public:
		float x, y;
		float size;
		float ratio;
		bool isusing;

		//-0.8, -0.8, 0.2, 1.0

		Block() {
			size = 0.05f;
			ratio = 5.0f*SR;
			x = 1.0f+(size/2);
			y = -1.0f+(size*ratio/2);
			isusing = false;
		}

		Block(float X, float Y, float SIZE, float RATIO) {
			x = X;
			y = Y;
			size = SIZE;
			ratio = RATIO * SR;
			isusing = false;
		}

		~Block() {

		}

		void Draw() {
			glBegin(GL_QUADS);
			glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
			glVertex2f(x - (size / 2), y - (size * ratio / 2));
			glColor4f(0.0f, 0.75f, 0.75f, 1.0f);
			glVertex2f(x - (size / 2), y + (size * ratio / 2));
			glColor4f(0.0f, 0.5f, 0.5f, 1.0f);
			glVertex2f(x + (size / 2), y + (size * ratio / 2));
			glColor4f(1.0f, 0.25f, 0.25f, 1.0f);
			glVertex2f(x + (size / 2), y - (size * ratio / 2));
			glEnd();
		}

		void move() {
			if (isusing == true) {
				x = x + spd;
				if (x <= -1.0f - (size / 2)) {
					x = 1.0f + (size / 2);
					isusing = false;
				}
			}
		}

		void speedup() {
			spd -= 0.01;
			if (spd <= -0.05f) {
				spd = -0.1f;
			}
		}
	};

	class Cloud {
	private:
		float spd = -0.01;
	public:
		float x, y;
		float size;
		float ratio;

		//-0.8, -0.8, 0.2, 1.0

		Cloud() {
			x = -0.8f;
			y = -0.8f;
			size = 0.2f;
			ratio = 1.0f;
		}

		Cloud(float X, float Y, float SIZE, float RATIO) {
			x = X;
			y = Y;
			size = SIZE;
			ratio = RATIO * SR;
		}

		~Cloud() {

		}

		void Draw() {
			glBegin(GL_QUADS);
			glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
			glVertex2f(x - (size / 2), y - (size * ratio / 2));
			glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
			glVertex2f(x - (size / 2), y + (size * ratio / 2));
			glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
			glVertex2f(x + (size / 2), y + (size * ratio / 2));
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glVertex2f(x + (size / 2), y - (size * ratio / 2));
			glEnd();
		}

		void move() {
			x = x + spd;
			if (x <= -1.0f-(size/2)) {
				x = 1.0f+ (size / 2);
			}
		}

		void speedup() {
			spd -= 0.001;
			if (spd <= -0.02f) {
				spd = -0.02f;
			}
		}
	};

	class Sun {
	private:
		float spd = -0.001;
	public:
		float x, y;
		float size;
		float ratio;

		//-0.8, -0.8, 0.2, 1.0

		Sun() {
			x = -0.8f;
			y = -0.8f;
			size = 0.2f;
			ratio = 1.0f;
		}

		Sun(float X, float Y, float SIZE, float RATIO) {
			x = X;
			y = Y;
			size = SIZE;
			ratio = RATIO * SR;
		}

		~Sun() {

		}

		void Draw() {
			glBegin(GL_QUADS);
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			glVertex2f(x - (size / 2), y - (size * ratio / 2));
			glColor4f(0.75f, 0.25f, 0.0f, 1.0f);
			glVertex2f(x - (size / 2), y + (size * ratio / 2));
			glColor4f(0.5f, 0.5f, 0.0f, 1.0f);
			glVertex2f(x + (size / 2), y + (size * ratio / 2));
			glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
			glVertex2f(x + (size / 2), y - (size * ratio / 2));
			glEnd();
		}

		void move() {
			x = x + spd;
			if (x <= -1.0f - (size / 2)) {
				x = 1.0f + (size / 2);
			}
		}

		void speedup() {
			spd -= 0.0001;
			if (spd <= -0.0015f) {
				spd = -0.0015f;
			}
		}
	};
}