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

char text[1000];//��������
int result[1000];//������ܽ��
int count = 0;//���ĳ���

char h[1000];//�����ϣֵ
int len = 0;//��ϣֵ����

//BKDR��ϣ�㷨ȡ��ɢֵ
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


//������Ϊ��Կ
int getNi(int e, int n)
{
    int d;
    for (d = 0; d < n; d++) 
    {
        if (e * d % n == 1)
            return d;
    }
}

//���������
int Gcd(int a, int b)
{
    if (a % b == 0)//����
        return b;
    else;
    return Gcd(b, a % b);
}

//���������e ��Ϊ˽Կ
int getrand(int p, int q)
{
    int m = (p - 1) * (q - 1);
    int e, c;
    while (1) 
    {
        srand((unsigned)time(NULL));//��ʼ�������������
        e = rand() % m;//���ش��ڵ��� 0 ��С�� m �ľ��ȷֲ����ʵ��
        c = Gcd(e, m);//��e��m����������ж�
        if (c == 1)
            break;
    }
    return e;
}

//�����㷨
void Encode(int n) 
{
    printf("���������ģ�");
    int c = getchar();
    while (1) {
        if (c == '\n')break;
        text[count] = c;
        count++;
        c = getchar();
    }
    //printf_s("text=%s", text);
    //printf_s("����=%d", count);

    unsigned int hash;
    hash = BKDRHash(text, count);
    //printf("��ϣֵΪ��%d",hash);

    sprintf_s(h, sizeof(h),"%d",hash);
    printf("\n-----------------");
    printf("\n���Ĺ�ϣ��ɢֵΪ��%s", h);
    printf("\n-----------------\n");

    len = strlen(h);
    //printf("\n����Ϊ��%d", len);
    
    int e;
    printf("\n������˽Կ��");
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

    printf("\n������ɢֵΪ��");
    for (int i = 0; i < len; i++)
        printf("%d", result[i]);
    printf("\n\n-------�������-------\n");
    
}

//�����㷨
void Decode(int n)
{
    int flag = 1;
    int m[1000];

    int d;
    printf("�����빫Կ��");
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
    printf("\n������ɢֵΪ��");
    for (int i = 0; i < len; i++)
        printf("%c", m[i]);
    printf("\n\n-------�������-------\n");
}


//�ж�����
int prime(int num,int x)
{
    int a = 0;
    if (num == 2)
    {
        x = 0;
        printf("������\n");
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
            printf("������\n");
        }
        else
        {
            printf("��������������������!\n");
        }
    }
    return x;
}

int main() 
{
    int p, q, n, a;

    //�ж��Ƿ�������������
    while (1)
    {
        int x=1, y=1;
        printf("������p q���������ÿո���� \n<p,q�ĳ˻�Ӧ����127>��");//ASCII�����Ϊ127
        scanf_s("%d %d", &p, &q);

        printf("\n");
        printf("��һ����");
        x=prime(p,x); 
        printf("�ڶ�����");
        y=prime(q,y); 
        printf("\n");

        if (x == 0 && y == 0)
            break;
    }

    n = p * q;//����ģ��
    int m = (p - 1) * (q - 1);//�����ܺ���=(p-1)(q-1)
    printf("n=%d", n);

    //˽Կ
    int e;
    e = getrand(p, q);
    printf("\n˽Կe=%d", e);

    //��Կ
    int d;
    d = getNi(e, m);
    printf("\n��Կd=%d", d);

    //�˵�
    int func = 0;
    while (func != 3) 
    {
        printf("\n==================");
        printf("\n��ѡ���ܣ�\n");
        printf("1������\n");
        printf("2������\n");
        printf("3���˳�\n");
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
