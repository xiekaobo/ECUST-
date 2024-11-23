#include <stdio.h>

#define MAX 10000

// ���̽ṹ��
struct Process {
    int pid;            // ����ID
    double arrival_time;   // ����ʱ��
    double finish_time;    // ���ʱ��
    double process_time;   // ����ʱ��
    double cpu_time;       // ���� CPU ʱ��
    double turnover_time;  // ��תʱ��
    double turnover_weight_time;// ��Ȩ��תʱ��
    char state;         // ����״̬������ W��Wait�������� R��Run������� F��Finish �� ����״̬֮һ
    struct Process *next;
};

void FCFS(Process processes[],int n) {
    int time = 0;//��ǰʱ��
    double average_turnover_time = 0,average_turnover_weight_time = 0;
    for (int i = 0; i < n; i++) {
        if (time < processes[i].arrival_time)time = processes[i].arrival_time;//��ʼ����ʱ��
        processes[i].finish_time = time + processes[i].process_time;//���ʱ��
        processes[i].cpu_time = processes[i].process_time;// ���� CPU ʱ��
        processes[i].turnover_time = processes[i].finish_time - processes[i].arrival_time;//��תʱ��
        processes[i].turnover_weight_time = processes[i].turnover_time / processes[i].process_time;//��Ȩ��תʱ��
        processes[i].state = 'F';
        time += processes[i].process_time;
        average_turnover_time += processes[i].turnover_time;
        average_turnover_weight_time += processes[i].turnover_weight_time;
    }
    average_turnover_time /= n;
    average_turnover_weight_time /= n;
    printf("FCFS ƽ����תʱ��:%lf ƽ����Ȩ��תʱ��:%lf\n", average_turnover_time, average_turnover_weight_time);
}

void SPN(Process processes[],int n) {
    int time = 0;
    double average_turnover_time = 0, average_turnover_weight_time = 0;
    for (int i = 0; i < n; i++) {//����n������
        int process_pid = i, min_process_time = MAX;
        for (int j = 0; j < n; j++) {//�ҵ���ǰʱ������̽���
            if (processes[j].arrival_time <= time && processes[j].process_time < min_process_time && processes[j].state == 'W') {
                process_pid = processes[j].pid;
                min_process_time = processes[j].process_time;
            }
        }
        if (min_process_time == MAX) time = processes[i].arrival_time;//����ǰʱ��Ϊ�ҵ������н��̣��ӿ�ʱ������һ�������н���
        processes[process_pid].finish_time = time + processes[process_pid].process_time;//���ʱ��
        processes[process_pid].cpu_time = processes[process_pid].process_time;// ���� CPU ʱ��
        processes[process_pid].turnover_time = processes[process_pid].finish_time - processes[process_pid].arrival_time;//��תʱ��
        processes[process_pid].turnover_weight_time = processes[process_pid].turnover_time / processes[process_pid].process_time;//��Ȩ��תʱ��
        processes[process_pid].state = 'F';
        time += processes[process_pid].process_time;
        average_turnover_time += processes[process_pid].turnover_time;
        average_turnover_weight_time += processes[process_pid].turnover_weight_time;
    }
    average_turnover_time /= n;
    average_turnover_weight_time /= n;
    printf("SPN ƽ����תʱ��:%lf ƽ����Ȩ��תʱ��:%lf\n", average_turnover_time, average_turnover_weight_time);
}

void RR(Process processes[],int n) {
    int time = 0;
    double average_turnover_time = 0, average_turnover_weight_time = 0;
    Process *headProcess=NULL, *tailProcess = NULL;//���ж�����βָ��

    int flag = n;//�����н��̸���
    while (flag) {//��n������δ���н���ʱ
        while (headProcess == NULL) {//�����ж���Ϊ��ʱ
            for (int i = 0; i < n; i++) {//����ǰʱ���ѵ�����δ��ɵĽ��̰�˳��������ж���
                if (processes[i].arrival_time <= time && processes[i].state == 'W'){
                    if (headProcess == NULL) {
                        headProcess = tailProcess = &processes[i];
                        tailProcess->next = NULL;
                    }else {
                        tailProcess->next = &processes[i];
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
        headProcess->cpu_time++;
        time++;
        for (int i = 0; i < n; i++) {//����Ƿ����½���Ҫ�������ж���
            if (processes[i].arrival_time == time) {
                tailProcess->next = &processes[i];
                tailProcess = tailProcess->next;
                tailProcess->next = NULL;
            }
        }
        if (headProcess->cpu_time == headProcess->process_time) {//���׽���ʹ��CPUʱ����������
            headProcess->state = 'F';
            headProcess->finish_time = time;
            headProcess->turnover_time = headProcess->finish_time - headProcess->arrival_time;//��תʱ��
            headProcess->turnover_weight_time = headProcess->turnover_time / headProcess->process_time;//��Ȩ��תʱ��
            average_turnover_time += headProcess->turnover_time;
            average_turnover_weight_time += headProcess->turnover_weight_time;
            flag--;
            headProcess = headProcess->next;
        }else {//���׽��̷�����β
            tailProcess->next = headProcess;
            tailProcess = tailProcess->next;
            headProcess = headProcess->next;
            tailProcess->next = NULL;
        }
    }
    average_turnover_time /= n;
    average_turnover_weight_time /= n;
    printf("RR ƽ����תʱ��:%lf ƽ����Ȩ��תʱ��:%lf\n", average_turnover_time, average_turnover_weight_time);
}

void restoreProcess(Process processes[], int n) {//�ָ�������������
    for (int i = 0; i < n; i++) {
        processes[i].finish_time = MAX;
        processes[i].cpu_time = 0;
        processes[i].state = 'W';
    }
}

int main() {
    Process processes[] = {
        {0,0,MAX,2,0,MAX,MAX,'W',NULL},
        {1,1,MAX,5,0,MAX,MAX,'W',NULL},
        {2,2,MAX,4,0,MAX,MAX,'W',NULL},
        {3,3,MAX,2,0,MAX,MAX,'W',NULL},
        {4,4,MAX,3,0,MAX,MAX,'W',NULL},
    };
    int n= sizeof(processes) / sizeof(processes[0]);
    
    FCFS(processes, n);
    restoreProcess(processes, n);
    SPN(processes, n);
    restoreProcess(processes, n);
    RR(processes, n);

    return 0;
}