#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct radix
{
	int nValue;
	struct radix *pNext;
}Radix;

void Sort(int arr[],int nLength,int nBegin,Radix **pRadix)
{
	//计算计数
	int nBase = 1;

	while(nBegin > 1)
	{
		nBase*=10;
		nBegin--;
	}

	int i;
	Radix *pTemp = NULL;
	int nIndex;
	Radix *pNode = NULL;
	for(i = 0;i<nLength;i++)
	{
		nIndex = arr[i]/nBase%10;

		pTemp = (Radix*)malloc(sizeof(Radix));
		pTemp->nValue = arr[i];
		pTemp->pNext = NULL;

		//尾添加
		if(pRadix[nIndex] == NULL)
		{
			pRadix[nIndex] = pTemp;
		}
		else
		{
			pNode = pRadix[nIndex];
			while(pNode->pNext != NULL)
			{
				pNode = pNode->pNext;
			}

			pNode->pNext = pTemp;
		}
	}

	//放回原数组
	nBegin = 0;
	for(i = 0;i<10;i++)
	{
		pTemp = pRadix[i];
		while(pTemp)
		{
			arr[nBegin] = pTemp->nValue;
			nBegin++;
			pTemp = pTemp->pNext;
		}
	}

	//释放
	for(i = 0;i<10;i++)
	{
		pTemp = pRadix[i];
		while(pTemp)
		{
			pNode = pTemp;
			pTemp = pTemp->pNext;
			free(pNode);
			pNode = NULL;
		}
	}

	memset(pRadix,0,sizeof(Radix*)*10);
}

void RadixSort(int arr[],int nLength)
{
	if(arr == NULL || nLength <= 0)return;
	
	//最大值
	int nMax = arr[0];
	int i;
	for(i = 1;i<nLength;i++)
	{
		if(arr[i] > nMax)
		{
			nMax = arr[i];
		}
	}

	//最大值位数
	int nLooptimes = 0;
	while(nMax)
	{
		nMax/=10;
		nLooptimes++;
	}
	
	//桶
	Radix **pRadix = NULL;
	pRadix = (Radix**)malloc(sizeof(Radix*)*10);
	memset(pRadix,0,sizeof(Radix*)*10);

	//按位处理
	for(i = 1;i<=nLooptimes;i++)
	{
		Sort(arr,nLength,i,pRadix);
	}
	
	//释放
	free(pRadix);
	pRadix = NULL;
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
	int arr[] = {18,92,331,109,315,1770,2003,122,101};
	RadixSort(arr,sizeof(arr)/sizeof(arr[0]));
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	return 0;
}
