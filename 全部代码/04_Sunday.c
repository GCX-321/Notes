#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int *GetNext(char *match)
{
	int *pNext = NULL;
	pNext = (int*)malloc(sizeof(int)*256);
	memset(pNext,-1,sizeof(int)*256);
	
	//以字符的ASC码值为下标
	int i = 0;
	for(i = 0;i<strlen(match);i++)
	{
		pNext[match[i]] = i;
	}

	return pNext;
}

int Sunday(char *src,char *match)
{
	if(src == NULL || match == NULL)return -1;

	//获得Next数组
	int *pNext = GetNext(match);

	//匹配
	int i = 0;
	int j = 0;
	int k = i;

	while(i < strlen(src)&&j<strlen(match))
	{
		if(src[i] == match[j])
		{
			i++;
			j++;
		}
		else
		{
			//不等
			if(k+strlen(match) < strlen(src))
			{
				i = k+strlen(match)-pNext[src[k+strlen(match)]];
				k = i;
				j = 0;
			}
			else
			{
				return -1;
			}
		}
	}

	if(j == strlen(match))
	{
		return k;
	}
	else
	{
		return -1;
	}
}

int main()
{
	int n = Sunday("awterqabababcaserubcaewgri","abcabc");
	printf("%d\n",n);
	return 0;
}
