#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 1000
char a[MAXSIZE];
char b[MAXSIZE];
typedef struct SNode *PtrtoNode;
typedef PtrtoNode Stack;
struct SNode{
    char *Data;
    int top;
    int maxsize;
};
int main()
{
    int N;
    scanf("%d",&N);
    char temp;
    int i,j,count,flag=1;
    Stack S1=(Stack)malloc(sizeof(struct SNode));
    S1->Data=(char*)malloc(N*sizeof(char));
    S1->top=-1;
    S1->maxsize=N;
    for(i=0;i<2*N;i++)
    {
        scanf("%c",&a[i]);//��ջ��������
    }
    for(i=0;i<2*N;i++)
    {
        scanf("%c",&b[i]);//��ջ��������
    }
    j=1;//��ջ����ջβָ��
    for(count=1,i=1;count<=N;count++,i+=2)//������ջ����
    {
        if(a[i]!=b[j]&&i<=2*N-1)
        {
            S1->Data[++(S1->top)]=a[i];//ѹջ
            //printf("%c-in\n",a[i]);
        }
        else if(a[i]==b[j]&&i<=2*N-1)
        {
            S1->Data[++(S1->top)]=a[i];
            //printf("%c-in\n",a[i]);
            while(S1->Data[S1->top]==b[j])
            {
                //printf("%c-out\n",S1->Data[S1->top]);
                S1->Data[S1->top]==' ';//��ջ���
                if(S1->top!=-1) (S1->top)--;//ջ��ָ�����
                j+=2;//��ջ����ָ����ƣ�׼���ж���һ�׶��Ƿ���Գ�ջ
            }
        }
    }
    if(j==2*N+1) printf("1\n");
    else {printf("0"); return 0;}
    //�����������һ�� ֻ��������������
    j=1;
    S1->top=-1;//ջ��ָ���λ��׼������
    for(count=1,i=1;count<=N;count++,i+=2)
    {
        if(a[i]!=b[j]&&i<=2*N-1)
        {
            S1->Data[++(S1->top)]=a[i];
            printf("%c-in\n",a[i]);
        }
        else if(a[i]==b[j]&&i<=2*N-1)
        {
            S1->Data[++(S1->top)]=a[i];
            printf("%c-in\n",a[i]);
            while(S1->Data[S1->top]==b[j])
            {
                printf("%c-out\n",S1->Data[S1->top]);
                S1->Data[S1->top]==' ';
                if(S1->top!=-1) (S1->top)--;
                j+=2;
            }
        }
    }
    return 0;
}
