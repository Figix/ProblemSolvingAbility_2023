/* 해당 코드는 GPT의 코드입니다.*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<int> adj[1001];
bool visited[1001];

void dfs(int v) {
    visited[v] = true;
    cout << v << ' ';
    for (int i = 0; i < adj[v].size(); i++) {
        int next = adj[v][i];
        if (!visited[next]) {
            dfs(next);
        }
    }
}

void bfs(int v) {
    queue<int> q;
    visited[v] = true;
    q.push(v);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        cout << x << ' ';
        for (int i = 0; i < adj[x].size(); i++) {
            int next = adj[x][i];
            if (!visited[next]) {
                visited[next] = true;
                q.push(next);
            }
        }
    }
}

int main() {
    int n, m, v;
    cin >> n >> m >> v;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    for (int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end());
    }
    dfs(v);
    cout << endl;
    fill(visited, visited + 1001, false);
    bfs(v);
    return 0;
}