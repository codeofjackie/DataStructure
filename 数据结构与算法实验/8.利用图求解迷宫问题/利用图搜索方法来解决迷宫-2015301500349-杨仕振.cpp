#include<stdio.h>
#include<stdlib.h>
#define M 8
#define N 8
#define Maxsize M*N

typedef struct ANode
{
	int i, j;
	struct ANode *nextarc;
}ArcNode;// 邻接表边节点
typedef struct Vnode
{
	ArcNode *firstarc;
}Vnode;// 邻接表头结点结构类型
typedef struct
{
	Vnode adjlist[M + 2][N + 2];
}ALGraph;// 邻接表结构类型
typedef struct
{
	int i;
	int j;
}Grid;// 迷宫中的格子
typedef struct
{
	Grid data[Maxsize];
	int length;
}Pathrecord;// 记录一条可走的路径
int visited[M + 2][N + 2] = { 0 };// 全局数组，记录当前格子是否已走
int count = 0;// 统计可走的迷宫路径条数
void CreateList(ALGraph *&G, int mg[][N + 2])// 将记录迷宫信息的数组转化为邻接表
{
	int i, j;
	ArcNode *p;
	G = (ALGraph*)malloc(sizeof(ALGraph));
	for (i = 0; i < M + 2; i++)
		for (j = 0; j < N + 2; j++)
			G->adjlist[i][j].firstarc = NULL;//初始化邻接表
	for (i = 1; i <= M; i++)
		for (j = 1; j <= N; j++)
			if (mg[i][j] == 0)
			{
				if (mg[i-1][j]==0)//依次检测四个格子是否可走
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

void DispAdj(ALGraph *G)//输出邻接表
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

void FindPath(ALGraph *G, int xi, int yi, int xe, int ye, Pathrecord path)//通过深度遍历找到所有路径并打印
{
	ArcNode *p;
	visited[xi][yi] = 1;//置当前格子为已访问
	path.data[path.length].i = xi; path.data[path.length].j = yi;
	path.length++;
	if (xi == xe&&yi == ye)//如果到达终点，则输出路径
	{
		printf("迷宫路径%d:", ++count);
		for (int k = 0; k < path.length; k++)
			printf("(%d,%d)", path.data[k].i, path.data[k].j);
		printf("\n");
	}
	p = G->adjlist[xi][yi].firstarc;
	while (p != NULL)
	{
		if (visited[p->i][p->j] == 0)
			FindPath(G, p->i, p->j, xe, ye, path);//未到达重点且格子未访问时递归调用FindPath函数
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
	};//储存迷宫的矩阵
	CreateList(G, mg);
	printf("迷宫对应的邻接表：\n"); DispAdj(G);
	Pathrecord path;
	path.length = 0;
	printf("所有的迷宫路径：\n");
	FindPath(G, 1, 1, M, N, path);
}