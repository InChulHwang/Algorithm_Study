//sourse.c
struct XY {
	int id;
	XY *next;
}xy_to_id[101][101],xy[10010];  // xy_to_id  = id값 연결해 나가는것. xy[10010] = id 값만 넣어서 달기.

struct air_bnb {
	int star;
	int reserve_day;
	int days;
	int prices;
	air_bnb *next;
	air_bnb *prev;
}sukso[40005],reserve_suk[5005],search_top5[10001],search_head;  // 숙소 4만개 id 가짐, (예약횟수는 5000번)

int max_M;
int search_count;
int xy_num;
int reserve_suk_num;

XY *my_XY_alloc(int id) {
	xy[xy_num].id = id;
	xy[xy_num].next = 0;
	return &xy[xy_num++];
}
void add_xy_id(XY *tmp,int y, int x) {
	XY *search_xy = &xy_to_id[y][x];
	while (search_xy->next) search_xy = search_xy->next;
	search_xy->next = tmp;
}

void my_bnb_alloc(int id, int star, int prices) {
	sukso[id].prices = prices;
	sukso[id].star = star;
}
air_bnb *search_top5_alloc(int prices, int star, int bid) {
	search_top5[search_count].prices = prices;
	search_top5[search_count].star = star;
	search_top5[search_count].days = bid;// 여기서는 bid로씀.
	return &search_top5[search_count++];
}

air_bnb *my_reserve_suk_alloc(int id,int cday, int night) {
	reserve_suk[reserve_suk_num].star = sukso[id].star;
	reserve_suk[reserve_suk_num].reserve_day = cday;
	reserve_suk[reserve_suk_num].days = cday + night - 1; // 체크아웃 날짜.
	reserve_suk[reserve_suk_num].prices = sukso[id].prices;
	reserve_suk[reserve_suk_num].next = 0;
	reserve_suk[reserve_suk_num].prev = 0;
	return &reserve_suk[reserve_suk_num++];
}

void init(int M)
{
	max_M = M;
	reserve_suk_num = 0;
	xy_num = 0;
	search_count = 0;
	for (register int i = 0; i < 40005; i++) { 
		sukso[i].next = 0; sukso[i].prev = 0; 
	}
	for (register int i = 0; i < 101; i++)
		for (register int j = 0; j < 101; j++)
			xy_to_id[i][j].next = 0;
}

void add_bnb(int bid, int y, int x, int price, int rating)
{
	XY *tmp = my_XY_alloc(bid);
	add_xy_id(tmp,y,x);
	my_bnb_alloc(bid, rating, price);
}

int reserve(int bid, int cday, int night) //안겹치게 예약해주자.. 우선순위 큐
{
	air_bnb *search_tmp = &sukso[bid];
	
	
	for (; search_tmp->next != 0; search_tmp = search_tmp->next) {
		if (search_tmp->next->reserve_day > cday) { // 같거나 크면??
			if (search_tmp->next->reserve_day > cday + night - 1) { // 숙박일 안겹치면
				break;
			}
			else{ // 숙박일 겹치는 경우
				return 0;
			}
		}
		else if (search_tmp->next->reserve_day == cday) return 0;
		else { //예약일보다 크지만 그전에 겹치는경우.
			if (search_tmp->next->days >= cday)
				return 0;
		}
	}
	air_bnb *tmp = my_reserve_suk_alloc(bid, cday, night);

	tmp->prev = search_tmp;
	tmp->next = search_tmp->next;
	if (search_tmp->next) search_tmp->next->prev = tmp;
	search_tmp->next = tmp;

	return 1;
}

void push_queue(air_bnb *tmp) {  // 가격, 평점, id 순
	int pricess = tmp->prices; 
	int stars = tmp->star;
	int bids = tmp->days;


	air_bnb *search_tmp = &search_head;
	for (; search_tmp->next != 0; search_tmp = search_tmp->next) {
		if (search_tmp->next->prices > pricess) { // 지금값이 최소값.
			break;
		}
		else if (search_tmp->next->prices == pricess) {
			if (search_tmp->next->star < stars) { // 지금값이 최대값
				break;
			}
			else if (search_tmp->next->star == stars) {
				if (search_tmp->next->days < bids)
					break;
			}
		}
	}

	
	tmp->prev = search_tmp;
	tmp->next = search_tmp->next;
	if (search_tmp->next) search_tmp->next->prev = tmp;
	search_tmp->next = tmp;
}

int reserve_OX(int bid, int cday, int night) //안겹치게 예약해주자.. 우선순위 큐
{
	air_bnb *search_tmp = &sukso[bid];


	for (; search_tmp->next != 0; search_tmp = search_tmp->next) {
		if (search_tmp->next->reserve_day > cday) { // 같거나 크면??
			if (search_tmp->next->reserve_day > cday + night - 1) { // 숙박일 안겹치면
				break;
			}
			else { // 숙박일 겹치는 경우
				return 0;
			}
		}
		else if (search_tmp->next->reserve_day == cday) return 0;
		else { //예약일보다 크지만 그전에 겹치는경우.
			if (search_tmp->next->days >= cday)
				return 0;
		}
	}

	return 1;
}

