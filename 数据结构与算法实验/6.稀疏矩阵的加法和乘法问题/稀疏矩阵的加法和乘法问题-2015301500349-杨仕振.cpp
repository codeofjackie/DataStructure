#include <stdio.h>
#include <stdlib.h>
#define M 5
#define N 5
#define Maxsize 25

typedef struct
{
	int r;
	int c;
	int d;
}TupNode;

typedef struct
{
	int rows;
	int cols;
	int nums;
	TupNode data[Maxsize];
}TSMatrix;

void CreatMat(TSMatrix &t, int A[M][N])//创建二维稀疏矩阵的三元组表示
{
	int i, j;
	t.rows = M; t.cols = N; t.nums = 0;
	for (i = 0; i<M; i++)
	{
		for (j = 0; j<N; j++)
		{
			if (A[i][j] != 0)
			{
				t.data[t.nums].r = i;
				t.data[t.nums].c = j;
				t.data[t.nums].d = A[i][j]; t.nums++;
			}
		}
	}
}

void sort(TSMatrix &tb)
{
	int tempr;
	int tempc;
	int tempd;
	int i = 0, j = 0;
	for (; i<tb.nums; i++)
	{
		for (j = i + 1; j < tb.nums; j++)
		{
			if (tb.data[i].r > tb.data[j].r || tb.data[i].r == tb.data[j].r&&tb.data[i].c > tb.data[j].c)
			{
				tempr = tb.data[i].r;
				tempc = tb.data[i].c;
				tempd = tb.data[i].d;
				tb.data[i].r = tb.data[j].r;
				tb.data[i].c = tb.data[j].c;
				tb.data[i].d = tb.data[j].d;
				tb.data[j].r = tempr;
				tb.data[j].c = tempc;
				tb.data[j].d = tempd;
			}
		}
	}
}

void TranTat(TSMatrix t, TSMatrix &tb)//矩阵转置
{
	int q, v = 0;
	tb.rows = t.cols; tb.cols = t.rows; tb.nums = t.nums;
	if (t.nums != 0)
	{
		for (q = 0; q < t.cols; q++)
			for (v = 0; v < t.nums; v++)
				if (t.data[v].c == q)
				{
					tb.data[v].r = t.data[v].c;
					tb.data[v].c = t.data[v].r;
					tb.data[v].d = t.data[v].d;
				}
	}
	sort(tb);
}

bool MatAdd(TSMatrix a, TSMatrix b, TSMatrix &c)//矩阵相加
{
	int i = 0, j = 0, k = 0;
	int v;
	if (a.rows != b.rows || a.cols != b.cols)
		return false;
	c.rows = a.rows; c.cols = a.cols;
	while (i<a.nums&&j<b.nums)
	{
		if (a.data[i].r == b.data[j].r)
		{
			if (a.data[i].c<b.data[j].c)
			{
				c.data[k].r = a.data[i].r;
				c.data[k].c = a.data[i].c;
				c.data[k].d = a.data[i].d;
				k++; i++;
			}
			else if (a.data[i].c>b.data[j].c)
			{
				c.data[k].r = b.data[i].r;
				c.data[k].c = b.data[i].c;
				c.data[k].d = b.data[i].d;
				k++; j++;
			}
			else
			{
				v = a.data[i].d + b.data[j].d;
				if (v != 0)
				{
					c.data[k].r = a.data[i].r;
					c.data[k].c = a.data[i].c;
					c.data[k].d = v;
					k++;
				}
				i++; j++;
			}
		}
		else if (a.data[i].r<b.data[j].r)
		{
			c.data[k].r = a.data[i].r;
			c.data[k].c = a.data[i].c;
			c.data[k].d = a.data[i].d;
			k++; i++;
		}
		else
		{
			c.data[k].r = b.data[j].r;
			c.data[k].c = b.data[j].c;
			c.data[k].d = b.data[j].d;
			k++; j++;
		}
		c.nums = k;
	}
	for (; i<a.nums; i++)
	{
		c.data[k].r = a.data[i].r;
		c.data[k].c = a.data[i].c;
		c.data[k].d = a.data[i].d;
		k++;
		c.nums = k;
	}
	for (; j<b.nums; j++)
	{
		c.data[k].r = b.data[j].r;
		c.data[k].c = b.data[j].c;
		c.data[k].d = b.data[j].d;
		k++;
		c.nums = k;
	}

	return true;
}

bool MatMul(TSMatrix a, TSMatrix b, TSMatrix &c)//矩阵相乘
{
	int v = 0;
	int m = 0, n = 0;
	int l = 0;
	int record = 0;
	TSMatrix *f;
	f = (TSMatrix *)malloc(sizeof(TSMatrix));
	if (a.cols != b.rows)
		return false;
	c.rows = a.rows; c.cols = b.cols;
	c.nums = 0;
	TranTat(b, *f);
	for (int i = 0; i<c.rows; i++)
	{
		record = m;
		for (int j = 0; j<c.cols; j++)
		{
			for (int k = 0; k<a.cols; k++)
			{
				l = k;
				if (k == a.data[m].c&&l == f->data[n].c&&i == a.data[m].r&&j == f->data[n].r)
				{
					v = v + a.data[m].d*f->data[n].d;
					m++; n++;
				}
				if ((i == a.data[m].r) && (k == a.data[m].c))
				{
					m++;
				}
				if ((l == f->data[n].c) && (j == f->data[n].r))
				{
					n++;
				}
			}
			if (v != 0)
			{
				c.data[c.nums].d = v;
				c.data[c.nums].r = i;
				c.data[c.nums].c = j;
				c.nums++;
			}
			v = 0;
			if(j!=c.cols-1)
				m = record;
		}
		n = 0;
	}
	return true;
}

void DispMat(TSMatrix t)//输出三元组
{
	int i;
	if (t.nums <= 0)
		return;
	printf("\t%d\t%d\t%d\n", t.rows, t.cols, t.nums);
	printf("\t-------------------\n");
	for (i = 0; i<t.nums; i++)
		printf("\t%d\t%d\t%d\n", t.data[i].r, t.data[i].c, t.data[i].d);
	printf("\t-------------------\n");
}

int main()
{
	TSMatrix a,b;
	TSMatrix *c,*d,*e;
	c = (TSMatrix *)malloc(sizeof(TSMatrix));
	d = (TSMatrix *)malloc(sizeof(TSMatrix));
	e = (TSMatrix *)malloc(sizeof(TSMatrix));
	int A[M][N] = { {},{1,1,1,0,0},{3,0,4,0,0},{2,1,2,0,0},{} };
	int B[M][N] = { {},{2,4,0,1,0},{1,0,3,0,0},{},{} };
	
	CreatMat(a,A);
	CreatMat(b,B);
	DispMat(a);
	DispMat(b);
	
	TranTat(a,*c);
	DispMat(*c);
	MatAdd(a,b,*d);
	DispMat(*d);
	MatMul(a,b,*e);
	DispMat(*e);
	
	return 0;
}