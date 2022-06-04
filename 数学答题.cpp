#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <windows.h>
#include<conio.h>
#include<process.h>

double NUM1[10] = { 0 }, NUM2[10] = { 0 };
int calculate[10] = { 0 };// 
char Quaternion[10] = { 0 };
double input[10] = { 0 };
int TURN_NUM=0;
int s = 0;
bool X = false;//控制计时器重启
bool Y[10];//控制QAQ函数是否进行下去

static DWORD t1 = 0, t2 = 0;//初始化计时器
void Init()//初始化
{
	srand(time(NULL));
	system("cls");
	for (int i = 0;i < 10;i++)
	{
		NUM1[i] = rand() % 99+1;//随机数1，2
		Sleep(5);
		NUM2[i] = rand() % 99+1;
		Sleep(5);
		calculate[i] = rand() % 4;//随机符号
		Y[i] = true;//初始化控制
		switch (calculate[i])
		{
		case 0:
			Quaternion[i] = '+';
			break;
		case 1:
			Quaternion[i] = '-';
			break;
		case 2:
			Quaternion[i] = '*';
			break;
		case 3:
			Quaternion[i] = '/';
			break;
		}
	}

}
DWORD WINAPI ThreadFun(LPVOID pM);


void QAQ()//主要运算函数
{
	system("cls");
	if (s == 10)
	{
		printf("答对了%d道题目，10秒后退出程序……", TURN_NUM);
		}
		else if (s < 10) {
			HANDLE handle = CreateThread(NULL, 0, ThreadFun, NULL, 0, NULL);
			printf("第%d题:%.0lf %c %.0lf = ?\n", s + 1, NUM1[s], Quaternion[s], NUM2[s]);
			scanf_s("%lf", &input[s]);
			if (Y[s]) 
			{
				Y[s] = false;
				X = true;
				switch (calculate[s])
				{
				case 0:
					if (input[s] == NUM1[s] + NUM2[s])
						TURN_NUM++;
					break;
				case 1:
					if (input[s] == NUM1[s] - NUM2[s])
						TURN_NUM++;
					break;
				case 2:
					if (input[s] == NUM1[s] * NUM2[s])
						TURN_NUM++;
					break;
				case 3:
					if (input[s] == NUM1[s] / NUM2[s])
						TURN_NUM++;
					break;
				}
				s++;
				QAQ();
			}
		}
		
	
}

DWORD WINAPI ThreadFun(LPVOID pM)
{
	DWORD t1 = GetTickCount(), t2 = GetTickCount();
	while(1) 
	{
		if (X) //输入时直接重置计时器
		{
			X = false;
			return 0;
		}
		
		if (t2 - t1 == 10000)
		{
			Y[s] = false;//使得该题永远终止,防止多次运行
			t1 = t2;
			s++;
			QAQ();
			return 0;
		}
		t2 = GetTickCount();
	/*	if ((t2 - t1) % 1000 == 0)
			printf("%d", (t2-t1)/1000);*/
		
	}
	return 0;
}

int main()
{

	Init();
	system("pause");
	system("cls");//清屏
	QAQ();
	Sleep(10000);

}