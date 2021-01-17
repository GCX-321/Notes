#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct graph
{
	int nVertex;
	int nEdge;
	int *pMatrix;
}Graph;

Graph *CreateGraph()
{
	int nV;
	int nE;
	printf("请输入顶点个数与边的数目:\n");
	scanf("%d%d",&nV,&nE);

	//申请空间
	Graph *pGraph = NULL;
	pGraph = (Graph*)malloc(sizeof(Graph));
	pGraph->nVertex = nV;
	pGraph->nEdge = nE;

	//矩阵
	pGraph->pMatrix = (int*)malloc(sizeof(int)*nV*nV);
	memset(pGraph->pMatrix,0,sizeof(int)*nV*nV);
	
	//边
	int i;
	int v1,v2;
	for(i = 0;i<nE;i++)
	{
		printf("请输入两个顶点确定一条边:\n");
		scanf("%d%d",&v1,&v2);

		if(v1 >= 1 && v1 <= nV && v2 >= 1 && v2 <= nV && v1 != v2 &&
			pGraph->pMatrix[(v1-1)*nV+(v2-1)] == 0)
		{
			pGraph->pMatrix[(v1-1)*nV+(v2-1)] = 1;
			pGraph->pMatrix[(v2-1)*nV+(v1-1)] = 1;
		}
		else
		{
			i--;
		}
	}
	
	return pGraph;
}

void MyDFS(Graph *pGraph,int nBegin,int *pMark)
{
	//打印
	printf("%d ",nBegin);

	//标记
	pMark[nBegin-1] = 1;

	//遍历
	int i;
	for(i = 0;i<pGraph->nVertex;i++)
	{
		//有关的 且未被打印的
		if(pGraph->pMatrix[(nBegin-1)*pGraph->nVertex+i] == 1 && pMark[i] == 0)
		{
			MyDFS(pGraph,i+1,pMark);
		}
	}
}

void DFS(Graph *pGraph,int nBegin)
{
	if(pGraph == NULL)return;

	//标记数组
	int *pMark = NULL;
	pMark = (int*)malloc(sizeof(int)*pGraph->nVertex);
	memset(pMark,0,sizeof(int)*pGraph->nVertex);
	
	//节点处理
	MyDFS(pGraph,nBegin,pMark);
}

int main()
{
	Graph *pGraph = NULL;
	pGraph = CreateGraph();
	
	DFS(pGraph,2);
	return 0;
}
