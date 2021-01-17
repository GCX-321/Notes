#include<stdio.h>

int Sort(int arr[],int nBegin,int nEnd)
{
	int temp = arr[nBegin];

	while(nBegin < nEnd)
	{
		//从后向前找比标准值小的
		while(nBegin < nEnd)
		{
			if(arr[nEnd] < temp)
			{
				//放入前面的坑
				arr[nBegin] = arr[nEnd];
				nBegin++;
				break;
			}
			nEnd--;
		}

		//从前向后遍历
		while(nBegin < nEnd)
		{
			if(arr[nBegin] > temp)
			{
				//放入后面的坑
				arr[nEnd] = arr[nBegin];
				nEnd--;
				break;
			}
			nBegin++;
		}
	}

	//标准值放入
	arr[nEnd] = temp;
	return nEnd;
}

int Sort2(int arr[],int nBegin,int nEnd)
{
	int nSmall = nBegin-1;

	for(nBegin;nBegin<nEnd;nBegin++)
	{
		if(arr[nBegin] < arr[nEnd])
		{
			//小区间扩张
			if(++nSmall != nBegin)
			{
				arr[nSmall] = arr[nSmall]^arr[nBegin];
				arr[nBegin] = arr[nSmall]^arr[nBegin];
				arr[nSmall] = arr[nSmall]^arr[nBegin];
			}
		}
	}

	//标准值放入
	if(++nSmall != nEnd)
	{
		arr[nSmall] = arr[nSmall]^arr[nEnd];
		arr[nEnd] = arr[nSmall]^arr[nEnd];
		arr[nSmall] = arr[nSmall]^arr[nEnd];
	}

	return nSmall;
}

void QuickSort(int arr[],int nBegin,int nEnd)
{
	if(arr == NULL || nBegin >= nEnd)return;

	//标准值
	int nStandard;
	nStandard = Sort2(arr,nBegin,nEnd);

	//根据标准值位置将数据分成两部分
	//两部分分别重复以上操作
	QuickSort(arr,nBegin,nStandard-1);
	QuickSort(arr,nStandard+1,nEnd);
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
	QuickSort(arr,0,sizeof(arr)/sizeof(arr[0])-1);
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	return 0;
}
