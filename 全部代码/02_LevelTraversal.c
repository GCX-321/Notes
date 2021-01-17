#include<stdio.h>
#include<stdlib.h>

typedef struct tree
{
	int nValue;
	struct tree *pLeft;
	struct tree *pRight;
}BinaryTree;

BinaryTree *CreateBinaryTree()
{
	BinaryTree *pRoot = NULL;

	//根
	pRoot = (BinaryTree*)malloc(sizeof(BinaryTree));
	pRoot->nValue = 1;

	//左
	pRoot->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
	pRoot->pLeft->nValue = 2;

	//左的左
	pRoot->pLeft->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
	pRoot->pLeft->pLeft->nValue = 4;
	pRoot->pLeft->pLeft->pLeft = NULL;
	pRoot->pLeft->pLeft->pRight = NULL;

	//左的右
	pRoot->pLeft->pRight = (BinaryTree*)malloc(sizeof(BinaryTree));
	pRoot->pLeft->pRight->nValue = 5;
	pRoot->pLeft->pRight->pLeft = NULL;
	pRoot->pLeft->pRight->pRight = NULL;

	//右
	pRoot->pRight = (BinaryTree*)malloc(sizeof(BinaryTree));
	pRoot->pRight->nValue = 3;
	pRoot->pRight->pLeft = NULL;
	pRoot->pRight->pRight = NULL;

	return pRoot;
}

typedef struct node1
{
	BinaryTree* nValue;
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

void q_Push(Queue *pQueue,BinaryTree* nNum)
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

BinaryTree* q_Pop(Queue *pQueue)
{
	if(pQueue == NULL)exit(1);

	if(pQueue->pHead == NULL)return NULL;

	MyQueue *pDel = pQueue->pHead;
	BinaryTree* nNum = pDel->nValue;

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

int q_IsEmpty(Queue *pQueue)
{
	if(pQueue == NULL)exit(1);

	return pQueue->nCount == 0?1:0;
}

void LevelTraversal(BinaryTree *pTree)
{
	if(pTree == NULL)return;

	//队列
	Queue *pQueue = NULL;
	q_Init(&pQueue);

	//根入队
	q_Push(pQueue,pTree);

	while(!q_IsEmpty(pQueue))
	{
		//弹出 
		pTree = q_Pop(pQueue);

		//打印
		printf("%d ",pTree->nValue);

		//非空左右入队
		if(pTree->pLeft != NULL)
		{
			q_Push(pQueue,pTree->pLeft);
		}
		if(pTree->pRight != NULL)
		{
			q_Push(pQueue,pTree->pRight);
		}
	}
}
int main()
{
	BinaryTree *pTree = CreateBinaryTree();
	LevelTraversal(pTree);
	printf("\n");
	return 0;
}
