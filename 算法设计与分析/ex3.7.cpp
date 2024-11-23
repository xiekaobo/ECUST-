#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;

const int MAX = 50;
int board[MAX][6];  //�洢n��������������ɫ
int solu[MAX][6];   //�洢��
int n;  //�������������ɫ����
int ans = 0;  //��ĸ���
int used[MAX];
char color[MAX];

//�ҵ�һ��������
void out(int edge[])
{
    int i, j, k, a, b, c, d;
    for(i=0; i<2; i++) //2����ͼ
    {
        for(j=0; j<n; j++)
            used[j] = 0;
        do{
            j = 0;
            d = c = -1;
            while(j<n && used[j]>0) //����һ��δ�õı�
                j++;
            if(j < n)
                do{
                    a = board[j][edge[i*n+j]*2];
                    b = board[j][edge[i*n+j]*2+1];
                    if(b == d)  //�����һ���ߵ��յ���b��ͬ��˵��bΪʼ�㣬��������֤aΪʼ��
                        swap(a, b);  //��֤����ߵ�ʼ���Ӧ��ǰ������棬�յ��Ӧ�ڱ��������
                    solu[j][i*2] = a;
                    solu[j][i*2+1] = b;
                    used[j] = 1;
                    if(c<0)  //��ʼ����
                        c = a;
                    d = b;
                    for(k=0; k<n; k++)  //����һ��������
                        if(used[k]==0 && (board[k][edge[i*n+k]*2]==b || board[k][edge[i*n+k]*2+1]==b))
                            j = k;
                }while(b != c);  //����һȦ���ص����
        }while(j<n);  //���������嶼�ұ�
    }
    for(j=0; j<n; j++) //������Ķ���͵������ɫ
    {
        k = 3 - edge[j] - edge[j+n];
        a = board[j][k*2];
        b = board[j][k*2+1];
        solu[j][4] = a;
        solu[j][5] = b;
    }
    for(i=0; i<n; i++)
    {
        for(j=0; j<6; j++)
            cout << color[solu[i][j]];
        cout << endl;
    }
}

void search()
{
    int i, t, cube;
    bool ok, newg, over;
    int *vert = new int[n];  //��¼��ͼ��ÿ������Ķȣ�Ӧ��Ϊ2
    int *edge = new int[n*2];  //��¼ÿ���������б߱�ѡ�õ�������ÿ��������ֻ��3���ߣ���������ͼҪѡ��
    for(i=0; i<n; i++)
        vert[i] = 0;
    t = -1;
    newg = true;
    while(t > -2)
    {
        t++;
        cube = t % n;  //ÿ����������2�Σ��õ���ʵ���������ţ�Ҳ����ͼ�бߵı��
        if(newg)  //���û�б߱�ѡ����ͼ
            edge[t] = -1;
        over = false;  //�Ƿ��������������ͼ�������
        ok = false;    //��Ǳ��Ƿ����ù���������ͼ��Ӧ�й�����
        while(!ok && !over)
        {
            edge[t]++;  //�߱�ѡ�ü�����ͼ��ʹ�ô�������
            if(edge[t]>2)  //��������ÿ�������Ķ�����һ���ߣ�ÿ��������ֻ��3����
                over = true;
            else
                ok = (t<n || edge[t]!=edge[cube]);  //�Ƿ����ù�
        }
        if(!over)
        {          //���ߵ���������Ķ�
            if(++vert[board[cube][edge[t]*2]] > 2+t/2*2) //����ǵ�һ����ͼ������Ȳ��ܳ���2
                ok = false;              //����ǵڶ�����ͼ�����ϵ�һ����ͼ������Ȳ��ܳ���4
            if(++vert[board[cube][edge[t]*2+1]] > 2+t/2*2)
                ok = false;
            if(t%n == n-1 && ok)  //���һ����������ͼ�ѹ������
                for(i=0; i<n; i++)
                    if(vert[i] > 2+t/n*2)
                        ok = false;
            if(ok)
            {
                if(t == n*2-1) //�ҵ���
                {
                    ans++;
                    out(edge);
                    return;
                }
                else
                    newg = true;
            }
            else //ȡ��һ����
            {
                --vert[board[cube][edge[t]*2]];  //�ߵ���������
                --vert[board[cube][edge[t]*2+1]];
                t--;
                newg = false;
            }
        }
        else //����
        {
            t--;
            if(t > -1)
            {
                cube = t % n;
                --vert[board[cube][edge[t]*2]];
                --vert[board[cube][edge[t]*2]];
            }
            t--;
            newg = false;
        }
    }
}

int main()
{

    cin >> n;
    for(int i=0; i<n; i++)
    {
        cin >> color[i];
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<6; j++)
        {
            cin >> board[i][j];
        }
    }
    search();
    if(ans == 0)
        cout << "No Solution��\n";
    cout << endl;
    return 0;
}
