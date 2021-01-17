#include<stdio.h>

void ShellSort(int arr[],int nLength)
{
	if(arr == NULL || nLength <= 0)return;
	
	int nGap;
	int i;
	int j;
	int k;
	int temp;

	//间隔
	for(nGap = nLength/2;nGap>=1;nGap/=2)
	{
		//组
		for(i = 0;i<nGap;i++)
		{
			//各组之内插入排序
			for(j = i+nGap;j<nLength;j+=nGap)
			{
				k = j-nGap;
				temp = arr[j];

				while(temp < arr[k] && k>=i)
				{
					arr[k+nGap] = arr[k];
					k-=nGap;
				}

				arr[k+nGap] = temp;
			}
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
	ShellSort(arr,sizeof(arr)/sizeof(arr[0]));
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	return 0;
}
