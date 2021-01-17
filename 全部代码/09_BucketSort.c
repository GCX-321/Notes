#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct bucket
{
	int nValue;
	struct bucket *pNext;
}Bucket;

void Sort(Bucket *pHead)
{
	if(pHead == NULL || pHead->pNext == NULL)return;
		
	Bucket *pNode = pHead;
	Bucket *pTemp = NULL;

	while(pNode->pNext != NULL)
	{
		pTemp = pHead;
		while(pTemp->pNext != NULL)
		{
			if(pTemp->nValue > pTemp->pNext->nValue)
			{
				pTemp->nValue = pTemp->nValue ^ pTemp->pNext->nValue;
				pTemp->pNext->nValue = pTemp->nValue ^ pTemp->pNext->nValue;
				pTemp->nValue = pTemp->nValue ^ pTemp->pNext->nValue;
			}
			pTemp = pTemp->pNext;
		}
		pNode = pNode->pNext;
	}
}

void BucketSort(int arr[],int nLength)
{
	if(arr == NULL || nLength <= 0)return;

	//找到最大值 最小值
	int nMax = arr[0];
	int nMin = arr[0];

	int i;
	for(i = 1;i<nLength;i++)
	{
		if(arr[i] >nMax)
		{
			nMax = arr[i];
		}
		if(arr[i] < nMin)
		{
			nMin = arr[i];
		}
	}

	//计算数字位数
	int nNum = nMax;
	int nCount = 1;

	while(nNum)
	{
		nNum/=10;
		nCount*=10;
	}
	nCount/=10;

	int nMinIndex = nMin/nCount;
	int nMaxIndex = nMax/nCount;

	//申请桶
	Bucket **pBucket = (Bucket**)malloc(sizeof(Bucket*)*(nMaxIndex-nMinIndex+1));
	memset(pBucket,0,sizeof(Bucket*)*(nMaxIndex-nMinIndex+1));

	//元素入桶
	Bucket *pTemp = NULL;
	for(i = 0;i<nLength;i++)
	{
		nNum = arr[i]/nCount - nMinIndex;
		pTemp = (Bucket*)malloc(sizeof(Bucket));
		pTemp->nValue = arr[i];
		pTemp->pNext = pBucket[nNum];
		pBucket[nNum] = pTemp;
	}

	//各桶之内进行排序
	for(i = 0;i<nMaxIndex-nMinIndex+1;i++)
	{
		Sort(pBucket[i]);
	}

	//元素放回数组
	nNum = 0;
	for(i = 0;i<nMaxIndex-nMinIndex+1;i++)
	{
		pTemp = pBucket[i];
		while(pTemp)
		{
			arr[nNum] = pTemp->nValue;
			nNum++;
			pTemp = pTemp->pNext;
		}
	}

	//释放
	Bucket *pDel = NULL;
	for(i = 0;i<nMaxIndex-nMinIndex+1;i++)
	{
		pTemp = pBucket[i];
		while(pTemp)
		{
			pDel = pTemp;
			pTemp = pTemp->pNext;
			free(pDel);
			pDel = NULL;
		}
	}

	free(pBucket);
	pBucket = NULL;
}
void Print(int arr[],int nLength)
{
	if(arr == NULL || nLength <= 0)return;

	int i;
	for(i = 0;i<nLength;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
}
int main()
{
	int arr[] = {901,551,244,110,782,591,520,101,587,201};
	BucketSort(arr,sizeof(arr)/sizeof(arr[0]));
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	
	return 0;
}
