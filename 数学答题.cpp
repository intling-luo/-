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
bool X = false;//���Ƽ�ʱ������
bool Y[10];//����QAQ�����Ƿ������ȥ

static DWORD t1 = 0, t2 = 0;//��ʼ����ʱ��
void Init()//��ʼ��
{
	srand(time(NULL));
	system("cls");
	for (int i = 0;i < 10;i++)
	{
		NUM1[i] = rand() % 99+1;//�����1��2
		Sleep(5);
		NUM2[i] = rand() % 99+1;
		Sleep(5);
		calculate[i] = rand() % 4;//�������
		Y[i] = true;//��ʼ������
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


void QAQ()//��Ҫ���㺯��
{
	system("cls");
	if (s == 10)
	{
		printf("�����%d����Ŀ��10����˳����򡭡�", TURN_NUM);
		}
		else if (s < 10) {
			HANDLE handle = CreateThread(NULL, 0, ThreadFun, NULL, 0, NULL);
			printf("��%d��:%.0lf %c %.0lf = ?\n", s + 1, NUM1[s], Quaternion[s], NUM2[s]);
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
		if (X) //����ʱֱ�����ü�ʱ��
		{
			X = false;
			return 0;
		}
		
		if (t2 - t1 == 10000)
		{
			Y[s] = false;//ʹ�ø�����Զ��ֹ,��ֹ�������
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
	system("cls");//����
	QAQ();
	Sleep(10000);

}