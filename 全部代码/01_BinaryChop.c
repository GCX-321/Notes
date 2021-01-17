#include<stdio.h>

int BinaryChop(int arr[],int nLength,int nNum)
{
	if(arr == NULL || nLength <= 0)return -1;

	int nBegin = 0;
	int nEnd = nLength-1;
	int nMid;

	while(nBegin <= nEnd)
	{
		nMid = nBegin + (nEnd-nBegin)/2;

		if(arr[nMid] == nNum)
		{
			return nMid;
		}
		else if(arr[nMid] > nNum)
		{
			//左侧
			nEnd = nMid-1;
		}
		else
		{
			//右侧
			nBegin = nMid+1;
		}
	}

	return -1;
}

int main()
{
	int arr[] = {1,2,3,5,6,8,10};
	int n = BinaryChop(arr,sizeof(arr)/sizeof(arr[0]),7);
	printf("%d\n",n);
	return 0;
}
