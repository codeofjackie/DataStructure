#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define Maxsize 20

int n, a, b, i;

typedef struct {
	int x;
	int y;
}chess;//�涨��¼���ӵ����귽ʽ

typedef struct {
	chess c[Maxsize];
	int top;
}stack;//����������ϵ�ջ
stack *s;

void printpath()//��ӡ���
{
	for (int j = 0; j<n; j++)
		printf("(%d,%d);", s->c[j].x, s->c[j].y);
	printf("\n");
}

void Push()//��ջ����
{
	s->top++;
	s->c[s->top].x = a;
	s->c[s->top].y = b;
}

void loadpath()
{
	for (i = 0; i <= s->top; i++)//�жϵ�ǰ�ĸ����Ƿ��ܹ���ջ
		if (b==n||a == s->c[i].x || abs(s->c[i].x - a) == abs(s->c[i].y - b) || s->top == n - 1)//��������ͬ�Խ����Ҳ�ͬ��
			break;//����ͻ������ֹѭ��
	if (i > s->top)
	{
		Push();
		b++;//������һ��
		a = 0;//���������Ϊ0
		loadpath();
	}
	else
	{
		if (s->top == n - 1)
			printpath();//��ӡ���
		while (a == n - 1 && b != 0||b==n)//���ﵽ�����Ҷ˻���˵ĸ��ӣ���������һ�е������
		{
			a = s->c[s->top].x;
			b = s->c[s->top].y;//����ǰ������Ϊջ������
			s->top--;//��ջ
		}
		a++;//����ǰλ����Ϊ��ǰ�����Ҳ�λ��
	}
}

int main()
{
	a = b = 0;
	s = (stack *)malloc(sizeof(stack));
	s->top = -1;
	printf("The  program is designed to solve Queen problem\n");
	printf("Please input the length of the chessboard's side(larger than zero)\n");
	do {
		scanf_s("%d", &n);
	} while (n<1);
	
	while (!((s->top == -1) && (a == n) && (b == 0)))//�ж��Ƿ��Ѿ�ɨ���������е����
		loadpath();
	
	system("PAUSE");
	return 0;
}