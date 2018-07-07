#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define virusMaxsize 4//病毒的最大DNA长度
#define humanMaxsize 6//人的最大DNA长度
//备注：病毒DNA必须比人类DNA短

typedef struct {
	char data[virusMaxsize + humanMaxsize];
	int length;
}Sqstring;

void GetNextval(Sqstring *&t, int nextval[])
{
	int j = 0, k = -1;
	nextval[0] = -1;
	while (j<t->length)
	{
		if (k == -1 || t->data[j] != t->data[k])
		{
			j++; k++;
			if (t->data[j] != t->data[k])
				nextval[j] = k;
			else
				nextval[j] = nextval[k];
		}
		else
			k = nextval[k];
	}
}

int KMPIndex(Sqstring *&s, Sqstring *&t)
{
	int nextval[virusMaxsize], i = 0, j = 0;
	GetNextval(t, nextval);
	while (i<s->length&&j<t->length)
	{
		if (j == -1 || s->data[i] == t->data[j])
		{
			i++;
			j++;
		}
		else
			j = nextval[j];
	}
	if (j >= t->length)
		return(i - t->length);
	else
		return(-1);
}

void infectcheck(Sqstring *&human,Sqstring *&virus)
{
	bool infected = false;
	int n = 0, c = 0;
	char viruslist[2*virusMaxsize];
	Sqstring newvirus;
	Sqstring *linevirus=(Sqstring *)malloc(sizeof(Sqstring));
	human->length = strlen(human->data);
	virus->length = strlen(virus->data);
	strcpy_s(newvirus.data,virus->data);
	strcat_s(newvirus.data, virus->data);
	newvirus.length = strlen(newvirus.data);
	for (int i = 0; i < virusMaxsize; i++)
	{
		for (int j = i; j < virusMaxsize; j++)
		{
			linevirus->data[j-i] = newvirus.data[j];
			linevirus->length = strlen(linevirus->data);
		}
		c = KMPIndex(human, linevirus);
	}

	if (c == -1)
	{
		printf("经检验该人感染病毒%s\n", virus->data);
		infected = true;
	}

	if (infected == false)
		printf("该人未感染病毒");
}

int main()
{
	int a;
	Sqstring *human;
	Sqstring *virus;
	human = (Sqstring *)malloc(sizeof(Sqstring));
	virus = (Sqstring *)malloc(sizeof(Sqstring));
	printf("病毒检测程序\n");
	printf("------------------\n");

	printf("请输入病毒的DNA序列,长度不超过%d,格式如：ab...\n", virusMaxsize - 1);
	gets_s(virus->data, virusMaxsize - 1);
	printf("请输入人的DNA序列,不超过3个,每个长度不超过%d,格式如：abcab...\n", humanMaxsize - 1);
	gets_s(human->data, humanMaxsize - 1);

	printf("下面开始检测");
	infectcheck(human, virus);
	system("PAUSE");
	return 0;
}