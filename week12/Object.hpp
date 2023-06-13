#pragma once
#pragma comment(lib, "opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "texturemappin.hpp"

#define SR 16.0f/9.0f //ScreenRatio È­¸é ºñ 16:9

namespace RunGame {
	class object {
		public:
			float x, y, size, ratio, objectType;
			enum ObjectType {
				PLAYER,
				GROUND,
				BLOCK,
				CLOUD,
				SUN
			};
			virtual void Draw() {}
			virtual void move() {}
	};


	class Player : public object{
	private:
		float gravityforce=0.05;
		float jumpforce=0;
		int drawindex=3;
	public:
		//-0.8, -0.8, 0.2, 1.0

		Player() : object() {
			x = -0.8f;
			y = -0.8f;
			size = 0.2f;
			ratio = 1.0f;
			objectType = PLAYER;
		}

		Player(float X, float Y, float SIZE, float RATIO) {
			x = X;
			y = Y;
			size = SIZE;
			ratio = RATIO*SR;
		}

		~Player() {

		}

		void Draw() override{
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textures[drawindex]);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(x - (size / 2), y - (size * ratio / 2));
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(x - (size / 2), y + (size * ratio / 2));
			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(x + (size / 2), y + (size * ratio / 2));
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(x + (size / 2), y - (size * ratio / 2));
			glEnd();
		}

		void convertDraw() {
			drawindex++;
			if (drawindex == 7) {
				drawindex = 3;
			}
		}

		void jump() { 
			if (jumpforce <= 0.05f) {
				jumpforce = 0.27f;
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

		void set(float X, float Y, float SIZE, float RATIO)  {
			x = X;
			y = Y;
			size = SIZE;
			ratio = RATIO * SR;
			jumpforce = 0;
			drawindex = 3;
		}
	};

	class Ground : public object {
	private:
		float spd = -0.01;
	public:

		//-0.8, -0.8, 0.2, 1.0

		Ground() : object() {
			x = -0.8f;
			y = -0.8f;
			size = 0.2f;
			ratio = 1.0f;
			objectType = GROUND;
		}

		Ground(float X, float Y, float SIZE, float RATIO) {
			x = X;
			y = Y;
			size = SIZE;
			ratio = RATIO * SR;
		}

		~Ground() {

		}

		void Draw() override {
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

		void move() override{
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

		void set(float X, float Y, float SIZE, float RATIO) {
			x = X;
			y = Y;
			size = SIZE;
			ratio = RATIO * SR;
			spd = -0.01;
		}
	};

	class Block : public object {
	private:
		float spd=-0.01;
	public:
		bool isusing;

		//-0.8, -0.8, 0.2, 1.0

		Block() : object() {
			size = 0.05f;
			ratio = 5.0f*SR;
			x = 1.0f+(size/2);
			y = -1.0f+(size*ratio/2);
			isusing = false;
			objectType = BLOCK;
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

		void Draw() override{
			glBegin(GL_QUADS);
			glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
			glVertex2f(x - (size / 2), y - (size * ratio / 2));
			glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
			glVertex2f(x - (size / 2), y + (size * ratio / 2));
			glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
			glVertex2f(x + (size / 2), y + (size * ratio / 2));
			glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
			glVertex2f(x + (size / 2), y - (size * ratio / 2));
			glEnd();
		}

		void move() override{
			if (isusing == true) {
				x = x + spd;
				if (x <= -1.0f - (size / 2)) {
					x = 1.0f + (size / 2);
					isusing = false;
				}
				if (y <= -(1.0f - (size * ratio / 2))) {
					y = y - spd;
				} 
				else if (y>= (1.0f - (size * ratio / 2))) {
					y = y + spd;
				}
			}
		}

		void speedup() {
			spd -= 0.01;
			if (spd <= -0.05f) {
				spd = -0.1f;
			}
		}

		void setblock() {
			isusing = true;
			spd = -0.01;
			srand((unsigned int)time(NULL));
			float sign = rand() % 2;

			size = 0.1;
			ratio = rand() % 5 + 5;

			x = 1.0f+(size/2);
			
			if (sign == 0) {
				y = -(1.0f + (size * ratio / 2));
			}
			else if (sign == 1) {
				y = (1.0f + (size * ratio / 2));
			}
		}

		void clear() {
			size = 0.05f;
			ratio = 5.0f * SR;
			x = 1.0f + (size / 2);
			y = -1.0f + (size * ratio / 2);
			isusing = false;
			spd = -0.01;
		}
	};

	class Cloud : public object {
	private:
		float spd = -0.01;
	public:

		//-0.8, -0.8, 0.2, 1.0

		Cloud() : object() {
			x = -0.8f;
			y = -0.8f;
			size = 0.2f;
			ratio = 1.0f;
			objectType = CLOUD;
		}

		Cloud(float X, float Y, float SIZE, float RATIO) {
			x = X;
			y = Y;
			size = SIZE;
			ratio = RATIO * SR;
		}

		~Cloud() {

		}

		void Draw() override{
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

		void move()override {
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
		void set(float X, float Y, float SIZE, float RATIO) {
			x = X;
			y = Y;
			size = SIZE;
			ratio = RATIO * SR;
			spd = -0.01;
		}
	};

	class Sun : public object {
	private:
		float spd = -0.001;
	public:

		//-0.8, -0.8, 0.2, 1.0

		Sun() : object() {
			x = -0.8f;
			y = -0.8f;
			size = 0.2f;
			ratio = 1.0f;
			objectType = SUN;
		}

		Sun(float X, float Y, float SIZE, float RATIO) {
			x = X;
			y = Y;
			size = SIZE;
			ratio = RATIO * SR;
		}

		~Sun() {

		}

		void Draw() override{
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

		void move() override{
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

		void set(float X, float Y, float SIZE, float RATIO) {
			x = X;
			y = Y;
			size = SIZE;
			ratio = RATIO * SR;
			spd = -0.001;
		}
	};
}