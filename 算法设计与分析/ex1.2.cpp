#include<bits/stdc++.h>
using namespace std;
struct Status//����ṹ�壬ά��4������
{int lSum,rSum,mSum,iSum;};
struct Status pushUp(struct Status l, struct Status r)
{
int iSum = l.iSum + r.iSum; //����������������Ϊ���������
int lSum = fmax ( l.lSum,l.iSum + r.lSum) ;
int rSum = fmax(r.rSum, r.iSum + l.rSum) ;
int mSum = fmax ( fmax( l.mSum,r.mSum), l.rSum + r.lSum ) ;
return (struct Status){lSum,rSum,mSum,iSum} ;
};
 struct Status get(int* a, int l, int r)
{
if ( l == r) {return (struct Status ){a[l],a[l], a[l], a[l]};}//�����䳤��Ϊ1ʱ
int m = ( l +r) >> 1;//�������Ϊ��������������������
struct Status lSub = get(a, l, m); //���������4������ֵ
struct Status rSub = get(a, m + 1,r); //���������4������ֵ
return pushUp( lSub, rSub);//���ϲ�"�����������ֵ
}
int maxSubArray (int* nums, int numssize) {return get(nums, 0,numssize - 1).mSum;}
int main()
{
    int a[10000]={0};
    int n,i;
    int ans=0;
    cin>>n;
    for(i=0;i<n;i++){cin>>a[i];}
    ans=maxSubArray(a,n);
    printf("%d",ans);
    return 0;
}
