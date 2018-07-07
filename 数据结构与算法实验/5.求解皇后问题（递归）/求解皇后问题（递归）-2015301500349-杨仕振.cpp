#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define Maxsize 20

int n, a, b, i;

typedef struct {
	int x;
	int y;
}chess;//规定记录棋子的坐标方式

typedef struct {
	chess c[Maxsize];
	int top;
}stack;//储存棋子组合的栈
stack *s;

void printpath()//打印组合
{
	for (int j = 0; j<n; j++)
		printf("(%d,%d);", s->c[j].x, s->c[j].y);
	printf("\n");
}

void Push()//入栈操作
{
	s->top++;
	s->c[s->top].x = a;
	s->c[s->top].y = b;
}

void loadpath()
{
	for (i = 0; i <= s->top; i++)//判断当前的格子是否能够入栈
		if (b==n||a == s->c[i].x || abs(s->c[i].x - a) == abs(s->c[i].y - b) || s->top == n - 1)//条件：不同对角线且不同列
			break;//若冲突，则中止循环
	if (i > s->top)
	{
		Push();
		b++;//推向下一行
		a = 0;//将横坐标归为0
		loadpath();
	}
	else
	{
		if (s->top == n - 1)
			printpath();//打印组合
		while (a == n - 1 && b != 0||b==n)//当达到了最右端或最顶端的格子（不包含第一行的情况）
		{
			a = s->c[s->top].x;
			b = s->c[s->top].y;//将当前格子置为栈顶格子
			s->top--;//出栈
		}
		a++;//将当前位置置为当前格子右侧位置
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
	
	while (!((s->top == -1) && (a == n) && (b == 0)))//判断是否已经扫描完了所有的情况
		loadpath();
	
	system("PAUSE");
	return 0;
}