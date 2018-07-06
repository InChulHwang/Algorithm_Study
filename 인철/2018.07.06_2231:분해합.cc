//https://www.acmicpc.net/problem/2231

#include <iostream>
#include <algorithm>

using namespace std;

int N;					//입력받는 자연수 N
int M;					//생성자를 구하는데 쓸 변수
int k;					//N의 자리 수를 카운트 할 변수
int check_num = 0;

void check(int a) {		//분해합을 구하는 함수
	M = a;				//초기 입력값을 M에 넣고
	int b = a;
	int ck = k;			//숫자의 자리수를 입력 받는다
	while (ck--) {		//각 자리수를 더해주는 loop
		M += b % 10;	
		b /= 10;
	}
	if (N == M) cout << a << '\n',check_num=1;
}

int main() {
	cin >> N;
	M = N, k = 1;
	while (M > 9) {
		M /= 10;
		k++;
	}
	for (int i = N - 9 * k; i < N; i++) {
		check(i);
		if (check_num) return 0;
	}
	cout << "0" << '\n';
	return 0;
}

