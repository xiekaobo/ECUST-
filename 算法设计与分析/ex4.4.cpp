#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=1e4+9;
int n,m,a[maxn];
double b[maxn],dp[maxn];  //dp[i]��Ԥ��Ϊi���õ�һ��offer��������
int main()
{
	while(cin>>n>>m)     //Ԥ��ΪnԪ m��ѧУ
	{
		if(n+m==0)
			break;
		memset(dp,0,sizeof(dp));
		for(int i=1; i<=m; i++)
			cin>>a[i]>>b[i];  //�����i��ѧУ�ķ��� ��ͨ���ĸ���
		for(int i=1; i<=m; i++)
		{
			for(int j=n; j>=a[i]; j--) //����01����
			{
				dp[j]=max(dp[j],1-(1-dp[j-a[i]])*(1-b[i]));
			}
		}
		printf("%.1f%%\n",dp[n]*100);
	}
	return 0;
}
