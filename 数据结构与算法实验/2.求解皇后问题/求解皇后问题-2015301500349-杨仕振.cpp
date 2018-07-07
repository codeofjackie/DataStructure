#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define Maxsize 20

typedef struct {
	int x;
	int y;
}chess;//�涨��¼���ӵ����귽ʽ

typedef struct {
	chess c[Maxsize];
	int top;
}stack;//����������ϵ�ջ

void printpath(stack *&s, int n)//��ӡ���
{
	for (int i = 0; i<n; i++)
		printf("(%d,%d);", s->c[i].x, s->c[i].y);
	printf("\n");
}

void Push(stack *&s, int a, int b)//��ջ����
{
	s->top++;
	s->c[s->top].x = a;
	s->c[s->top].y = b;
}

void scangrid(stack *&s, int n)
{
	int a = 0;
	int b = 0;
	int i;
	while (!((s->top == -1) && (a == n)&&(b==0)))//�ж��Ƿ��Ѿ�ɨ���������е����
	{
		for (a = 0; a < n; a++)
		{
			for (i = 0; i <= s->top; i++)//�жϵ�ǰ�ĸ����Ƿ��ܹ���ջ
				if (a == s->c[i].x || abs(s->c[i].x - a) == abs(s->c[i].y - b) || s->top == n - 1)//��������ͬ�Խ����Ҳ�ͬ��
					break;//����ͻ������ֹѭ��
			if (i > s->top)//���i��ջ��ָ���˵��������ջ
			{
				Push(s, a, b);//��ջ
				b++;//����ǰλ��������һ��
				if (s->top == n - 1)//���ջ��
				{
					printpath(s, n);//��ӡ���
					while (a == n - 1&&b!=0)//���ﵽ�����Ҷ˵ĸ��ӣ���������һ�е������
					{
						a = s->c[s->top].x;
						b = s->c[s->top].y;//����ǰ������Ϊջ������
						s->top--;//��ջ
					}
					continue;//��������ɨ��
				}
				break;//�������У�ɨ����һ��
			}
			else//���������ջ
			{
				while (a == n - 1&&b!=0)//���ﵽ�����Ҷ˵ĸ��ӣ���������һ�е������
				{
					a = s->c[s->top].x;
					b = s->c[s->top].y;//����ǰ������Ϊջ������
					s->top--;//��ջ
				}
			}
		}
	}
}

int main()
{
	int n;
	stack *s = (stack *)malloc(sizeof(stack));
	s->top = -1;
	printf("The  program is designed to solve Queen problem\n");
	printf("Please input the length of the chessboard's side(larger than zero)\n");
	do{
		scanf_s("%d", &n);
	}while(n<1);
	scangrid(s, n);
	system("PAUSE");
	return 0;
}