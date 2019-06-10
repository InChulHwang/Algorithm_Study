#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#define NUM(x) (x-'0')

char n[210], m[210];
int N[210], M[210];
int sol[210];	              	//정답을 저장 해 놓을 배열
int pos;			                //정답의 위치를 저장할 변수
int a, b;
int start, end;		            //큰 배열에서 연산에 쓰이는 부분의 처음과 끝 위치를 지정
int len;		                	//나누는 수의 크기를 저장

//입력받은 두 배열의 크기를 구해  a,b 에 저장
//입력받은 문자열을 숫자로 바꿔 N,M 에 저장
//두 배열중 나누는 수의 크기를 len에 저장
void cal_size() {
	int i;
	for (i = 0; n[i]; i++) {
		N[i] = NUM(n[i]);
	}
	a = i - 1;
	for (i = 0; m[i]; i++) {
		M[i] = NUM(m[i]);
	}
	b = i - 1;
	len = a > b ? b : a;
}

//앞에것이 크면 1, 작으면 -1, 같으면 0을 반환
int strcmp(int* x, int* y) {
	for (int i = 0; i <= len; i++) {
		if (x[i] > y[i])return 1;
		else if (x[i] < y[i])return -1;
	}
	return 0;
}

//나눠지는 수는 start 지점, 나누는 수는 0번지를 입력받음
void minus(int* x, int* y) {

	//뺄셈 과정을 가능 한 최대한 뺀다.
	while (1) {
		//나눌 수 있는지 판단
		for (int i = 0; i <= len; i++) {
			if (x[i] > y[i]) break;			                //나눠지는 수가 더 크기 때문에 나눌 수 있다.
			if (x[i] < y[i]) return;		                //나눠지는 수가 더 작기 때문에 나눌 수 없다.
		}

		//뺄셈 시작
		for (int i = len; i >= 0; i--) {
			//빼지는 수가 더 크면 그냥 뺀다.
			if (x[i] >= y[i]) {
				x[i] -= y[i];
			}
			//빼지는 수가 더 작으면 앞자리 수를 1 감소하고 10을 더한다.
			else {
				x[i] = x[i] - y[i] + 10;
				x[i - 1]--;
			}
		}
		sol[pos]++;							                       //뺄셈 1번이 완료되면 그 위치의 결과값에 1 추가.
	}
}

void clear() {
	for (int i = 0; i < 210; i++)
		sol[i] = 0;
}

void solve() {

	cal_size();							                         	//사이즈 외 이것저것 계산.
	start = 0;						                        		//start와 end를 초기화
	end = len;
	pos = 0;							                          	//결과를 저장할 위치 초기화
	clear();

	if (a > b) {					                        		//n이 나눠지는 수
		while (1) {							
			minus(N+start, M);			                			//뺄셈 1회 진행
			pos++;
			if (end != a) {					                    	//end의 위치가 끝 지점이 아니라면
				start++;					                        	//뺄셈이 끝났으니 시작,끝 위치 갱신
				end++;
				N[start] += N[start - 1] * 10;            	//이전 시작점에 남은 값을 다음 연산을 위해 이동
			}
			else break;
		}
	}
	else if (a < b) {					                      	//m이 나눠지는 수
		while (1) {
			minus(M+start, N);					
			pos++;
			if (end != b) {						
				start++;					
				end++;
				M[start] += M[start - 1] * 10;	
			}
			else break;
		}
	}
	else {									                          //몰라 구해야 해
		if (strcmp(N, M)==1) {			                  	//n이 나눠지는 수
			while (1) {
				minus(N + start, M);				            		//뺄셈 1회 진행
				pos++;
				if (end != a) {					                   	//end의 위치가 끝 지점이 아니라면
					start++;						                      //뺄셈이 끝났으니 시작,끝 위치 갱신
					end++;
					N[start] += N[start - 1] * 10;	          //이전 시작점에 남은 값을 다음 연산을 위해 이동
				}
				else break;
			}
		}
		else if (strcmp(N, M) == -1) {		              //m이 나눠지는 수
			while (1) {
				minus(M + start, N);
				pos++;
				if (end != b) {
					start++;
					end++;
					M[start] += M[start - 1] * 10;
				}
				else break;
			}
		}
		else {								                          //n과 m은 같은 수  -> 1을 출력
			printf("1\n");
			return;
		}
	}

	if (sol[0] != 0) {
		for (int i = 0; i < pos; i++)
			printf("%d", sol[i]);
	}
	else {
		for (int i = 1; i < pos; i++)
			printf("%d", sol[i]);
	}
	printf("\n");

}

int main() {
	while (1) {
		scanf("%s", &n);
		if (n[0] == '0') return 0;
		scanf("%s", &m);
		if (m[0] == '0') return 0;

		solve();
	}
}
