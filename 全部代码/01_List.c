#include<stdio.h>
#include<stdlib.h>

typedef struct list
{
	int nValue;
	struct list *pNext;
}List;

List *CreateList()
{
	int nCount;
	int nNum;
	List *pHead = NULL;
	List *pTail = NULL;

	printf("请输入链表节点个数:\n");
	scanf("%d",&nCount);

	List *pTemp = NULL;
	while(nCount)
	{
		scanf("%d",&nNum);
		pTemp = (List*)malloc(sizeof(List));
		pTemp->nValue = nNum;
		pTemp->pNext = NULL;

		//空
		if(pHead == NULL)
		{
			pHead = pTemp;
		}
		else
		{
			pTail->pNext = pTemp;
		}
		pTail = pTemp;
		nCount--;
	}

	return pHead;
}

void Print(List *pHead)
{
	while(pHead)
	{
		printf("%d ",pHead->nValue);
		pHead = pHead->pNext;
	}
	printf("\n");
}

void RePrint(List *pHead)
{
	if(pHead == NULL)return;

	//处理下一个
	RePrint(pHead->pNext);

	//打印当前节点
	printf("%d ",pHead->nValue);
}

List *Reverse(List *pHead)
{
	if(pHead == NULL || pHead->pNext == NULL)return pHead;

	List *p1 = NULL;
	List *p2 = pHead;
	List *p3 = pHead->pNext;

	while(p3 != NULL)
	{
		p2->pNext = p1;

		//指针移动
		p1 = p2;
		p2 = p3;
		p3 = p3->pNext;
	}

	p2->pNext = p1;
	return p2;
}

int main()
{
	List *pHead = NULL;
	pHead = CreateList();
	Print(pHead);
	RePrint(pHead);
	printf("\n");
	pHead = Reverse(pHead);
	Print(pHead);
	return 0;
}
