#include<bits/stdc++.h>
using namespace std;
int count_in_range(int* nums,int target,int lo,int hi)// ����ָ����Χ��������ĳ���ض�Ԫ��target�ĳ��ִ���
{
    int count=0;
    for(int i=lo;i<=hi;++i)
    {
        if (nums[i]==target) ++count;
    }
    return count;
}
int majority_element_rec(int* nums,int lo, int hi)
{
    if (lo==hi) return nums[lo];// ���䳤��Ϊ1ʱ��������Ϊ��������
    int mid = (lo + hi) / 2;// �м�����mid
    int left_majority=majority_element_rec(nums,lo,mid);// ��벿�ֵ�����
    int right_majority=majority_element_rec(nums,mid+1,hi); //�Ұ벿�ֵ�����
    if (count_in_range(nums,left_majority,lo,hi)>(hi-lo+1)/2) return left_majority;
    if (count_in_range(nums,right_majority,lo,hi)>(hi-lo+1)/2) return right_majority;
    return -1; // ��벿�ֺ��Ұ벿�ֶ�û�ж���Ԫ�أ��򷵻�-1
}
int majorityElement(int* nums, int numsSize)
{
    return majority_element_rec(nums,0,numsSize-1);
}
int main()
{
    int a[10000]={0};
    int n,i,ans=0;
    cin>>n;
    for(i=0;i<n;i++){cin>>a[i];}
    ans=majorityElement(a,n);
    printf("%d",ans);
    return 0;
}
