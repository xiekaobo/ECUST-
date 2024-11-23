#include<iostream>
#include<fstream>
#include"MinHeap.h"
using namespace std;

//��С�ѽ��
class HeapNode                              //�ѽ���ࣻ
{
    friend class DealNode;
public:
    operator int()const { return cn; }
private:
    int i,                                  //i��ʾ���н���
        cn,                                 //cn��ʾ��ǰ����ĸ��Ƕ�����Ȩ��֮��
        * x,                                 //x�����ʾ��Щ��������˸��Ƕ��������
        * c;                                 //c�����ʾX�еĸ��Ƕ��������е��ڽӶ���
};

// VC�������Զ��н���ڲ��ĵĲ���
class DealNode
{
    friend MinCover(int**, int[], int);
private:
    void BBVC();
    bool cover(HeapNode E);
    void AddLiveNode(MinHeap<HeapNode>& H, HeapNode E, int cn, int i, bool ch);
    int** a, n, * w, * bestx, bestn;
};

void DealNode::BBVC()
{
    //������ʼ�ն�
    MinHeap<HeapNode>H(1000);
    HeapNode E;
    E.x = new int[n + 1];
    E.c = new int[n + 1];
    for (int j = 1; j <= n; j++)
    {
        E.x[j] = E.c[j] = 0;
    }

    int i = 1, cn = 0;
    while (true)
    {
        if (i > n)
        {
            if (cover(E))
            {
                for (int j = 1; j <= n; j++)
                    bestx[j] = E.x[j];
                bestn = cn;
                break;
            }
        }
        else
        {
            if (!cover(E))
                AddLiveNode(H, E, cn, i, true);//��������Ϊi �Ľ�㵽���㸲�Ǽ��У����Ѹ��º�Ľ���ٲ������
            AddLiveNode(H, E, cn, i, false); //���ѽ����Ϊ i �Ľ����뵽���㸲�Ǽ��У����Ѹ��º�Ľ��������
        }
        if (H.IsEmpty())break;
        H.RemoveMin(E);  //ȡ�Ѷ��㸳��E
        cn = E.cn;
        i = E.i + 1;
    }
}

//���ͼ�Ƿ񱻸���
bool DealNode::cover(HeapNode E)
{
    for (int j = 1; j <= n; j++)
    {
        if (E.x[j] == 0 && E.c[j] == 0)//��������һ���ߵ��������㶼Ϊ0������£�Ϊδ�������
            return false;      //X[j]��¼���Ƕ��㣬c[j]��¼�븲�Ƕ��������Ķ��� 0����δ���ǣ�1�����Ѹ���
    }
    return true;
}

void DealNode::AddLiveNode(MinHeap<HeapNode>& H, HeapNode E, int cn, int i, bool ch)
{
    HeapNode N;
    N.x = new int[n + 1];
    N.c = new int[n + 1];
    for (int j = 1; j <= n; j++)
    {
        N.x[j] = E.x[j];
        N.c[j] = E.c[j];
    }
    N.x[i] = ch ? 1 : 0;

    if (ch)
    {
        N.cn = cn + w[i];       //��¼i�����Ƿ���븲�ǵ������У�
        for (int j = 1; j <= n; j++)
            if (a[i][j] > 0)   //���i,j���ڣ��հ�j������븲���ڽӶ��㼯�У�
                N.c[j]++;
    }
    else
    {
        N.cn = cn;
    }
    N.i = i;
    H.Insert(N);                                                        //�������
}

int MinCover(int** a, int v[], int n)
{
    DealNode Y;
    Y.w = new int[n + 1];
    for (int j = 1; j <= n; j++)
    {
        Y.w[j] = v[j];                   //��ʼ��DealNode�����Y;
    }
    Y.a = a;
    Y.n = n;
    Y.bestx = v;                        //����ַ����bestx��
    Y.BBVC();
    return Y.bestn;                   //bestn��������С���㸲�Ǽ�Ȩ�أ�
}

int main()
{
    int startV, endV,i;        //һ���ߵ���ʼ�ڵ㣬��ֹ�ڵ�
    int vertexNum, edgeNum;  //������������

    //���������ļ��е�����
    fstream fin;
    fin.open("input.txt", ios::in);
    if (fin.fail())
    {
        cout << "File does not exist!" << endl;
        cout << "Exit program" << endl;
        return 0;
    }

    fin >> vertexNum >> edgeNum;

    int** a;                            //ͼ���ڽӾ����ʾ��1��ʾ�б�
    a = new int* [vertexNum + 1];

    for (int k = 0; k <= vertexNum; k++)
        a[k] = new int[vertexNum + 1];
    for (int i = 0; i <= vertexNum; i++)
        for (int j = 0; j <= vertexNum; j++)
            a[i][i] = 0;

    int* p;                             //�����Ȩֵ����
    p = new int[vertexNum + 1];
    for (i = 1; i <= vertexNum; i++)
        fin >> p[i];

    for (i = 1; i <= edgeNum; i++)
    {
        fin >> startV >> endV;
        a[startV][endV] = 1;
        a[endV][startV] = 1;
    }

    //���������д�뵽����ļ�
    fstream fout;
    fout.open("output.txt", ios::out);

    int minVertex = MinCover(a, p, vertexNum);

    cout << minVertex << endl;
    fout << minVertex << endl;

    for (i = 1; i <= vertexNum; i++)
    {
        cout << p[i] << " ";
        fout << p[i] << " ";
    }

    cout << endl;

    fin.close();
    fout.close();
    system("pause");
    return 0;
}
