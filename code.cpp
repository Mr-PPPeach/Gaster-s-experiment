#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include<sys/stat.h>
#pragma comment(lib, "winmm.lib")
#define WIDTH 1000
#define HEIGHT 1000
#define pi acos(-1)
int CODE = 1;
int init_health;
double E=5;

struct player {
	double x;
	double y;
	int health;
	bool win;
}player;

struct gaster {
	int head_x;
	int head_y;
	int body_x;
	int body_y;
}gaster;

struct laser {
	int left = 0;
	int top = 0;
	int right = 0;
	int bottom = 0;
}laser[100];

struct blaster{
	int x;
	int y;
	int position;//1-4，左上右下
	int borntime;
	bool life=false;
}blaster[1000];

typedef struct grade {
	char ID[16];
	int health;
}DATA;

IMAGE PLAYER[2];
IMAGE GASTER_HEAD[2];
IMAGE GASTER_BODY[2];
IMAGE GASTER_BLASTER_CLOSE_DOWN[2];
IMAGE GASTER_BLASTER_CLOSE_LEFT[2];
IMAGE GASTER_BLASTER_CLOSE_UP[2];
IMAGE GASTER_BLASTER_CLOSE_RIGHT[2];
IMAGE GASTER_BLASTER_OPEN_DOWN[2];
IMAGE GASTER_BLASTER_OPEN_LEFT[2];
IMAGE GASTER_BLASTER_OPEN_UP[2];
IMAGE GASTER_BLASTER_OPEN_RIGHT[2];
IMAGE GAME_OVER;
IMAGE L_GASTER_BLASTER_CLOSE_DOWN[2];
IMAGE L_GASTER_BLASTER_CLOSE_LEFT[2];
IMAGE L_GASTER_BLASTER_CLOSE_UP[2];
IMAGE L_GASTER_BLASTER_CLOSE_RIGHT[2];
IMAGE L_GASTER_BLASTER_OPEN_DOWN[2];
IMAGE L_GASTER_BLASTER_OPEN_LEFT[2];
IMAGE L_GASTER_BLASTER_OPEN_UP[2];
IMAGE L_GASTER_BLASTER_OPEN_RIGHT[2];

void loadimg() {//图片加载
	loadimage(&PLAYER[0], "./images/heart_1.jpg", WIDTH / 50, HEIGHT / 50);
	loadimage(&PLAYER[1], "./images/heart_2.jpg", WIDTH / 50, HEIGHT / 50);
	loadimage(&GASTER_HEAD[0], "./images/gaster_head_1.jpg", WIDTH / 2, HEIGHT / 3.2);
	loadimage(&GASTER_HEAD[1], "./images/gaster_head_2.jpg", WIDTH / 2, HEIGHT / 3.2);
	loadimage(&GASTER_BODY[0], "./images/gaster_body_1.jpg", WIDTH / 2, HEIGHT / 3.2);
	loadimage(&GASTER_BODY[1], "./images/gaster_body_2.jpg", WIDTH / 2, HEIGHT / 3.2);
	loadimage(&GASTER_BLASTER_CLOSE_DOWN[0], "./images/gaster_blaster/close/down_1.jpg", WIDTH / 8, HEIGHT / 8 / 2 * 3);
	loadimage(&GASTER_BLASTER_CLOSE_DOWN[1], "./images/gaster_blaster/close/down_2.jpg", WIDTH / 8, HEIGHT / 8 / 2 * 3);
	loadimage(&GASTER_BLASTER_CLOSE_UP[0], "./images/gaster_blaster/close/up_1.jpg", WIDTH / 8, HEIGHT / 8 / 2 * 3);
	loadimage(&GASTER_BLASTER_CLOSE_UP[1], "./images/gaster_blaster/close/up_2.jpg", WIDTH / 8, HEIGHT / 8 / 2 * 3);
	loadimage(&GASTER_BLASTER_CLOSE_LEFT[0], "./images/gaster_blaster/close/left_1.jpg", WIDTH / 8 / 2 * 3, HEIGHT / 8);
	loadimage(&GASTER_BLASTER_CLOSE_LEFT[1], "./images/gaster_blaster/close/left_2.jpg", WIDTH / 8 / 2 * 3, HEIGHT / 8);
	loadimage(&GASTER_BLASTER_CLOSE_RIGHT[0], "./images/gaster_blaster/close/right_1.jpg", WIDTH / 8 / 2 * 3, HEIGHT / 8);
	loadimage(&GASTER_BLASTER_CLOSE_RIGHT[1], "./images/gaster_blaster/close/right_2.jpg", WIDTH / 8 / 2 * 3, HEIGHT / 8);
	loadimage(&GASTER_BLASTER_OPEN_DOWN[0], "./images/gaster_blaster/open/down_1.jpg", WIDTH / 8, HEIGHT / 8 / 2 * 3);
	loadimage(&GASTER_BLASTER_OPEN_DOWN[1], "./images/gaster_blaster/open/down_2.jpg", WIDTH / 8, HEIGHT / 8 / 2 * 3);
	loadimage(&GASTER_BLASTER_OPEN_UP[0], "./images/gaster_blaster/open/up_1.jpg", WIDTH / 8, HEIGHT / 8 / 2 * 3);
	loadimage(&GASTER_BLASTER_OPEN_UP[1], "./images/gaster_blaster/open/up_2.jpg", WIDTH / 8, HEIGHT / 8 / 2 * 3);
	loadimage(&GASTER_BLASTER_OPEN_LEFT[0], "./images/gaster_blaster/open/left_1.jpg", WIDTH / 8 / 2 * 3, HEIGHT / 8);
	loadimage(&GASTER_BLASTER_OPEN_LEFT[1], "./images/gaster_blaster/open/left_2.jpg", WIDTH / 8 / 2 * 3, HEIGHT / 8);
	loadimage(&GASTER_BLASTER_OPEN_RIGHT[0], "./images/gaster_blaster/open/right_1.jpg", WIDTH / 8 / 2 * 3, HEIGHT / 8);
	loadimage(&GASTER_BLASTER_OPEN_RIGHT[1], "./images/gaster_blaster/open/right_2.jpg", WIDTH / 8 / 2 * 3, HEIGHT / 8);
	loadimage(&GAME_OVER, "./images/game_over.jpg", WIDTH, HEIGHT / 1000 * 400);
	loadimage(&L_GASTER_BLASTER_CLOSE_DOWN[0], "./images/gaster_blaster/close/down_1.jpg", WIDTH / 8 * 2, HEIGHT / 8 / 2 * 3 * 2);
	loadimage(&L_GASTER_BLASTER_CLOSE_DOWN[1], "./images/gaster_blaster/close/down_2.jpg", WIDTH / 8 * 2, HEIGHT / 8 / 2 * 3 * 2);
	loadimage(&L_GASTER_BLASTER_CLOSE_UP[0], "./images/gaster_blaster/close/up_1.jpg", WIDTH / 8 * 2, HEIGHT / 8 / 2 * 3 * 2);
	loadimage(&L_GASTER_BLASTER_CLOSE_UP[1], "./images/gaster_blaster/close/up_2.jpg", WIDTH / 8 * 2, HEIGHT / 8 / 2 * 3 * 2);
	loadimage(&L_GASTER_BLASTER_CLOSE_LEFT[0], "./images/gaster_blaster/close/left_1.jpg", WIDTH / 8 / 2 * 3 * 2, HEIGHT / 8 * 2);
	loadimage(&L_GASTER_BLASTER_CLOSE_LEFT[1], "./images/gaster_blaster/close/left_2.jpg", WIDTH / 8 / 2 * 3 * 2, HEIGHT / 8 * 2);
	loadimage(&L_GASTER_BLASTER_CLOSE_RIGHT[0], "./images/gaster_blaster/close/right_1.jpg", WIDTH / 8 / 2 * 3 * 2, HEIGHT / 8 * 2);
	loadimage(&L_GASTER_BLASTER_CLOSE_RIGHT[1], "./images/gaster_blaster/close/right_2.jpg", WIDTH / 8 / 2 * 3 * 2, HEIGHT / 8 * 2);
	loadimage(&L_GASTER_BLASTER_OPEN_DOWN[0], "./images/gaster_blaster/open/down_1.jpg", WIDTH / 8 * 2, HEIGHT / 8 / 2 * 3 * 2);
	loadimage(&L_GASTER_BLASTER_OPEN_DOWN[1], "./images/gaster_blaster/open/down_2.jpg", WIDTH / 8 * 2, HEIGHT / 8 / 2 * 3 * 2);
	loadimage(&L_GASTER_BLASTER_OPEN_UP[0], "./images/gaster_blaster/open/up_1.jpg", WIDTH / 8 * 2, HEIGHT / 8 / 2 * 3 * 2);
	loadimage(&L_GASTER_BLASTER_OPEN_UP[1], "./images/gaster_blaster/open/up_2.jpg", WIDTH / 8 * 2, HEIGHT / 8 / 2 * 3 * 2);
	loadimage(&L_GASTER_BLASTER_OPEN_LEFT[0], "./images/gaster_blaster/open/left_1.jpg", WIDTH / 8 / 2 * 3 * 2, HEIGHT / 8 * 2);
	loadimage(&L_GASTER_BLASTER_OPEN_LEFT[1], "./images/gaster_blaster/open/left_2.jpg", WIDTH / 8 / 2 * 3 * 2, HEIGHT / 8 * 2);
	loadimage(&L_GASTER_BLASTER_OPEN_RIGHT[0], "./images/gaster_blaster/open/right_1.jpg", WIDTH / 8 / 2 * 3 * 2, HEIGHT / 8 * 2);
	loadimage(&L_GASTER_BLASTER_OPEN_RIGHT[1], "./images/gaster_blaster/open/right_2.jpg", WIDTH / 8 / 2 * 3 * 2, HEIGHT / 8 * 2);

}

void gameinit() {//初始化函数（包含图片加载）
	loadimg();
	player.x = WIDTH / 2 - WIDTH / 100;
	player.y = HEIGHT / 4 * 3;
	player.health = 20;//初始化生命值
	player.win = false;
	gaster.body_x = WIDTH * 0.25;
	gaster.body_y = 0;
	gaster.head_x = WIDTH * 0.25;
	gaster.head_y = 0;
}

