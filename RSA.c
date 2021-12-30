/*
* create by xyw
* 2021.12.27
*  Easy RSA digital signature and verification with hash algorithm
*/


#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<math.h>
#include <string.h>

char text[1000];//储存明文
int result[1000];//储存加密结果
int count = 0;//明文长度

char h[1000];//储存哈希值
int len = 0;//哈希值长度

//BKDR哈希算法取离散值
unsigned int BKDRHash(char* str, unsigned int len)
{
    unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
    unsigned int hash = 0;
    unsigned int i = 0;

    for (i = 0; i < len; str++, i++)
    {
        hash = (hash * seed) + (*str);
    }

    return hash;
}


//求逆作为公钥
int getNi(int e, int n)
{
    int d;
    for (d = 0; d < n; d++) 
    {
        if (e * d % n == 1)
            return d;
    }
}

//求最大公因数
int Gcd(int a, int b)
{
    if (a % b == 0)//余数
        return b;
    else;
    return Gcd(b, a % b);
}

//产生随机数e 作为私钥
int getrand(int p, int q)
{
    int m = (p - 1) * (q - 1);
    int e, c;
    while (1) 
    {
        srand((unsigned)time(NULL));//初始化随机数发生器
        e = rand() % m;//返回大于等于 0 及小于 m 的均匀分布随机实数
        c = Gcd(e, m);//求e和m最大公因数，判断
        if (c == 1)
            break;
    }
    return e;
}

//加密算法
void Encode(int n) 
{
    printf("请输入明文：");
    int c = getchar();
    while (1) {
        if (c == '\n')break;
        text[count] = c;
        count++;
        c = getchar();
    }
    //printf_s("text=%s", text);
    //printf_s("长度=%d", count);

    unsigned int hash;
    hash = BKDRHash(text, count);
    //printf("哈希值为：%d",hash);

    sprintf_s(h, sizeof(h),"%d",hash);
    printf("\n-----------------");
    printf("\n明文哈希离散值为：%s", h);
    printf("\n-----------------\n");

    len = strlen(h);
    //printf("\n长度为：%d", len);
    
    int e;
    printf("\n请输入私钥：");
    scanf_s("%d",&e);

    int flag = 1;
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < e; j++) 
        {
            flag = flag * (int)h[i] % n;
        }
        result[i] = flag;
        flag = 1;
    }

    printf("\n加密离散值为：");
    for (int i = 0; i < len; i++)
        printf("%d", result[i]);
    printf("\n\n-------加密完成-------\n");
    
}

//解密算法
void Decode(int n)
{
    int flag = 1;
    int m[1000];

    int d;
    printf("请输入公钥：");
    scanf_s("%d", &d);

    for (int i = 0; i < len; i++) 
    {
        for (int j = 0; j < d; j++) 
        {
            flag = flag * result[i] % n;
        }
        m[i] = flag;
        flag = 1;
    }
    printf("\n解密离散值为：");
    for (int i = 0; i < len; i++)
        printf("%c", m[i]);
    printf("\n\n-------解密完成-------\n");
}


//判断质数
int prime(int num,int x)
{
    int a = 0;
    if (num == 2)
    {
        x = 0;
        printf("检测可用\n");
    }
    else 
    {
        for (int i = 2; i <= num - 1; i++)
        {
            if (num % i == 0)
            {
                a++;
            }
        }
        if (a == 0) 
        {
            x = 0;
            printf("检测可用\n");
        }
        else
        {
            printf("并非质数，请重新设置!\n");
        }
    }
    return x;
}

int main() 
{
    int p, q, n, a;

    //判断是否两个都是质数
    while (1)
    {
        int x=1, y=1;
        printf("请输入p q两个素数用空格隔开 \n<p,q的乘积应大于127>：");//ASCII码最大为127
        scanf_s("%d %d", &p, &q);

        printf("\n");
        printf("第一个数");
        x=prime(p,x); 
        printf("第二个数");
        y=prime(q,y); 
        printf("\n");

        if (x == 0 && y == 0)
            break;
    }

    n = p * q;//两数模数
    int m = (p - 1) * (q - 1);//计算总含量=(p-1)(q-1)
    printf("n=%d", n);

    //私钥
    int e;
    e = getrand(p, q);
    printf("\n私钥e=%d", e);

    //公钥
    int d;
    d = getNi(e, m);
    printf("\n公钥d=%d", d);

    //菜单
    int func = 0;
    while (func != 3) 
    {
        printf("\n==================");
        printf("\n请选择功能：\n");
        printf("1、加密\n");
        printf("2、解密\n");
        printf("3、退出\n");
        printf("==================\n");
        scanf_s("%d", &func);
        
        if (func == 1) 
        {
            a = getchar();
            Encode(n);
        }
        else if (func == 2) 
        {
            a = getchar();
            Decode(n);
        }
        else
            return 0;
    }
    return 0;
}
