#include<bits/stdc++.h>
using namespace std;
void dfs( char* str, int s, int e, char *res, int *max)
{
if(s >= e) return;
bool f = true;
int i;
for(i=s ;i<=e ;i++)
{
//����str[i]��Ӧ�Ĵ�д(Сд)�ַ��Ƿ���ڣ������ڻ�Ҫ�ж��ַ��Ƿ�����s ~ e������
    char *pos = strchr(str+s,str[i] <= 'Z' ? str[i]+32 : str[i]-32);
    if(!(pos && pos <= str+e ))
    {
        f = false;
        break;
    }
}
if(!f)
{
//���str[i����str[s~e]��Ϊ�Ƿ��ַ�����ݹ鴦���󲿺��Ҳ����ȴ�������Ϊ��ĿҪ�󷵻��ȳ��ֵĽ��
dfs (str, s, i-1, res,max );
dfs(str, i+1,e, res,max ) ;
}
else
{
    //l���str[s~e]��һ�������ַ���,�ж��䳤���Ƿ�������⣬���������滻
    if(e-s+1 > *max )
    {
        *max = e-s+1;
        for(int i=s ;i<=e;i++) {res[i-s] = str[i];}
    }
}
}
int main()
{
    string c;
    string ans="";
    cin >> c;
    char* p = (char*)c.c_str(); // ��ȡ�����ַ����� C ����ַ���
    char* p0 = (char*)ans.c_str();
    int max_length = 0;
    dfs(p, 0, c.length(), p0, &max_length);
    // �������ַ���
    for (int i = 0;p0[i] != '\0'; i++) {
        printf("%c", p0[i]);
    }
    return 0;
}
