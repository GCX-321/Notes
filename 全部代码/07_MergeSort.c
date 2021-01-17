#include<stdio.h>
#include<stdlib.h>

void Merge(int arr[],int nBegin,int nEnd)
{
	int nLow1;
	int nHigh1;
	int nLow2;
	int nHigh2;

	nLow1 = nBegin;
	nHigh1 = nBegin+(nEnd-nBegin)/2;
	nLow2 = nHigh1+1;
	nHigh2 = nEnd;

	int *pTemp = (int*)malloc(sizeof(int)*(nEnd-nBegin+1));
	int i = 0;
	
	//合并
	while(nLow1 <= nHigh1&&nLow2 <= nHigh2)
	{
		if(arr[nLow1] < arr[nLow2])
		{
			pTemp[i] = arr[nLow1];
			i++;
			nLow1++;
		}
		else
		{
			pTemp[i] = arr[nLow2];
			i++;
			nLow2++;
		}
	}

	//将有剩余的数组元素继续放入
	while(nLow1 <= nHigh1)
	{
		pTemp[i]= arr[nLow1];
		i++;
		nLow1++;
	}

	while(nLow2 <= nHigh2)
	{
		pTemp[i] = arr[nLow2];
		i++;
		nLow2++;
	}

	//元素放回原数组
	for(i = 0;i<nEnd-nBegin+1;i++)
	{
		arr[nBegin+i] = pTemp[i];
	}

	free(pTemp);
	pTemp = NULL;
}
void MergeSort(int arr[],int nBegin,int nEnd)
{
	if(arr == NULL || nBegin >= nEnd)return;

	int nMid;
	nMid = nBegin+(nEnd-nBegin)/2;

	//两部分
	MergeSort(arr,nBegin,nMid);
	MergeSort(arr,nMid+1,nEnd);

	//合并
	Merge(arr,nBegin,nEnd);
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
	int arr[] = {8,2,1,9,5,10,3,22,11};
	MergeSort(arr,0,sizeof(arr)/sizeof(arr[0])-1);
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	return 0;
}
