#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int pow;//�������ʽ����
	float coe;//�������ʽ��ϵ��
	struct node *next;
} term;//�������ʽ��һ��

void CreatePoly(term *&L);//��������ʽ
void DispPoly(term *&L);//��ʾ����ʽ
void AddPoly(term *&p, term *&q);//����������ʽ�ϲ�
void DestroyPoly(term *&L);//������ʽ�ݻ�

int main()
{
	term *i, *ii;
	printf("�밴����˳�������һ������ʽ,����-1ֹͣ\n");
	CreatePoly(i);
	printf("��һ������ʽΪ��");
	DispPoly(i);
	printf("\n�밴����˳������ڶ�������ʽ,����-1ֹͣ\n");
	CreatePoly(ii);
	printf("�ڶ�������ʽΪ��");
	DispPoly(ii);

	AddPoly(i, ii);
	printf("\n���֮��Ľ���ǣ�");
	DispPoly(i);

	DestroyPoly(i);
	free(ii);
	system("PAUSE");
	return 0;
}

void CreatePoly(term *&L)//��������ʽ
{
	int a;//��¼��
	float b;//��¼ϵ��
	term *n, *m;
	L = (term *)malloc(sizeof(term));
	L->next = NULL;//��ʼ��������
	m = L;
	printf("��������,ϵ��");
	while (1) {
		scanf_s("%d,%f", &a, &b);
		if (a == -1) break;//�趨����ֹͣ������
		n = (term *)malloc(sizeof(term));
		n->pow = a;
		n->coe = b;//���������µ�����ӵ�����ʽ��
		m->next = n;
		m = n;
	}
	m->next = NULL;
}

void DispPoly(term *&L)//��ʾ����ʽ
{
	term *p;
	p = L;
	if (p != NULL&&p->next != NULL)//�ж϶���ʽ�Ƿ񵽴�β��
	{
		while (1)
		{
			p = p->next;//��ָ��ָ����һ��
			if (p->pow != 0)
				printf("%fx^%d", p->coe, p->pow);
			else
				printf("%f", p->coe);//��������㣬��ôֻ��ʾϵ��
			if (p->next == NULL) break;/*���p�����һ���
									   ��ô���治����"+"*/
			printf("+");//ͨ��ѭ�������á�+��
		}
	}
	else printf("�����������ʽ��");
}

void AddPoly(term *&p, term *&q)//������ʽ���
{
	term *x = p->next;//��������ɨ���һ������ʽ��ָ��
	term *y = q->next;//��������ɨ��ڶ�������ʽ��ָ��
	term *temp = p;//��¼x����һ���ڵ�
	term *pre = q;//��¼y����һ���ڵ�
	while (x != NULL)
	{
		while (y != NULL)
		{
			if (x->pow == y->pow)
			{
				x->coe = x->coe + y->coe;//����������ʽ������ͬ���ϵ�����
				pre->next=y->next;
				free(y);//���ڶ�������ʽ������ͬ����ɾ��
				y = q->next;
				break;
			}
			pre = y;
			y = y->next;
		}
		pre=q;
		y = pre->next;//�ӵڶ�������ʽ�ĵ�һ�ʼɨ��
		x = x->next;//��ʼƥ���һ������ʽ����һ��
	}
	//���ˣ���������ʽ��ÿһ����ݶ�������ͬ
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
				pre = pre->next;/*���ڶ�������ʽ��ÿһ����ݵĴ�С˳�����
								��һ������ʽ*/
				if(pre!=NULL)
					y = pre->next;//���pre��Ϊ�գ���ô�Ͱ�y�������ָ
				else
					y = pre;//���Ϊ�գ���ô�Ͱ�yҲָ��NULL
			}
			else break;//���y��ָ����ݱȵ�һ������ʽ���ݶ�����ô����ѭ��
		}
		temp = x;
		x = x->next;//����ָ����һ��x
	}
	if (y != NULL)	temp->next = y;/*���ii����ʽ��ĳһ�ʼ�ݶ�����i����ʽ��
	��ô�Ͱ�ii�ӵ�i����β��*/
	//���ˣ��ݲ�ͬ�����ӵڶ�������ʽ���ơ����˵�һ������ʽ��
}

void DestroyPoly(term *&L)//���ٶ���ʽ
{
	term *q = L->next;
	while (q != NULL) {
		free(L);
		L = q;
		q = q->next;
	}
	free(L);
}