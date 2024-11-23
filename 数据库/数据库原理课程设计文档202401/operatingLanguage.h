//���ݿ����
//���� / �л����ݿ⣺ use <���ݿ�����>;		//���򴴽�,����ʹ��
//ɾ�����ݿ� ��		  db.dropDatabase();		//������ȷ������ʹ�ø����ݿ⡣
//չʾ���ݿ�������Ϣ��db.showDatabase(); //������ȷ������ʹ�ø����ݿ⡣
//
//���ϲ���
//��������db.createCollection("<��������>");
//ɾ������db.deleteCollection("<��������>");
//��ѯ����db.inquiryCollection("<��������>");
//չʾ����db.showCollection("<��������>");
//
//�ĵ�����
//�����ĵ�db.<��������>.createDocument("<�ĵ�����>", "<�ĵ�����>��);
//ɾ���ĵ�db.<��������>.deleteDocument("<�ĵ�����>");
//�޸��ĵ�db.<��������>.updateDocument("<�ĵ�����>", "<�ĵ�����>��);
//��ѯ�ĵ�db.<��������>.inquiryDocument("<�ĵ�����>");
//չʾ�ĵ�db.<��������>.showDocument("<�ĵ�����>");

#include"dataStructure.h"

using namespace std;

vector<char> instruction;	//����ָ��
int index = 0;				//ָ������
int sym;					//��������
string id;					//��ʶ��
float num_f;				//ʵ����ֵ

//����ö��
enum sym_Type {
	IDENT,      //��ʶ��
	NUM_REAL,	//ʵ��
	ERR,		//����
	DOT,		//С����
	LEFTP,		//������
	RIGHTP,		//������
	QUOTATION,	//����
	SEMICOLON,	//�ֺ�
	COMMA,		//����
};

//��ȡ�ַ�
char getch() {
	if (index == instruction.size()) return EOF;
	return instruction[index++];
}

//��ȡ����
int getsym() {
	string nowSym = "";
	char ch = getch();
	while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
		ch = getch();
	} //���˿ո��Ʊ�������з����س���
	if (ch == EOF) {
		sym = EOF;
		return sym;
	}
	else if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z') {//��ͷ����ĸ
		do {
			nowSym += ch;
			ch = getch();
		} while (((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) && ch != EOF);
		index--;
		if (ch != EOF) {
			sym = IDENT;
			id = nowSym;
			return sym;
		}
		else {
			sym = ERR;
			return sym;
		}
	}
	//��ͷ������
	else if (ch >= '0' && ch <= '9') {
		int integer = 0;
		float real = 0;
		do {
			nowSym += ch;
			integer = 10 * integer + ch - '0';
			ch = getch();
		} while ((ch >= '0' && ch <= '9') && ch != EOF);//��ȡ������ֵ(��ȡС����ǰ����)
		if (ch != EOF) {
			if (ch == '.') {//��ֵ����С����
				ch = getch();//���С�����һλ�ַ�
				if (ch >= '0' && ch <= '9') {//С����������֣�ȷ��Ϊʵ��
					nowSym += '.';
					real = (float)integer;
					float k = 1;//С��λ
					do {
						nowSym += ch;
						k /= 10;
						real += k * (ch - '0');
						ch = getch();
					} while ((ch >= '0' && ch <= '9') && ch != EOF);//��ȡ����С������
					index--;
					if (ch != EOF) {
						sym = NUM_REAL;//��������Ϊʵ��
						num_f = real;
						return sym;
					}
					else {
						sym = ERR;
						return sym;
					}
				}
				else {
					sym = ERR;
					return sym;
				}
			}
			else {
				index--;
				sym = NUM_REAL;
				num_f = float(integer);
				return sym;
			}
		}
		else {
			sym = ERR;
			return sym;
		}
	}
	else if (ch == '.') {
		sym = DOT;
		id = ".";
		return sym;
	}
	else if (ch == '(') {
		sym = LEFTP;
		id = "(";
		return sym;
	}
	else if (ch == ')') {
		sym = RIGHTP;
		id = ")";
		return sym;
	}
	else if (ch == '"') {
		sym = QUOTATION;
		id = "\"";
		return sym;
	}
	else if (ch == ';') {
		sym = SEMICOLON;
		id = ";";
		return sym;
	}
	else if (ch == ',') {
		sym = COMMA;
		id = ",";
		return sym;
	}
	else {
		sym = -1;
		return sym;
	}
	return EOF;
}

