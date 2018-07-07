#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int pow;//定义多项式的幂
	float coe;//定义多项式的系数
	struct node *next;
} term;//定义多项式的一项

void CreatePoly(term *&L);//创建多项式
void DispPoly(term *&L);//显示多项式
void AddPoly(term *&p, term *&q);//将两个多项式合并
void DestroyPoly(term *&L);//将多项式摧毁

int main()
{
	term *i, *ii;
	printf("请按升幂顺序输入第一个多项式,输入-1停止\n");
	CreatePoly(i);
	printf("第一个多项式为：");
	DispPoly(i);
	printf("\n请按升幂顺序输入第二个多项式,输入-1停止\n");
	CreatePoly(ii);
	printf("第二个多项式为：");
	DispPoly(ii);

	AddPoly(i, ii);
	printf("\n相加之后的结果是：");
	DispPoly(i);

	DestroyPoly(i);
	free(ii);
	system("PAUSE");
	return 0;
}

void CreatePoly(term *&L)//创建多项式
{
	int a;//记录幂
	float b;//记录系数
	term *n, *m;
	L = (term *)malloc(sizeof(term));
	L->next = NULL;//初始化多相似
	m = L;
	printf("请输入幂,系数");
	while (1) {
		scanf_s("%d,%f", &a, &b);
		if (a == -1) break;//设定输入停止的条件
		n = (term *)malloc(sizeof(term));
		n->pow = a;
		n->coe = b;//创建并将新的项添加到多项式中
		m->next = n;
		m = n;
	}
	m->next = NULL;
}

void DispPoly(term *&L)//显示多项式
{
	term *p;
	p = L;
	if (p != NULL&&p->next != NULL)//判断多项式是否到达尾部
	{
		while (1)
		{
			p = p->next;//将指针指向下一个
			if (p->pow != 0)
				printf("%fx^%d", p->coe, p->pow);
			else
				printf("%f", p->coe);//如果幂是零，那么只显示系数
			if (p->next == NULL) break;/*如果p是最后一个项，
									   那么后面不放置"+"*/
			printf("+");//通过循环来放置“+”
		}
	}
	else printf("请先输入多项式！");
}

void AddPoly(term *&p, term *&q)//将多项式相加
{
	term *x = p->next;//设置用来扫描第一个多项式的指针
	term *y = q->next;//设置用来扫描第二个多项式的指针
	term *temp = p;//记录x的上一个节点
	term *pre = q;//记录y的上一个节点
	while (x != NULL)
	{
		while (y != NULL)
		{
			if (x->pow == y->pow)
			{
				x->coe = x->coe + y->coe;//将两个多项式里幂相同项的系数相加
				pre->next=y->next;
				free(y);//将第二个多项式里幂相同的项删除
				y = q->next;
				break;
			}
			pre = y;
			y = y->next;
		}
		pre=q;
		y = pre->next;//从第二个多项式的第一项开始扫描
		x = x->next;//开始匹配第一个多项式的下一项
	}
	//至此，两个多项式的每一项的幂都各不相同
	x = p->next;
	while (x != NULL)
	{
		while (y != NULL)
		{
			if (y->pow < x->pow)
			{
				pre->next = y->next;
				y->next = x;
				temp->next = y;
				pre = pre->next;/*将第二个多项式的每一项按照幂的大小顺序插入
								第一个多项式*/
				if(pre!=NULL)
					y = pre->next;//如果pre不为空，那么就把y继续向后指
				else
					y = pre;//如果为空，那么就把y也指向NULL
			}
			else break;//如果y所指项的幂比第一个多项式的幂都大，那么结束循环
		}
		temp = x;
		x = x->next;//继续指向下一个x
	}
	if (y != NULL)	temp->next = y;/*如果ii多项式的某一项开始幂都大于i多项式，
	那么就把ii接到i链的尾部*/
	//至此，幂不同的项便从第二个多项式“移”到了第一个多项式上
}

void DestroyPoly(term *&L)//销毁多项式
{
	term *q = L->next;
	while (q != NULL) {
		free(L);
		L = q;
		q = q->next;
	}
	free(L);
}