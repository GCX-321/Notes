#include<stdio.h>

#define LEFT 2*nRootID+1
#define RIGHT 2*nRootID+2

void Adjust(int arr[],int nLength,int nRootID)
{
	while(1)
	{
		//两个孩子
		if(RIGHT < nLength)
		{
			//两个孩子里大的
			if(arr[RIGHT] < arr[LEFT])
			{
				//大的和父亲比较
				if(arr[LEFT] > arr[nRootID])
				{
					//交换
					arr[LEFT] = arr[nRootID]^arr[LEFT];
					arr[nRootID] = arr[nRootID]^arr[LEFT];
					arr[LEFT] = arr[nRootID]^arr[LEFT];

					nRootID = LEFT;
					continue;
				}
				else
				{
					break;
				}
			}
			else
			{
				if(arr[RIGHT] > arr[nRootID])
				{
					arr[RIGHT] = arr[RIGHT]^arr[nRootID];
					arr[nRootID] = arr[RIGHT]^arr[nRootID];
					arr[RIGHT] = arr[RIGHT]^arr[nRootID];

					nRootID = RIGHT;
					continue;
				}
				else
				{
					break;
				}
			}
		}
		//一个孩子
		else if(LEFT < nLength)
		{
			if(arr[LEFT] > arr[nRootID])
			{
				//交换
				arr[LEFT] = arr[nRootID]^arr[LEFT];
				arr[nRootID] = arr[nRootID]^arr[LEFT];
				arr[LEFT] = arr[nRootID]^arr[LEFT];

				nRootID = LEFT;
				continue;
			}
			else
			{
				break;
			}
		}
		//没有孩子
		else
		{
			break;
		}
	}
}

void Adjust2(int arr[],int nLength,int nRootID)
{
	int MAX;

	for(MAX = LEFT;MAX < nLength;MAX = LEFT )
	{
		//两个孩子
		if(RIGHT < nLength)
		{
			//两个孩子里的大值
			if(arr[RIGHT]>arr[MAX])
			{
				MAX = RIGHT;
			}
		}

		//大的和父亲比较
		if(arr[MAX] > arr[nRootID])
		{
			arr[MAX] = arr[nRootID]^arr[MAX];
			arr[nRootID] = arr[nRootID]^arr[MAX];
			arr[MAX] = arr[nRootID]^arr[MAX];

			nRootID = MAX;
		}
		else
		{
			break;
		}
	}
}

void HeapSort(int arr[],int nLength)
{
	if(arr == NULL || nLength <= 0)return;

	int i;

	//建初始堆
	for(i = nLength/2-1;i>=0;i--)
	{
		//调整各个父亲节点
		Adjust2(arr,nLength,i);
	}

	//排序
	for(i = nLength-1;i>0;i--)
	{
		//交换
		arr[0] = arr[i]^arr[0];
		arr[i] = arr[i]^arr[0];
		arr[0] = arr[i]^arr[0];

		//调整堆顶
		Adjust2(arr,i,0);
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
	HeapSort(arr,sizeof(arr)/sizeof(arr[0]));
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	return 0;
}
