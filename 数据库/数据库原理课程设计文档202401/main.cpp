#include"operatingLanguage.h"

using namespace std;
namespace fs = std::filesystem;

vector<Database> databases_now;

int main() {
    //��ȡ��¼�û���
    fs::path userloadingPath = "D:\\ABC.txt";
    ifstream inputFile(userloadingPath);
    if (inputFile.is_open()) {
        getline(inputFile, user_now.userName);
        inputFile.close();
    }
    else {
        std::cerr << "��ȡ��¼�û�ʧ��" << std::endl;
    }

    //��ʼ���ǹ�ϵ�����ݿ�
    Initial(user_now.userName);

    //ָ�����
    string line;
    while(true){
        cout << "\n������ָ�" << endl;
        getline(cin, line);
        // ����˳�����
        if (line == "exit") {
            cout << "ϵͳ���˳�" << endl;;
            break;
        }
        else {
            instruction.assign(line.begin(), line.end());
            identifyInstruction();
        }
    }
    return 0;
}
