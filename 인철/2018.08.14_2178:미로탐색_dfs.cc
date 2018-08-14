//https://www.acmicpc.net/problem/2178

#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstdio>

using namespace std;

int N, M;				//배열의 크기를 저장 할 변수.		
int map[100][100];		//지도를 입력 받을 배열.
bool visited[100][100];	//방문 기록을 저장 할 배열.
queue<pair<int,int> > q;	//방문 위치를 저장 할 큐.
int dr[4] = {0,1,0,-1};
int dc[4] = {1,0,-1,0};
int turn = 0;			//지나오는 도로의 수를 저장 할 변수.
int r, c;
int check = 0;

int main() {
	scanf_s("%d %d", &N,&M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j <M; j++) {
			scanf_s("%1d", &map[i][j]);
		}

	q.push({ 0,0 });
	visited[0][0] = true;

	while (!q.empty()) {
		int sz = q.size();
		turn++;
		while (sz--) {
			r = q.front().first;
			c = q.front().second;
			q.pop();

			if (r == N - 1 && c == M - 1) {
				cout << turn << '\n';
				check = 1;
				break;
			}
			for (int i = 0; i < 4; i++)
				if (!(map[r + dr[i]][c + dc[i]] == 0 || visited[r + dr[i]][c + dc[i]] || r + dr[i] < 0 || r + dr[i] >= N || c + dc[i] < 0 || c + dc[i] >= M)) {
					q.push({ r + dr[i],c + dc[i] });
					visited[r + dr[i]][c + dc[i]] = true;
				}
		}
		if (check) break;
	}
}
