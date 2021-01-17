#include<stdio.h>
#include<stdlib.h>

enum COLOR{RED,BLACK};

typedef struct tree
{
	int nValue;
	int nColor;
	struct tree *pLeft;
	struct tree *pRight;
	struct tree *pFather;
}RBT;

RBT *pRBT = NULL;

void RightRotate(RBT **pTree)
{
	if(*pTree == NULL || (*pTree)->pLeft == NULL)return;

	RBT *pNode = *pTree;  //A
	RBT *pMark = pNode->pLeft; //B

	//三个孩子关系
	pNode->pLeft = pMark->pRight;
	pMark->pRight = pNode;

	if(pNode->pFather != NULL)
	{
		if(pNode == pNode->pFather->pLeft)
		{
			pNode->pFather->pLeft = pMark;
		}
		else
		{
			pNode->pFather->pRight = pMark;
		}
	}
	else
	{
		//根
		pRBT = pMark;
	}

	//三个父亲关系
	if(pNode->pLeft != NULL)
	{
		pNode->pLeft->pFather = pNode;
	}

	pMark->pFather = pNode->pFather;
	pNode->pFather = pMark;
}
void LeftRotate(RBT **pTree)
{
	if(*pTree == NULL || (*pTree)->pRight == NULL)return;

	RBT *pNode = *pTree;  //A
	RBT *pMark = pNode->pRight; //B

	//三个孩子关系
	pNode->pRight = pMark->pLeft;
	pMark->pLeft = pNode;

	if(pNode->pFather != NULL)
	{
		if(pNode == pNode->pFather->pLeft)
		{
			pNode->pFather->pLeft = pMark;
		}
		else
		{
			pNode->pFather->pRight = pMark;
		}
	}
	else
	{
		//根
		pRBT = pMark;
	}

	//三个父亲关系
	if(pNode->pRight != NULL)
	{
		pNode->pRight->pFather = pNode;
	}

	pMark->pFather = pNode->pFather;
	pNode->pFather = pMark;
}

RBT *FindNode(RBT *pTree,int nNum)
{
	if(pTree == NULL)return NULL;

	while(pTree)
	{
		if(pTree->nValue > nNum)
		{
			if(pTree->pLeft == NULL)
			{
				return pTree;
			}
			pTree = pTree->pLeft;
		}
		else if(pTree->nValue < nNum)
		{
			if(pTree->pRight == NULL)
			{
				return pTree;
			}
			pTree = pTree->pRight;
		}
		else
		{
			//相等
			printf("data error.\n");
			exit(1);
		}
	}
}

RBT *GetUncle(RBT *pNode)
{
	if(pNode == pNode->pFather->pLeft)
	{
		return pNode->pFather->pRight;
	}
	else
	{
		return pNode->pFather->pLeft;
	}
}

void AddNode(RBT *pTree,int nNum)
{
	//查找
	RBT *pNode = NULL;
	pNode = FindNode(pTree,nNum);
	
	RBT *pTemp = NULL;
	pTemp = (RBT*)malloc(sizeof(RBT));
	pTemp->nValue = nNum;
	pTemp->nColor = RED;
	pTemp->pLeft = NULL;
	pTemp->pRight = NULL;
	pTemp->pFather = pNode;

	//1.空树
	if(pNode == NULL)
	{
		pRBT = pTemp;
		pRBT->nColor = BLACK;
		return;
	}

	//非空树 节点放入树中
	if(nNum < pNode->nValue)
	{
		pNode->pLeft = pTemp;
	}
	else
	{
		pNode->pRight = pTemp;
	}

	//2.父亲是黑的
	if(pNode->nColor == BLACK)
	{
		return;
	}

	//3.父亲是红的
	RBT *pUncle = NULL;
	RBT *pGrandFather = NULL;

	while(pNode->nColor == RED)
	{
		pGrandFather = pNode->pFather;
		pUncle = GetUncle(pNode);

		//3.1叔叔是红的
		if(pUncle != NULL && pUncle->nColor == RED)
		{
			pUncle->nColor = BLACK;
			pNode->nColor = BLACK;
			pGrandFather->nColor = RED;

			pTemp = pGrandFather;
			pNode = pTemp->pFather;

			//根
			if(pNode == NULL)
			{
				pRBT->nColor = BLACK;
				break;
			}
			continue;
		}

		//3.2叔叔是黑的
		if(pUncle == NULL || pUncle->nColor == BLACK)
		{
			//3.2.1父亲是爷爷的左
			if(pNode == pGrandFather->pLeft)
			{
				//3.2.1.1当前节点是父亲的右
				if(pTemp == pNode->pRight)
				{
					pTemp = pNode;

					LeftRotate(&pTemp);

					pNode = pTemp->pFather;
				}

				//3.2.1.2当前节点是父亲的左
				if(pTemp == pNode->pLeft)
				{
					pNode->nColor = BLACK;
					pGrandFather->nColor = RED;

					RightRotate(&pGrandFather);
					break;
				}
			}

			//3.2.2父亲是爷爷的右
			if(pNode == pGrandFather->pRight)
			{
				//3.2.2.1当前节点是父亲的左
				if(pTemp == pNode->pLeft)
				{
					pTemp = pNode;

					RightRotate(&pTemp);

					pNode = pTemp->pFather;
				}

				//3.2.2.2当前节点是父亲的右
				if(pTemp == pNode->pRight)
				{
					pNode->nColor = BLACK;
					pGrandFather->nColor = RED;

					LeftRotate(&pGrandFather);
					break;
				}
			}
		}
	}
}


