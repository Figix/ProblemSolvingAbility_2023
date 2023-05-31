#pragma once
#pragma comment(lib, "opengl32.lib")
namespace RunGame {
	class Object {
	protected:
		float x, y;

	public:
		Object(float X, float Y) {
			x = X;
			y = Y;
		}

		~Object() {

		}
	};

	class block : public Object {
	public:
		float size;
		float ratio;

		block(float X, float Y, float r, float s) : Object(X, Y) {
			size = s;
			ratio = r;
		}

		~block() {

		}

		void Draw() {
			glBegin(GL_QUADS);
				glVertex2f(x - (size / 2), y - (size * ratio / 2));
				glVertex2f(x - (size / 2), y + (size * ratio / 2));
				glVertex2f(x + (size / 2), y + (size * ratio / 2));
				glVertex2f(x + (size / 2), y - (size * ratio / 2));
			glEnd();
		}
	};

	class block2 : public Object {
	public:
		float size;
		float ratio;

		block2(float X, float Y, float r, float s) : Object(X, Y) {
			size = s;
			ratio = r;
		}

		~block2() {

		}

		void Draw() {
			glBegin(GL_QUADS);
			glVertex2f(x - (size / 2), y - (size * ratio / 2));
			glVertex2f(x - (size / 2), y + (size * ratio / 2));
			glVertex2f(x + (size / 2), y + (size * ratio / 2));
			glVertex2f(x + (size / 2), y - (size * ratio / 2));
			glEnd();
		}
	};
	class block3 : public Object {
	public:
		float size;
		float ratio;

		block3(float X, float Y, float r, float s) : Object(X, Y) {
			size = s;
			ratio = r;
		}

		~block3() {

		}

		void Draw() {
			glBegin(GL_QUADS);
			glVertex2f(x - (size / 2), y - (size * ratio / 2));
			glVertex2f(x - (size / 2), y + (size * ratio / 2));
			glVertex2f(x + (size / 2), y + (size * ratio / 2));
			glVertex2f(x + (size / 2), y - (size * ratio / 2));
			glEnd();
		}
	};
}