void gamedraw(int timing) {//绘图函数
	static int initialhealth=player.health;
	init_health = initialhealth;
	char cur_hp[10],hp[10];
	setfillcolor(WHITE);
	solidrectangle(WIDTH / 4 - (WIDTH / 100), HEIGHT / 2, WIDTH / 4, HEIGHT / 8 * 7 + (HEIGHT / 100));
	solidrectangle(WIDTH / 4 - (WIDTH / 100), HEIGHT / 2 - (HEIGHT / 100), WIDTH / 4 * 3 + (WIDTH / 100), HEIGHT / 2);
	solidrectangle(WIDTH / 4 * 3, HEIGHT / 2 - (HEIGHT / 100), WIDTH / 4 * 3 + (WIDTH / 100), HEIGHT / 8 * 7 + (HEIGHT / 100));
	solidrectangle(WIDTH / 4 - (WIDTH / 100), HEIGHT / 8 * 7, WIDTH / 4 * 3 + (WIDTH / 100), HEIGHT / 8 * 7 + (WIDTH / 100));
	putimage(player.x, player.y, &PLAYER[1], SRCAND);
	putimage(player.x, player.y, &PLAYER[0], SRCPAINT);
	if (timing >= 35000 && timing <= 52500) {
		setfillcolor(RED);
		solidcircle(gaster.head_x+WIDTH/1000*215, HEIGHT/1000*gaster.head_y+140, WIDTH / 1000*3 );
		solidcircle(gaster.head_x+WIDTH/1000*262, HEIGHT/1000*gaster.head_y+135, WIDTH / 1000 * 3);
	}
	putimage(gaster.head_x, gaster.head_y, &GASTER_HEAD[1], SRCAND);
	putimage(gaster.head_x, gaster.head_y, &GASTER_HEAD[0], SRCPAINT);
	putimage(gaster.body_x, gaster.body_y, &GASTER_BODY[1], SRCAND);
	putimage(gaster.body_x, gaster.body_y, &GASTER_BODY[0], SRCPAINT);
	settextstyle(HEIGHT / 32, WIDTH / 64, "Consolas");
	outtextxy(WIDTH / 4, HEIGHT / 8 * 7 + HEIGHT / 32, "HP");
	sprintf_s(cur_hp, "%d", player.health);
	sprintf_s(hp, "%d", initialhealth);
	settextcolor(YELLOW);
	outtextxy(WIDTH / 4+WIDTH/64*3, HEIGHT / 8 * 7 + HEIGHT / 32, cur_hp);
	settextcolor(WHITE);
	outtextxy(WIDTH / 4 + WIDTH / 64 * 5, HEIGHT / 8 * 7 + HEIGHT / 32, "/");
	outtextxy(WIDTH / 4 + WIDTH / 64 * 6, HEIGHT / 8 * 7 + HEIGHT / 32, hp);
	setlinecolor(WHITE);
	setfillcolor(BLACK);
	fillrectangle(WIDTH / 4 + WIDTH / 64*10, HEIGHT / 8 * 7 + HEIGHT / 32, WIDTH / 4 * 3, HEIGHT / 8 * 7 + HEIGHT / 32 * 2);
	setfillcolor(RED);
	fillrectangle(WIDTH / 4 + WIDTH / 64 * 10, HEIGHT / 8 * 7 + HEIGHT / 32, WIDTH / 4 + WIDTH / 64 * 10 + (WIDTH / 4 * 3 - (WIDTH / 4 + WIDTH / 64 * 10)) * player.health / initialhealth , HEIGHT / 8 * 7 + HEIGHT / 32 * 2);
}

void playermovement(double speed) {//玩家移动函数
	if (GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP)) {
		if (player.y >= HEIGHT / 2) {
			player.y -= speed;
		}
	}
	if (GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN)) {
		if (player.y <= HEIGHT / 8 * 7 - HEIGHT / 50) {
			player.y += speed;
		}
	}
	if (GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT)) {
		if (player.x >= WIDTH / 4) {
			player.x -= speed;
		}
	}
	if (GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT)) {
		if (player.x <= WIDTH / 4 * 3 - WIDTH / 50) {
			player.x += speed;
		}
	}
}

void menudraw(int i) {
	if (i == 0) {
		FlushBatchDraw();
		cleardevice();
		settextstyle(HEIGHT / 1000 * 60, WIDTH / 1000 * 30, "Consolas");
		outtextxy(WIDTH / 1000 * 220, HEIGHT / 1000*400, "GASTER'S EXPERIMENT");
		settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Consolas");
		outtextxy(WIDTH / 1000 * 840, HEIGHT - HEIGHT / 1000 * 20, "Made by Mr.Peach");
		settextstyle(HEIGHT / 20, WIDTH / 40, "Consolas");
		outtextxy(WIDTH / 1000 * 440, HEIGHT / 2, "START");
		outtextxy(WIDTH / 1000 * 450, HEIGHT / 2 + HEIGHT / 20, "HELP");
		outtextxy(WIDTH / 1000 * 450, HEIGHT / 2 + HEIGHT / 20 + HEIGHT / 20, "QUIT");
		line(WIDTH / 1000 * 425, HEIGHT / 2, WIDTH / 1000 * 425, HEIGHT / 2 + (HEIGHT / 20) * 3);//左线
		line(WIDTH / 1000 * 425, HEIGHT / 2, WIDTH / 1000 * 575, HEIGHT / 2);//上线
		line(WIDTH / 1000 * 575, HEIGHT / 2, WIDTH / 1000 * 575, HEIGHT / 2 + (HEIGHT / 20) * 3);//右线
		line(WIDTH / 1000 * 425, HEIGHT / 2 + (HEIGHT / 20) * 3, WIDTH / 1000 * 575, HEIGHT / 2 + (HEIGHT / 20) * 3);//下线
		line(WIDTH / 1000 * 425, HEIGHT / 2 + HEIGHT / 20, WIDTH / 1000 * 575, HEIGHT / 2 + HEIGHT / 20);//中1线
		line(WIDTH / 1000 * 425, HEIGHT / 2 + HEIGHT / 20 + HEIGHT / 20, WIDTH / 1000 * 575, HEIGHT / 2 + HEIGHT / 20 + HEIGHT / 20);//中2线
	}
	if (i == 1) {
		FlushBatchDraw();
		cleardevice();
		settextstyle(HEIGHT / 1000 * 60, WIDTH / 1000 * 30, "Consolas");
		outtextxy(WIDTH / 1000 * 220, HEIGHT / 1000 * 400, "GASTER'S EXPERIMENT");
		settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Consolas");
		outtextxy(WIDTH / 1000 * 840, HEIGHT - HEIGHT / 1000 * 20, "Made by Mr.Peach");
		setfillcolor(WHITE);
		solidrectangle(WIDTH / 1000 * 425, HEIGHT / 2, WIDTH / 1000 * 575, HEIGHT / 2 + HEIGHT / 20);
		settextstyle(HEIGHT / 20, WIDTH / 40, "Consolas");
		settextcolor(BLACK);
		outtextxy(WIDTH / 1000 * 440, HEIGHT / 2, "START");
		settextcolor(WHITE);
		outtextxy(WIDTH / 1000 * 450, HEIGHT / 2 + HEIGHT / 20, "HELP");
		outtextxy(WIDTH / 1000 * 450, HEIGHT / 2 + HEIGHT / 20 + HEIGHT / 20, "QUIT");
		line(WIDTH / 1000 * 425, HEIGHT / 2, WIDTH / 1000 * 425, HEIGHT / 2 + (HEIGHT / 20) * 3);//左线
		line(WIDTH / 1000 * 425, HEIGHT / 2, WIDTH / 1000 * 575, HEIGHT / 2);//上线
		line(WIDTH / 1000 * 575, HEIGHT / 2, WIDTH / 1000 * 575, HEIGHT / 2 + (HEIGHT / 20) * 3);//右线
		line(WIDTH / 1000 * 425, HEIGHT / 2 + (HEIGHT / 20) * 3, WIDTH / 1000 * 575, HEIGHT / 2 + (HEIGHT / 20) * 3);//下线
		line(WIDTH / 1000 * 425, HEIGHT / 2 + HEIGHT / 20, WIDTH / 1000 * 575, HEIGHT / 2 + HEIGHT / 20);//中1线
		line(WIDTH / 1000 * 425, HEIGHT / 2 + HEIGHT / 20 + HEIGHT / 20, WIDTH / 1000 * 575, HEIGHT / 2 + HEIGHT / 20 + HEIGHT / 20);//中2线
	}
	if (i == 2) {
		FlushBatchDraw();
		cleardevice();
		settextstyle(HEIGHT / 1000 * 60, WIDTH / 1000 * 30, "Consolas");
		outtextxy(WIDTH / 1000 * 220, HEIGHT / 1000 * 400, "GASTER'S EXPERIMENT");
		settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Consolas");
		outtextxy(WIDTH / 1000 * 840, HEIGHT - HEIGHT / 1000 * 20, "Made by Mr.Peach");
		setfillcolor(WHITE);
		solidrectangle(WIDTH / 1000 * 425, HEIGHT / 2 + HEIGHT / 20, WIDTH / 1000 * 575, HEIGHT / 2 + (HEIGHT / 20)*2);
		settextstyle(HEIGHT / 20, WIDTH / 40, "Consolas");
		outtextxy(WIDTH / 1000 * 440, HEIGHT / 2, "START");
		settextcolor(BLACK);
		outtextxy(WIDTH / 1000 * 450, HEIGHT / 2 + HEIGHT / 20, "HELP");
		settextcolor(WHITE);
		outtextxy(WIDTH / 1000 * 450, HEIGHT / 2 + HEIGHT / 20 + HEIGHT / 20, "QUIT");
		line(WIDTH / 1000 * 425, HEIGHT / 2, WIDTH / 1000 * 425, HEIGHT / 2 + (HEIGHT / 20) * 3);//左线
		line(WIDTH / 1000 * 425, HEIGHT / 2, WIDTH / 1000 * 575, HEIGHT / 2);//上线
		line(WIDTH / 1000 * 575, HEIGHT / 2, WIDTH / 1000 * 575, HEIGHT / 2 + (HEIGHT / 20) * 3);//右线
		line(WIDTH / 1000 * 425, HEIGHT / 2 + (HEIGHT / 20) * 3, WIDTH / 1000 * 575, HEIGHT / 2 + (HEIGHT / 20) * 3);//下线
		line(WIDTH / 1000 * 425, HEIGHT / 2 + HEIGHT / 20, WIDTH / 1000 * 575, HEIGHT / 2 + HEIGHT / 20);//中1线
		line(WIDTH / 1000 * 425, HEIGHT / 2 + HEIGHT / 20 + HEIGHT / 20, WIDTH / 1000 * 575, HEIGHT / 2 + HEIGHT / 20 + HEIGHT / 20);//中2线
	}
	if (i == 3) {
		FlushBatchDraw();
		cleardevice();
		settextstyle(HEIGHT / 1000 * 60, WIDTH / 1000 * 30, "Consolas");
		outtextxy(WIDTH / 1000 * 220, HEIGHT / 1000 * 400, "GASTER'S EXPERIMENT");
		settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Consolas");
		outtextxy(WIDTH / 1000 * 840, HEIGHT - HEIGHT / 1000 * 20, "Made by Mr.Peach");
		setfillcolor(WHITE);
		solidrectangle(WIDTH / 1000 * 425, HEIGHT / 2 + (HEIGHT / 20)*2, WIDTH / 1000 * 575, HEIGHT / 2 + (HEIGHT / 20 )*3);
		settextstyle(HEIGHT / 20, WIDTH / 40, "Consolas");
		outtextxy(WIDTH / 1000 * 440, HEIGHT / 2, "START");
		outtextxy(WIDTH / 1000 * 450, HEIGHT / 2 + HEIGHT / 20, "HELP");
		settextcolor(BLACK);
		outtextxy(WIDTH / 1000 * 450, HEIGHT / 2 + HEIGHT / 20 + HEIGHT / 20, "QUIT");
		settextcolor(WHITE);
		line(WIDTH / 1000 * 425, HEIGHT / 2, WIDTH / 1000 * 425, HEIGHT / 2 + (HEIGHT / 20) * 3);//左线
		line(WIDTH / 1000 * 425, HEIGHT / 2, WIDTH / 1000 * 575, HEIGHT / 2);//上线
		line(WIDTH / 1000 * 575, HEIGHT / 2, WIDTH / 1000 * 575, HEIGHT / 2 + (HEIGHT / 20) * 3);//右线
		line(WIDTH / 1000 * 425, HEIGHT / 2 + (HEIGHT / 20) * 3, WIDTH / 1000 * 575, HEIGHT / 2 + (HEIGHT / 20) * 3);//下线
		line(WIDTH / 1000 * 425, HEIGHT / 2 + HEIGHT / 20, WIDTH / 1000 * 575, HEIGHT / 2 + HEIGHT / 20);//中1线
		line(WIDTH / 1000 * 425, HEIGHT / 2 + HEIGHT / 20 + HEIGHT / 20, WIDTH / 1000 * 575, HEIGHT / 2 + HEIGHT / 20 + HEIGHT / 20);//中2线
	}
}

