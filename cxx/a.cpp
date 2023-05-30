#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//ZHAO QIAN SUN LI ZHOU WU ZHENG WANG CHANG CHAO YANG JIN
int main() 
{
    char keys[12][7],chart[16][7];//关键字、哈希表的字符串
    int hashValue[12],length[12];//哈希函数值、查找长度
    int sum = 0;//总查找长度
    for (int i = 0; i < 12; i++)
    {
        scanf("%s", keys[i]);
        hashValue[i] = length[i] = 0;
        for (int j = 0; keys[i][j] != '\0'; j++)
        {
            hashValue[i] += keys[i][j] - 'A'+1;
        }
        hashValue[i] %= 16;
    }
    for (int i = 0; i < 16; i++)
    {
        chart[i][0] = '#';
        chart[i][1] = '\0';
    }
    printf("哈希函数值分别为:");
    for (int i = 0; i < 12; i++)
    {
        printf("%d ", hashValue[i]);
    }
    printf("\n");
    for (int i = 0; i < 12; i++)
    {
        length[i] = 1;
        if (chart[hashValue[i]][0]=='#')
        {
            
            strcpy(chart[hashValue[i]], keys[i]);
        }
        else
        {
            int j = hashValue[i];
            while (chart[j][0] != '#')
            {
                length[i]++;
                j++;
                if (j == 16)
                {
                    j = 0;
                }
            }
            strcpy(chart[j], keys[i]);
        }
        sum += length[i];
    }
    printf("构造的哈希表是:");
    for (int i = 0; i < 16; i++)
    {
        printf("%s ", chart[i]);
    }
    printf("\n");
    printf("平均查找长度为%d/12\n", sum);
    return 0;
}