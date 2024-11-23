#include <bits/stdc++.h>
using namespace std;

int n;
int boy[21][21], girl[21][21];
int Max = INT_MIN; //MAX������Ů˫���������Ƶ��ܺ͵����ֵ ��������ָ�������������ܱ�ʾ����Сֵ��
int sum = 0;
int res[21][21]; //data[i][j]���ڴ�����˶�Աi��Ժ��˫����������
int maxSum[21];   //����ÿ������ƥ���ɴﵽ�����˫����������
int book[21];    //���Ů�˶�Ա�Ƿ��Ѿ�ƥ�� 0δƥ�� 1��ƥ��

//Max��40 -> 52
void dfs(int t){
    if(t>=n)  //t����n�󣬴���ȫ����Ƿ����ˣ��õ������ֵ
    {
        Max = max(Max, sum);
        return;
    }
    int cnt = 0;
    //��t��t֮������ƥ��Ů�������ֵ�ĺ�
    for (int i = t; i < n;i++){
        cnt += maxSum[i];
        //�����̰�ĵ���ÿ�����˶�Աƥ�����ŵ�Ů�˶�Ա
    }

    //��֦������֮ǰt���Ѿ�ƥ��õ���Ů�˶�Ա��sum��
    //֮���t->n-1����Ůƥ������ֵ�������õ���Max�Ƚ�
    //��ǰ��<=Max����֦
    if(sum+cnt<Max)
        return;
        //��cnt>=Max��Ҫ������������
        //�ӵ�t��������ʼƥ�䣬��δƥ���Ů��
    for (int i = 0; i < n;i++){
        if(!book[i]){//����i��Ů��δƥ��
            book[i] = 1;
            sum += res[t][i];
            dfs(t + 1);
            book[i] = 0; //����t������ƥ��Ů��i�õ���sum������Max�������
            sum -= res[t][i];
        }
    }
}

int main(){
    cin >> n;
    for (int i = 0; i < n;i++){
        for (int j = 0; j < n;j++){
            cin >> boy[i][j];
        }
    }
    for (int i = 0; i < n;i++){
        for (int j = 0; j < n;j++){
            cin >> girl[i][j];
        }
    }
    for (int i = 0; i < n;i++){
        for (int j = 0; j < n;j++){
            //��ÿ������������Ů˫���������ƣ��ܵõ�i*j�ֽ��
            res[i][j] = boy[i][j] * girl[j][i];
            //��¼ÿ������ƥ���ɴﵽ�����˫���������ƣ����ں���ļ�֦
            maxSum[i] = max(maxSum[i], res[i][j]);
        }
    }
    dfs(0);
    cout << Max << endl;
    return 0;
}
