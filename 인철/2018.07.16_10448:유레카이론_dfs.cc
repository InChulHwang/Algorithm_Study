//https://www.acmicpc.net/problem/10448

#include <iostream>
#include <algorithm>

using namespace std;

int N,M;				//테스트케이스의 수 & 테스트케이스를 임시 저장할 변수
int tri[100];			//삼각수를 저장할 배열
int num[1000];			//테스트케이스를 입력받는 배열
int sum = 0;			//삼각수의 합을 저장할 변수
int k;
int check;				//세 삼각수의 합으로 표현 가능 유무를 체크할 변수

void make_num() {
	k = 1;				//for loop에서 i의 최대치를 제한할 변수
	int tri_num;		//삼각수를 구하는데 쓸 변수
	while(1) {
		tri_num = 0;	
		for (int i = 1; i <= k; i++) {	//1부터 k까지의 합을 구할 loop
			tri_num += i;
		}
		if (tri_num <= 1000) {
			tri[k - 1] = tri_num;
			//cout << "tri : " << tri[k - 1] << '\n';
		}
		else break;
		k++;
	}
}						//이 함수를 마칠때의 k-1값은 1000이하의 삼각수의 수이다. 

void dfs(int turn) {
	if (!check) {		//check가 1이면 즉 답을 찾았으면 return
		if (turn == 3) {
			if (sum == M) {
				cout << "1" << '\n', check = 1;
			}
			return;
		}
		for (int i = 0; i < k - 1; i++) {
			sum += tri[i];
			//cout <<"turn : "<<turn<< "   tri : " << tri[i]<<"   sum : "<<sum << '\n';
			dfs(turn + 1);
			sum -= tri[i];
		}
		return;
	}
	else return;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)	cin >> num[i];
	make_num();
	for (int i = 0; i < N; i++) {
		check = 0;
		M = num[i];
		dfs(0);
		if (!check) cout << "0" << '\n';
	}
	return 0;
}
