//https://www.acmicpc.net/problem/2309

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>

using namespace std;

int high[9];		    			//9명의 키를 입력받을 배열
int sum=0;				        //키의 합을 저장 할 배열
bool visited[9];	  			//방문상태(7명에 포함되는것을 체크할) 배열
int sol[7];					//일곱 난쟁이의 키를 저장할 배열
int check = 0;	  				//첫번째 답을 찾았는지를 판별할 변수

void dfs(int turn) {

	if (!check) {                                     	      //check=1이면 답을 찾았으니 진행x
		if (turn == 7) {                                      //7난쟁이를 찾았으면 키의 합이 100인지 판별
			if (sum == 100) {
				int j = 0;
				for (int i = 0; i < 9; i++) {
					if (visited[i]) sol[j] = high[i], j++;
				}
				sort(sol, sol + 7);                   //찾은 7명의 키를 sol 배열에 옮긴 후 

				for (int i = 0; i < 7; i++)
					cout << sol[i] << '\n';
				check = 1;
				return;
			}
			else return;
		}

		for (int i = 0; i < 9; i++) {
			if (!visited[i]) {
				visited[i] = true;
				sum = sum + high[i];
				dfs(turn + 1);
				sum = sum - high[i];
				visited[i] = false;
			}
		}
	}
	return;
}

int main() {
	for (int i = 0; i < 9; i++)
		cin >> high[i];
	dfs(0);
}
