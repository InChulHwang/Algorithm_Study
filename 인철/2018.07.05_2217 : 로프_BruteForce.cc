//https://www.acmicpc.net/problem/2217

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>

using namespace std;

int N;				//로프의 수
int rope[100000];	//로프의 무게 한도를 저장할 배열
int maxi = 0;

bool desc(int a, int b) {
	return a > b;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> rope[i];
	sort(rope, rope + N,desc);

	for (int i = 0; i < N; i++) {
		maxi = max(maxi, rope[i]*(i+1));
	}
	cout << maxi;
	return 0;
}
