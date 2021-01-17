#include<stdio.h>

void InsertSort(int arr[],int nLength)
{
	if(arr == NULL || nLength <= 0)return;
	
	int i;
	int j;
	int temp;

	//无序元素
	for(i = 1;i<nLength;i++)
	{
		j = i-1;//有序的最后一个元素
		temp = arr[i]; //无序的第一个

		//倒序遍历有序数组
		while(arr[j] > temp && j>=0)
		{
			//向后移动
			arr[j+1] = arr[j];
			j--;
		}

		//值放入
		arr[j+1] = temp;
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
	InsertSort(arr,sizeof(arr)/sizeof(arr[0]));
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	return 0;
}