void CreateRBT(int arr[],int nLength)
{
	if(arr == NULL || nLength <= 0)return;

	int i;
	for(i = 0;i<nLength;i++)
	{
		AddNode(pRBT,arr[i]);
	}
}

RBT* Search(RBT *pTree,int nNum)
{
	if(pTree == NULL)return NULL;

	while(pTree)
	{
		if(pTree->nValue == nNum)
		{
			return pTree;
		}
		else if(pTree->nValue > nNum)
		{
			pTree = pTree->pLeft;
		}
		else
		{
			pTree = pTree->pRight;
		}
	}
}

void DelNode(RBT *pTree,int nNum)
{
	//查找
	RBT *pTemp = NULL;
	
	pTemp = Search(pTree,nNum);

	if(pTemp == NULL)return;

	//两个孩子
	RBT *pMark = NULL;
	if(pTemp->pLeft != NULL && pTemp->pRight != NULL)
	{
		pMark = pTemp;

		//左的最右
		pTemp = pTemp->pLeft;
		while(pTemp->pRight != NULL)
		{
			pTemp = pTemp->pRight;
		}

		//值覆盖
		pMark->nValue = pTemp->nValue;
	}

	//颜色情况
	RBT *pNode = pTemp->pFather;

	//1.根 且无孩子
	if(pNode == NULL && pTemp->pLeft == NULL && pTemp->pRight == NULL)
	{
		free(pTemp);
		pTemp = NULL;
		pRBT = NULL;
		return;
	}

	//2.根 有一个红孩子
	if(pNode == NULL && (pTemp->pLeft != NULL || pTemp->pRight != NULL))
	{
		pRBT = pTemp->pLeft ? pTemp->pLeft : pTemp->pRight;
		pRBT->nColor = BLACK;
		pRBT->pFather = NULL;

		free(pTemp);
		pTemp = NULL;
		return;
	}

	//3.非根 是红色
	if(pTemp->nColor == RED)
	{
		if(pTemp == pNode->pLeft)
		{
			pNode->pLeft = NULL;
		}
		else
		{
			pNode->pRight = NULL;
		}

		free(pTemp);
		pTemp = NULL;
		return;
	}

	//4.非根 黑色 且有一个红孩子
	if(pTemp->nColor == BLACK && (pTemp->pLeft != NULL || pTemp->pRight != NULL))
	{
		if(pTemp == pNode->pLeft)
		{
			pNode->pLeft = pTemp->pLeft ? pTemp->pLeft : pTemp->pRight;
			pNode->pLeft->pFather = pNode;
			pNode->pLeft->nColor = BLACK;
		}
		else
		{
			pNode->pRight = pTemp->pLeft ? pTemp->pLeft :pTemp->pRight;
			pNode->pRight->pFather = pNode;
			pNode->pRight->nColor = BLACK;
		}
		free(pTemp);
		pTemp = NULL;
		return;
	}

	//5.非根 黑色 且无孩子
	RBT *pBrother = NULL;
	pBrother = GetUncle(pTemp);

	//假删除
	if(pTemp == pNode->pLeft)
	{
		pNode->pLeft = NULL;
	}
	else
	{
		pNode->pRight = NULL;
	}

	pMark = pTemp;

	while(1)
	{
		//5.1兄弟是红
		if(pBrother->nColor == RED)
		{
			pNode->nColor = RED;
			pBrother->nColor = BLACK;
			
			//5.1.1兄弟是父亲的左
			if(pBrother == pNode->pLeft)
			{
				RightRotate(&pNode);

				pBrother = pNode->pLeft;
				continue;
			}

			//5.1.2兄弟是父亲的右
			if(pBrother == pNode->pRight)
			{
				LeftRotate(&pNode);

				pBrother = pNode->pRight;
				continue;
			}
		}

		//5.2兄弟是黑色
		if(pBrother->nColor == BLACK)
		{
			//5.2.1两个侄子全黑
			if((pBrother->pLeft == NULL && pBrother->pRight == NULL)||
				((pBrother->pLeft != NULL && pBrother->pLeft->nColor == BLACK)&&
				(pBrother->pRight != NULL && pBrother->pRight->nColor == BLACK)))
			{
				//5.2.1.1父亲是红色
				if(pNode->nColor == RED)
				{
					pBrother->nColor = RED;
					pNode->nColor = BLACK;
					break;
				}

				//5.2.1.2父亲是黑色
				if(pNode->nColor == BLACK)
				{
					pBrother->nColor = RED;

					pTemp = pNode;
					pNode = pTemp->pFather;

					if(pNode == NULL)
					{
						break;
					}
					pBrother = GetUncle(pTemp);
					continue;
				}
			}

			//5.2.2左侄子红 右侄子黑
			if((pBrother->pLeft != NULL && pBrother->pLeft->nColor == RED)&&
				(pBrother->pRight == NULL || pBrother->pRight->nColor == BLACK))
			{
				//5.2.2.1兄弟是父亲的右
				if(pBrother== pNode->pRight)
				{
					pBrother->nColor = RED;
					pBrother->pLeft->nColor = BLACK;

					RightRotate(&pBrother);

					pBrother = pNode->pRight;
					continue;
				}

				//5.2.2.2兄弟是父亲的左
				if(pBrother == pNode->pLeft)
				{
					pBrother->nColor = pNode->nColor;
					pNode->nColor = BLACK;
					pBrother->pLeft->nColor = BLACK;

					RightRotate(&pNode);
					break;
				}
			}

			//5.2.3右侄子红
			if(pBrother->pRight != NULL && pBrother->pRight->nColor == RED)
			{
				//5.2.3.1兄弟是父亲的左
				if(pBrother == pNode->pLeft)
				{
					pBrother->nColor = RED;
					pBrother->pRight->nColor = BLACK;

					LeftRotate(&pBrother);
					pBrother = pNode->pLeft;
					continue;
				}

				//5.2.3.2兄弟是父亲的右
				if(pBrother == pNode->pRight)
				{
					pBrother->nColor = pNode->nColor;
					pNode->nColor = BLACK;
					pBrother->pRight->nColor = BLACK;

					LeftRotate(&pNode);
					break;
				}
			}
		}
	}
	
	free(pMark);
	pMark = NULL;
}

void Traversal(RBT *pTree)
{
	if(pTree == NULL)return;

	printf("val == %d\tcol == %d\n",pTree->nValue,pTree->nColor);

	Traversal(pTree->pLeft);
	Traversal(pTree->pRight);
}

int main()
{
	int arr[] = {11,2,14,1,7,15,5,8};
	CreateRBT(arr,sizeof(arr)/sizeof(arr[0]));
	Traversal(pRBT);
	printf("=============================\n");
	/*AddNode(pRBT,4);
	Traversal(pRBT);
	*/
	DelNode(pRBT,1);
	Traversal(pRBT);
	printf("=============================\n");
	DelNode(pRBT,14);
	Traversal(pRBT);
	printf("=============================\n");
	DelNode(pRBT,15);
	Traversal(pRBT);
	printf("=============================\n");
	DelNode(pRBT,7);
	Traversal(pRBT);
	printf("=============================\n");
	DelNode(pRBT,2);
	Traversal(pRBT);

	return 0;
}
