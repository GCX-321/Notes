#include<stdio.h>

void BubbleSort(int arr[],int nLength)
{
	if(arr == NULL || nLength <= 0)return;

	int i;
	int j;
	int nflag;
	int nCount = 0;
	for(i = 0;i<nLength-1;i++)
	{
		nflag = 0;
		for(j = 0;j<nLength-1-i;j++)
		{
			if(arr[j] > arr[j+1])
			{
				arr[j] = arr[j]^arr[j+1];
				arr[j+1] = arr[j]^arr[j+1];
				arr[j] = arr[j]^arr[j+1];
				nflag = j+1;
			}
			nCount++;
		}

		if(nflag == 0)break;
		i = nLength-nflag-1;
	}
	printf("%d\n",nCount);
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
	int arr[] = {8,2,1,9,5,10,23,22,29};
	BubbleSort(arr,sizeof(arr)/sizeof(arr[0]));
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	return 0;
}
