#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <random>

using namespace std;

const int MAX = 101;

// �̷��� ũ�⸦ �����ϴ� ����ü
struct Size {
    int x;
    int y;
};

class Maze {
public:
    int rows, cols;
    int maze[MAX][MAX]; // �̷� ������ �����ϴ� �迭
    int dist[MAX][MAX]; // ���������κ����� �Ÿ��� �����ϴ� �迭
    Size start, end;    // �������� �������� �����ϴ� ����ü
    int dx[4] = { -1, 1, 0, 0 };
    int dy[4] = { 0, 0, -1, 1 };

    void generateMaze() {
        // �̷��� ũ�⸦ �Է¹���
        cout << "�̷��� ũ�⸦ �Է� (��, ��) : ";
        cin >> rows >> cols;

        for (int j = 0; j < rows; j++) {
            for (int i = 0; i < cols; i++) {
                maze[i][j] = 0;
                dist[i][j] = -1;
            }
        }

        // �Ÿ� �迭 �ʱ�ȭ
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                dist[i][j] = -1; // �ʱⰪ�� -1�� �����Ͽ� �湮���� ���� ���·� �ʱ�ȭ
            }
        }
    }
    void generateMine() {
        int wall = 0;
        int counter = 0;
        cout << "�̷ο� ���� ��ֹ� �� : ";
        cin >> wall;
        // �õ尪�� ��� ���� random_device ����.
        random_device rd;
        // random_device �� ���� ���� ���� ������ �ʱ�ȭ �Ѵ�.
        mt19937 gen(rd());
        // 0 ���� n*m ���� �յ��ϰ� ��Ÿ���� �������� �����ϱ� ���� �յ� ���� ����.
        uniform_int_distribution<int> dis(0, rows * cols - 1);
        /* 0���� n*m���� ��Ƽ� �����ڸ� �������� ���� ������
            'dis(gen);' �̷��� �ѹ� ȣ���ϸ� ���� �� �̱� ������ */
            //������ֹ� ���� �ڵ�
        while (counter < wall) {    // ��ֹ��� 10�� �����ΰ�?
            int tmp = dis(gen);

            if (maze[tmp / rows][tmp % rows] == 0) { //�������� ¤�� ���� �� ���ΰ�?
                maze[tmp / rows][tmp % rows] = 1;
                counter++;
            }
        }

        cout << "��ֹ� ��ġ �Ϸ�" << endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (maze[i][j] == 0) {
                    cout << "�� ";
                }
                else if (maze[i][j] == 1) {
                    cout << "�� ";
                }
            }
            cout << endl;
        }
    }
    void decideA2B() {
        // �������� �������� �Է¹���
        cout << endl << "������ܺ��� 0���� �����մϴ�." << endl;
        cout << "�������� ��� �� �Է� : ";
        cin >> start.x >> start.y;
        cout << "�������� ��� �� �Է� : ";
        cin >> end.x >> end.y;
    }
    void solveMaze() {
        // �������� �Ÿ��� 0���� �����ϰ� ť�� ����
        dist[start.x][start.y] = 0;
        queue<Size> q;
        q.push(start);

        // BFS�� �̿��Ͽ� �ִ� �Ÿ��� ���
        while (!q.empty()) {
            int x = q.front().x;
            int y = q.front().y;
            q.pop();

            for (int dir = 0; dir < 4; ++dir) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                // �̷� ������ ����� �ʰ�, �̵��� �� �ִ� ��ġ�̸�, ���� �湮���� ���� ��ġ���
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && maze[nx][ny] == 0 && dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y] + 1; // �Ÿ��� �����ϰ� ť�� ����
                    q.push({ nx, ny });
                }
            }
        }
    }
    void printSolution() {
        // ���������� ������������ ��� ���
        if (dist[end.x][end.y] == -1) {
            cout << "��ΰ� �������� �ʽ��ϴ�." << endl;
        }
        else {
            // ������������ �ִ� �Ÿ� ���
            cout << "�ִ� �Ÿ�: " << dist[end.x][end.y] << endl;
            cout << "���: ";
            int x = end.x;
            int y = end.y;
            vector<Size> path;
            path.push_back({ x, y });

            while (x != start.x || y != start.y) {
                for (int dir = 0; dir < 4; ++dir) {
                    int nx = x + dx[dir];
                    int ny = y + dy[dir];

                    if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && dist[nx][ny] == dist[x][y] - 1) {
                        x = nx;
                        y = ny;
                        path.push_back({ x, y });
                        break;
                    }
                }
            }

            for (int i = path.size() - 1; i >= 0; --i) {
                cout << "(" << path[i].x << ", " << path[i].y << ")";
                if (i > 0) {
                    cout << " -> ";
                }
                maze[path[i].x][path[i].y] = 4;
            }
            maze[start.x][start.y] = 2;
            maze[end.x][end.y] = 3;
            cout << endl;

            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    if (maze[i][j] == 0) {
                        cout << "�� ";
                    }
                    else if (maze[i][j] == 1) {
                        cout << "�� ";
                    }
                    else if (maze[i][j] == 2) {
                        cout << "�� ";
                    }
                    else if (maze[i][j] == 3) {
                        cout << "�� ";
                    }
                    else if (maze[i][j] == 4) {
                        cout << "�� ";
                    }
                }
                cout << endl;
            }
        }
    }
};