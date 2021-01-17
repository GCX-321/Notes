#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct trie
{
	int nCount;
	struct trie *pCharacter[26];
	char *str;
}TrieTree;

TrieTree *GetNode()
{
	TrieTree *pTemp = NULL;
	pTemp = (TrieTree*)malloc(sizeof(TrieTree));
	memset(pTemp,0,sizeof(TrieTree));
	return pTemp;
}

void AddWord(TrieTree *pTree,char *str)
{
	int i = 0;
	while(i < strlen(str))
	{
		if(pTree->pCharacter[str[i]-97] == NULL)
		{
			pTree->pCharacter[str[i]-97] = GetNode();
		}
		pTree = pTree->pCharacter[str[i]-97];
	 	i++;
	}

	//末尾标志
	pTree->nCount++;
	pTree->str = str;
}

TrieTree *CreateTrieTree(char *str[],int nLength)
{
	if(str == NULL || nLength <= 0)return NULL;

	//根
	TrieTree *pRoot = NULL;
	pRoot = GetNode();

	//单词添加
	int i;
	for(i = 0;i<nLength;i++)
	{
		AddWord(pRoot,str[i]);
	}

	return pRoot;
}

void Search(TrieTree *pTree,char *str)
{
	if(pTree == NULL || str == NULL)return;

	int i = 0;
	while(i < strlen(str))
	{
		if(pTree->pCharacter[str[i]-97] == NULL)
		{
			printf("failed TAT.\n");
			return;
		}
		pTree = pTree->pCharacter[str[i]-97];
		i++;
	}

	//检测末尾标志
	if(pTree->nCount != 0)
	{
		printf("%s\n",pTree->str);
	}
	else
	{
		printf("failed QAQ.\n");
		return;
	}
}

void Traversal(TrieTree *pTree)
{
	if(pTree == NULL)return;

	if(pTree->nCount != 0)
	{
		printf("%s\n",pTree->str);
	}

	int i;
	for(i = 0;i<26;i++)
	{
		Traversal(pTree->pCharacter[i]);
	}
}

int main()
{
	char *str[] = {"apple","lemon","orange","ice","icecream","peach","banana"};
	TrieTree *pTree = CreateTrieTree(str,7);
	Traversal(pTree);
	Search(pTree,"watermelon");
	return 0;
}
