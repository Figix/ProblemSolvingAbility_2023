#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <random>

using namespace std;

const int MAX = 101;

// 미로의 크기를 저장하는 구조체
struct Size {
    int x;
    int y;
};

class Maze {
public:
    int rows, cols;
    int maze[MAX][MAX]; // 미로 정보를 저장하는 배열
    int dist[MAX][MAX]; // 시작점으로부터의 거리를 저장하는 배열
    Size start, end;    // 시작점과 도착점을 저장하는 구조체
    int dx[4] = { -1, 1, 0, 0 };
    int dy[4] = { 0, 0, -1, 1 };

    void generateMaze() {
        // 미로의 크기를 입력받음
        cout << "미로의 크기를 입력 (행, 열) : ";
        cin >> rows >> cols;

        for (int j = 0; j < rows; j++) {
            for (int i = 0; i < cols; i++) {
                maze[i][j] = 0;
                dist[i][j] = -1;
            }
        }

        // 거리 배열 초기화
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                dist[i][j] = -1; // 초기값을 -1로 설정하여 방문하지 않은 상태로 초기화
            }
        }
    }
    void generateMine() {
        int wall = 0;
        int counter = 0;
        cout << "미로에 넣을 장애물 수 : ";
        cin >> wall;
        // 시드값을 얻기 위한 random_device 생성.
        random_device rd;
        // random_device 를 통해 난수 생성 엔진을 초기화 한다.
        mt19937 gen(rd());
        // 0 부터 n*m 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
        uniform_int_distribution<int> dis(0, rows * cols - 1);
        /* 0부터 n*m으로 잡아서 가장자리 안쪽으로 맵을 생성함
            'dis(gen);' 이렇게 한번 호출하면 랜덤 값 뽑기 가능함 */
            //랜덤장애물 생성 코드
        while (counter < wall) {    // 장애물이 10개 이하인가?
            int tmp = dis(gen);

            if (maze[tmp / rows][tmp % rows] == 0) { //랜덤으로 짚은 곳이 빈 곳인가?
                maze[tmp / rows][tmp % rows] = 1;
                counter++;
            }
        }

        cout << "장애물 배치 완료" << endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (maze[i][j] == 0) {
                    cout << "□ ";
                }
                else if (maze[i][j] == 1) {
                    cout << "■ ";
                }
            }
            cout << endl;
        }
    }
    void decideA2B() {
        // 시작점과 도착점을 입력받음
        cout << endl << "좌측상단부터 0으로 시작합니다." << endl;
        cout << "시작점의 행과 열 입력 : ";
        cin >> start.x >> start.y;
        cout << "도착점의 행과 열 입력 : ";
        cin >> end.x >> end.y;
    }
    void solveMaze() {
        // 시작점의 거리를 0으로 설정하고 큐에 넣음
        dist[start.x][start.y] = 0;
        queue<Size> q;
        q.push(start);

        // BFS를 이용하여 최단 거리를 계산
        while (!q.empty()) {
            int x = q.front().x;
            int y = q.front().y;
            q.pop();

            for (int dir = 0; dir < 4; ++dir) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                // 미로 범위를 벗어나지 않고, 이동할 수 있는 위치이며, 아직 방문하지 않은 위치라면
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && maze[nx][ny] == 0 && dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y] + 1; // 거리를 갱신하고 큐에 넣음
                    q.push({ nx, ny });
                }
            }
        }
    }
    void printSolution() {
        // 시작점에서 도착점까지의 경로 출력
        if (dist[end.x][end.y] == -1) {
            cout << "경로가 존재하지 않습니다." << endl;
        }
        else {
            // 도착점까지의 최단 거리 출력
            cout << "최단 거리: " << dist[end.x][end.y] << endl;
            cout << "경로: ";
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
                        cout << "□ ";
                    }
                    else if (maze[i][j] == 1) {
                        cout << "■ ";
                    }
                    else if (maze[i][j] == 2) {
                        cout << "☆ ";
                    }
                    else if (maze[i][j] == 3) {
                        cout << "★ ";
                    }
                    else if (maze[i][j] == 4) {
                        cout << "♤ ";
                    }
                }
                cout << endl;
            }
        }
    }
};