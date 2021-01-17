#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void CountSort(int arr[],int nLength)
{
	if(arr == NULL || nLength <= 0)return;
	
	//找最小值最大值
	int nMax,nMin;
	int i;
	nMax = arr[0];
	nMin = arr[0];

	for(i = 1;i<nLength;i++)
	{
		if(arr[i] > nMax)
		{
			nMax = arr[i];
		}
		if(arr[i] < nMin)
		{
			nMin = arr[i];
		}
	}

	//申请计数数组
	int *pCount = NULL;
	pCount = (int*)malloc(sizeof(int)*(nMax-nMin+1));
	memset(pCount,0,sizeof(int)*(nMax-nMin+1));

	//计数
	for(i = 0;i<nLength;i++)
	{
		pCount[arr[i]-nMin]++;
	}

	//放入
	int j = 0;
	for(i = 0;i<nMax-nMin+1;i++)
	{
		//计数非0
		while(pCount[i] != 0)
		{
			arr[j] = i+nMin;
			j++;
			pCount[i]--;
		}
	}

	//释放
	free(pCount);
	pCount = NULL;

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
	CountSort(arr,sizeof(arr)/sizeof(arr[0]));
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	return 0;
}
