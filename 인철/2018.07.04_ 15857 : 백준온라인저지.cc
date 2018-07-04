//https://www.acmicpc.net/problem/15857

#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

int N;

int main() {
	cin >> N;

	if (N == 1) {
		cout << 'a';
	}
	else if (N == 2) {
		cout << 'b';
	}
	else if (N == 3) {
		cout << 'b';
	}
	else if (N == 4) {
		cout << 'c';
	}
	else if (N == 5) {
		cout << 'd';
	}else if(N==6){
		cout << 'd';
	}
	else if (N == 7) {
		cout << 'd';
	}
	else {
		cout << 'c';
	}
}
