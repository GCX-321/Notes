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

typedef struct node1
{
	int nValue;
	struct node1 *pNext;
}MyQueue;

typedef struct queue
{
	int nCount;
	MyQueue *pHead;
	MyQueue *pTail;
}Queue;

void q_Init(Queue **pQueue)
{
	*pQueue = (Queue*)malloc(sizeof(Queue));
	(*pQueue)->nCount = 0;
	(*pQueue)->pHead = NULL;
	(*pQueue)->pTail = NULL;
}

void q_Push(Queue *pQueue,int nNum)
{
	if(pQueue == NULL)exit(1);

	MyQueue *pTemp = NULL;
	pTemp = (MyQueue*)malloc(sizeof(MyQueue));
	pTemp->nValue = nNum;
	pTemp->pNext = NULL;

	//尾添加
	if(pQueue->pHead == NULL)
	{
		pQueue->pHead = pTemp;
	}
	else
	{
		pQueue->pTail->pNext = pTemp;
	}
	pQueue->pTail = pTemp;
	pQueue->nCount++;
}

int q_Pop(Queue *pQueue)
{
	if(pQueue == NULL)exit(1);

	if(pQueue->pHead == NULL)return -1;

	MyQueue *pDel = pQueue->pHead;
	int nNum = pDel->nValue;

	pQueue->pHead = pQueue->pHead->pNext;
	free(pDel);
	pDel = NULL;
	pQueue->nCount--;

	if(pQueue->nCount == 0)
	{
		pQueue->pTail = NULL;
	}
	return nNum;
}

void BFS(Graph *pGraph,int nBegin)
{
	if(pGraph == NULL)return;
	
	Queue *pQueue = NULL;
	q_Init(&pQueue);

	int *pMark = NULL;
	pMark = (int*)malloc(sizeof(int)*pGraph->nVertex);
	memset(pMark,0,sizeof(int)*pGraph->nVertex);

	//起始顶点入队
	q_Push(pQueue,nBegin);
	pMark[nBegin-1] = 1;

	while(pQueue->nCount != 0)
	{
		//弹出 
		nBegin = q_Pop(pQueue);

		//打印
		printf("%d ",nBegin);

		//遍历
		int i;
		for(i = 0;i<pGraph->nVertex;i++)
		{
			//有关的 且未被打印过得
			if(pGraph->pMatrix[(nBegin-1)*pGraph->nVertex+i] == 1 &&
				pMark[i] == 0)
			{
				//入队
				q_Push(pQueue,i+1);

				//标记
				pMark[i] = 1;
			}
		}
	}
	free(pMark);
	pMark = NULL;
}


int main()
{
	Graph *pGraph = NULL;
	pGraph = CreateGraph();
	
	BFS(pGraph,3);
	return 0;
}
