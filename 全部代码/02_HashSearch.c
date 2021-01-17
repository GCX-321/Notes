#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct hash
{
	int nValue;
	struct hash *pNext;
}Hash;

Hash **CreateHashTable(int arr[],int nLength)
{
	if(arr == NULL || nLength <= 0)return NULL;

	Hash **pHash = NULL;

	//表头
	pHash = (Hash**)malloc(sizeof(Hash*)*nLength);
	memset(pHash,0,sizeof(Hash*)*nLength);

	//元素入表
	int i;
	int nIndex;
	Hash *pTemp = NULL;
	for(i = 0;i<nLength;i++)
	{
		pTemp = (Hash*)malloc(sizeof(Hash));
		pTemp->nValue = arr[i];
		
		nIndex = arr[i]%nLength;
		//头添加
		pTemp->pNext = pHash[nIndex];
		pHash[nIndex] = pTemp;
	}

	return pHash;
}

void HashSearch(Hash **pHash,int nLength,int nNum)
{
	if(pHash == NULL)return;

	int nIndex = nNum%nLength;

	//遍历链表
	Hash *pTemp = pHash[nIndex];
	while(pTemp)
	{
		if(pTemp->nValue == nNum)
		{
			printf("%d\n",pTemp->nValue);
		}
		pTemp = pTemp->pNext;
	}
}

int main()
{
	int arr[] = {18,999,26,1,87,53,276,110,561,8};
	Hash **pHash = CreateHashTable(arr,sizeof(arr)/sizeof(arr[0]));
	HashSearch(pHash,sizeof(arr)/sizeof(arr[0]),29);
	return 0;
}
