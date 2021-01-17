#include<stdio.h>

void SelectSort(int arr[],int nLength)
{
	if(arr == NULL || nLength <= 0)return;
	
	int i;
	int j;
	int nMin;

	for(i = 0;i<nLength-1;i++)
	{
		nMin = i;
		for(j = i+1;j<nLength;j++)
		{
			if(arr[j] < arr[nMin])
			{
				nMin = j;
			}
		}

		//交换 最小值放到对应的位置上
		if(nMin != i)
		{
			arr[nMin] = arr[nMin]^arr[i];
			arr[i] = arr[nMin]^arr[i];
			arr[nMin] = arr[nMin]^arr[i];

		}
	}
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
	SelectSort(arr,sizeof(arr)/sizeof(arr[0]));
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	return 0;
}
