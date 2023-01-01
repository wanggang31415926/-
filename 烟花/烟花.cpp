#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<graphics.h>
#include<Mmsystem.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include <conio.h>
#pragma comment (lib , "Winmm.lib")

#define NUM 10
#define PI 3.14

// �̵�
struct jet {
	int x, y;			//�̻�������
	int hx, hy;			//�̻�����ߵ�����
	bool shoot;			//�̻����Ƿ��ڷ���״̬
	DWORD t1, t2, dt;	//����ʱ��  ����ʱ��  ���ʱ��
	IMAGE img[2];		//2��ͼƬ һ��һ�� 01�±�
	byte n : 1;
}jet[NUM];

// �����̻�   ѧ��c/c++ �߱����¶�����
struct Fire
{
	int x, y;				//�̻�������
	int r;					//�̻��İ뾶
	int max_r;				//�̻������뾶
	int cen_x, cen_y;		//���ľ����Ͻǵľ���
	int width, height;		//����
	int xy[240][240];		//��Ҫ�����أ�����
	bool draw;				//����
	bool show;				//��ʾ
	DWORD t1, t2, dt;		//����ʱ��  ����ʱ��  ���ʱ��
}fire[NUM];


void FireInit(int i)
{
	//��ʼ���̻���
	jet[i].t1 = GetTickCount();	//GetTickCount()���شӲ���ϵͳ��������ǰ�������ĺ�������ʹ��ǰ����windows.h��
	jet[i].shoot = false;		//δ����
	jet[i].dt = 10;				//����ʱ��
	jet[i].n = 0;				//��ʼ���̻�
	fire[i].show = false;		//δ����
	fire[i].r = 0;
	fire[i].dt = 5;				//����ʱ��
	fire[i].t1 = GetTickCount();
	fire[i].max_r = rand() % 50 + 100;	//100-149
	fire[i].cen_x = rand() % 30 + 80;	//���ľ����Ͻǵľ���
	fire[i].cen_y = rand() % 30 + 80;	//
	fire[i].width = 240;				//��
	fire[i].height = 240;				//��
}
void Load()
{
	//�����̻���
	IMAGE jetimg;
	loadimage(&jetimg, "./shoot.jpg", 200, 50);
	SetWorkingImage(&jetimg);
	for (int i = 0; i < NUM; i++)
	{
		int n = rand() % 5;			//01234
		getimage(&jet[i].img[0], n * 20, 0, 20, 50);
		getimage(&jet[i].img[1], (n + 5) * 20, 0, 20, 50);
	}
	SetWorkingImage(NULL);
	//�����̻�
	IMAGE fireimage, Fireimage;
	loadimage(&Fireimage, "./flower.bmp", 3120, 240);
	for (int i = 0; i < NUM; i++)
	{
		SetWorkingImage(&Fireimage);
		getimage(&fireimage, i * 240, 0, 240, 240);
		SetWorkingImage(&fireimage);
		for (int a = 0; a < 240; a++)
		{
			for (int b = 0; b < 240; b++)
			{
				fire[i].xy[a][b] = getpixel(a, b);
			}
		}
	}
	SetWorkingImage(NULL);
}
void ChoiceJet(DWORD& t1)
{
	DWORD t2 = GetTickCount();
	if (t2 - t1 > 100)		//�̻������ֵ�ʱ����100ms
	{
		//�̻�������
		int i = rand() % 10;
		//�����ڷ���״̬
		if (jet[i].shoot == false && fire[i].show == false)
		{
			//�̻���
			jet[i].x = rand() % 1000;
			jet[i].y = rand() % 100 + 450;	//450-549
			jet[i].hx = jet[i].x;
			jet[i].hy = rand() % 300;		//0-299
			jet[i].shoot = true;			//����״̬

			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
		}
		t1 = t2;
	}
}
void Shoot()
{
	for (int i = 0; i < NUM; i++)
	{
		jet[i].t2 = GetTickCount();
		if (jet[i].t2 - jet[i].t1 >= jet[i].dt && jet[i].shoot == true)
		{
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
			if (jet[i].y >= jet[i].hy)
			{
				jet[i].n++;			//��˸
				jet[i].y -= 5;
			}
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);

			if (jet[i].y <= jet[i].hy)
			{
				putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
				jet[i].shoot = false;
				//�ﵽ���߶ȣ������������̻�
				//���·���
				fire[i].x = jet[i].hx;
				fire[i].y = jet[i].hy;
				fire[i].show = true;
			}
		}
		jet[i].t1 = jet[i].t2;
	}
}
//��ʾ�̻�
void ShowFire(DWORD* pMem)
{
	int drt[16] = { 5, 5, 5, 5, 5, 10, 25, 25, 25, 25, 55, 55, 55, 55, 55, 65 };

	for (int i = 0; i < NUM; i++)
	{
		fire[i].t2 = GetTickCount();
		if (fire[i].t2 - fire[i].t1 >= fire[i].dt && fire[i].show == true)
		{
			if (fire[i].r < fire[i].max_r)
			{
				fire[i].r++;
				fire[i].dt = drt[fire[i].r / 10];
				fire[i].draw = true;
			}
			if (fire[i].r >= fire[i].max_r - 1)
			{
				fire[i].draw = false;
				FireInit(i);
			}
			fire[i].t1 = fire[i].t2;
			// ����ú��ڻ��ɱ�ը�����ݵ�ǰ��ը�뾶���̻�����ɫֵ�ӽ���ɫ�Ĳ������
			if (fire[i].draw)
			{
				for (double a = 0; a <= 6.28; a += 0.01)
				{
					int x1 = (int)(fire[i].cen_x + fire[i].r * cos(a));
					int y1 = (int)(fire[i].cen_y - fire[i].r * sin(a));
					if (x1 > 0 && x1 < fire[i].width && y1>0 && y1 < fire[i].height)
					{
						int b = fire[i].xy[x1][y1] & 0xff;
						int g = (fire[i].xy[x1][y1] >> 8) & 0xff;
						int r = (fire[i].xy[x1][y1] >> 16);
						// �̻����ص��ڴ����ϵ�����
						int xx = (int)(fire[i].x + fire[i].r * cos(a));
						int yy = (int)(fire[i].y - fire[i].r * sin(a));
						//�ϰ������ص㲻�������ֹԽ��
						if (r > 0x20 && g > 0x20 && b > 0x20 && xx > 0 && xx < 1000 && yy >0 && yy < 600)
						{
							pMem[yy * 1000 + xx] = BGR(fire[i].xy[x1][y1]);
						}
						fire[i].draw = false;
					}
				}
			}
		}
	}
}
void welcome()
{
	setcolor(YELLOW);
	for (int i = 0; i < 50; i++)
	{
		int x = 600 + int(180 * sin(PI * 2 * i / 60));
		int y = 200 + int(180 * cos(PI * 2 * i / 60));
		cleardevice();
		settextstyle(i, 0, "����");
		outtextxy(x - 80, y, "2023");
		outtextxy(x - 10, y + 100, "�������");
		Sleep(65);
	}
	Sleep(130);
	cleardevice();
	settextstyle(25, 0, "����");
	outtextxy(400, 200, "��!  2023���!");
	outtextxy(400, 250, "�ټ���2022!");
	outtextxy(400, 300, "�ǽ���Ҳ���µĿ�ʼ");
	outtextxy(400, 350, "���ź�������2022��!");
	outtextxy(400, 400, "ף������2023��������!");
	outtextxy(400, 450, "Ըո�µ�2023ɽ�����,���¾���!");
	outtextxy(520, 500, "ף�����2023����ʤ��");
	Sleep(4000);
	cleardevice();
}



int main()
{
	//��ʼ���棨1000��600��
	initgraph(1000, 600);
	//��ʼ������
	srand((unsigned int)time(NULL));
	welcome();
	DWORD t1 = GetTickCount();
	DWORD* pMem = GetImageBuffer();
	for (int i = 0; i < NUM; i++)
	{
		FireInit(i);
	}
	Load();
	BeginBatchDraw();
	while (1)
	{
		// ���ѡ�����ص����
		for (int clr = 0; clr < 200; clr++)
		{
			int px1 = rand() % 1000;
			int py1 = rand() % 600;

			// ��ֹԽ��
			if (py1 < 599)
			{
				//���Դ渳ֵ�������ص�
				pMem[py1 * 1000 + px1] = pMem[py1 * 1000 + px1 + 1] = BLACK;
			}
		}
		ChoiceJet(t1);
		Shoot();
		ShowFire(pMem);
		FlushBatchDraw();
	}
	system("pause");
	return 0;
}
