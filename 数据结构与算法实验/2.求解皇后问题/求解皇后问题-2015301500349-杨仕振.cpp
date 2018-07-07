#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define Maxsize 20

typedef struct {
	int x;
	int y;
}chess;//规定记录棋子的坐标方式

typedef struct {
	chess c[Maxsize];
	int top;
}stack;//储存棋子组合的栈

void printpath(stack *&s, int n)//打印组合
{
	for (int i = 0; i<n; i++)
		printf("(%d,%d);", s->c[i].x, s->c[i].y);
	printf("\n");
}

void Push(stack *&s, int a, int b)//入栈操作
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
	while (!((s->top == -1) && (a == n)&&(b==0)))//判断是否已经扫描完了所有的情况
	{
		for (a = 0; a < n; a++)
		{
			for (i = 0; i <= s->top; i++)//判断当前的格子是否能够入栈
				if (a == s->c[i].x || abs(s->c[i].x - a) == abs(s->c[i].y - b) || s->top == n - 1)//条件：不同对角线且不同列
					break;//若冲突，则中止循环
			if (i > s->top)//如果i比栈顶指针大，说明可以入栈
			{
				Push(s, a, b);//入栈
				b++;//将当前位置推向下一行
				if (s->top == n - 1)//如果栈满
				{
					printpath(s, n);//打印组合
					while (a == n - 1&&b!=0)//当达到了最右端的格子（不包含第一行的情况）
					{
						a = s->c[s->top].x;
						b = s->c[s->top].y;//将当前格子置为栈顶格子
						s->top--;//出栈
					}
					continue;//继续向右扫描
				}
				break;//跳出该行，扫描下一行
			}
			else//如果不能入栈
			{
				while (a == n - 1&&b!=0)//当达到了最右端的格子（不包含第一行的情况）
				{
					a = s->c[s->top].x;
					b = s->c[s->top].y;//将当前格子置为栈顶格子
					s->top--;//出栈
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