int cancel(int bid, int cday)
{
	air_bnb *search_tmp = &sukso[bid];

	for (; search_tmp->next != 0; search_tmp = search_tmp->next) {
		if (search_tmp->next->reserve_day > cday) return 0; // 커지면 삭제 불가능.
		if (search_tmp->next->reserve_day == cday) { // 같으면 삭제가능
			break;
		}
	}
	air_bnb *tmp = search_tmp->next;
	if (!tmp)return 0;   //같은게 없는경우. 즉 삭제 불가능
	tmp->prev->next = tmp->next;
	if(tmp->next)tmp->next->prev = tmp->prev;

	return 1;
}

int search(int opt, int y, int x, int cday, int night, int top5_bid[5])
{
	int bid, count = 0;
	search_count = 0;
	search_head.next = 0;
	search_head.prev = 0;
	if (opt) { // opt 1인경우. 3x3 위치 검사.
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (y + i < 0 || x + j < 0 || y + i >= max_M || x + j >= max_M)
					continue;
				XY*search_tmp = &xy_to_id[y + i][x + j];
				for (; search_tmp->next != 0; search_tmp = search_tmp->next) {	// 좌표에 해당하는 숙소들 검색. 
																				//해당 숙소별 우선순위, 가격->평점-> id값
					bid = search_tmp->next->id;
					if (reserve_OX(bid, cday, night)) {  //예약 가능한경우
						air_bnb *tmp = search_top5_alloc(sukso[bid].prices, sukso[bid].star, bid);
						push_queue(tmp);
						count++;
					}
				}
			}
		}
	}
	else { // opt 0인경우 해당 위치 검사.
		XY*search_tmp = &xy_to_id[y][x];
		for (; search_tmp->next != 0; search_tmp = search_tmp->next) {	// 좌표에 해당하는 숙소들 검색. 
																		//해당 숙소별 우선순위, 가격->평점-> id값
			bid = search_tmp->next->id;
			if (reserve_OX(bid, cday, night)) {  //예약 가능한경우
				air_bnb *tmp = search_top5_alloc(sukso[bid].prices, sukso[bid].star, bid);
				push_queue(tmp);
				count++;
			}
		}
	}

	air_bnb *search_tmp = search_head.next;
	if (count >= 5) {
		for (int i = 0; i < 5; i++) {
			top5_bid[i] = search_tmp->days;
			search_tmp = search_tmp->next;
		}
		count = 5;
	}
	else {
		for (int i = 0; i < count; i++) {
			top5_bid[i] = search_tmp->days;
			search_tmp = search_tmp->next;
		}
	}

	return count;
}





//main.c
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int M);
extern void add_bnb(int bid, int y, int x, int price, int rating);
extern int reserve(int bid, int cday, int night);
extern int cancel(int bid, int cday);
extern int search(int opt, int y, int x, int cday, int night, int top5_bid[5]);

int main() {
	freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);

	int tc = 0;
	scanf("%d", &tc);
	for (int t = 1; t <= tc; t++) {
		int map_size;
		scanf("%d", &map_size);
		init(map_size);

		int score = 100;
		int i;
		int bid, y, x, price, rating, cday, night, opt;
		int result, user_res, top5[5], user_top5[5];

		char cmd = ' ';
		while (cmd != 'E') {
			scanf(" %c", &cmd);
			switch (cmd) {
			case 'B':
				scanf("%d %d %d %d %d %d", &bid, &y, &x, &price, &rating, &result);
				add_bnb(bid, y, x, price, rating);
				break;

			case 'R':
				scanf("%d %d %d", &bid, &cday, &night);
				user_res = reserve(bid, cday, night);

				scanf("%d", &result);
				if (result != user_res)
					score = 0;
				break;

			case 'C':
				scanf("%d %d", &bid, &cday);
				user_res = cancel(bid, cday);

				scanf("%d", &result);
				if (result != user_res)
					score = 0;
				break;

			case 'S':
				scanf("%d %d %d %d %d", &opt, &y, &x, &cday, &night);
				for (i = 0; i < 5; i++) {
					user_top5[i] = 0;
				}
				user_res = search(opt, y, x, cday, night, user_top5);

				scanf("%d", &result);
				for (i = 0; i < result; i++) {
					scanf("%d", top5 + i);
				}
				if (result != user_res)
					score = 0;
				else {
					for (i = 0; i < result; i++)
						if (top5[i] != user_top5[i])
							score = 0;
				}
				break;
			case 'E':
				printf("#%d %d\n", t, score);
			}
		}
	}
	return 0;
}
