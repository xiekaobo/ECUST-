
#ifndef RUN_PL0_GETSYM_H
#define RUN_PL0_GETSYM_H
#define keywords_num 29
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


vector<int> integerArray;//������̬����
vector<float> realArray;//ʵ����̬����
vector<string> identifierArray;//��ʶ����̬����
const string keywords[keywords_num] = 
{ 
	"const",	//0
	"var",		//1
	"procedure", //2
	"begin",	// 3
	"end",		//4
	"odd",		//5			 
	"if",		//6
	"then",		//7
	"call",     //8
	"while",	//9
	"do",		//10
	"read",		//11
	"write",	//12

	"type",
	"array",
	"of",
	"integer",
	"real",
	"Boolean",
	"function",
	"else",
	"exit",
	"or",
	"and",
	"not",
	"div",
	"mod",
	"true",
	"false",


};//�ؼ���
int lineSum = 0; //��¼Դ��������������ڳ�����
//ifstream fcin;   //���ļ�NOLINT
char FileBuff[1 * 1 << 20];//�ļ�������
long long Cur = 0;//���ļ���λ��

bool IsKey = false;
int SYM_type;//�ؼ������ͣ����
int Int_numValue = 0;//�޷���������ֵ
float Real_numValue = 0;//ʵ����ֵ
string id;
//#if DEBUG
string debugId;  //�ʷ����������ı�ʶ��
string Int_debugNum; //�ʷ������������޷���������string��ʽ
int Int_debugNumber; //�ʷ������������޷�������
string Real_debugNum; //�ʷ�����������ʵ����string��ʽ
float Real_debugNumber; //�ʷ�����������ʵ��

//#endif

//����ö��
enum SYM_class {
	CONST_SYM,     // const
	VAR_SYM,       // var
	PROCEDURE_SYM, // procedure
	BEGIN_SYM,     // begin
	END_SYM,       // end
	ODD_SYM,       // odd
	IF_SYM,        // if
	THEN_SYM,      // then
	CALL_SYM,      // call
	WHILE_SYM,     // while
	DO_SYM,        // do
	READ_SYM,      // read
	WRITE_SYM,     // write

	TYPE_SYM,		//type
	ARRAY_SYM,		//array
	OF_SYM,			//of
	INTEGER_SYM,	//integer
	REAL_SYM,		//real
	BOOLEAN_SYM,	//Boolean
	FUNCTION_SYM,	//function
	ELSE_SYM,		//else
	EXIT_SYM,		//exit
	OR_SYM,			//or
	AND_SYM,		//and
	NOT_SYM,		//not
	INT_DIV_SYM,	//div
	MOD_SYM,		//mod
	TRUE_SYM,		//true
	FALSE_SYM,		//false
	//�������
	ADD_SYM,       // +
	SUB_SYM,       // -
	MULT_SYM,      // *
	DIV_SYM,       // /
	EQUAL_SYM,     // =
	NEQUAL_SYM,    // <>
	LESS_SYM,      // <
	ELESS_SYM,     // <=
	GRE_SYM,       // >
	EGRE_SYM,      // >=
	LEFTP_SYM,     // (
	RIGHTP_SYM,    // )
	DOT_SYM,       // .
	COMMA_SYM,     // ,
	ASSI_SYM,      // :=
	COLON_SYM,      // :������
	SEMICOLON_SYM, // ;
	INT_NUM_SYM,	//����
	REAL_NUM_SYM,	//ʵ��
	//NUM_SYM,       //����
	IDE_SYM        //��ʶ��
};

//�ʷ�������������
enum ERROR_CODE 
{ 
	TOOLONG,	//̫��
	ASSI_ERROR, //��ֵ����
	ANOTHER_WORD, //��ʶ��
	WRONG_NUMBER //������
};

int insertIdentifier(const string& str) //���뵽��ʶ�����ű�
{
	int location = 0;
	auto itd = identifierArray.begin();//��ʶ����̬����Ŀ�ʼ
	for (; itd != identifierArray.end(); ++itd) {
		if (*itd == str)
			break;
		location++;
	}
	if (itd == identifierArray.end()) {
		identifierArray.push_back(str);//���µı�ʶ������
		return location;//���ر�ʶ������λ��
	}
	else
		return location;//���ر�ʶ������λ��
}

