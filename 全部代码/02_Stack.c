#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int nValue;
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

void s_Push(Stack *pStack,int nNum)
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

int s_Pop(Stack *pStack)
{
	if(pStack == NULL|| pStack->pTop == NULL)return -1;

	MyStack *pDel = pStack->pTop;
	int nNum = pDel->nValue;

	pStack->pTop = pStack->pTop->pNext;
	free(pDel);
	pDel = NULL;

	pStack->nCount--;
	return nNum;
}

void s_Clear(Stack *pStack)
{
	if(pStack == NULL)exit(1);

	while(pStack->nCount != 0 )
	{
		s_Pop(pStack);
	}
}

void s_Destroy(Stack **pStack)
{
	s_Clear(*pStack);
	free(*pStack);
	*pStack = NULL;
}

int s_GetCount(Stack *pStack)
{
	if(pStack == NULL)exit(1);

	return pStack->nCount;
}

MyStack *s_GetTop(Stack *pStack)
{
	if(pStack == NULL)exit(1);

	return pStack->pTop;
}

int s_IsEmpty(Stack *pStack)
{
	if(pStack == NULL)exit(1);

	return pStack->nCount == 0?1:0;
}

int  main()
{
	Stack *pStack = NULL;

	s_Init(&pStack);
	s_Push(pStack,1);
	s_Push(pStack,2);
	s_Push(pStack,3);
	s_Push(pStack,4);

	printf("%d\n",s_Pop(pStack));
	printf("%d\n",s_Pop(pStack));
	printf("%d\n",s_Pop(pStack));
	printf("%d\n",s_Pop(pStack));

	s_Destroy(&pStack);
	s_Push(pStack,100);
	return 0;
}
