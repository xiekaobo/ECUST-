#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
int a[110];
int s[110];
bool vis[110];
int main()
{
	while(cin>>n&&n!=0)
	{
		memset(a,0,sizeof(a));
		memset(s,0,sizeof(s));
		int num=n*(n-1)/2;
		for(int i=1;i<=num;i++) cin>>s[i];
		int cc=s[2]-s[1];//cc=a[3]-a[2]
		for(int i=3;i<=num;i++)
		{
			//�������ܵ�a[2]+a[3]
			if((cc+s[i])%2) continue;
			memset(vis,false,sizeof(vis));
			bool flag=true;
			vis[1]=vis[2]=vis[i]=true;
			a[3]=(cc+s[i])/2;
			a[1]=s[2]-a[3];
			a[2]=s[1]-a[1];
			for(int j=4;j<=n;j++)
			{
				int pos=0;
				//�ҵ����е�s����С��  ȷ��a[j]
				for(int k=1;k<=num;k++)
				{
					if(vis[k]==false)
					{
						pos=k;
						break;
					}
				}
				if(pos)
				{
					vis[pos]=true;
					a[j]=s[pos]-a[1];
					//�ų���a[1]+a[j],a[2]+a[j],a[3]+a[j]~~
					for(int k=1;k<j;k++)
					{
						int temp=a[j]+a[k];
						bool ff=false;
						for(int m=1;m<=num;m++)
						{
							if(s[m]==temp)
							{
								ff=true;
								if(!vis[m])
								{
									vis[m]=true;
									break;
								}
							}
						}
						if(!ff)
						{
							//���s����û��a[k]+a[j]��һԪ��
							//��˵����������a[2]+a[3]�Ǵ��
							flag=false;
							break;
						}
					}
					//������� ��������
					if(!flag) break;
				}
			}
			//������ȷ ��Ψһ ��������
			if(flag) break;
		}
		for(int i=1;i<=n;i++) cout<<a[i]<<" ";
		cout<<endl;
	}
	return 0;
}
