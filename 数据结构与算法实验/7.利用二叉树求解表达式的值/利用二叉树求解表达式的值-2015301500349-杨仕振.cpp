#include<stdio.h>
#include<stdlib.h>
#define Maxsize 12//其值减一为表达式的最大长度

int result;//表达式的结果
typedef struct
{
	int top;
	int value[Maxsize];
}stack;//运算时用来存储临时结果的栈
stack st;

typedef struct btnode
{
	char data;
	struct btnode *lchild;
	struct btnode *rchild;
}BTNode;//声明二叉树节点结构

BTNode *CreateBTNode(char *str)
{
	BTNode * EXPT[Maxsize];//定义栈EXPT，用于存储未处理的算式
	BTNode * OPTR[Maxsize];//定义栈OPTR，用于处理未处理的算符
	BTNode *b;//定义二叉树的根节点
	int topEXPT = -1;//EXPT栈顶指针
	int topOPTR = -1;//OPTR栈顶指针
	int j = 0;
	char ch=str[j];//定义字符数组，记录表达式
	while (ch != '\0')//遍历运算表达式的每一个字符
	{
		BTNode *node;
		node = (BTNode *)malloc(sizeof(BTNode));//生成一个新的二叉树节点
		switch (ch)
		{
			case'+':
			case'-':node->data = ch;
				if (topOPTR != -1)//处理操作符栈内的加减运算符
				{
					OPTR[topOPTR]->rchild =	EXPT[topEXPT];
					OPTR[topOPTR]->lchild = EXPT[topEXPT - 1];
					topEXPT--;
					EXPT[topEXPT] = OPTR[topOPTR];
					topOPTR--;
				}
				topOPTR++;
				OPTR[topOPTR] = node;//记录该节点的内容
				break;
			case'*':
			case'/':node->data = ch;
				node->lchild = EXPT[topEXPT];
				topOPTR++;
				OPTR[topOPTR] = node;//记录该节点的内容
				break;
			default:node->data = ch;
				node->lchild = node->rchild = NULL;
				topEXPT++;
				EXPT[topEXPT] = node;//记录该节点的内容
				if (topOPTR>-1 &&(OPTR[topOPTR]->data == '*' || OPTR[topOPTR]->data == '/'))
					//处理乘除运算符前后的两个数
				{
					OPTR[topOPTR]->rchild = EXPT[topEXPT];
					topEXPT--;
					EXPT[topEXPT] = OPTR[topOPTR];
					topOPTR--;
				}
		}
		j++;
		ch = str[j];
	}
	if (topOPTR != -1)//如果最后一个运算符是加减运算符，则进行相应的处理
	{
		OPTR[topOPTR]->rchild = EXPT[topEXPT];
		OPTR[topOPTR]->lchild = EXPT[topEXPT - 1];
		topEXPT--;
		EXPT[topEXPT] = OPTR[topOPTR];
		topOPTR--;
	}
	b = EXPT[topEXPT];
	return b;
}

void PostOrder(BTNode *&b)
//进行遍历和运算，找到需要进行运算的每一个元素，如果扫描的双亲节点为运算符，那么就根据运算符的内容对数值进行操作。
{
	if (b != NULL)
	{
		PostOrder(b->lchild);
		PostOrder(b->rchild);
		switch (b->data)
		{
			case '+':result = st.value[st.top] + st.value[st.top - 1];
				st.top--;
				st.value[st.top] = result; break;
			case '-':result = st.value[st.top-1] - st.value[st.top];
				st.top--;
				st.value[st.top] = result; break;
			case '*':result = st.value[st.top] * st.value[st.top - 1];
				st.top--;
				st.value[st.top] = result; break;
			case '/':result = st.value[st.top-1] / st.value[st.top];
				st.top--;
				st.value[st.top] = result; break;
			default:st.top++;
				st.value[st.top] = b->data-48;//将字符还原为对应的数值
		}
	}
}

void CalculateBTNode(BTNode *b)//运算算法
{
	st.top = -1;
	result = 0;
	PostOrder(b);
	printf("\n该算式的运算结果是:%d\n",result);
}

int main()
{
	BTNode *b;
	char str[Maxsize];

	printf("下面是用二叉树表示的算式的运算结果\n");
	printf("请输入运算表达式，只能包含加减乘除和数字,且不要试图使除数为0,长度不超过%d\n", Maxsize - 1);
	scanf_s("%s", str, Maxsize - 1);
	b=CreateBTNode(str);//创建算式二叉树
	CalculateBTNode(b);//进行运算

	system("PAUSE");
	return 0;
}