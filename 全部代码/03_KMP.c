#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int *GetNext(char *match)
{
	int *pNext = NULL;
	pNext = (int*)malloc(sizeof(int)*strlen(match));

	pNext[0] = 0;

	int i = 1;
	int j = i-1;

	while(i < strlen(match))
	{
		if(match[i] == match[pNext[j]])
		{
			pNext[i] = pNext[j]+1;
			i++;
			j = i-1;
		}
		else if(pNext[j] == 0)
		{
			pNext[i] = 0;
			i++;
			j = i-1;
		}
		else
		{
			j = pNext[j]-1;
		}
	}

	return pNext;
}

int KMP(char *src,char *match)
{
	if(src == NULL || match == NULL)return -1;

	//获得next数组
	int *pNext = GetNext(match);

	//匹配
	int i = 0;
	int j = 0;

	while(i < strlen(src)&&j<strlen(match))
	{
		if(src[i] == match[j])
		{
			i++;
			j++;
		}
		else
		{
			//匹配串跳转
			if(j == 0)
			{
				//匹配串到头了 主串向后移动
				i++;
			}
			else
			{
				j = pNext[j-1];
			}
		}
	}
	
	//匹配串走完 匹配成功
	if(j == strlen(match))
	{
		return i-j;
	}
	else
	{
		//失败
		return -1;
	}
}

int main()
{
	int n = KMP("ag","abcabcd");
	printf("%d\n",n);
	return 0;
}
