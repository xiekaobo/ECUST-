#include <bits/stdc++.h>
using namespace std;

int n,m;
int depth=1;   //�Ӽ�������ȡ�һ��һ����ң�������γ��Ӽ�����˵���任�ɹ�������Ⱦ������ٱ任����
string str="";   //���ݵļ�¼���

bool dfs(int n,int curDepth)
{
    if(curDepth>depth)   //��ǰ�����㳬���Ӽ�������ȣ�����
        return false;
    int operation=n;   //����������������������n*3����������n/2;
    for(int i=0;i<2;i++)
    {
        i==0?operation=3*n:operation=n/2;   //���i=0�����������������򣬽���������
        if(operation==m||dfs(operation,curDepth+1))   //����������������󣬵õ�����operation = m�����߾�����һ�β����󣬵õ�����operation = m
        {
            i==0?str+="f":str+="g";   //�������������ӡ�f�����������������ӡ�g��
            return true;   //���������Ϳ��Է�����
        }
    }
    return false;
}
int main()
{
    cin>>n>>m;
    while(!dfs(n,1))   //�ӵ�һ�㿪ʼ��������dfs����false,��ʾû�б任�ɹ������򣬼�����һ��ѭ����ֱ���Ӽ�������
    {
        depth++;   //��Ⱦ�����С�ı任����
    }
    cout<<depth<<endl;
    cout<<str<<endl;
    return 0;
}
