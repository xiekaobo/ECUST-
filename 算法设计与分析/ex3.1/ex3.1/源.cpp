#include<iostream>
using namespace std;
const int N = 1000;
int a[N]; // �洢����Ԫ��
bool vis[N]; // �洢����Ԫ�ص�״̬
int subSum;  //�Ӽ���ǰ��
int flag = 0;//����Ƿ��ҵ�����
int n, c;

void print(int i) {//��������������Ӽ���Ԫ��
	for (int j = 0; j <= i; j++) {
		if (vis[j] == true) {
			if (j != i)printf("%d ", a[j]);
			else printf("%d\n", a[j]);
		}
	}
}
void search(int i) {
	//С�ڣ��ͼ���������������ڣ��ͻ��ݷ�����һ�ڵ㣻���ڣ���������ٻ��ݷ�����һ�ڵ�
	if (i >= n) 	return;	//������Χ
	vis[i] = true;
	subSum += a[i];
	if (subSum == c) {//���� ���
		flag = 1;//��ʾ���ҵ��������������Ӽ�
		print(i);
	}
	else if (subSum < c) {// ���� ����ȡ��
		search(i + 1);
	}
	//���subSum > m,�ͻ���,�ѵ�ǰ��������õ���������һ���ڵ������
	vis[i] = false;
	subSum -= a[i];
	search(i + 1);//����һ������ʼ
	return;
}

int main() {
	cin >> n >> c;
	for (int i = 0; i < n; i++)	cin >> a[i];
	search(0);
	if (!flag)	printf("No Solution!");
	return 0;
}