//���ݿ����
void useDatabase();			//����/�л����ݿ�
void dropDatabase();		//ɾ�����ݿ�
void showDatabase();		//չʾ���ݿ�

//���ϲ���
void createCollection();	//��������
void deleteCollection();	//ɾ������
void inquiryCollection();	//��ѯ����
void showCollection();		//չʾ����

//�ĵ�����
void createDocument();		//�����ĵ�
void deleteDocument();		//ɾ���ĵ�
void updateDocument();		//�޸��ĵ�
void inquiryDocument();		//��ѯ�ĵ�
void showDocument();		//չʾ�ĵ�

//������
void errorSolution() {
	cout << "�������" << endl;
}

string tempCol;//��¼ָ���еļ�������

//ָ��ʶ��
void identifyInstruction() {
	index = 0;
	if (getsym() == IDENT) {
		if (id == "use")
			useDatabase();
		else if (id == "db") {
			if (getsym() == DOT && getsym() == IDENT) {
				tempCol = id;
				if (id == "dropDatabase")
					dropDatabase();
				else if (id == "showDatabase")
					showDatabase();
				else if (id == "createCollection")
					createCollection();
				else if (id == "deleteCollection")
					deleteCollection();
				else if (id == "inquiryCollection")
					inquiryCollection();
				else if (id == "showCollection")
					showCollection();
				else if (getsym() == DOT && getsym() == IDENT) {
					if (id == "createDocument")
						createDocument();
					else if (id == "deleteDocument")
						deleteDocument();
					else if (id == "updateDocument")
						updateDocument();
					else if (id == "inquiryDocument")
						inquiryDocument();
					else if (id == "showDocument")
						showDocument();
					else
						errorSolution();
				}
				else
					errorSolution();
			}
			else
				errorSolution();
		}
		else
			errorSolution();
	}
	else
		errorSolution();
}

void useDatabase() {
	string temp;
	if (getsym() == IDENT) {
		temp = id;
		if (getsym() == SEMICOLON) {
			user_now.insertDatabase(temp);
			databasePath = userPath / temp;
			cout << "���ݿ��л��ɹ�,��ǰ���ݿ�·����"<< databasePath << endl;
		}
	}
	else
		errorSolution();
}


void dropDatabase() {
	if (getsym() == LEFTP && getsym() == RIGHTP && getsym() == SEMICOLON) {
		if (databasePath != userPath) {
			user_now.deleteDatabase(databasePath.filename().string());
			databasePath = userPath;
		}
		else
			errorSolution();
	}
	else
		errorSolution();
};

void showDatabase() {
	if (getsym() == LEFTP && getsym() == RIGHTP && getsym() == SEMICOLON) {
		if (databasePath != userPath) {
			user_now.findDatabase(databasePath.filename().string())->showDatabase();
		}
		else
			errorSolution();
	}
	else
		errorSolution();
};

void createCollection() {
	if (getsym() == LEFTP && getsym() == QUOTATION && getsym() == IDENT) {
		string temp = id;
		if (getsym() == QUOTATION && getsym() == RIGHTP && getsym() == SEMICOLON) {
			if (databasePath != userPath) {
				user_now.findDatabase(databasePath.filename().string())->insertCollection(temp);
			}
			else
				errorSolution();
		}else
			errorSolution();
	}
	else
		errorSolution();
};

void deleteCollection() {
	if (getsym() == LEFTP && getsym() == QUOTATION && getsym() == IDENT) {
		string temp = id;
		if (getsym() == QUOTATION && getsym() == RIGHTP && getsym() == SEMICOLON) {
			if (databasePath != userPath) {
				user_now.findDatabase(databasePath.filename().string())->deleteCollection(temp);
			}
			else
				errorSolution();
		}
		else
			errorSolution();
	}
	else
		errorSolution();
};

