#include "interpret.h"

int main() {
	integerArray.clear();
	identifierArray.clear();
	streambuf* stdin_backup = cin.rdbuf(); //���ݱ�׼������
	//const char* fileinname = "demo.txt";
	string fileinname;
	cout << "������Դ�ļ�����";
	cin >> fileinname;
	getchar();
	ifstream fcin("./test/"+fileinname);
	if (!fcin.is_open()) {
		cout << "failed to open " << fileinname << endl;
		return 0;
	}
	fcin.seekg(0, ios::end);
	long length = fcin.tellg();
	fcin.clear();
	fcin.seekg(0, ios::beg);
	fcin.read(FileBuff, length);
	fcin.close();

	auto* BLOCKT = new treeNode("����");//�﷨�������
	while (Cur != length) {
		BLOCK(BLOCKT);
		if (sym == "finish" || sym == "error")
			break;
	}
	if (!error_grammar) {
		printTreeNode(BLOCKT, 0);
		printTables();
		printCodes();
	}
	cin.rdbuf(stdin_backup);
	Interpret();

	getchar();
	return 0;
}
