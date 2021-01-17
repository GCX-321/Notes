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

void Search(BST *pTree,BST **pDel,BST **pFather,int nNum)
{
	while(pTree)
	{
		if(pTree->nValue == nNum)
		{
			*pDel = pTree;
			return;
		}
		else if(pTree->nValue > nNum)
		{
			//左侧
			*pFather = pTree;
			pTree = pTree->pLeft;
		}
		else
		{
			//右侧
			*pFather = pTree;
			pTree = pTree->pRight;
		}
	}

	*pFather = NULL;
}

void DelNode(BST **pTree,int nNum)
{
	if(*pTree == NULL)return;

	//查找
	BST *pDel = NULL;
	BST *pFather = NULL;
	Search(*pTree,&pDel,&pFather,nNum);

	//情况分析
	if(pDel == NULL)return;

	//两个孩子
	BST *pMark = NULL;
	if(pDel->pLeft != NULL && pDel->pRight != NULL)
	{
		pMark = pDel;

		//左的最右
		//向左走一步
		pFather = pDel;
		pDel = pDel->pLeft;
		//最右
		while(pDel->pRight != NULL)
		{
			pFather = pDel;
			pDel = pDel->pRight;
		}

		//值覆盖
		pMark->nValue = pDel->nValue;
	}

	//0个或1个孩子
	//根
	if(pFather == NULL)
	{
		//换根
		*pTree = pDel->pLeft ? pDel->pLeft : pDel->pRight;
		free(pDel);
		pDel = NULL;
		return;
	}

	//非根
	if(pDel == pFather->pLeft)
	{
		pFather->pLeft = pDel->pLeft?pDel->pLeft:pDel->pRight;
	}
	else
	{
		pFather->pRight = pDel->pLeft?pDel->pLeft:pDel->pRight;
	}
	free(pDel);
	pDel = NULL;
}

int main()
{
	int arr[] = {10,1,99,2,18,27,35,16,3,5};
	BST *pTree = NULL;
	pTree = CreateBST(arr,sizeof(arr)/sizeof(arr[0]));
	Traversal(pTree);
	printf("\n");
	DelNode(&pTree,1);
	Traversal(pTree);
	return 0;
}
