#include<stdio.h>
#include<stdlib.h>

typedef struct bst
{
	int nValue;
	struct bst *pLeft;
	struct bst *pRight;
}BST;

void AddNode(BST **pTree,int nNum)
{
	BST *pTemp = NULL;
	pTemp = (BST*)malloc(sizeof(BST));
	pTemp->nValue = nNum;
	pTemp->pLeft = NULL;
	pTemp->pRight = NULL;

	//空树
	if(*pTree == NULL)
	{
		*pTree = pTemp;
		return;
	}

	//遍历 添加
	BST *pNode = *pTree;
	while(pNode)
	{
		if(pNode->nValue > nNum)
		{
			//左侧
			if(pNode->pLeft == NULL)
			{
				pNode->pLeft = pTemp;
				return;
			}
			pNode = pNode->pLeft;
		}
		else if(pNode->nValue < nNum)
		{
			//右侧
			if(pNode->pRight == NULL)
			{
				pNode->pRight = pTemp;
				return;
			}
			pNode = pNode->pRight;
		}
		else
		{
			//相等
			printf("data errpr.\n");
			free(pTemp);
			pTemp = NULL;
			return;
		}
	}
}

BST *CreateBST(int arr[],int nLength)
{
	if(arr == NULL || nLength <= 0)return NULL;

	int i;
	BST *pTree = NULL;
	for(i = 0;i<nLength;i++)
	{
		//添加节点
		AddNode(&pTree,arr[i]);
	}

	return pTree;
}

void Traversal(BST *pTree)
{
	if(pTree == NULL)return;
	Traversal(pTree->pLeft);
	printf("%d ",pTree->nValue);
	Traversal(pTree->pRight);
}

void BSTToList(BST *pTree,BST **pHead,BST **pTail)
{
	if(pTree == NULL)return;

	//左
	BSTToList(pTree->pLeft,pHead,pTail);

	//节点添加
	if(*pHead == NULL)
	{
		*pHead = pTree;
	}
	else
	{
		(*pTail)->pRight = pTree;
		pTree->pLeft = *pTail;
	}
	*pTail = pTree;

	//右
	BSTToList(pTree->pRight,pHead,pTail);
}

void Print(BST *pHead)
{
	while(pHead)
	{
		printf("%d ",pHead->nValue);
		pHead = pHead->pRight;
	}
	printf("\n");
}

int main()
{
	int arr[] = {10,1,99,2,18,27,35,16,3,5};
	BST *pTree = NULL;
	pTree = CreateBST(arr,sizeof(arr)/sizeof(arr[0]));
	Traversal(pTree);
	printf("\n");
	BST *pHead = NULL;
	BST *pTail = NULL;
	BSTToList(pTree,&pHead,&pTail);
	Print(pHead);
	return 0;
}
