#include <bits/stdc++.h>
using namespace std;

int n;    //��������
int m;    //��Ӧ������
int d;    //�۸�����
int bestw;   //��С������
int** c = NULL;    //��ά���飬ÿ��������ͬ�̼ҵļ۸�
int** w = NULL;     //��ά���飬ÿ��������ͬ�̼ҵ�����
//ÿһ����������Ϣ
class Node {
public:
    int weight;        //��ǰ��ѡ������������
    int val;           //��ǰ��ѡ�����ļ�ֵ��
    int source;        //�ĸ�������
    int level;         //�ڼ���,Ҳ�����˵ڼ�������
    int priority;      //���ȼ�
    Node* father;
};

Node* leaf;//Ҷ�ӽ��
void Input() {
    scanf("%d %d %d",&n,&m,&d);
    w = (int**)malloc(sizeof(int*)*(n + 1));
    c = (int**)malloc(sizeof(int*)*(n + 1));
    for (int i = 1; i <= n; i++) {
        w[i] = (int*)malloc(sizeof(int)*(m + 1));
        c[i] = (int*)malloc(sizeof(int)*(m + 1));
    }
    leaf = NULL;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d",&c[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d",&w[i][j]);
}

//�Ż������ȼ��趨
bool operator<(Node a, Node b)  //level���ռ���
{
    if (a.priority == b.priority)return a.level < b.level;  //���������ͬ��ѡ��level��ġ�
    return a.priority > b.priority;//��������С���ȳ���
}

//���㵱ǰ�ڵ�����ȼ�
void QueuePriority(Node a) {
    int currentMinW;
    a.priority = a.val;
    //int temp_min_c = INT_MAX;
    for (int i = a.level + 1; i <= n; i++)//ѡ��ʣ��Ĳ������ۻ����й������С����,����ѡ��ÿһ����С������
    {
        currentMinW = 999999;
        for (int j = 1; j <= m; j++)  //ÿһ������С��
        {
            currentMinW = currentMinW < w[i][j] ? currentMinW : w[i][j];//��m���̼���ѡ�񵱲�������С��
        }
        a.priority += currentMinW;
    }
}

//Լ������
bool constraint(Node* pNode, int i) {
    return pNode->val + c[pNode->level + 1][i] <= d || pNode->weight + w[pNode->level + 1][i] <= bestw;
}

//�����ڵ�
Node createNode(int level, Node* father, int source, int val, int weight) {
    Node newNode{};
    newNode.level = level;//��μ�1
    newNode.father = father;
    newNode.source = source;
    newNode.val = val;
    newNode.weight = weight;
    return newNode;
}

void MinWeightMachine() {
    int i, j;
    bestw = 999999;
    Node initial{};
    initial = createNode(0, NULL, 0, 0, 0);
    QueuePriority(initial);      //�������ȼ�
    priority_queue<Node> heap;   //�����ȶ��У�����һ����С�ѡ������ȥ�ͻ��Զ��ź���ġ�
    heap.push(initial);
    while (!heap.empty()) {
        Node* pNode = new Node(heap.top());
        heap.pop();//����Ԫ����Ϊ���ڵ���ӣ������ȼ�ֵС�Ļ�������չ
        if (pNode->level == n)//����Ҷ�ڵ㣬������չ ,�õ�һ����
        {
            if (pNode->weight < bestw)   //����
            {
                bestw = pNode->weight;
                //MinValue  = pNode ->val;
                leaf = pNode;   //��¼��������ĸ��������,���ڻ��������Ž�
            }
        }
        else {
            for (i = 1; i <= m; i++)//��չ��㣬����ѡ��ÿ���ۻ��̣�ÿ�ζ���m����
            {
                //�����Լ�֦���޽��֦
                if (constraint(pNode, i)) {
                    Node newNode{};//�����ӽ��
                    newNode = createNode(pNode->level + 1, pNode, i, pNode->val + c[pNode->level + 1][i], pNode->weight + w[pNode->level + 1][i]);
                    QueuePriority(newNode);     //��������ֵ
                    heap.push(newNode);//�������
                }
            }
        }
    }

}

void Output() {
    printf("%d\n",bestw);
    int* result = (int*)malloc(sizeof(int)*(n + 1));
    for (int i = n; i >= 1; i--) {
        result[i] = leaf->source;//�����Ҷ�ӽ����ݵ����ڵ�
        leaf = leaf->father;
    }
    for (int i = 1; i <= n; i++)
        if(i==1) printf("%d",result[i]);
        else printf(" %d",result[i]);
    putchar('\n');
}
int main() {
    Input();
    MinWeightMachine();
    Output();
    return 0;
}
