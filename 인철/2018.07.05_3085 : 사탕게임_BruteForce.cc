//https://www.acmicpc.net/problem/2309

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>

using namespace std;

int N;
char map[50][50];
char temp;
int cnt;
int maxi = 1;

void find_maximum() {
	for (int i = 0; i < N; i++) {			//column에서 최대값을 찾는 loop
		cnt = 1;
		for (int j = 0; j < N-1; j++) {
			if (map[i][j] == map[i][j + 1]) cnt++;
			else {
				if (maxi < cnt) maxi = cnt;
				cnt = 1;
			}
		}
		if (maxi < cnt) maxi = cnt;
	}

	for (int j = 0; j< N; j++) {			//row에서 최대값을 찾는 loop
		cnt = 1;
		for (int i = 0; i < N - 1; i++) {
			if (map[i][j] == map[i+1][j ]) cnt++;
			else {
				if (maxi < cnt) maxi = cnt;
				cnt = 1;
			}
		}
		if (maxi < cnt) maxi = cnt;
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	for(int i=0;i<N;i++)		//column에서 두개를 바꾸는 loop
		for (int j = 0; j < N-1; j++) {
			temp = map[i][j];
			map[i][j] = map[i][j + 1];
			map[i][j + 1] = temp;
			find_maximum();
			map[i][j + 1] = map[i][j];
			map[i][j] = temp;
		}

	for (int i = 0; i<N-1; i++)	//row에서 두개를 바꾸는 loop
		for (int j = 0; j < N; j++) {
			temp = map[i][j];
			map[i][j] = map[i + 1][j];
			map[i + 1][j] = temp;
			find_maximum();
			map[i + 1][j] = map[i][j];
			map[i][j] = temp;
		}
	cout << maxi;
	return 0;
}