int mouse() {
	MOUSEMSG msg;
	//while (1) {
		msg = GetMouseMsg();
		if (msg.x >= WIDTH / 1000 * 425 && msg.x <= WIDTH / 1000 * 575 && msg.y <= HEIGHT / 2 + HEIGHT / 20 && msg.y >= HEIGHT / 2) {
			menudraw(1);
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
				return 1;
			}
		}
		if (msg.x >= WIDTH / 1000 * 425 && msg.x <= WIDTH / 1000 * 575 && msg.y <= HEIGHT / 2 + HEIGHT / 20 + HEIGHT / 20 && msg.y >= HEIGHT / 2 + HEIGHT / 20) {
			menudraw(2);
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
				return 2;
			}
		}
		if (msg.x >= WIDTH / 1000 * 425 && msg.x <= WIDTH / 1000 * 575 && msg.y <= HEIGHT / 2 + (HEIGHT / 20) * 3 && msg.y >= HEIGHT / 2 + HEIGHT / 20 + HEIGHT / 20) {
			menudraw(3);
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
				return 3;
			}
		}
		else {
			menudraw(0);
		}
	//}
}

bool timer(int timing, int code, int ms) {//点开始后过了多少毫秒，计时器编号，时间间隔
	static int t1[100];
	int t2 = timing;
	if (t2 - t1[code] >= ms) {
		t1[code] = t2;
		return true;
	}
	return false;
}

typedef struct BULLET {
	double x;
	double y;
	double v;//速度
	double k;//方向
	int code;//子弹编号
	int color;//子弹颜色
	struct BULLET* next;
}bullet;

bullet* blt(int timing,double x, double y, double v, int a, int type) {//静态变量c用来记子弹编号，子弹横坐标，子弹纵坐标，子弹速度，子弹数量，子弹类型
	int i;
	bullet* p;
	bullet* head = NULL;
	bullet* last = NULL;
	static double increase;
	for (i = 1;i <= a; i++) {
		p = (bullet*)malloc(sizeof(bullet));
		p->x = x;
		p->y = y;
		p->v = v;
		p->color = 0;
		if (timing >= 35000 && timing <= 51500)p->color = 1;
		if (type == 1) {
			p->k = 0.174 * i;
		}
		if (type == 2) {
			p->k = 0.174 * i + increase;
			increase = increase + 0.001;
		}
		if (type == 3) {
			p->k = 0.348 * i + increase;
			increase = increase + 0.001;
		}
		if (type == 4) {
			p->k = 0.348 * i - increase;
			increase = increase + 0.001;
		}
		if (type == 5) {
			p->k = 0.174 * i + increase;
			increase = increase + 0.002;
		}
		if (type == 6) {
			p->k = 0.348 * i + increase;
			increase = increase + 0.002;
		}
		p->code = CODE;
		CODE++;
		p->next = NULL;
		if (head == NULL) {
			head = p;
		}
		else {
			last->next = p;
		}
		last = p;
	}
	return head;
}

bullet* delnode(bullet* H, int code) {
	bullet* paohui;
	bullet* h;
	bullet* m = H;
	if (code == H->code) {
		paohui = H;
		H = H->next;
		free(paohui);
	}
	else {
		for (h = H;h != NULL;) {
			if (h->code == code) {
				while (m->next != h) {
					m = m->next;
				}
				m->next = h->next;
				free(h);
				break;
			}
			else {
				h = h->next;
			}
		}
	}
	return H;
}

void bulletmovement(bullet* h, int move) {	//子弹链表，子弹移动样式
	switch (move) {
	case 1:
		h->x += sin(h->k) * h->v;
		h->y += cos(h->k) * h->v;
		setfillcolor(WHITE);
		if (h->color == 1) {
			setfillcolor(RGB(166,0,0));
		}
		solidcircle(h->x, h->y, WIDTH / 1000 * 5);
		break;
	case 2:
		h->x += sin(h->k) * h->v;
		h->y += cos(h->k) * h->v;
		setfillcolor(RGB(166, 0, 0));
		solidcircle(h->x, h->y, WIDTH / 1000 * 5);
		break;
		break;
	}
}

void putblaster(double x, double y, int c, int a, int b) {//龙骨炮横坐标，龙骨炮纵坐标，大小（1小，2大），开关（1关，2开），方向（1左，2上，3右，4下）
	if (c == 1) {
		if (a == 1) {
			if (b == 1) {
				putimage(x, y, &GASTER_BLASTER_CLOSE_LEFT[1], SRCAND);
				putimage(x, y, &GASTER_BLASTER_CLOSE_LEFT[0], SRCPAINT);
			}
			if (b == 2) {
				putimage(x, y, &GASTER_BLASTER_CLOSE_UP[1], SRCAND);
				putimage(x, y, &GASTER_BLASTER_CLOSE_UP[0], SRCPAINT);
			}
			if (b == 3) {
				putimage(x, y, &GASTER_BLASTER_CLOSE_RIGHT[1], SRCAND);
				putimage(x, y, &GASTER_BLASTER_CLOSE_RIGHT[0], SRCPAINT);
			}
			if (b == 4) {
				putimage(x, y, &GASTER_BLASTER_CLOSE_DOWN[1], SRCAND);
				putimage(x, y, &GASTER_BLASTER_CLOSE_DOWN[0], SRCPAINT);
			}
		}
		if (a == 2) {
			if (b == 1) {
				putimage(x, y, &GASTER_BLASTER_OPEN_LEFT[1], SRCAND);
				putimage(x, y, &GASTER_BLASTER_OPEN_LEFT[0], SRCPAINT);
			}
			if (b == 2) {
				putimage(x, y, &GASTER_BLASTER_OPEN_UP[1], SRCAND);
				putimage(x, y, &GASTER_BLASTER_OPEN_UP[0], SRCPAINT);
			}
			if (b == 3) {
				putimage(x, y, &GASTER_BLASTER_OPEN_RIGHT[1], SRCAND);
				putimage(x, y, &GASTER_BLASTER_OPEN_RIGHT[0], SRCPAINT);
			}
			if (b == 4) {
				putimage(x, y, &GASTER_BLASTER_OPEN_DOWN[1], SRCAND);
				putimage(x, y, &GASTER_BLASTER_OPEN_DOWN[0], SRCPAINT);
			}
		}
	}
	if (c == 2) {
		if (a == 1) {
			if (b == 1) {
				putimage(x, y, &L_GASTER_BLASTER_CLOSE_LEFT[1], SRCAND);
				putimage(x, y, &L_GASTER_BLASTER_CLOSE_LEFT[0], SRCPAINT);
			}
			if (b == 2) {
				putimage(x, y, &L_GASTER_BLASTER_CLOSE_UP[1], SRCAND);
				putimage(x, y, &L_GASTER_BLASTER_CLOSE_UP[0], SRCPAINT);
			}
			if (b == 3) {
				putimage(x, y, &L_GASTER_BLASTER_CLOSE_RIGHT[1], SRCAND);
				putimage(x, y, &L_GASTER_BLASTER_CLOSE_RIGHT[0], SRCPAINT);
			}
			if (b == 4) {
				putimage(x, y, &L_GASTER_BLASTER_CLOSE_DOWN[1], SRCAND);
				putimage(x, y, &L_GASTER_BLASTER_CLOSE_DOWN[0], SRCPAINT);
			}
		}
		if (a == 2) {
			if (b == 1) {
				putimage(x, y, &L_GASTER_BLASTER_OPEN_LEFT[1], SRCAND);
				putimage(x, y, &L_GASTER_BLASTER_OPEN_LEFT[0], SRCPAINT);
			}
			if (b == 2) {
				putimage(x, y, &L_GASTER_BLASTER_OPEN_UP[1], SRCAND);
				putimage(x, y, &L_GASTER_BLASTER_OPEN_UP[0], SRCPAINT);
			}
			if (b == 3) {
				putimage(x, y, &L_GASTER_BLASTER_OPEN_RIGHT[1], SRCAND);
				putimage(x, y, &L_GASTER_BLASTER_OPEN_RIGHT[0], SRCPAINT);
			}
			if (b == 4) {
				putimage(x, y, &L_GASTER_BLASTER_OPEN_DOWN[1], SRCAND);
				putimage(x, y, &L_GASTER_BLASTER_OPEN_DOWN[0], SRCPAINT);
			}
		}
	}
}