int insertConst(int number) //���뵽������
{
	int location = 0;
	auto itd = integerArray.begin();//������̬���鿪ʼ
	for (; itd != integerArray.end(); ++itd) {
		if (*itd == number)//���е�����������ѭ��
			break;
		location++;
	}
	if (itd == integerArray.end()) {
		integerArray.push_back(number);//���µ�������
		return location;//������������λ��
	}
	else
		return location;
}

int insertReal(float number) //���뵽ʵ����
{
	int location = 0;
	auto itd = realArray.begin();//ʵ����̬���鿪ʼ
	for (; itd != realArray.end(); ++itd) {
		if (*itd == number)//���е�ʵ��������ѭ��
			break;
		location++;
	}
	if (itd == realArray.end()) {
		realArray.push_back(number);//���µ�������
		return location;//����ʵ������λ��
	}
	else
		return location;
}

int error(int ERROR_CODE_TYPE) { // NOLINT
	switch (ERROR_CODE_TYPE) {
	case TOOLONG:
		cout << "Identifier " << id << " in line " << lineSum << " is too long" << endl;
		break;
	case ASSI_ERROR:
		cout << "wrong assignment in line " << lineSum << endl;
		break;
	case ANOTHER_WORD:
		cout << "wrong words in line " << lineSum << endl;
		break;
	case WRONG_NUMBER:
		cout << "wrong number in line " << lineSum << endl;
		break;
	default:
		break;
	}
	return -1;
}

/*template<class T>
void print_result(int sym, T name,  int value)
{
	;
	switch (sym) {
		case NUM_SYM:
			cout << "( number," << name << "," << value << " )" << endl;
			break;
		case IDE_SYM:
			cout << "( identifier," << name << "," << value << " )" << endl;
			break;
		default:
			break;
	}
}*/

/*void print_result(int sym)
{
	;
	switch (sym) {
		case CONST_SYM:
			cout << "( 'const',- )" << endl;
			break;
		case VAR_SYM:
			cout << "( 'var',- )" << endl;
			break;
		case PROCEDURE_SYM:
			cout << "( 'procedure',- )" << endl;
			break;
		case BEGIN_SYM:
			cout << "( 'begin',- )" << endl;
			break;
		case END_SYM:
			cout << "( 'end',- )" << endl;
			break;
		case ODD_SYM:
			cout << "( 'odd',- )" << endl;
			break;
		case IF_SYM:
			cout << "( 'if',- )" << endl;
			break;
		case THEN_SYM:
			cout << "( 'then',- )" << endl;
			break;
		case CALL_SYM:
			cout << "( 'call',- )" << endl;
			break;
		case WHILE_SYM:
			cout << "( 'while',- )" << endl;
			break;
		case DO_SYM:
			cout << "( 'do',- )" << endl;
			break;
		case READ_SYM:
			cout << "( 'read',- )" << endl;
			break;
		case WRITE_SYM:
			cout << "( 'write',- )" << endl;
			break;
		case ADD_SYM:
			cout << "( '+',- )" << endl;
			break;
		case SUB_SYM:
			cout << "( '-',- )" << endl;
			break;
		case MULT_SYM:
			cout << "( '*',- )" << endl;
			break;
		case DIV_SYM:
			cout << "( '/',- )" << endl;
			break;
		case EQUAL_SYM:
			cout << "( '=',- )" << endl;
			break;
		case NEQUAL_SYM:
			cout << "( '#',- )" << endl;
			break;
		case LESS_SYM:
			cout << "( '<',- )" << endl;
			break;
		case ELESS_SYM:
			cout << "( '<=',- )" << endl;
			break;
		case GRE_SYM:
			cout << "( '>',- )" << endl;
			break;
		case EGRE_SYM:
			cout << "( '>=',- )" << endl;
			break;
		case LEFTP_SYM:
			cout << "( '(',- )" << endl;
			break;
		case RIGHTP_SYM:
			cout << "( ')',- )" << endl;
			break;
		case DOT_SYM:
			cout << "( '.',- )" << endl;
			break;
		case COMMA_SYM:
			cout << "( ',',- )" << endl;
			break;
		case ASSI_SYM:
			cout << "( ':=',- )" << endl;
			break;
		case SEMICOLON_SYM:
			cout << "( ';',- )" << endl;
			break;
		default:
			break;
	}
}*/

