//https://www.acmicpc.net/problem/15651

#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

int N, M;
int store[8];
int visited[8];

void dfs(int turn) {
	if (turn == M) {
		/*
				for (int m = 0; m < M-1; m++) {
					if (store[m] > store[m + 1])
						return;
				}
				*/

		for (int k = 0; k < M; k++)
			cout << store[k] << " ";
		cout << '\n';
		return;
	}

	for (int i = 0; i < N; i++) {
		//if (!visited[i]) {
			//visited[i] = 1;
		store[turn] = i + 1;
		dfs(turn + 1);
		//visited[i] = 0;
	//}
	}
}

int main() {
	cin >> N >> M;
	dfs(0);
}
