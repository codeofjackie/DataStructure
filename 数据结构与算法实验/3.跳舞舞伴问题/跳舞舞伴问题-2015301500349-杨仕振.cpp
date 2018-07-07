#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define Queuesize 5

typedef struct{
	char name[20];
	char sex;
}person_type;	//定义一个舞者

typedef struct{
	person_type queue[Queuesize];
	int front;
	int count;
}CirQueue;	//定义不同性别的队

void InitQueue(CirQueue *&q)//初始化男女队列
{
	q = (CirQueue*)malloc(sizeof(CirQueue));
	if (!q)  {
		printf("创建失败，程序终止！"); 
		exit(-1);
	}	//如果内存申请失败，则退出程序。
	q->front = q->count = 0;
}

bool enQueue(CirQueue *&q, person_type p)	//进队
{
	int rear;//临时的rear指针
	if (q->count == Queuesize)  {
		printf("队列已满，无法进队！"); //若队列已满，则无法进队
		return false;
	}
	else  {
		rear = (q->front + q->count) % Queuesize; //确定临时队尾的位置
		rear = (rear + 1) % Queuesize;
		q->queue[rear]=p;
		q->count++;
		return true;
	}
}

bool deQueue(CirQueue *&q, person_type &p)	//出队
{
	if (q->count == 0)  {
		printf("队列已空，无法出队！");//若队中没有元素，则不可出队
		return false;
	}
	else  {
		q->front = (q->front + 1) % Queuesize;//修改出队后队头的位置
		p = q->queue[q->front];
		q->count--;
		return true;
	}
}

person_type queue_front(CirQueue *&q)	//求队中的第一个人
{
	if (q->count == 0)  {
		printf("队列为空，操作失败");
		exit(-1);
	}	//队空则退出程序
	return q->queue[(q->front+1)%Queuesize];
}

void dancepartners(CirQueue *&female, CirQueue *&male, int round)
{
	person_type p;
	person_type q;
	int m = male->count;//求男队人数
	int n = female->count;//求女队人数
	for (int j = 1; j <= round; j++)
	{
		printf("------------------------");
		printf("第%d轮配对情况：\n", j);
		for (int i = 1; i <= (n<m ? n : m); i++)
		{
			deQueue(male, p);
			deQueue(female, q);
			printf("男:%s和女:%s配对成功\n", p.name, q.name);
			enQueue(male, p);
			enQueue(female, q);
		}
		if (m>n)  {
			printf("男队中还有%d个人在等待!\n", m - n);
			printf("男队中第一个等待的是：%s\n", queue_front(male).name);
		}
		else if (m<n)  {
			printf("女队中还有%d个人在等待!\n", n - m);
			printf("女队中第一个等待的是：%s\n", queue_front(female).name);
		}
		else  {
			printf("没有人剩余!\n");
		}
	}
}

int main()
{
	int round;//定义配对的轮数
	int i, num;//定义计数变量和总的人数
	CirQueue *male, *female;//定义男队
	person_type dancers[2*Queuesize];//定义包含所有人的队列
	InitQueue(male);
	InitQueue(female);//初始化两个队列
	do {
		printf("请输入男女舞者的总人数，其值大于等于1,且男女生的数量均不要超过%d\n",Queuesize);
		scanf_s("%d", &num);
	}while (num<1 || num>2*Queuesize);
	printf("输入姓名和性别（m 男性，f 女性），如：\nzhangsan m\n");
	for (i = 0; i<num; i++)
	{
		scanf_s("%s %c",&dancers[i].name,20,&dancers[i].sex);
		if (dancers[i].sex != 'f'&&dancers[i].sex != 'm')
		{
			printf("第%d个人的信息有误,请重新输入", (i--) + 1);
			continue;
		}
		switch (dancers[i].sex)
		{
			case 'm':enQueue(male,dancers[i]);	break;
			case 'f':enQueue(female,dancers[i]);break;//通过选择，将不同的人进入不同的队
		}
	}
	do{
		printf("\n请输入匹配的轮数，其值大于等于1\n");
		scanf_s("%d", &round);
	}while (round<1);
	dancepartners(female, male, round);
	system("PAUSE");
	return 0;
}