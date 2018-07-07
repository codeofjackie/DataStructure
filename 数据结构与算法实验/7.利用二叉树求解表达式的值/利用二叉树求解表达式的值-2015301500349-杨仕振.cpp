#include<stdio.h>
#include<stdlib.h>
#define Maxsize 12//��ֵ��һΪ���ʽ����󳤶�

int result;//���ʽ�Ľ��
typedef struct
{
	int top;
	int value[Maxsize];
}stack;//����ʱ�����洢��ʱ�����ջ
stack st;

typedef struct btnode
{
	char data;
	struct btnode *lchild;
	struct btnode *rchild;
}BTNode;//�����������ڵ�ṹ

BTNode *CreateBTNode(char *str)
{
	BTNode * EXPT[Maxsize];//����ջEXPT�����ڴ洢δ�������ʽ
	BTNode * OPTR[Maxsize];//����ջOPTR�����ڴ���δ��������
	BTNode *b;//����������ĸ��ڵ�
	int topEXPT = -1;//EXPTջ��ָ��
	int topOPTR = -1;//OPTRջ��ָ��
	int j = 0;
	char ch=str[j];//�����ַ����飬��¼���ʽ
	while (ch != '\0')//����������ʽ��ÿһ���ַ�
	{
		BTNode *node;
		node = (BTNode *)malloc(sizeof(BTNode));//����һ���µĶ������ڵ�
		switch (ch)
		{
			case'+':
			case'-':node->data = ch;
				if (topOPTR != -1)//���������ջ�ڵļӼ������
				{
					OPTR[topOPTR]->rchild =	EXPT[topEXPT];
					OPTR[topOPTR]->lchild = EXPT[topEXPT - 1];
					topEXPT--;
					EXPT[topEXPT] = OPTR[topOPTR];
					topOPTR--;
				}
				topOPTR++;
				OPTR[topOPTR] = node;//��¼�ýڵ������
				break;
			case'*':
			case'/':node->data = ch;
				node->lchild = EXPT[topEXPT];
				topOPTR++;
				OPTR[topOPTR] = node;//��¼�ýڵ������
				break;
			default:node->data = ch;
				node->lchild = node->rchild = NULL;
				topEXPT++;
				EXPT[topEXPT] = node;//��¼�ýڵ������
				if (topOPTR>-1 &&(OPTR[topOPTR]->data == '*' || OPTR[topOPTR]->data == '/'))
					//����˳������ǰ���������
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
	if (topOPTR != -1)//������һ��������ǼӼ���������������Ӧ�Ĵ���
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
//���б��������㣬�ҵ���Ҫ���������ÿһ��Ԫ�أ����ɨ���˫�׽ڵ�Ϊ���������ô�͸�������������ݶ���ֵ���в�����
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
				st.value[st.top] = b->data-48;//���ַ���ԭΪ��Ӧ����ֵ
		}
	}
}

void CalculateBTNode(BTNode *b)//�����㷨
{
	st.top = -1;
	result = 0;
	PostOrder(b);
	printf("\n����ʽ����������:%d\n",result);
}

int main()
{
	BTNode *b;
	char str[Maxsize];

	printf("�������ö�������ʾ����ʽ��������\n");
	printf("������������ʽ��ֻ�ܰ����Ӽ��˳�������,�Ҳ�Ҫ��ͼʹ����Ϊ0,���Ȳ�����%d\n", Maxsize - 1);
	scanf_s("%s", str, Maxsize - 1);
	b=CreateBTNode(str);//������ʽ������
	CalculateBTNode(b);//��������

	system("PAUSE");
	return 0;
}