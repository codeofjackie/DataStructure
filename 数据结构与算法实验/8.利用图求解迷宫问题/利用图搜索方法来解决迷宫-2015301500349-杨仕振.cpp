#include<stdio.h>
#include<stdlib.h>
#define M 8
#define N 8
#define Maxsize M*N

typedef struct ANode
{
	int i, j;
	struct ANode *nextarc;
}ArcNode;// �ڽӱ�߽ڵ�
typedef struct Vnode
{
	ArcNode *firstarc;
}Vnode;// �ڽӱ�ͷ���ṹ����
typedef struct
{
	Vnode adjlist[M + 2][N + 2];
}ALGraph;// �ڽӱ�ṹ����
typedef struct
{
	int i;
	int j;
}Grid;// �Թ��еĸ���
typedef struct
{
	Grid data[Maxsize];
	int length;
}Pathrecord;// ��¼һ�����ߵ�·��
int visited[M + 2][N + 2] = { 0 };// ȫ�����飬��¼��ǰ�����Ƿ�����
int count = 0;// ͳ�ƿ��ߵ��Թ�·������
void CreateList(ALGraph *&G, int mg[][N + 2])// ����¼�Թ���Ϣ������ת��Ϊ�ڽӱ�
{
	int i, j;
	ArcNode *p;
	G = (ALGraph*)malloc(sizeof(ALGraph));
	for (i = 0; i < M + 2; i++)
		for (j = 0; j < N + 2; j++)
			G->adjlist[i][j].firstarc = NULL;//��ʼ���ڽӱ�
	for (i = 1; i <= M; i++)
		for (j = 1; j <= N; j++)
			if (mg[i][j] == 0)
			{
				if (mg[i-1][j]==0)//���μ���ĸ������Ƿ����
				{
					p = (ArcNode *)malloc(sizeof(ArcNode));
					p->i = i-1; p->j = j;
					p->nextarc = G->adjlist[i][j].firstarc;
					G->adjlist[i][j].firstarc = p;
				}
				if (mg[i][j+1] == 0)
				{
					p = (ArcNode *)malloc(sizeof(ArcNode));
					p->i = i; p->j = j+1;
					p->nextarc = G->adjlist[i][j].firstarc;
					G->adjlist[i][j].firstarc = p;
				}
				if (mg[i+1][j] == 0)
				{
					p = (ArcNode *)malloc(sizeof(ArcNode));
					p->i = i+1; p->j = j;
					p->nextarc = G->adjlist[i][j].firstarc;
					G->adjlist[i][j].firstarc = p;
				}
				if (mg[i][j-1] == 0)
				{
					p = (ArcNode *)malloc(sizeof(ArcNode));
					p->i = i; p->j = j-1;
					p->nextarc = G->adjlist[i][j].firstarc;
					G->adjlist[i][j].firstarc = p;
				}
			}
}

void DispAdj(ALGraph *G)//����ڽӱ�
{
	int i, j;
	ArcNode *p;
	for (i = 0; i<M + 2; i++)
		for (j = 0; j < N + 2; j++)
		{
			printf("[%d,%d]:", i, j);
			p = G->adjlist[i][j].firstarc;
			while (p != NULL)
			{
				printf("(%d,%d)", p->i, p->j);
				p = p->nextarc;
			}
			printf("\n");
		}
}

void FindPath(ALGraph *G, int xi, int yi, int xe, int ye, Pathrecord path)//ͨ����ȱ����ҵ�����·������ӡ
{
	ArcNode *p;
	visited[xi][yi] = 1;//�õ�ǰ����Ϊ�ѷ���
	path.data[path.length].i = xi; path.data[path.length].j = yi;
	path.length++;
	if (xi == xe&&yi == ye)//��������յ㣬�����·��
	{
		printf("�Թ�·��%d:", ++count);
		for (int k = 0; k < path.length; k++)
			printf("(%d,%d)", path.data[k].i, path.data[k].j);
		printf("\n");
	}
	p = G->adjlist[xi][yi].firstarc;
	while (p != NULL)
	{
		if (visited[p->i][p->j] == 0)
			FindPath(G, p->i, p->j, xe, ye, path);//δ�����ص��Ҹ���δ����ʱ�ݹ����FindPath����
		p = p->nextarc;
	}
	visited[xi][yi] = 0;
}

void main()
{
	ALGraph *G;
	int mg[M + 2][N + 2] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
		{ 1, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
		{ 1, 0, 0, 0, 0, 1, 1, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 0, 0, 1, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
		{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	};//�����Թ��ľ���
	CreateList(G, mg);
	printf("�Թ���Ӧ���ڽӱ�\n"); DispAdj(G);
	Pathrecord path;
	path.length = 0;
	printf("���е��Թ�·����\n");
	FindPath(G, 1, 1, M, N, path);
}