int main() {
	srand((unsigned)time(NULL));
	HWND console_hwnd = GetConsoleWindow();
	FILE* data;
	int starttime = 0, timing, i, first = 0, j = 1, l, m = 0, n, a = 1,ni=0,jiange=1000,health,g=1;
	char subject_code[10], name[16], namei;
	static int k;
	bool skip = false,play=false,cursor=true;
	bullet* H = NULL;
	bullet* h = NULL;
	bullet* s = NULL;
	initgraph(WIDTH, HEIGHT);
	setbkmode(0);
	settextstyle(HEIGHT / 20, WIDTH / 40, "Consolas");
	outtextxy(WIDTH / 1000 * 415, HEIGHT / 2, "LOADING");
	mciSendString("open \"./music/gaster_theme_remix.mp3\" alias fight", NULL, 0, NULL);
	mciSendString("open \"./music/gaster_theme.mp3\" alias menu", NULL, 0, NULL);
	mciSendString("open \"./music/gaster_theme_remix_cut.mp3\" alias fight_cut", NULL, 0, NULL);
	mciSendString("open \"./music/Determination.mp3\" alias fail", NULL, 0, NULL);
	mciSendString("open \"./music/blaster_prepare.mp3\" alias prepare", NULL, 0, NULL);
	mciSendString("open \"./music/blaster_shoot.mp3\" alias shoot", NULL, 0, NULL);
	mciSendString("open \"./music/gaster_talk.mp3\" alias talk", NULL, 0, NULL);
	mciSendString("open \"./music/Fallen_Down.mp3\" alias end", NULL, 0, NULL);
	mciSendString("open \"./music/flowery_laugh.mp3\" alias laugh", NULL, 0, NULL);
	mciSendString("open \"./music/fight_begin.mp3\" alias begin", NULL, 0, NULL);
	mciSendString("open \"./music/dark.mp3\" alias dark", NULL, 0, NULL);
	/*mciSendString("play prepare", NULL, 0, NULL);
	mciSendString("pause prepare", NULL, 0, NULL);
	mciSendString("play shoot", NULL, 0, NULL);
	mciSendString("pause shoot", NULL, 0, NULL);*/
	mciSendString("play fight_cut", NULL, 0, NULL);
	mciSendString("pause fight_cut", NULL, 0, NULL);
	mciSendString("play menu repeat", NULL, 0, NULL);
	//cleardevice();
	menudraw(0);
	BeginBatchDraw();
	while(1){
		switch (mouse()) {
		default:
			break;
			putimage(gaster.head_x, gaster.head_y, &GASTER_HEAD[1], SRCAND);
			putimage(gaster.head_x, gaster.head_y, &GASTER_HEAD[0], SRCPAINT);
			putimage(gaster.body_x, gaster.body_y, &GASTER_BODY[1], SRCAND);
			putimage(gaster.body_x, gaster.body_y, &GASTER_BODY[0], SRCPAINT);
			break;
		case 1:
			EndBatchDraw();
			cleardevice();
			settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Consolas");
			outtextxy(WIDTH / 1000 * 380, HEIGHT / 1000 * 400, "*Name yourself, Subject ");
			outtextxy(WIDTH / 1000 * 380, HEIGHT / 1000 * 450, "*给我你的名字，  号实验体 ");
			sprintf_s(subject_code, "%d", 1 + rand() % (1000 - 1 + 1));
			outtextxy(WIDTH / 1000 * 620, HEIGHT / 1000 * 400, subject_code);
			outtextxy(WIDTH / 1000 * 520, HEIGHT / 1000 * 450, subject_code);
			settextcolor(YELLOW);
			outtextxy(WIDTH / 1000 * 380, HEIGHT / 1000 * 550, "Press 'enter' to complete");
			settextcolor(WHITE);
			play = true;
			while (1) {
				if (timer(clock(), 90, 500) ){
					cursor=!cursor;
				}
				if (cursor) {
					line(WIDTH / 1000 * 380 + ni * (WIDTH / 1000 * 10), HEIGHT / 1000 * 500, WIDTH / 1000 * 380 + ni * (WIDTH / 1000 * 10), HEIGHT / 1000 * 520);
				}
				if (!cursor) {
					clearrectangle(WIDTH / 1000 * 380 + ni * (WIDTH / 1000 * 10), HEIGHT / 1000 * 500, WIDTH / 1000 * 380 + ni * (WIDTH / 1000 * 10), HEIGHT / 1000 * 520);
				}
				namei = NULL;
				for (int i = 0; i < 256; i++) // 检查所有虚拟键码
				{
					if ( GetAsyncKeyState(i) & 0x8000) // 检查虚拟键码是否处于按下状态
					{
						bool caps_lock = (GetKeyState(VK_CAPITAL) & 0x0001) != 0;
						if (i >= 65 && i <= 90) {
							if (caps_lock) {
								namei = MapVirtualKey(i, MAPVK_VK_TO_CHAR); // 将虚拟键码转换为字符
								break;
							}
							else if (!caps_lock) {
								namei = MapVirtualKey(i, MAPVK_VK_TO_CHAR); // 将虚拟键码转换为字符
								namei += 32;
								break;
							}
						}
						else {
							namei = MapVirtualKey(i, MAPVK_VK_TO_CHAR); // 将虚拟键码转换为字符
							break;
						}
					}
				}
				if (((namei >= 'a' && namei <= 'z'&&ni<15) || (namei >= 'A' && namei <= 'Z'&&ni<15) || (namei >= '0' && namei <= '9' && ni < 15))) {
					name[ni] = namei;
					ni++;
					name[ni] = '\0';
					cleardevice();
					settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Consolas");
					outtextxy(WIDTH / 1000 * 380, HEIGHT / 1000 * 400, "*Name yourself, Subject ");
					outtextxy(WIDTH / 1000 * 380, HEIGHT / 1000 * 450, "*给我你的名字，  号实验体 ");
					outtextxy(WIDTH / 1000 * 620, HEIGHT / 1000 * 400, subject_code);
					outtextxy(WIDTH / 1000 * 520, HEIGHT / 1000 * 450, subject_code);
					settextcolor(YELLOW);
					outtextxy(WIDTH / 1000 * 380, HEIGHT / 1000 * 550, "Press 'enter' to complete");
					settextcolor(WHITE);
					settextcolor(YELLOW);
					settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Consolas");
					outtextxy(WIDTH / 1000 * 380 , HEIGHT / 1000 * 500, name);
					//outtextxy(WIDTH / 1000 * 380 + ni * (WIDTH / 1000 * 10), HEIGHT / 1000 * 500, &namei);
					settextcolor(WHITE);
					Sleep(200);
				}
				else if (namei == '\b' && ni > 0) {
					name[ni] = '\0';
					setfillcolor(BLACK);
					ni--;
					solidrectangle(WIDTH / 1000 * 380 + ni * (WIDTH / 1000 * 10), HEIGHT / 1000 * 500, WIDTH, HEIGHT / 1000 * 500 + HEIGHT / 1000 * 20);
					setfillcolor(WHITE);
					Sleep(200);
				}
				else if (ni!=0&&GetAsyncKeyState(VK_RETURN)) {
					name[ni] = '\0';
					settextstyle(HEIGHT / 20, WIDTH / 40, "Consolas");
					outtextxy(WIDTH / 1000 * 415, HEIGHT / 2, "LOADING");
					mciSendString("stop menu", NULL, 0, NULL);
					mciSendString("close menu", NULL, 0, NULL);
					mciSendString("play fight", NULL, 0, NULL);
					starttime = clock();
					cleardevice();
					break;
				}
			}
			break;
		case 2:
			EndBatchDraw();
			cleardevice();
			settextstyle(HEIGHT / 1000 * 30, WIDTH / 1000 * 15, "Consolas");
			outtextxy(WIDTH / 1000 * 100, HEIGHT / 1000 * 100, "欢迎来到帮助界面，在这里你可以学会怎样游玩此游戏");
			settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Consolas");
			outtextxy(WIDTH / 1000 * 100, HEIGHT / 1000 * 300, "此游戏是undertale的同人游戏");
			outtextxy(WIDTH / 1000 * 100, HEIGHT / 1000 * 350, "在游戏中，你需要按下键盘上的 'WASD' 或 '↑↓←→' 来控制红心移动");
			outtextxy(WIDTH / 1000 * 100, HEIGHT / 1000 * 400, "你会遭遇两种弹幕，一种是子弹类弹幕，一种是激光类弹幕");
			outtextxy(WIDTH / 1000 * 100, HEIGHT / 1000 * 450, "被子弹击中会使你的生命值减一，被激光击中则会使你在短时间内损失大量生命值");
			outtextxy(WIDTH / 1000 * 100, HEIGHT / 1000 * 500, "不过激光在发射之前会有一条红色的预警线提示它的中心位置，利用好这段时间躲开它！");
			outtextxy(WIDTH / 1000 * 100, HEIGHT / 1000 * 550, "除了上述的基本操作，在游戏开始后大约持续17秒的预热阶段，你还可以通过按下空格键来跳过对话");
			outtextxy(WIDTH / 1000 * 100, HEIGHT / 1000 * 600, "这对于想要通过练习不断提高自己成绩的玩家来说很有必要");
			outtextxy(WIDTH / 1000 * 100, HEIGHT / 1000 * 650, "以上就是此游戏的全部教程了，愿你能撑过这次实验");
			outtextxy(WIDTH / 1000 * 800, HEIGHT / 1000 * 980, "特别鸣谢:Jerry StaRk");
			settextcolor(YELLOW);
			outtextxy(WIDTH / 1000 * 380, HEIGHT / 1000 * 900, "按'退格键'来返回主菜单");
			settextcolor(WHITE);
			while (1) {
				if (GetAsyncKeyState(VK_BACK) & 0x8000) {
					break;
				}
			}
			BeginBatchDraw();
			break;
		case 3:
			closegraph();
			return 0;
		}
		if (play)break;
	}
	gameinit();
	int compare_hp = player.health;
	BeginBatchDraw();
	while (1) {
		if (skip == false) {
			timing = clock() - starttime;
		}
		else if (skip == true) {
			static int current = timing;
			int buchang = 16000 - current;
			//int buchang = 70000 - current;
			timing = clock() - starttime + buchang;
		}
		//printf("%d\n", timing);
		/*char buff[100];
		mciSendString("status fight_cut mode", buff, 100, NULL);
		printf("%s\n", buff);*/
		playermovement(4/E);//输入玩家速度
		if (timer(timing, 0, 1000)) {
			switch (j++) {
			case 1:
				gaster.head_y -= HEIGHT / 1000 * 10;
				break;
			case 2:
				gaster.head_y -= HEIGHT / 1000 * 10;
				break;
			case 3:
				gaster.head_y += HEIGHT / 1000 * 10;
				break;
			case 4:
				gaster.head_y += HEIGHT / 1000 * 10;
				j = 1;
				break;
			}
		}
		//弹幕前对话
		if (timing <= 17000) {
			settextcolor(YELLOW);
			settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Consolas");
			outtextxy(WIDTH / 1000 * 280, HEIGHT / 1000 * 350, "Press 'WASD' or '↑↓←→' to move");
			outtextxy(WIDTH / 1000 * 280, HEIGHT / 1000 * 375, "使用 'WASD' 或 '↑↓←→' 来移动");
			//outtextxy(WIDTH / 1000 * 300, HEIGHT / 1000 * 350, "Press 'WASD' or '↑↓←→' to move");
			settextcolor(WHITE);
			if (GetAsyncKeyState(VK_SPACE)) {//跳过对话	
				skip = true;
				mciSendString("stop fight", NULL, 0, NULL);
				mciSendString("close fight", NULL, 0, NULL);
				mciSendString("resume fight_cut", NULL, 0, NULL);
			}
			else {
				settextcolor(YELLOW);
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Consolas");
				outtextxy(WIDTH / 1000 * 280, HEIGHT / 1000 * 400, "Press 'space' to skip the dialogue");
				outtextxy(WIDTH / 1000 * 280, HEIGHT / 1000 * 425, "按 '空格键' 来跳过对话");
				//outtextxy(WIDTH / 1000 * 300, HEIGHT / 1000 * 400, "Press 'space' to skip the dialogue");
				settextcolor(WHITE);
			}
			if (timing <= 200)
				mciSendString("play talk", NULL, 0, NULL);
				mciSendString("play begin", NULL, 0, NULL);
			if (timing <= 2250) {
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Consolas");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 100, "*Dark,dark,yet darker");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 125, "*黑暗，黑暗，更加黑暗");
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Wingdings");
				outtextxy(WIDTH / 1000 * 650, HEIGHT / 1000 * 100, "Dark,dark,yet darker");
			}
			if (timing >= 2250 && timing <= 4500) {
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Consolas");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 100, "*The darkness keeps growing");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 125, "*黑暗持续增长");
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Wingdings");
				outtextxy(WIDTH / 1000 * 650, HEIGHT / 1000 * 100, "The darkness keeps growing");
			}
			if (timing >= 4500 && timing <= 6750) {
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Consolas");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 100, "*The shadows cutting deeper");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 125, "*阴影印得更深");
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Wingdings");
				outtextxy(WIDTH / 1000 * 650, HEIGHT / 1000 * 100, "The shadows cutting deeper");
			}
			if (timing >= 6750 && timing <= 9000) {
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Consolas");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 100, "*Photons readings negative");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 125, "*光子读数为负");
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Wingdings");
				outtextxy(WIDTH / 1000 * 650, HEIGHT / 1000 * 100, "Photons readings negative");
			}
			if (timing >= 9000 && timing <= 11250) {
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Consolas");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 100, "*This next experience");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 125, "*这个实验");
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Wingdings");
				outtextxy(WIDTH / 1000 * 650, HEIGHT / 1000 * 100, "This next experience");
			}
			if (timing >= 11250 && timing <= 12875) {
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Consolas");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 100, "*Seems very");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 125, "*看起来非常..");
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Wingdings");
				outtextxy(WIDTH / 1000 * 650, HEIGHT / 1000 * 100, "Seems very");
			}
			if (timing >= 12875 && timing <= 14500) {
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Consolas");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 100, "*very interseting");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 125, "*..非常有趣");
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Wingdings");
				outtextxy(WIDTH / 1000 * 650, HEIGHT / 1000 * 100, "very interesting");
			}
			if (timing >= 14500 && timing <= 17000) {
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Consolas");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 100, "*What do you two think");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 125, "*你们两个觉得呢？");
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Wingdings");
				outtextxy(WIDTH / 1000 * 650, HEIGHT / 1000 * 100, "What do you two think");
			}
		}
		if (timing >= 17000) {
			mciSendString("stop talk", NULL, 0, NULL);
			mciSendString("close talk", NULL, 0, NULL);
		}
		//攻击开始
		if (timer(timing, 1, 500) && timing >= 18000 && timing <= 22000) {
			if (first == 0) {//如果是第一次攻击，建立链表
				H = blt(timing, WIDTH / 1000 * 500, HEIGHT / 1000 * 375, 5/E, 36, 1);//子弹横坐标，子弹纵坐标，子弹速度，子弹数量，子弹类型
				h = H;
			}
			else {
				h = H;
				while (h->next != NULL) {
					h = h->next;
				}
				h->next = blt(timing, WIDTH / 1000 * 500, HEIGHT / 1000 * 375, 5/E, 36, 1);//子弹横坐标，子弹纵坐标，子弹速度，子弹数量，子弹类型
			}
		}
		if (timer(timing, 2, 500) && timing >= 22000 && timing <= 26000) {
			h = H;
			while (h->next != NULL) {
				h = h->next;
			}
			h->next = blt(timing, WIDTH / 1000 * 250, HEIGHT / 1000 * 375, 5/E, 36, 1);//子弹横坐标，子弹纵坐标，子弹速度，子弹数量，子弹类型
		}
		if (timer(timing, 3, 500) && timing >= 22000 && timing <= 26000) {
			h = H;
			while (h->next != NULL) {
				h = h->next;
			}
			h->next = blt(timing, WIDTH / 1000 * 750, HEIGHT / 1000 * 375, 5/E, 36, 1);//子弹横坐标，子弹纵坐标，子弹速度，子弹数量，子弹类型
		}
		if (timer(timing, 4, 500) && timing >= 26000 && timing <= 31000) {
			h = H;
			while (h->next != NULL) {
				h = h->next;
			}
			h->next = blt(timing, WIDTH / 1000 * 500, HEIGHT / 1000 * 375, 5/E, 36, 2);//子弹横坐标，子弹纵坐标，子弹速度，子弹数量，子弹类型
		}
		if (timer(timing, 6, 500) && timing >= 31000 && timing <= 35000) {
			h = H;
			while (h->next != NULL) {
				h = h->next;
			}
			h->next = blt(timing, WIDTH / 1000 * 250, HEIGHT / 1000 * 500, 5/E, 36, 1);//子弹横坐标，子弹纵坐标，子弹速度，子弹数量，子弹类型
		}
		if (timer(timing, 7, 500) && timing >= 31000 && timing <= 35000) {
			h = H;
			while (h->next != NULL) {
				h = h->next;
			}
			h->next = blt(timing, WIDTH / 1000 * 750, HEIGHT / 1000 * 500, 5/E, 36, 1);//子弹横坐标，子弹纵坐标，子弹速度，子弹数量，子弹类型
		}
		//进入高潮
		if (timer(timing, 8, 300) && timing >= 35000 && timing <= 39300) {
			h = H;
			while (h->next != NULL) {
				h = h->next;
			}
			h->next = blt(timing, WIDTH / 1000 * 500, HEIGHT / 1000 * 375, 8/E, 36, 2);//子弹横坐标，子弹纵坐标，子弹速度，子弹数量，子弹类型
		}
		if (timer(timing, 9, 300) && timing >= 39300 && timing <= 43600) {
			h = H;
			while (h->next != NULL) {
				h = h->next;
			}
			h->next = blt(timing, WIDTH / 1000 * 250, HEIGHT / 1000 * 375, 8/E, 36, 1);//子弹横坐标，子弹纵坐标，子弹速度，子弹数量，子弹类型
		}
		if (timer(timing, 10, 300) && timing >= 39300 && timing <= 43600) {
			h = H;
			while (h->next != NULL) {
				h = h->next;
			}
			h->next = blt(timing, WIDTH / 1000 * 750, HEIGHT / 1000 * 375, 8/E, 36, 1);//子弹横坐标，子弹纵坐标，子弹速度，子弹数量，子弹类型
		}
		if (timer(timing, 11, 300) && timing >= 43600 && timing <= 48000) {
			h = H;
			while (h->next != NULL) {
				h = h->next;
			}
			h->next = blt(timing, WIDTH / 4, HEIGHT / 2, 6/E, 18, 3);//子弹横坐标，子弹纵坐标，子弹速度，子弹数量，子弹类型
		}
		if (timer(timing, 12, 300) && timing >= 43600 && timing <= 48000) {
			h = H;
			while (h->next != NULL) {
				h = h->next;
			}
			h->next = blt(timing, WIDTH / 4 * 3, HEIGHT / 2, 6/E, 18, 4);//子弹横坐标，子弹纵坐标，子弹速度，子弹数量，子弹类型
		}
		if (timer(timing, 13, 300) && timing >= 48000 && timing <= 51500) {
			h = H;
			while (h->next != NULL) {
				h = h->next;
			}
			h->next = blt(timing, WIDTH / 1000 * 500, HEIGHT / 1000 * 375, 8/E, 36, 5);//子弹横坐标，子弹纵坐标，子弹速度，子弹数量，子弹类型
		}
		if (timer(timing, 14, 500) && timing >= 51500 && timing <= 70000) {
			h = H;
			while (h->next != NULL) {
				h = h->next;
			}
			h->next = blt(timing, WIDTH / 1000 * 500, HEIGHT / 1000 * 375, 5/E, 18, 6);//子弹横坐标，子弹纵坐标，子弹速度，子弹数量，子弹类型
		}
		//判定
		if (H != NULL)for (h = H;h != NULL; ) {//判定与子弹移动
			first = 1;
			if (h->x<0 || h->x>WIDTH || h->y<0 || h->y>HEIGHT) {//边界判定
				int C = h->code;
				h = h->next;
				H = delnode(H, C);
			}
			if (h != NULL && sqrt(pow(player.x + WIDTH / 150 - h->x, 2) + pow(player.y + HEIGHT / 150 - h->y, 2)) <= WIDTH / 150 + WIDTH / 1000 * 5) {//子弹击中判定
				int C = h->code;
				h = h->next;
				H = delnode(H, C);
				player.health--;
			}
			else if (h != NULL) {
				bulletmovement(h, 1);//子弹移动样式
				h = h->next;
			}
		}
		//龙骨炮1
		if (timing >= 17000 && timing <= 20000) {//龙骨炮攻击(进入高潮）
			if (timing >= 17000 && timing <= 17010) {
				//PlaySound(TEXT("./music/blaster_prepare.wav"), NULL, SND_FILENAME | SND_ASYNC);
				mciSendString("play prepare", NULL, 0, NULL);
			}
			if (timing >= 17000 && timing <= 18000) {
				putblaster(WIDTH / 4 - WIDTH / 8 / 2 * 3, HEIGHT / 8 * 7 - HEIGHT / 8, 1, 1, 3);//龙骨炮横坐标，龙骨炮纵坐标，开关（1关，2开），方向（1左，2上，3右，4下）
				putblaster(WIDTH / 16 * 5, HEIGHT / 2 - HEIGHT / 8 / 2 * 3, 1, 1, 4);
				putblaster(WIDTH / 4 * 3, HEIGHT / 2, 1, 1, 1);
				putblaster(WIDTH / 16 * 11 - WIDTH / 8, HEIGHT / 8 * 7, 1, 1, 2);
				setlinecolor(RED);
				line(WIDTH / 4 - WIDTH / 8 / 4, HEIGHT / 8 * 7 - HEIGHT / 8 / 2, WIDTH, HEIGHT / 8 * 7 - HEIGHT / 8 / 2);
				line(WIDTH / 16 * 5 + WIDTH / 8 / 2, HEIGHT / 2 - HEIGHT / 8 / 4, WIDTH / 16 * 5 + WIDTH / 8 / 2, HEIGHT);
				line(WIDTH / 4 * 3 + WIDTH / 8 / 4, HEIGHT / 2 + HEIGHT / 16, 0, HEIGHT / 2 + HEIGHT / 16);
				line(WIDTH / 16 * 11 - WIDTH / 16, HEIGHT / 8 * 7 + HEIGHT / 8 / 4, WIDTH / 16 * 11 - WIDTH / 16, 0);
			}
			if (timing >= 18000 && timing <= 20000) {
				putblaster(WIDTH / 4 - WIDTH / 8 / 2 * 3, HEIGHT / 8 * 7 - HEIGHT / 8, 1, 2, 3);//龙骨炮横坐标，龙骨炮纵坐标，开关（1关，2开），方向（1左，2上，3右，4下）
				putblaster(WIDTH / 16 * 5, HEIGHT / 2 - HEIGHT / 8 / 2 * 3, 1, 2, 4);
				putblaster(WIDTH / 4 * 3, HEIGHT / 2, 1, 2, 1);
				putblaster(WIDTH / 16 * 11 - WIDTH / 8, HEIGHT / 8 * 7, 1, 2, 2);
				laser[0].left = WIDTH / 4 - WIDTH / 8 / 4;
				laser[0].top = HEIGHT / 8 * 7 - HEIGHT / 8 / 4 * 3;
				laser[0].right = WIDTH;
				laser[0].bottom = HEIGHT / 8 * 7 - HEIGHT / 8 / 4;
				laser[1].left = WIDTH / 16 * 5 + WIDTH / 8 / 4;
				laser[1].top = HEIGHT / 2 - HEIGHT / 8 / 4;
				laser[1].right = WIDTH / 16 * 5 + WIDTH / 8 / 4 * 3;
				laser[1].bottom = HEIGHT;
				laser[2].left = 0;
				laser[2].top = HEIGHT / 2 + HEIGHT / 8 / 4;
				laser[2].right = WIDTH / 4 * 3 + WIDTH / 8 / 4;
				laser[2].bottom = HEIGHT / 2 + HEIGHT / 8 / 4 * 3;
				laser[3].left = WIDTH / 16 * 11 - WIDTH / 8 / 4 * 3;
				laser[3].top = 0;
				laser[3].right = WIDTH / 16 * 11 - WIDTH / 8 / 4;
				laser[3].bottom = HEIGHT / 8 * 7 + HEIGHT / 8 / 4;
				if (timing <= 18010) {
					//PlaySound(TEXT("./music/blaster_shoot.wav"), NULL, SND_FILENAME | SND_ASYNC);
					mciSendString("play shoot", NULL, 0, NULL);
				}
				for (i = 0;i <= 3;i++) {
					setfillcolor(WHITE);
					solidrectangle(laser[i].left, laser[i].top, laser[i].right, laser[i].bottom);
					//激光击中判定
					if (player.x + WIDTH / 100 >= laser[i].left && player.x + WIDTH / 100 <= laser[i].right && player.y + HEIGHT / 100 >= laser[i].top && player.y + HEIGHT / 100 <= laser[i].bottom) {
						int t = timing;
						if (timer(timing, 99, 100)) {
							player.health--;
						}
					}
				}
			}
		}
		//龙骨炮2
		if (timing >= 34000 && timing <= 37000) {
			if (timing <= 34010) {
				//PlaySound(TEXT("./music/blaster_prepare.wav"), NULL, SND_FILENAME | SND_ASYNC);
				mciSendString("seek prepare to 0", NULL, 0, NULL);
				mciSendString("play prepare", NULL, 0, NULL);
			}
			if (timing <= 35000) {
				putblaster(WIDTH / 2 - WIDTH / 8, HEIGHT / 2 - HEIGHT / 4 / 2 * 3, 2, 1, 4);//龙骨炮横坐标，龙骨炮纵坐标，大小（1小，2大），开关（1关，2开），方向（1左，2上，3右，4下）
				putblaster(WIDTH / 4 - WIDTH / 8 / 2 * 3, HEIGHT / 8 * 7 - HEIGHT / 8, 1, 1, 3);
				putblaster(WIDTH / 4 * 3, HEIGHT / 2, 1, 1, 1);
				setlinecolor(RED);
				line(WIDTH / 2, HEIGHT / 2 - HEIGHT / 4 / 4, WIDTH / 2, HEIGHT);
				line(WIDTH / 4 - WIDTH / 8 / 4, HEIGHT / 8 * 7 - HEIGHT / 8 / 2, WIDTH, HEIGHT / 8 * 7 - HEIGHT / 8 / 2);
				line(WIDTH / 4 * 3 + WIDTH / 8 / 4, HEIGHT / 2 + HEIGHT / 16, 0, HEIGHT / 2 + HEIGHT / 16);
			}
			if (timing >= 35000) {
				putblaster(WIDTH / 2 - WIDTH / 8, HEIGHT / 2 - HEIGHT / 4 / 2 * 3, 2, 2, 4);
				putblaster(WIDTH / 4 - WIDTH / 8 / 2 * 3, HEIGHT / 8 * 7 - HEIGHT / 8, 1, 2, 3);
				putblaster(WIDTH / 4 * 3, HEIGHT / 2, 1, 2, 1);
				laser[4].left = WIDTH / 2 - WIDTH / 8 / 4;
				laser[4].top = HEIGHT / 2 - HEIGHT / 4 / 4;
				laser[4].right = WIDTH / 2 + WIDTH / 8 / 4;
				laser[4].bottom = HEIGHT;
				laser[5].left = WIDTH / 4 - WIDTH / 8 / 4;
				laser[5].top = HEIGHT / 8 * 7 - HEIGHT / 8 / 4 * 3;
				laser[5].right = WIDTH;
				laser[5].bottom = HEIGHT / 8 * 7 - HEIGHT / 8 / 4;
				laser[6].left = 0;
				laser[6].top = HEIGHT / 2 + HEIGHT / 8 / 4;
				laser[6].right = WIDTH / 4 * 3 + WIDTH / 8 / 4;
				laser[6].bottom = HEIGHT / 2 + HEIGHT / 8 / 4 * 3;
				if (timing <= 35010) {
					//PlaySound(TEXT("./music/blaster_shoot.wav"), NULL, SND_FILENAME | SND_ASYNC);
					mciSendString("seek shoot to 0", NULL, 0, NULL);
					mciSendString("play shoot", NULL, 0, NULL);
				}
				for (i = 4;i <= 6;i++) {
					setfillcolor(WHITE);
					solidrectangle(laser[i].left, laser[i].top, laser[i].right, laser[i].bottom);
					//激光击中判定
					if (player.x + WIDTH / 100 >= laser[i].left && player.x + WIDTH / 100 <= laser[i].right && player.y + HEIGHT / 100 >= laser[i].top && player.y + HEIGHT / 100 <= laser[i].bottom) {
						int t = timing;
						if (timer(timing, 98, 100)) {
							player.health--;
						}
					}
				}
			}
		}
		//龙骨炮3
		if (timing >= 51500 && timing <= 54500) {
			if (timing <= 51510) {
				//PlaySound(TEXT("./music/blaster_prepare.wav"), NULL, SND_FILENAME | SND_ASYNC);
				mciSendString("seek prepare to 0", NULL, 0, NULL);
				mciSendString("play prepare", NULL, 0, NULL);
			}
			if (timing <= 52500) {
				putblaster(WIDTH / 2 - WIDTH / 8, HEIGHT / 2 - HEIGHT / 4 / 2 * 3, 2, 1, 4);//龙骨炮横坐标，龙骨炮纵坐标，大小（1小，2大），开关（1关，2开），方向（1左，2上，3右，4下）
				setlinecolor(RED);
				line(WIDTH / 2, HEIGHT / 2 - HEIGHT / 4 / 4, WIDTH / 2, HEIGHT);
			}
			if (timing >= 52500) {
				putblaster(WIDTH / 2 - WIDTH / 8, HEIGHT / 2 - HEIGHT / 4 / 2 * 3, 2, 2, 4);
				laser[7].left = WIDTH / 2 - WIDTH / 8 / 4;
				laser[7].top = HEIGHT / 2 - HEIGHT / 4 / 4;
				laser[7].right = WIDTH / 2 + WIDTH / 8 / 4;
				laser[7].bottom = HEIGHT;
				if (timing <= 52510) {
					//PlaySound(TEXT("./music/blaster_shoot.wav"), NULL, SND_FILENAME | SND_ASYNC);
					mciSendString("seek shoot to 0", NULL, 0, NULL);
					mciSendString("play shoot", NULL, 0, NULL);
				}
				for (i = 7;i <= 7;i++) {
					setfillcolor(WHITE);
					solidrectangle(laser[i].left, laser[i].top, laser[i].right, laser[i].bottom);
					//激光击中判定
					if (player.x + WIDTH / 100 >= laser[i].left && player.x + WIDTH / 100 <= laser[i].right && player.y + HEIGHT / 100 >= laser[i].top && player.y + HEIGHT / 100 <= laser[i].bottom) {
						int t = timing;
						if (timer(timing, 97, 100)) {
							player.health--;
						}
					}
				}
			}
		}
		//尾杀
		if (timing >= 52500) {
			if (timer(timing,96,100)){
				jiange -= 3;
			}
			if (timer(timing, 95, jiange) && timing <= 70000) {
				//a = 1+rand()%(4-1+1);//1到4的随机数
				switch (a) {
				case 1:
					blaster[k].life = true;
					blaster[k].x = WIDTH / 4 - WIDTH / 8 / 2 * 3;
					blaster[k].y = HEIGHT / 2 - HEIGHT / 8 / 4 + rand() % (HEIGHT / 8 * 7 - HEIGHT / 8 + HEIGHT / 8 / 4 - (HEIGHT / 2 - HEIGHT / 8 / 4) + 1);
					blaster[k].position = 1;
					blaster[k].borntime = timing;
					l = k;
					k++;
					a++;
					break;
				case 2:
					blaster[k].life = true;
					blaster[k].x = WIDTH / 4 - WIDTH / 8 / 4 + rand() % (WIDTH / 4 * 3 - WIDTH / 8 + WIDTH / 8 / 4 - (WIDTH / 4 - WIDTH / 8 / 4) + 1);
					blaster[k].y = HEIGHT / 2 - HEIGHT / 8 / 2 * 3;
					blaster[k].position = 2;
					blaster[k].borntime = timing;
					l = k;
					k++;
					a++;
					break;
				case 3:
					blaster[k].life = true;
					blaster[k].x = WIDTH / 4 * 3;
					blaster[k].y = HEIGHT / 2 - HEIGHT / 8 / 4 + rand() % (HEIGHT / 8 * 7 - HEIGHT / 8 + HEIGHT / 8 / 4 - (HEIGHT / 2 - HEIGHT / 8 / 4) + 1);
					blaster[k].position = 3;
					blaster[k].borntime = timing;
					l = k;
					k++;
					a++;
					break;
				case 4:
					blaster[k].life = true;
					blaster[k].x = WIDTH / 4 - WIDTH / 8 / 4 + rand() % (WIDTH / 4 * 3 - WIDTH / 8 + WIDTH / 8 / 4 - (WIDTH / 4 - WIDTH / 8 / 4) + 1);
					blaster[k].y = HEIGHT / 8 * 7;
					blaster[k].position = 4;
					blaster[k].borntime = timing;
					l = k;
					k++;
					a = 1;
					break;
				}
			}
		}
		for (l = 0;l <= k;l++) {
			if (timing >= blaster[l].borntime + 3000) {
				blaster[l].life = false;
			}
			if (blaster[l].life) {
				if (timing <= blaster[l].borntime + 1000) {
					if (timing <= blaster[l].borntime + 10) {
						mciSendString("seek prepare to 0", NULL, 0, NULL);
						mciSendString("play prepare", NULL, 0, NULL);
					}
					switch (blaster[l].position) {
					case 1:
						putblaster(blaster[l].x, blaster[l].y, 1, 1, 3);//龙骨炮横坐标，龙骨炮纵坐标，大小（1小，2大），开关（1关，2开），方向（1左，2上，3右，4下）
						setlinecolor(RED);
						line(blaster[l].x + WIDTH / 8 / 4 * 3, blaster[l].y + HEIGHT / 8 / 2, WIDTH, blaster[l].y + HEIGHT / 8 / 2);
						break;
					case 2:
						putblaster(blaster[l].x, blaster[l].y, 1, 1, 4);//龙骨炮横坐标，龙骨炮纵坐标，大小（1小，2大），开关（1关，2开），方向（1左，2上，3右，4下）
						setlinecolor(RED);
						line(blaster[l].x + WIDTH / 8 / 2, blaster[l].y + HEIGHT / 8 / 4 * 3, blaster[l].x + WIDTH / 8 / 2, HEIGHT);
						break;
					case 3:
						putblaster(blaster[l].x, blaster[l].y, 1, 1, 1);//龙骨炮横坐标，龙骨炮纵坐标，大小（1小，2大），开关（1关，2开），方向（1左，2上，3右，4下）
						setlinecolor(RED);
						line(blaster[l].x + WIDTH / 8 / 4, blaster[l].y + HEIGHT / 8 / 2, 0, blaster[l].y + HEIGHT / 8 / 2);
						break;
					case 4:
						putblaster(blaster[l].x, blaster[l].y, 1, 1, 2);//龙骨炮横坐标，龙骨炮纵坐标，大小（1小，2大），开关（1关，2开），方向（1左，2上，3右，4下）
						setlinecolor(RED);
						line(blaster[l].x + WIDTH / 8 / 2, blaster[l].y + HEIGHT / 8 / 4, blaster[l].x + WIDTH / 8 / 2, 0);
						break;
					}
				}
				if (timing >= blaster[l].borntime + 1000) {
					if (timing <= blaster[l].borntime + 1010) {
						mciSendString("seek shoot to 0", NULL, 0, NULL);
						mciSendString("play shoot", NULL, 0, NULL);
					}
					switch (blaster[l].position) {
					case 1:
						putblaster(blaster[l].x, blaster[l].y, 1, 2, 3);//龙骨炮横坐标，龙骨炮纵坐标，大小（1小，2大），开关（1关，2开），方向（1左，2上，3右，4下）
						setfillcolor(WHITE);
						solidrectangle(WIDTH / 4 - WIDTH / 8 / 4, blaster[l].y + HEIGHT / 8 / 4, WIDTH, blaster[l].y + HEIGHT / 8 / 4 * 3);
						if (player.x + WIDTH / 100 >= WIDTH / 4 - WIDTH / 8 / 4 && player.x + WIDTH / 100 <= WIDTH && player.y + HEIGHT / 100 >= blaster[l].y + HEIGHT / 8 / 4 && player.y + HEIGHT / 100 <= blaster[l].y + HEIGHT / 8 / 4 * 3) {
							if (timer(timing, 94, 100)) {
								player.health--;
							}
						}
						break;
					case 2:
						putblaster(blaster[l].x, blaster[l].y, 1, 2, 4);//龙骨炮横坐标，龙骨炮纵坐标，大小（1小，2大），开关（1关，2开），方向（1左，2上，3右，4下）
						setfillcolor(WHITE);
						solidrectangle(blaster[l].x + WIDTH / 8 / 4, HEIGHT/2-HEIGHT/8/4, blaster[l].x + WIDTH / 8 / 4 * 3, HEIGHT);
						if (player.x + WIDTH / 100 >= blaster[l].x + WIDTH / 8 / 4 && player.x + WIDTH / 100 <= blaster[l].x + WIDTH / 8 / 4 * 3 && player.y + HEIGHT / 100 >= HEIGHT / 2 - HEIGHT / 8 / 4 && player.y + HEIGHT / 100 <= HEIGHT) {
							if (timer(timing, 93, 100)) {
								player.health--;
							}
						}
						break;
					case 3:
						putblaster(blaster[l].x, blaster[l].y, 1, 2, 1);//龙骨炮横坐标，龙骨炮纵坐标，大小（1小，2大），开关（1关，2开），方向（1左，2上，3右，4下）
						setfillcolor(WHITE);
						solidrectangle(0, blaster[l].y + HEIGHT / 8 / 4, blaster[l].x + WIDTH / 8 / 4, blaster[l].y + HEIGHT / 8 / 4 * 3);
						if (player.x + WIDTH / 100 >= 0 && player.x + WIDTH / 100 <= blaster[l].x + WIDTH / 8 / 4 && player.y + HEIGHT / 100 >= blaster[l].y + HEIGHT / 8 / 4 && player.y + HEIGHT / 100 <= blaster[l].y + HEIGHT / 8 / 4 * 3) {
							if (timer(timing, 92, 100)) {
								player.health--;
							}
						}
						break;
					case 4:
						putblaster(blaster[l].x, blaster[l].y, 1, 2, 2);//龙骨炮横坐标，龙骨炮纵坐标，大小（1小，2大），开关（1关，2开），方向（1左，2上，3右，4下）
						setfillcolor(WHITE);
						solidrectangle(blaster[l].x + WIDTH / 8 / 4, 0, blaster[l].x + WIDTH / 8 / 4 * 3, blaster[l].y + HEIGHT / 8 / 4);
						if (player.x + WIDTH / 100 >= blaster[l].x + WIDTH / 8 / 4 && player.x + WIDTH / 100 <= blaster[l].x + WIDTH / 8 / 4 * 3 && player.y + HEIGHT / 100 >= 0 && player.y + HEIGHT / 100 <= blaster[l].y + HEIGHT / 8 / 4) {
							if (timer(timing, 91, 100)) {
								player.health--;
							}
						}
						break;
					}
				}
			}
		}
		//死或生
		if (player.health <= 0&&player.win==false) {//死
			cleardevice();
			putimage(0, HEIGHT / 1000 * 300, &GAME_OVER);
			settextstyle(HEIGHT / 1000 * 40, WIDTH / 1000 * 20, "Consolas");
			settextcolor(YELLOW);
			outtextxy(WIDTH / 1000 * 310, HEIGHT / 1000 * 700, "Press “esc” to quit");
			settextcolor(WHITE);
			FlushBatchDraw();
			mciSendString("stop fight", NULL, 0, NULL);
			mciSendString("stop fight_cut", NULL, 0, NULL);
			mciSendString("close fight", NULL, 0, NULL);
			mciSendString("close fight_cut", NULL, 0, NULL);
			mciSendString("play fail", NULL, 0, NULL);
			while (1) {
				if (GetAsyncKeyState(VK_ESCAPE)) {
					break;
				}
			}
			break;
		}
		if (player.health <= 0 && player.win) {//生
			PlaySound(TEXT("./music/Fallen_Down.wav"), NULL, SND_FILENAME | SND_ASYNC);
			int x, y, z,temp,m;
			char ctemp[16],cur_hp[10],hp[10],init_hp[10];
			DATA a,b[1000],c[1000];
			bool same = false;
			struct stat data_;
			stat("./playerdata.dat", &data_);
			fopen_s(&data, "./playerdata.dat", "rb+");
			for (i = 0;i < data_.st_size / sizeof(DATA);i++) {//遍历，判断是否有重名情况
				fread(&c[i], sizeof(DATA), 1, data);
				if (strcmp(name, c[i].ID) == 0) {//名字相同
					strcpy_s(a.ID, name);
					if (c[i].health < health) a.health = health;//新数据更好，用新数据替换
					else a.health = c[i].health;//新数据更差，用旧数据替换
					fseek(data, (-1) * sizeof(DATA), SEEK_CUR);
					fwrite(&a, sizeof(DATA), 1, data);
					same = true;
					break;
				}
			}
			fclose(data);
			if (same==false) {//如果不同名
				fopen_s(&data, "./playerdata.dat", "ab");
				strcpy_s(a.ID, name);
				a.health = health;
				fwrite(&a, sizeof(DATA), 1, data);
				fclose(data);
			}
			stat("./playerdata.dat", &data_);
			fopen_s(&data, "./playerdata.dat", "rb");
			for (i = 0;i < data_.st_size / sizeof(DATA);i++) {
				fread(&b[i], sizeof(DATA), 1, data);
			}
			fclose(data);
			//排序
			z = data_.st_size / sizeof(DATA);
			for (x = 0;x < data_.st_size / sizeof(DATA);x++) {
				int exchange = 0;
				for (y = 0;y < z - 1;y++) {
					if (b[y].health < b[y + 1].health) {
						temp = b[y].health;
						b[y].health = b[y + 1].health;
						b[y + 1].health = temp;
						strcpy_s(ctemp, b[y].ID);
						strcpy_s(b[y].ID, b[y+1].ID);
						strcpy_s(b[y+1].ID, ctemp);
						exchange = 1;
					}
				}
				z--;
				if (!exchange)break;
			}
			//输出
			cleardevice();
			settextstyle(HEIGHT / 1000 * 40, WIDTH / 1000 * 20, "Consolas");
			outtextxy(WIDTH / 1000 * 430, HEIGHT / 1000 * 100, "YOU WIN");
			settextstyle(HEIGHT / 1000 * 30, WIDTH / 1000 * 15, "Consolas");
			outtextxy(WIDTH / 1000 * 200, HEIGHT / 1000 * 150, "Name:");
			outtextxy(WIDTH / 1000 * 600, HEIGHT / 1000 * 150, "Remaining HP:");
			settextcolor(YELLOW);
			outtextxy(WIDTH / 1000 * 300, HEIGHT / 1000 * 150, name);
			sprintf_s(cur_hp, "%d", health);
			outtextxy(WIDTH / 1000 * 800, HEIGHT / 1000 * 150, cur_hp);
			sprintf_s(init_hp, "%d", init_health);
			outtextxy(WIDTH / 1000 * 840, HEIGHT / 1000 * 150, "/");
			outtextxy(WIDTH / 1000 * 850, HEIGHT / 1000 * 150, init_hp);
			settextcolor(WHITE);
			outtextxy(WIDTH / 1000 * 380, HEIGHT / 1000 * 300, "Top ten players:");
			if (data_.st_size / sizeof(DATA)<=10) {
				m = data_.st_size / sizeof(DATA);
			}
			else {
				m = 10;
			}
			for (i = 0;i < m;i++) {
				sprintf_s(hp, "%d", b[i].health);
				outtextxy(WIDTH / 1000 * 200, HEIGHT / 1000 * 350 + i * (HEIGHT / 1000 * 50), "Name:");
				outtextxy(WIDTH / 1000 * 600, HEIGHT / 1000 * 350 + i * (HEIGHT / 1000 * 50), "Remaining HP:");
				if(strcmp(name, b[i].ID) == 0&&b[i].health==health)settextcolor(YELLOW);
				else if (strcmp(name, b[i].ID) == 0 && b[i].health != health)settextcolor(RED);
				outtextxy(WIDTH / 1000 * 840, HEIGHT / 1000 * 350 + i * (HEIGHT / 1000 * 50), "/");
				outtextxy(WIDTH / 1000 * 850, HEIGHT / 1000 * 350 + i * (HEIGHT / 1000 * 50), init_hp);
				outtextxy(WIDTH / 1000 * 300, HEIGHT / 1000 * 350 + i * (HEIGHT / 1000 * 50), b[i].ID);
				outtextxy(WIDTH / 1000 * 800, HEIGHT / 1000 * 350 + i * (HEIGHT / 1000 * 50), hp);
				settextcolor(WHITE);
			}
			settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 *10, "Consolas");
			settextcolor(YELLOW);
			outtextxy(WIDTH / 1000 * 400, HEIGHT / 1000 * 900, "Press “esc” to quit");
			settextcolor(WHITE);
			FlushBatchDraw();
			while (1) {
				if (GetAsyncKeyState(VK_ESCAPE)) {
					break;
				}
			}
		}
		if (timing >= 70000 && H == NULL && player.health > 0 ) {//生之演出
			static int endtime = timing;
			player.win = true;
			static int HEALTH = player.health;
			health = HEALTH;
			if (timing <= endtime+10) {
				//char buff[16];
				//mciSendString("open \"./music/gaster_talk.mp3\" alias talk", NULL, 0, NULL);
				//mciSendString("seek talk to 0", NULL, 0, NULL);
				//mciSendString("play talk", NULL, 0, NULL);
				//mciSendString("status talk mode", buff, 16, NULL);
				//printf("%s", buff);
				mciSendString("play dark", NULL, 0, NULL);
				PlaySound(TEXT("./music/gaster_talk.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			if (timing <= endtime + 3000) {
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Consolas");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 100, "*Not bad");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 125, "*不错");
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Wingdings");
				outtextxy(WIDTH / 1000 * 650, HEIGHT / 1000 * 100, "Not bad");
			}
			if (timing>= endtime + 3000&&timing <= endtime + 6000) {
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Consolas");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 100, "*You passed the test");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 125, "*你通过了实验");
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Wingdings");
				outtextxy(WIDTH / 1000 * 650, HEIGHT / 1000 * 100, "You passed the test");
			}
			if (timing >= endtime + 6000 && timing <= endtime + 9000) {
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Consolas");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 100, "*The data has been collected");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 125, "*数据已经被收集");
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Wingdings");
				outtextxy(WIDTH / 1000 * 650, HEIGHT / 1000 * 100, "The data has been collected");
			}
			if (timing >= endtime + 9000) {
				setfillcolor(RED);
				solidcircle(gaster.head_x + WIDTH / 1000 * 215, HEIGHT / 1000 * gaster.head_y + 140, WIDTH / 1000 * 3);
				solidcircle(gaster.head_x + WIDTH / 1000 * 262, HEIGHT / 1000 * gaster.head_y + 135, WIDTH / 1000 * 3);
			}
			if (timing >= endtime + 9000 && timing <= endtime + 12000) {
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Consolas");
				settextcolor(RGB(166, 0, 0));
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 100, "*Now die");
				outtextxy(WIDTH / 1000 * 125, HEIGHT / 1000 * 125, "*现在死吧");
				settextstyle(HEIGHT / 1000 * 20, WIDTH / 1000 * 10, "Wingdings");
				outtextxy(WIDTH / 1000 * 650, HEIGHT / 1000 * 100, "Now die");
				settextcolor(WHITE);
			}
			if (timing>=endtime+11000&&timing<=endtime+11010) {
				PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
				//PlaySound(TEXT("./music/flowery_laugh.wav"), NULL, SND_FILENAME | SND_ASYNC);
				mciSendString("stop dark", NULL, 0, NULL);
				mciSendString("play laugh", NULL, 0, NULL);

			}
			if (timer(timing, 90, 100) && timing >= endtime + 12000) {
				switch (a) {
				case 1:
					blaster[k].life = true;
					blaster[k].x = WIDTH / 4 - WIDTH / 8 / 2 * 3;
					blaster[k].y = HEIGHT / 2-HEIGHT/8/4 + rand() % (HEIGHT / 8 * 7 - HEIGHT / 8+HEIGHT/8/4 - (HEIGHT / 2-HEIGHT/8/4) + 1);
					blaster[k].position = 1;
					blaster[k].borntime = timing;
					l = k;
					k++;
					a++;
					break;
				case 2:
					blaster[k].life = true;
					blaster[k].x = WIDTH / 4-WIDTH/8/4 + rand() % (WIDTH / 4 * 3 - WIDTH / 8+WIDTH/8/4 - (WIDTH / 4 - WIDTH / 8 / 4) + 1);
					blaster[k].y = HEIGHT / 2 - HEIGHT / 8 / 2 * 3;
					blaster[k].position = 2;
					blaster[k].borntime = timing;
					l = k;
					k++;
					a++;
					break;
				case 3:
					blaster[k].life = true;
					blaster[k].x = WIDTH / 4 * 3;
					blaster[k].y = HEIGHT / 2 - HEIGHT / 8 / 4 + rand() % (HEIGHT / 8 * 7 - HEIGHT / 8 + HEIGHT / 8 / 4 - (HEIGHT / 2 - HEIGHT / 8 / 4) + 1);
					blaster[k].position = 3;
					blaster[k].borntime = timing;
					l = k;
					k++;
					a++;
					break;
				case 4:
					blaster[k].life = true;
					blaster[k].x = WIDTH / 4 - WIDTH / 8 / 4 + rand() % (WIDTH / 4 * 3 - WIDTH / 8 + WIDTH / 8 / 4 - (WIDTH / 4 - WIDTH / 8 / 4) + 1);
					blaster[k].y = HEIGHT / 8 * 7;
					blaster[k].position = 4;
					blaster[k].borntime = timing;
					l = k;
					k++;
					a = 1;
					break;
				}
			}
			for (l = 0;l <= k;l++) {
				if (timing >= blaster[l].borntime + 3000) {
					blaster[l].life = false;
				}
				if (blaster[l].life) {
					if (timing <= blaster[l].borntime + 1000) {
						if (timing <= blaster[l].borntime + 10) {
							mciSendString("seek prepare to 0", NULL, 0, NULL);
							mciSendString("play prepare", NULL, 0, NULL);
						}
						switch (blaster[l].position) {
						case 1:
							putblaster(blaster[l].x, blaster[l].y, 1, 1, 3);//龙骨炮横坐标，龙骨炮纵坐标，大小（1小，2大），开关（1关，2开），方向（1左，2上，3右，4下）
							setlinecolor(RED);
							line(blaster[l].x + WIDTH / 8 / 4 * 3, blaster[l].y + HEIGHT / 8 / 2, WIDTH, blaster[l].y + HEIGHT / 8 / 2);
							break;
						case 2:
							putblaster(blaster[l].x, blaster[l].y, 1, 1, 4);//龙骨炮横坐标，龙骨炮纵坐标，大小（1小，2大），开关（1关，2开），方向（1左，2上，3右，4下）
							setlinecolor(RED);
							line(blaster[l].x + WIDTH / 8 / 2, blaster[l].y + HEIGHT / 8 / 4 * 3, blaster[l].x + WIDTH / 8 / 2, HEIGHT);
							break;
						case 3:
							putblaster(blaster[l].x, blaster[l].y, 1, 1, 1);//龙骨炮横坐标，龙骨炮纵坐标，大小（1小，2大），开关（1关，2开），方向（1左，2上，3右，4下）
							setlinecolor(RED);
							line(blaster[l].x + WIDTH / 8 / 4, blaster[l].y + HEIGHT / 8 / 2, 0, blaster[l].y + HEIGHT / 8 / 2);
							break;
						case 4:
							putblaster(blaster[l].x, blaster[l].y, 1, 1, 2);//龙骨炮横坐标，龙骨炮纵坐标，大小（1小，2大），开关（1关，2开），方向（1左，2上，3右，4下）
							setlinecolor(RED);
							line(blaster[l].x + WIDTH / 8 / 2, blaster[l].y + HEIGHT / 8 / 4, blaster[l].x + WIDTH / 8 / 2, 0);
							break;
						}
					}
					if (timing >= blaster[l].borntime + 1000) {
						if (timing <= blaster[l].borntime + 1010) {
							mciSendString("seek shoot to 0", NULL, 0, NULL);
							mciSendString("play shoot", NULL, 0, NULL);
						}
						switch (blaster[l].position) {
						case 1:
							putblaster(blaster[l].x, blaster[l].y, 1, 2, 3);//龙骨炮横坐标，龙骨炮纵坐标，大小（1小，2大），开关（1关，2开），方向（1左，2上，3右，4下）
							setfillcolor(WHITE);
							solidrectangle(WIDTH / 4 - WIDTH / 8 / 4, blaster[l].y + HEIGHT / 8 / 4, WIDTH, blaster[l].y + HEIGHT / 8 / 4 * 3);
							if (player.x + WIDTH / 100 >= WIDTH / 4 - WIDTH / 8 / 4 && player.x + WIDTH / 100 <= WIDTH && player.y + HEIGHT / 100 >= blaster[l].y + HEIGHT / 8 / 4 && player.y + HEIGHT / 100 <= blaster[l].y + HEIGHT / 8 / 4 * 3) {
								if (timer(timing, 94, 100)) {
									player.health--;
								}
							}
							break;
						case 2:
							putblaster(blaster[l].x, blaster[l].y, 1, 2, 4);//龙骨炮横坐标，龙骨炮纵坐标，大小（1小，2大），开关（1关，2开），方向（1左，2上，3右，4下）
							setfillcolor(WHITE);
							solidrectangle(blaster[l].x + WIDTH / 8 / 4, HEIGHT / 2 - HEIGHT / 8 / 4, blaster[l].x + WIDTH / 8 / 4 * 3, HEIGHT);
							if (player.x + WIDTH / 100 >= blaster[l].x + WIDTH / 8 / 4 && player.x + WIDTH / 100 <= blaster[l].x + WIDTH / 8 / 4 * 3 && player.y + HEIGHT / 100 >= HEIGHT / 2 - HEIGHT / 8 / 4 && player.y + HEIGHT / 100 <= HEIGHT) {
								if (timer(timing, 93, 100)) {
									player.health--;
								}
							}
							break;
						case 3:
							putblaster(blaster[l].x, blaster[l].y, 1, 2, 1);//龙骨炮横坐标，龙骨炮纵坐标，大小（1小，2大），开关（1关，2开），方向（1左，2上，3右，4下）
							setfillcolor(WHITE);
							solidrectangle(0, blaster[l].y + HEIGHT / 8 / 4, blaster[l].x + WIDTH / 8 / 4, blaster[l].y + HEIGHT / 8 / 4 * 3);
							if (player.x + WIDTH / 100 >= 0 && player.x + WIDTH / 100 <= blaster[l].x + WIDTH / 8 / 4 && player.y + HEIGHT / 100 >= blaster[l].y + HEIGHT / 8 / 4 && player.y + HEIGHT / 100 <= blaster[l].y + HEIGHT / 8 / 4 * 3) {
								if (timer(timing, 92, 100)) {
									player.health--;
								}
							}
							break;
						case 4:
							putblaster(blaster[l].x, blaster[l].y, 1, 2, 2);//龙骨炮横坐标，龙骨炮纵坐标，大小（1小，2大），开关（1关，2开），方向（1左，2上，3右，4下）
							setfillcolor(WHITE);
							solidrectangle(blaster[l].x + WIDTH / 8 / 4, 0, blaster[l].x + WIDTH / 8 / 4 * 3, blaster[l].y + HEIGHT / 8 / 4);
							if (player.x + WIDTH / 100 >= blaster[l].x + WIDTH / 8 / 4 && player.x + WIDTH / 100 <= blaster[l].x + WIDTH / 8 / 4 * 3 && player.y + HEIGHT / 100 >= 0 && player.y + HEIGHT / 100 <= blaster[l].y + HEIGHT / 8 / 4) {
								if (timer(timing, 91, 100)) {
									player.health--;
								}
							}
							break;
						}
					}
				}
			}
			/*cleardevice();
			settextstyle(HEIGHT / 1000 * 40, WIDTH / 1000 * 20, "Consolas");
			outtextxy(WIDTH / 1000 * 430, HEIGHT / 1000 * 500, "YOU WIN");
			settextstyle(HEIGHT / 1000 * 40, WIDTH / 1000 * 20, "Consolas");
			outtextxy(WIDTH / 1000 * 310, HEIGHT / 1000 * 700, "Press “esc” to quit");
			FlushBatchDraw();
			while (1) {
				if (GetAsyncKeyState(VK_ESCAPE)) {
					break;
				}
			}*/
		}
		if (player.health < compare_hp) {
			PlaySound(TEXT("./music/hurt.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		compare_hp = player.health;
		if (GetAsyncKeyState(VK_ESCAPE)) {
			break;
		}
		gamedraw(timing);
		FlushBatchDraw();
		cleardevice();
		Sleep(1);
	}
	EndBatchDraw();
	closegraph();
}