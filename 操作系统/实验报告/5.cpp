#include<iostream>
#include<stdio.h>
#include<cmath>
using namespace std;
struct process
{
    char processName[50];         //������
    int arrivalTime;              //����ʱ��
    int completionTime;           //���ʱ��
    int requiredTime;             //��Ҫ���е�ʱ��
    int turnovertime;             //������תʱ��
    float weightedTurnaroundTime; //��Ȩ��תʱ��
    int No;                       //���̱��
    bool visited;                 //��ǰ�ڵ��Ƿ񱻷��ʹ�
    struct process* next;         //��һ���ڵ�ָ��
    char state;                   //���̵�״̬
    double cpu_time;              //����CPUʱ��
};
int main()
{
    process a[100];
    int n, i, j, k, time = 0, pian;//timeΪϵͳ��ǰʱ��,pianΪʱ��Ƭ��С
    float sum1 = 0, sum2 = 0;//sum1����תʱ��ƽ����sum2�Ǵ�Ȩ��תʱ��ƽ��
    cin >> n;
    cin >> pian;
    for (i = 1; i <= n; i++)
    {
        cin >> a[i].processName;
        cin >> a[i].arrivalTime;
        cin >> a[i].requiredTime;
        a[i].No = i;
        a[i].visited = false;
    }
    //FCFS�㷨
    cout << "---------------FCFS----------------" << endl;
    for (i = 1; i <= n; i++)
    {
        if (a[i].arrivalTime >= time)
        {
            time = a[i].arrivalTime;
            time += a[i].requiredTime;
            a[i].completionTime = time;
            a[i].turnovertime = a[i].completionTime - a[i].arrivalTime;
            a[i].weightedTurnaroundTime = 1.0 * a[i].turnovertime / a[i].requiredTime;
            sum1 += a[i].turnovertime;
            sum2 += a[i].weightedTurnaroundTime;
        }
        else
        {
            time += a[i].requiredTime;
            a[i].completionTime = time;
            a[i].turnovertime = a[i].completionTime - a[i].arrivalTime;
            a[i].weightedTurnaroundTime = 1.0 * a[i].turnovertime / a[i].requiredTime;
            sum1 += a[i].turnovertime;
            sum2 += a[i].weightedTurnaroundTime;
        }
    }
    sum1 = sum1 * 1.0 / n;
    sum2 /= n;
    for (i = 1; i <= n; i++)
    {
        cout << "��" << i << "������" << endl;
        cout << "��������" << a[i].processName << "���ʱ��" << a[i].completionTime <<
         " ��תʱ��" << a[i].turnovertime << "��Ȩ��תʱ�� " << a[i].weightedTurnaroundTime;
        cout << endl;
    }
    cout << "ƽ����תʱ��:" << sum1 << "ƽ����Ȩ��תʱ��:" << sum2 << endl;
    cout << "-----------------------------------" << endl;
    //SPN�㷨
    cout << "----------------SPN----------------" << endl;
    time = 0;
    sum1 = 0, sum2 = 0;
    process temp;
    for (i = n; i > 1; i--)
    {
        for (j = 1; j < i; j++)
        {
            if (a[j].requiredTime > a[j + 1].requiredTime)
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    int solved = 0;
    while (solved < n)
    {
        for (i = 1; i <= n; i++)
        {
            if (a[i].arrivalTime <= time)
            {
                if (a[i].visited == false)
                {
                    time += a[i].requiredTime;
                    a[i].completionTime = time;
                    a[i].turnovertime = a[i].completionTime - a[i].arrivalTime;
                    a[i].weightedTurnaroundTime = 1.0 * a[i].turnovertime / a[i].requiredTime;
                    sum1 += a[i].turnovertime;
                    sum2 += a[i].weightedTurnaroundTime;
                    a[i].visited = true;
                    solved++;
                    break;
                }
            }
        }
    }
    for (i = n; i > 1; i--)
    {
        for (j = 1; j < i; j++)
        {
            if (a[j].No > a[j + 1].No)
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    sum1 = sum1 * 1.0 / n;
    sum2 /= n;
    for (i = 1; i <= n; i++)
    {
        cout << "��" << i << "������" << endl;
        cout << "��������" << a[i].processName << "���ʱ��" << a[i].completionTime <<
        " ��תʱ��" << a[i].turnovertime << "��Ȩ��תʱ�� " << a[i].weightedTurnaroundTime;
        cout << endl;
    }
    cout << "ƽ����תʱ��:" << sum1 << "ƽ����Ȩ��תʱ��:" << sum2 << endl;
    cout << "-----------------------------------" << endl;
    //RR�㷨
    cout << "----------------RR-----------------" << endl;
    time = 0, solved = 0;
    sum1 = 0, sum2 = 0;
    for (i = 1; i <= n; i++)
    {
        a[i].visited = false;
        a[i].state = 'W';
        a[i].cpu_time = 0;
    }
    process* headProcess = NULL, * tailProcess = NULL;//���ж�����βָ��
    int flag = n;//�����н��̸���
    while (flag) {//��n������δ���н���ʱ
        while (headProcess == NULL) {//�����ж���Ϊ��ʱ
            for (int i = 1; i <= n; i++) {//����ǰʱ���ѵ�����δ��ɵĽ��̰�˳��������ж���
                if (a[i].arrivalTime <= time && a[i].state == 'W') {
                    a[i].state == 'R';
                    if (headProcess == NULL) {
                        headProcess = tailProcess = &a[i];
                        tailProcess->next = NULL;
                    }
                    else {
                        tailProcess->next = &a[i];
                        tailProcess = tailProcess->next;
                        tailProcess->next = NULL;
                    }
                }
            }
            if (headProcess == NULL) {//��ǰʱ��û�н��̿�����
                time++;
            }
        }
        //�н��������ж�����ʱ
        //�н��������ж�����ʱ�����ж��׽���
        if ((headProcess->requiredTime - headProcess->cpu_time) > pian) {//���׽�������ʱ�����һ��ʱ��Ƭ
            time += pian;
            headProcess->cpu_time += pian;
        }
        else {//���׽�������ʱ��<=һ��ʱ��Ƭ
            time += headProcess->requiredTime - headProcess->cpu_time;
            headProcess->cpu_time += headProcess->requiredTime - headProcess->cpu_time;

        }

        //����Ƿ����½���Ҫ�������ж���
        for (int i = 1; i <= n; i++) {
            if (a[i].arrivalTime <= time && a[i].state == 'W') {
                a[i].state = 'R';
                tailProcess->next = &a[i];
                tailProcess = tailProcess->next;
                tailProcess->next = NULL;
            }
        }
        if (headProcess->cpu_time == headProcess->requiredTime) {//���׽���ʹ��CPUʱ����������
            headProcess->state = 'F';
            headProcess->completionTime = time;
            headProcess->turnovertime = headProcess->completionTime - headProcess->arrivalTime;//��תʱ��
            headProcess->weightedTurnaroundTime = 1.0*headProcess->turnovertime / headProcess->requiredTime;//��Ȩ��תʱ��
            sum1 += headProcess->turnovertime;
            sum2 += headProcess->weightedTurnaroundTime;
            flag--;
            headProcess = headProcess->next;
        }
        else {//���׽��̷�����β
            tailProcess->next = headProcess;
            tailProcess = tailProcess->next;
            headProcess = headProcess->next;
            tailProcess->next = NULL;
        }
    }
    sum1 = sum1 * 1.0 / n;
    sum2 /= n;
    for (i = 1; i <= n; i++)
    {
        cout << "��" << i << "������" << endl;
        cout << "��������" << a[i].processName << "���ʱ��" << a[i].completionTime << " ��תʱ��"
        << a[i].turnovertime << "��Ȩ��תʱ�� " << a[i].weightedTurnaroundTime;
        cout << endl;
    }
    cout << "ƽ����תʱ��:" << sum1 << "ƽ����Ȩ��תʱ��:" << sum2 << endl;
    return 0;
}
