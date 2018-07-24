//https://www.acmicpc.net/problem/15903

#include<iostream>
#include<algorithm>

using namespace std;

int N,M;
long score[1000];
long sum = 0;

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> score[i];

	while (M--) {
		sort(score, score + N);
		score[0] += score[1];
		score[1] = score[0];
	}

	for (int i = 0; i < N; i++)
		sum += score[i];
	
	cout << sum;
}
