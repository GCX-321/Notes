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

typedef struct node
{
	BinaryTree* nValue;
	struct node *pNext;
}MyStack;

typedef struct stack
{
	int nCount;
	MyStack *pTop;
}Stack;

void s_Init(Stack **pStack)
{
	*pStack = (Stack*)malloc(sizeof(Stack));
	(*pStack)->nCount = 0;
	(*pStack)->pTop = NULL;
}

void s_Push(Stack *pStack,BinaryTree* nNum)
{
	if(pStack == NULL)
	{
		printf("栈不存在!\n");
		return;
	}

	MyStack *pTemp = NULL;
	pTemp = (MyStack*)malloc(sizeof(MyStack));
	pTemp->nValue = nNum;

	pTemp->pNext = pStack->pTop;
	pStack->pTop = pTemp;
	pStack->nCount++;
}

BinaryTree* s_Pop(Stack *pStack)
{
	if(pStack == NULL|| pStack->pTop == NULL)return NULL;

	MyStack *pDel = pStack->pTop;
	BinaryTree* nNum = pDel->nValue;

	pStack->pTop = pStack->pTop->pNext;
	free(pDel);
	pDel = NULL;

	pStack->nCount--;
	return nNum;
}

void UnRecPreorderTraversal(BinaryTree *pTree)
{
	if(pTree == NULL)return;

	//栈
	Stack *pStack = NULL;
	s_Init(&pStack);

	while(1)
	{
		while(pTree)
		{
			//打印
			printf("%d ",pTree->nValue);

			//保存
			s_Push(pStack,pTree);

			//向左走
			pTree = pTree->pLeft;
		}

		//弹出
		pTree = s_Pop(pStack);

		if(pTree == NULL)break;

		//右侧
		pTree = pTree->pRight;
	}
}
void UnRecInorderTraversal(BinaryTree *pTree)
{
	if(pTree == NULL)return;

	//栈
	Stack *pStack = NULL;
	s_Init(&pStack);

	while(1)
	{
		while(pTree)
		{
			//保存
			s_Push(pStack,pTree);

			//向左走
			pTree = pTree->pLeft;
		}

		//弹出
		pTree = s_Pop(pStack);

		if(pTree == NULL)break;

		//打印
		printf("%d ",pTree->nValue);

		//右侧
		pTree = pTree->pRight;
	}
}

void UnRecLastorderTraversal(BinaryTree *pTree)
{
	if(pTree == NULL)return;

	Stack *pStack = NULL;
	s_Init(&pStack);
	BinaryTree *pMark = NULL;
	while(1)
	{
		while(pTree)
		{
			s_Push(pStack,pTree);
			pTree = pTree->pLeft;
		}

		if(pStack->pTop == NULL)break;

		//栈顶
		if(pStack->pTop->nValue->pRight == NULL ||pStack->pTop->nValue->pRight == pMark)
		{
			//弹出 标记
			pMark = s_Pop(pStack);

			//打印
			printf("%d ",pMark->nValue);
		}
		else
		{
			pTree = pStack->pTop->nValue->pRight;
		}
	}
}
int main()
{
	BinaryTree *pTree = NULL;
	pTree = CreateBinaryTree();
	UnRecPreorderTraversal(pTree);
	printf("\n");
	UnRecInorderTraversal(pTree);
	printf("\n");
	UnRecLastorderTraversal(pTree);
	printf("\n");
	return 0;
}