string GETSYM() {
	IsKey = false;//��ʼ��Ϊfalse
	string strToken; //��Ź��ɵ��ʵ��ַ���
	strToken = "";
	char ch; //������¶�����Դ�����ַ�
	ch = FileBuff[Cur]; Cur++;
	while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
		if (ch == '\n')
			lineSum++;//�������з���������1
		ch = FileBuff[Cur]; Cur++;
	} //���˿ո�tab�����з������Ի��з�����ͳ�ƣ��Ա��ڶ�λ����λ�á�
	while (ch == '/') {//����ע��,����λ�ã���Ϊѭ����������������ע��
		ch = FileBuff[Cur]; Cur++;
		if (ch == '/') {
			ch = FileBuff[Cur]; Cur++;
			while (ch != '\n') {//���ǻ��з���һֱ���룬������
				ch = FileBuff[Cur]; Cur++;
			}
			lineSum++;//�������з���������1
			
			ch = FileBuff[Cur]; Cur++;
			while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
				if (ch == '\n')
					lineSum++;//�������з���������1
				ch = FileBuff[Cur]; Cur++;
			} //���˿ո�tab�����з������Ի��з�����ͳ�ƣ��Ա��ڶ�λ����λ�á�
		}
		else if (ch == '*') {
			ch = FileBuff[Cur]; Cur++;
			while ( FileBuff[Cur-2] != '*'||ch != '/') {//û������*/��ѭ��Cur-2��λ�ò���*
				if (ch == '\n')
					lineSum++;//�������з���������1
				ch = FileBuff[Cur]; Cur++;
			}

			ch = FileBuff[Cur]; Cur++;
			while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
				if (ch == '\n')
					lineSum++;//�������з���������1
				ch = FileBuff[Cur]; Cur++;
			} //���˿ո�tab�����з������Ի��з�����ͳ�ƣ��Ա��ڶ�λ����λ�á�
		}
		else {
			Cur--;
			SYM_type = DIV_SYM;
			// print_result(SYM_type);
			return "/";
		}

	}
	if (ch == EOF) {
		return "finish";
	}
	if (isalpha(ch)) { // ch����ĸ���򵥴ʿ����Ǳ�ʶ�����߹ؼ���
		do {
			strToken += ch;
			ch = FileBuff[Cur]; 
			Cur++;
		} while (isalpha(ch) || isdigit(ch));
		id = strToken;
		if (id.size() > 10) { //�ؼ������ʶ���Ĵ�С����Ϊ10
			error(TOOLONG);//����
			return "error";
		}
		for (int i = 0; i < keywords_num; ++i) //�����Ƿ����ڹؼ���
			if (id == keywords[i]) {
				IsKey = true;
				SYM_type = i;
				break;
			}
		if (IsKey) { //�ؼ��ֵ����
			;        // print_result(SYM_type);
		}
		else {     //��ʶ�������
			SYM_type = IDE_SYM;
			insertIdentifier(id);
			// print_result<string>(SYM_type, id, insertIdentifier(id));
			//#if DEBUG
			debugId = id;
			//#endif
			id = "identifier";
		}
		Cur--;//���˶���ַ�
		return id;
	}
	else if (isdigit(ch)) {//������ʵ������
		int count = 0;
		float real = 0;
		do {
			strToken += ch;//���ַ�
			count = count * 10 + ch - '0';//��ֵ
			ch = FileBuff[Cur]; 
			Cur++;//��ȡλ����ǰ��
		} while (isdigit(ch));
		SYM_type = INT_NUM_SYM;//����������Ϊ��������
		//����ʵ���ʷ�����
		if (ch == '.') {
			strToken += ch;//�ӵ�
			ch = FileBuff[Cur];
			Cur++;//ָ����һ���ַ�
			real = (float)count;
			int i = 0;//���ڼ�¼С������λ��
			float add_num;
			while (isdigit(ch)) {//С����֮����ַ�
				i++;
				strToken += ch;//ʵ���ַ�
				add_num = ch - '0';
				for (int j = 0; j < i; j++) {
					add_num /= 10;
				}
				real += add_num;//ʵ��ֵ
				ch = FileBuff[Cur];
				Cur++;//��ȡλ����ǰ��
			}
			SYM_type = REAL_NUM_SYM;//���ʵ������
		}
		if (isalpha(ch)) {
			error(WRONG_NUMBER);//��������ַ����������֣�����
			return "error";
		}
		if (SYM_type == REAL_NUM_SYM) {
			Real_numValue = real;
			Cur--;
			insertReal(Real_numValue);
			Real_debugNum = strToken;
			Real_debugNumber = Real_numValue;
			return "real_number";
		}
		else if(SYM_type==INT_NUM_SYM){
			Int_numValue = count;
			Cur--;
			insertConst(Int_numValue);//���뵽��������
			// print_result<int>(SYM_type, Int_numValue, insertConst(Int_numValue));
			//#if DEBUG
			Int_debugNum = strToken;
			Int_debugNumber = Int_numValue;
			//#endif
			return "int_number";
		}
		
	}
	else if (ch == '+') {
		SYM_type = ADD_SYM;
		// print_result(SYM_type);
		return "+";
	}
	else if (ch == '-') {
		SYM_type = SUB_SYM;
		// print_result(SYM_type);
		return "-";
	}
	else if (ch == '*') {
		SYM_type = MULT_SYM;
		// print_result(SYM_type);
		return "*";
	}
	else if (ch == '=') {
		SYM_type = EQUAL_SYM;
		// print_result(SYM_type);
		return "=";
	}
	else if (ch == '<') {
		ch = FileBuff[Cur]; Cur++;
		if (ch == '=') {
			SYM_type = ELESS_SYM;
			// print_result(SYM_type);
			return "<=";
		}
		else if (ch == '>') {
			SYM_type = NEQUAL_SYM;
			return "<>";
		}
		else {
			SYM_type = LESS_SYM;
			// print_result(SYM_type);
			Cur--;

			return "<";
		}
	}
	else if (ch == '>') {
		ch = FileBuff[Cur]; Cur++;
		if (ch == '=') {
			SYM_type = EGRE_SYM;
			// print_result(SYM_type);
			return ">=";
		}
		else {
			SYM_type = GRE_SYM;
			// print_result(SYM_type);
			Cur--;

			return ">";
		}
	}
	else if (ch == '(') {
		SYM_type = LEFTP_SYM;
		// print_result(SYM_type);
		return "(";
	}
	else if (ch == ')') {
		SYM_type = RIGHTP_SYM;
		// print_result(SYM_type);
		return ")";
	}
	else if (ch == '.') {
		SYM_type = DOT_SYM;
		// print_result(SYM_type);
		return ".";
	}
	else if (ch == ',') {
		SYM_type = COMMA_SYM;
		// print_result(SYM_type);
		return ",";
	}
	else if (ch == ':') {//��ӡ�:������
		ch = FileBuff[Cur]; Cur++;
		if (ch == '=') {
			SYM_type = ASSI_SYM;
			// print_result(SYM_type);
			return ":=";
		}
		else {//
			SYM_type = COLON_SYM;
			Cur--;
			return ":";
			/*error(ASSI_ERROR);
			return "error_assi_error";*/
		}
	}
	else if (ch == ';') {
		SYM_type = SEMICOLON_SYM;
		// print_result(SYM_type);
		return ";";
	}
	else if (ch == '%') {
		SYM_type = MOD_SYM;
		// print_result(SYM_type);
		return "%";
	}
	else {
		error(ANOTHER_WORD);
		return "error";
	}
	return nullptr;
}

#endif // RUN_PL0_GETSYM_H
