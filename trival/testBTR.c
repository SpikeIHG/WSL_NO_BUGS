#include<stdio.h>
#include"SBTree.h"
#include<time.h>
int main(void)
{
    BiTree t=NULL;
    srand(time(NULL));
    for(int i=1;i!=10;++i)
    InsertBST(&t,i*2);
    InOrderTraverse(t,visit);

    DeleteBTS(&t,10);
    InOrderTraverse(t,visit);

    return 0;
}