void inquiryCollection() {
	if (getsym() == LEFTP && getsym() == QUOTATION && getsym() == IDENT) {
		string temp = id;
		if (getsym() == QUOTATION && getsym() == RIGHTP && getsym() == SEMICOLON) {
			if (databasePath != userPath) {
				user_now.findDatabase(databasePath.filename().string())->findCollection(temp);
			}
			else
				errorSolution();
		}
		else
			errorSolution();
	}
	else
		errorSolution();
};

void showCollection() {
	if (getsym() == LEFTP && getsym() == QUOTATION && getsym() == IDENT) {
		string temp = id;
		if (getsym() == QUOTATION && getsym() == RIGHTP && getsym() == SEMICOLON) {
			if (databasePath != userPath) {
				user_now.findDatabase(databasePath.filename().string())->findCollection(temp)->showCollection();
			}
			else
				errorSolution();
		}
		else
			errorSolution();
	}
	else
		errorSolution();
};

void createDocument() {
	if (getsym() == LEFTP && getsym() == QUOTATION && getsym() == IDENT) {
		Document tempDuc = Document();
		tempDuc.document_name = id+".txt";
		if (getsym() == QUOTATION && getsym() == COMMA && getsym() == QUOTATION && getsym() == IDENT) {
			tempDuc.content = id;
			if (getsym() == QUOTATION && getsym() == RIGHTP && getsym() == SEMICOLON) {
				if (databasePath != userPath) {
					user_now.findDatabase(databasePath.filename().string())->findCollection(tempCol)->insertDocument(tempDuc);
				}
				else
					errorSolution();
			}
			else
				errorSolution();
		}
		else
			errorSolution();
	}
	else
		errorSolution();
};


void deleteDocument() {
	if (getsym() == LEFTP && getsym() == QUOTATION && getsym() == IDENT) {
		string temp = id + ".txt";
		if (getsym() == QUOTATION && getsym() == RIGHTP && getsym() == SEMICOLON) {
			if (databasePath != userPath) {
				user_now.findDatabase(databasePath.filename().string())->findCollection(tempCol)->deleteDocument(temp);
			}
			else
				errorSolution();
		}
		else
			errorSolution();
	}
	else
		errorSolution();
};

void updateDocument() {
	if (getsym() == LEFTP && getsym() == QUOTATION && getsym() == IDENT) {
		string tempDuc = id + ".txt";
		if (getsym() == QUOTATION && getsym() == COMMA && getsym() == QUOTATION && getsym() == IDENT) {
			string tempCon = id;
			if (getsym() == QUOTATION && getsym() == RIGHTP && getsym() == SEMICOLON) {
				if (databasePath != userPath) {
					user_now.findDatabase(databasePath.filename().string())->findCollection(tempCol)->updateDocument(tempDuc, tempCon);
				}
				else
					errorSolution();
			}
			else
				errorSolution();
		}
		else
			errorSolution();
	}
	else
		errorSolution();
};

void inquiryDocument() {
	if (getsym() == LEFTP && getsym() == QUOTATION && getsym() == IDENT) {
		string temp = id + ".txt";
		if (getsym() == QUOTATION && getsym() == RIGHTP && getsym() == SEMICOLON) {
			if (databasePath != userPath) {
				user_now.findDatabase(databasePath.filename().string())->findCollection(tempCol)->findDocument(temp);
			}
			else
				errorSolution();
		}
		else
			errorSolution();
	}
	else
		errorSolution();
};

void showDocument() {
	if (getsym() == LEFTP && getsym() == QUOTATION && getsym() == IDENT) {
		string temp = id + ".txt";
		if (getsym() == QUOTATION && getsym() == RIGHTP && getsym() == SEMICOLON) {
			if (databasePath != userPath) {
				user_now.findDatabase(databasePath.filename().string())->findCollection(tempCol)->findDocument(temp)->showDocument();
			}
			else
				errorSolution();
		}
		else
			errorSolution();
	}
	else
		errorSolution();
};