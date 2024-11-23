#include<iostream>
#include<cstring>
using namespace std;
int n;
int d[10010];
char result[10010][10010];
int num = 0;
bool isLeagal(int row, int col) { //�Ƿ��������
    bool judge = true;
    for (int i = 1; i < row; i++) {
        if (col == d[i]) {
            judge = false;
            break;
        }
        if (i - d[i] == row - col) {
            judge = false;
            break;
        }
        if (i + d[i] == row + col) {
            judge = false;
            break;
        }
    }
    return judge;
}
void dfs(int row) {
    if (row == n + 1) {
        num++;
        return ;
    }
    //���Ĵ���
    for (int col = 1; col <= n; col++) {  //��row��һ��ÿһ����ô��
        if (isLeagal(row, col)) {
            d[row] = col;
            result[row][col- 1] = 'Q';
            dfs(row + 1);
            result[row][col-1] = '.';
            d[row] = 0;
        }
    }

}
int main() {
    while(1)
    {
        num=0;
        cin >> n;
        if(n==0) break;
        for (int i = 1; i <= n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = '.';
        }
    }
    dfs(1);
    cout << num << endl;
    }
    return 0;
}
