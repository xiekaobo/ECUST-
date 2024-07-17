#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <cstring>
#define		MAX_LENGTH_OF_A_WORD				10		//һ�����ʵ�����ַ�����
#define		MAX_NUMBER_OF_WORDS					1000	//��ʶ�����൥�ʸ���
#define		MAX_NUMBER_INSTRUCTS					200		//���������ָ����
#define		MAX_NUMBER_NAME_TABLE				100		//���ֱ��еĳ���

enum	WORD_TYPE_ENUM {//��������ö��ֵ
	INVALID_WORD,
	IDENTIFIER,
	NUMBER,
	CONST,
	VAR,
	PROCEDURE,
	BEGIN,
	END,
	IF,
	THEN,
	WHILE,
	DO,
	WRITE,
	READ,
	CALL,
	LEFT_PARENTHESIS,
	RIGHT_PARENTHESIS,
	COMMA,
	SEMICOLON,
	PERIOD,
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,
	ODD,
	EQL,
	NEQ,
	LES,
	LEQ,
	GTR,
	GEQ,
	ASSIGN,
	DTA,
	SL_COMMENT,//
	ML_COMMENT,
	BOOL,
	TRUE,
	FALSE,
	FLOAT,
	ELSE,
	FOR
};

struct	WORD_STRUCT {//һ�����ʵ����ݽṹ
	char												szName[MAX_LENGTH_OF_A_WORD];//�������ֵ��ַ���
	enum WORD_TYPE_ENUM		eType;//��������ö��ֵ
	double												nNumberValue;//�����ʵ�ֵ
	int												nLineNo;//��Դ�����ļ��е������ڵ�����
};

enum	TYPE_ENUM {
	CONSTANT_TYPE,
	VARIABLE_TYPE,
	PROCEDURE_TYPE,
};

//���ֱ�ṹ
struct TABLE_STRUCT
{
	char											szName[MAX_LENGTH_OF_A_WORD];	//�����ַ���
	enum TYPE_ENUM				eType;					//����,const, var, array or procedure
	int											nVal;					//���ʵ���ֵ
	int											nLevel;					//������,��const��ʹ��
	int											nAddress;			//��ַ,��const��ʹ��
	int											nSize;					//��Ҫ������������ռ�,��procedureʹ��
};
TABLE_STRUCT				g_NameTable[MAX_NUMBER_NAME_TABLE];//���ֱ�
int										g_nNameTableIndex;//���ֱ��±�

//�����ָ�������
enum	INSTRUCT_ENUM {
	JMP_INSTRUCT,				//ֱ����ת����ַΪ��������ָ��
	JPC_INSTRUCT,				//������ת.���ջ�����ݵ�����,����תִ�е�ַΪ��������ָ��,����ִ����һ��ָ��
	ALLOCATE_INSTRUCT,	//�����ڴ�,ջ��ָ�����Ӳ�����
	INSTANT_INSTRUCT,		//ֱ�ӽ���������ֵѹ��ջ��
	LOAD_INSTRUCT,			//ȡĳ����̵���Ե�ַΪ���������ڴ��ֵ��ջ��
	STORE_INSTRUCT,			//��ջ�����ݴ浽ĳ����̵���Ե�ַΪ���������ڴ���
	CALL_INSTRUCT,				//���ù���,���ص�ַѹջ
	ENDCALL_INSTRUCT,		//��������,��ջ,���ص�ԭ���ù��̴�
	NEGATIVE_INSTRUCT,	//ȡ������,��ջ������ȡ�����Է���ջ��
	ADD_INSTRUCT,				//�ӷ�ָ��,ȡ��ջ�����ݺʹ�ջ�����ݵĺ��ٷŵ�ջ��
	SUB_INSTRUCT,				//����ָ��,ȡ��ջ�����ݺʹ�ջ�����ݵĲ��ٷŵ�ջ��
	MULTI_INSTRUCT,			//���ָ��,ȡ��ջ�����ݺʹ�ջ�����ݵĻ��ٷŵ�ջ��
	DIVID_INSTRUCT,			//���ָ��,ȡ��ջ�����ݺʹ�ջ�����ݵ����ٷŵ�ջ��
	ODD_INSTRUCT,				//�ж�ջ�������Ƿ�Ϊ����.�����,��ջ������Ϊ1,����Ϊ0
	EQL_INSTRUCT,				//ȡ�����ж�ջ�����ݺʹ�ջ�������Ƿ���ͬ.�����ͬ,��ջ������Ϊ1,����Ϊ0
	NEQ_INSTRUCT,				//ȡ�����ж�ջ�����ݺʹ�ջ�������Ƿ���ͬ.�����ͬ,��ջ������Ϊ0,����Ϊ1
	LES_INSTRUCT,				//ȡ�����жϴ�ջ�������Ƿ�С��ջ������.�����,��ջ������Ϊ1,����Ϊ0
	LEQ_INSTRUCT,				//ȡ�����жϴ�ջ�������Ƿ�С�ڵ���ջ������.�����,��ջ������Ϊ1,����Ϊ0
	GTR_INSTRUCT,				//ȡ�����жϴ�ջ�������Ƿ����ջ������.�����,��ջ������Ϊ1,����Ϊ0
	GEQ_INSTRUCT,				//ȡ�����жϴ�ջ�������Ƿ���ڵ���ջ������.�����,��ջ������Ϊ1,����Ϊ0��
	OUT_INSTRUCT,				//�������ָ��,���ջ������
	IN_INSTRUCT,					//��������ָ��,��ȡ���ݵ�ջ��
};
//�����ָ��ṹ
struct INSTRUCT_STRUCT
{
	enum INSTRUCT_ENUM		eInstruct;		//������
	int											nLevel;			//���ò���������Ĳ�β�
	int											nOperand;	//������
};
INSTRUCT_STRUCT			g_Instructs[MAX_NUMBER_INSTRUCTS];//���ɺ�Ĵ������
int										g_nInstructsIndex;//�����ָ��ָ��,ȡֵ��Χ[0,MAX_NUMBER_INSTRUCTS-1]

void InitializeInstructs();
void InitializeNameTable();
int BlockGenerate(int nLevel, int nIndentNum);
int OneConstantGenerate(int nLevel, int* pAddressInCurrentLevel, int nIndentNum);
int OneVariableGenerate(int nLevel, int* pAddressInCurrentLevel, int nIndentNum);
int StatementGenerate(int nLevel, int nIndentNum);
int ConditionGenerate(int nLevel, int nIndentNum);
int ExpressionGenerate(int nLevel, int nIndentNum);
int TermGenerate(int nLevel, int nIndentNum);
int FactorGenerate(int nLevel, int nIndentNum);
void PrintInGenerate(int nWordsIndex, int nIndentNum, char* pString);
int InstructFromEnumToString(enum INSTRUCT_ENUM eInstruct, char* szString);
int GenerateOneInstruction(INSTRUCT_ENUM eInstruct, int nLevel, int nAddress);
void PrintAllInstructions();
void PrintAVariable(int nNameTableIndex);
void RegisterInNameTable(enum TYPE_ENUM eType, char* szName, int nNumberValue, int* pAddressInThisLevel, int nLevel);

extern	WORD_STRUCT			g_Words[MAX_NUMBER_OF_WORDS];
extern	int									g_nWordsIndex;
extern	int									g_nInstructsIndex;

int GenerateAnalysis()
{
	InitializeInstructs();
	InitializeNameTable();

	printf("\n----------------Generate Begin!--------------\n");
	printf("No  Line--(Word)-----\t\t\t        Index Instructs  Level Address\n");

	g_nWordsIndex = 0;
	g_nNameTableIndex = 0;
	g_nInstructsIndex = 0;//��һ��ָ�����aInstructs[0]��

	PrintInGenerate(g_nWordsIndex, 0, "Block");//��ӡ������Ϣ
	BlockGenerate(0, 1);//�����ɷֳ���Block��ʼ

	if (g_Words[g_nWordsIndex].eType == PERIOD)//�����'.'����
	{
		PrintInGenerate(g_nWordsIndex, 0, "PERIOD");//��ӡ������Ϣ
		printf("\n----------------Generate Successfull Finished!--------------\n");

		PrintAllInstructions();//����ӡ�������ɵ�ָ��

		return OK;
	}
	else
		return ERROR;
}

void InitializeInstructs()//��ʼ���������
{
	int i;

	for (i = 0; i < MAX_NUMBER_INSTRUCTS; i++)
	{
		g_Instructs[i].eInstruct = (INSTRUCT_ENUM)-1;
		g_Instructs[i].nLevel = -1;
		g_Instructs[i].nOperand = -1;
	}
}

void InitializeNameTable()//��ʼ�����ֱ�
{
	int	i;

	for (i = 0; i < MAX_NUMBER_NAME_TABLE; i++)
	{
		g_NameTable[i].eType = (TYPE_ENUM)-1;
		g_NameTable[i].nAddress = -1;
		g_NameTable[i].nLevel = -1;
		g_NameTable[i].nSize = -1;
		g_NameTable[i].nVal = -1;
		g_NameTable[i].szName[0] = '\0';
	}
}
//"�ֳ���"Block��������
int BlockGenerate(int nLevel, int nIndentNum)//nLevel�Ƿֳ������ڵĲ��,nIndentNum�Ǵ�ӡʱҪ�����Ŀո���
{
	int		nCurrentLevelAddress;
	int		nCurrentLevelFirstInstructAddress;//���ַ��䵽����Ե�ַ
	int		nCurrentLevelNameTableFirstIndex;//���汾�����ֱ��еĳ�ʼλ��

	nCurrentLevelAddress = 3;//����ָ��ƫ�Ƶ�ַ,ÿ��"�ֳ���"(Block)�ı���ָ��ƫ�Ƶ�ַ��3��ʼ
	nCurrentLevelNameTableFirstIndex = g_nNameTableIndex;//�������ֱ��б������ֵĳ�ʼλ��
	g_NameTable[g_nNameTableIndex].nAddress = g_nInstructsIndex;//�����ֱ��м�¼����ָ��ĳ�ʼλ��

	GenerateOneInstruction(JMP_INSTRUCT, 0, 0);//����JMP��ת�������1��ָ��

	if (g_Words[g_nWordsIndex].eType == CONST)//�����ǰ������"const"
	{
		PrintInGenerate(g_nWordsIndex, nIndentNum, "CONST");//��ӡ������Ϣ

		g_nWordsIndex++;//ȡ��һ������
		PrintInGenerate(g_nWordsIndex, nIndentNum, "OneConstant");//��ӡ������Ϣ
		OneConstantGenerate(nLevel, &nCurrentLevelAddress, nIndentNum + 1);//����������һ��"��������"

		while (g_Words[g_nWordsIndex].eType == COMMA)//��������ж���','
		{
			PrintInGenerate(g_nWordsIndex, nIndentNum, "COMMA");//��ӡ������Ϣ

			g_nWordsIndex++;//ȡ��һ������
			PrintInGenerate(g_nWordsIndex, nIndentNum, "OneConstant");//��ӡ������Ϣ
			OneConstantGenerate(nLevel, &nCurrentLevelAddress, nIndentNum + 1);//�����ٴ���һ����������
		}

		if (g_Words[g_nWordsIndex].eType == SEMICOLON)//������������Էֺ�';'����
		{
			PrintInGenerate(g_nWordsIndex, nIndentNum, ";");//��ӡ������Ϣ
			g_nWordsIndex++;//ȡ��һ������
		}
		else
			return ERROR;//����,©���˶��Ż��߷ֺ�
	}
	if (g_Words[g_nWordsIndex].eType == VAR)//�����ǰ������"var"
	{
		PrintInGenerate(g_nWordsIndex, nIndentNum, "VAR");//��ӡ������Ϣ

		g_nWordsIndex++;//ȡ��һ������
		PrintInGenerate(g_nWordsIndex, nIndentNum, "OneVariable");//��ӡ������Ϣ
		OneVariableGenerate(nLevel, &nCurrentLevelAddress, nIndentNum + 1);//����������һ��"��������"

		while (g_Words[g_nWordsIndex].eType == COMMA)//��������ж���','
		{
			PrintInGenerate(g_nWordsIndex, nIndentNum, "COMMA");//��ӡ������Ϣ

			g_nWordsIndex++;//ȡ��һ������
			PrintInGenerate(g_nWordsIndex, nIndentNum, "OneVariable");//��ӡ������Ϣ
			OneVariableGenerate(nLevel, &nCurrentLevelAddress, nIndentNum + 1);//�����ٴ���һ��"��������"
		}

		if (g_Words[g_nWordsIndex].eType == SEMICOLON)//������������Էֺ�';'����
		{
			PrintInGenerate(g_nWordsIndex, nIndentNum, ";");//��ӡ������Ϣ
			g_nWordsIndex++;//ȡ��һ������
		}
		else
			return ERROR;
	}
	while (g_Words[g_nWordsIndex].eType == PROCEDURE)//�����ǰ������"procedure",�����"��������"��������
	{
		PrintInGenerate(g_nWordsIndex, nIndentNum, "PROCEDURE");//��ӡ������Ϣ

		g_nWordsIndex++;//ȡ��һ������
		if (g_Words[g_nWordsIndex].eType == IDENTIFIER)//"procedure"��ӦΪ��ʶ��
		{
			PrintInGenerate(g_nWordsIndex, nIndentNum, "IDENTIFIER");//��ӡ������Ϣ

			RegisterInNameTable(PROCEDURE_TYPE, g_Words[g_nWordsIndex].szName, -1, (int*)-1, nLevel);//�Ǽǹ����е�����
			g_nWordsIndex++;//ȡ��һ������
		}
		else
			return ERROR;

		if (g_Words[g_nWordsIndex].eType == SEMICOLON)//��ʶ����ӦΪ�ֺ�';'
		{
			PrintInGenerate(g_nWordsIndex, nIndentNum, ";");//��ӡ������Ϣ
			g_nWordsIndex++;//ȡ��һ������
		}
		else
			return ERROR;//©���˷ֺ�

		PrintInGenerate(g_nWordsIndex, nIndentNum, "Block");//��ӡ������Ϣ
		BlockGenerate(nLevel + 1, nIndentNum + 1);//��"��������"��,�ֺź�����"�ֳ���"Block

		if (g_Words[g_nWordsIndex].eType == SEMICOLON)//"�ֳ���"Block����Ӧ�Ƿֺ�';'
		{
			PrintInGenerate(g_nWordsIndex, nIndentNum, ";");//��ӡ������Ϣ
			g_nWordsIndex++;//ȡ��һ������
		}
		else
			return ERROR;//©���˷ֺ�
	}

	//��ʼ���ɵ�ǰ����ָ��
	//ȡ�������1��ָ��ĵ�ַ,��JMP_INSTRUCT 0 0ָ��ĵ�ַ
	nCurrentLevelFirstInstructAddress = g_NameTable[nCurrentLevelNameTableFirstIndex].nAddress;
	//�������1��ָ��,��JMP_INSTRUCT 0 0ָ���޸�ΪJMP_INSTRUCT 0 g_nInstructsIndex,��ת����ǰ��ָ��
	g_Instructs[nCurrentLevelFirstInstructAddress].nOperand = g_nInstructsIndex;

	//�Ǽǵ�ǰ���̵�һ��ָ���ַ
	g_NameTable[nCurrentLevelNameTableFirstIndex].nAddress = g_nInstructsIndex;
	//ǰ���������������ÿ����һ���������������nCurrentLevelAddress����l,
	//��������nCurrentLevelAddress���ǵ�ǰ�������ݵ�nSize
	g_NameTable[nCurrentLevelNameTableFirstIndex].nSize = nCurrentLevelAddress;

	GenerateOneInstruction(ALLOCATE_INSTRUCT, 0, nCurrentLevelAddress);//���ɷ����ڴ�ָ��

	PrintInGenerate(g_nWordsIndex, nIndentNum, "Statement");//��ӡ������Ϣ
	StatementGenerate(nLevel, nIndentNum + 1);//"�ֳ���"Block�б�����"���"

	GenerateOneInstruction(ENDCALL_INSTRUCT, 0, 0);//ÿ�����̳��ڶ�Ҫʹ�õ��ͷ����ݶ�ָ��

	return OK;
}
//�����ֱ��еǼǵ���
void RegisterInNameTable(enum TYPE_ENUM eType, char* szName, int nNumberValue, int* pAddressInThisLevel, int nLevel)
{
	g_nNameTableIndex++;//���ֱ�����һ���հ״�

	strcpy(g_NameTable[g_nNameTableIndex].szName, szName);//�Ǽǵ�������
	g_NameTable[g_nNameTableIndex].eType = eType;//�Ǽǵ�������

	switch (eType)//������ʵ�����
	{
	case CONSTANT_TYPE://���ʵ������ǳ���
		g_NameTable[g_nNameTableIndex].nVal = nNumberValue;//�Ǽǳ�����ֵ
		break;

	case VARIABLE_TYPE://���ʵ������Ǳ���
		g_NameTable[g_nNameTableIndex].nLevel = nLevel;//�ǼǱ������ڵĲ���
		g_NameTable[g_nNameTableIndex].nAddress = (*pAddressInThisLevel);//�ǼǱ�����������ڴ�ռ��ַ

		PrintAVariable(g_nNameTableIndex);//��ӡ�������

		(*pAddressInThisLevel)++;//�ڴ�ռ�����һ�������ĵ�ַ��һ
		break;

	case PROCEDURE_TYPE://������ʵ������ǹ���
		g_NameTable[g_nNameTableIndex].nLevel = nLevel;//�Ǽǹ������ڵĲ���
		break;
	}
}
int LookUpNameTable(char* pIdentifier)//�����ֱ��в��ҵ���(����,�����������)
{
	int		i;

	for (i = 0; i <= g_nNameTableIndex; i++)
		if (strcmp(g_NameTable[i].szName, pIdentifier) == 0)
			return i;

	return 0;
}

//"һ����������"��������
int OneConstantGenerate(int nLevel, int* pAddressInCurrentLevel, int nIndentNum)//nLevel�Ƿֳ������ڵĲ��,pAddressInCurrentLevel�Ǳ���ָ��ƫ�Ƶ�ַ(ָ��),nIndentNum�Ǵ�ӡʱҪ�����Ŀո���
{
	char	szConstantName[100];

	if (g_Words[g_nWordsIndex].eType == IDENTIFIER)//"һ����������"�Ա�ʶ����ͷ
	{
		PrintInGenerate(g_nWordsIndex, nIndentNum, "IDENTIFIER");//��ӡ������Ϣ

		strcpy(szConstantName, g_Words[g_nWordsIndex].szName);

		g_nWordsIndex++;//ȡ��һ������
		if (g_Words[g_nWordsIndex].eType == EQL)//��ʶ������Ӧ��'='
		{
			PrintInGenerate(g_nWordsIndex, nIndentNum, "EQL");//��ӡ������Ϣ

			g_nWordsIndex++;//ȡ��һ������
			if (g_Words[g_nWordsIndex].eType == NUMBER)//'='����ĵ���Ӧ����
			{
				PrintInGenerate(g_nWordsIndex, nIndentNum, "NUMBER");//��ӡ������Ϣ

				//�����ֱ��еǼǳ���
				RegisterInNameTable(CONSTANT_TYPE, szConstantName, g_Words[g_nWordsIndex].nNumberValue, pAddressInCurrentLevel, nLevel);

				g_nWordsIndex++;//ȡ��һ������
				return OK;
			}
			if (g_Words[g_nWordsIndex].eType == FLOAT)//'='����ĵ���Ӧ����
			{
				PrintInGenerate(g_nWordsIndex, nIndentNum, "FLOAT");//��ӡ������Ϣ

				//�����ֱ��еǼǳ���
				RegisterInNameTable(CONSTANT_TYPE, szConstantName, g_Words[g_nWordsIndex].nNumberValue, pAddressInCurrentLevel, nLevel);

				g_nWordsIndex++;//ȡ��һ������
				return OK;
			}
			else
				return ERROR;
		}
		else
			return ERROR;
	}
	else
		return ERROR;

	return ERROR;
}
//"һ����������"��������
int OneVariableGenerate(int nLevel, int* pAddressInCurrentLevel, int nIndentNum)//nLevel�Ƿֳ������ڵĲ��,pAddressInCurrentLevel�Ǳ���ָ��ƫ�Ƶ�ַ(ָ��),nIndentNum�Ǵ�ӡʱҪ�����Ŀո���
{
	if (g_Words[g_nWordsIndex].eType == IDENTIFIER)//һ�������������Ǳ�ʶ��
	{
		PrintInGenerate(g_nWordsIndex, nIndentNum, "IDENTIFIER");//��ӡ������Ϣ

		//�����ֱ��еǼǱ���
		RegisterInNameTable(VARIABLE_TYPE, g_Words[g_nWordsIndex].szName, g_Words[g_nWordsIndex].nNumberValue, pAddressInCurrentLevel, nLevel);

		g_nWordsIndex++;//ȡ��һ������

		return OK;
	}
	else
		return ERROR;

	return ERROR;
}

//һ��"���"��������
int StatementGenerate(int nLevel, int nIndentNum)//nLevel�Ƿֳ������ڵĲ��,nIndentNum�Ǵ�ӡʱҪ�����Ŀո���
{
	int nNameTableIndex, nInstructIndexCopy1, nInstructIndexWhenFalse, nNameTableIndexOfAssignedVariable;

	switch (g_Words[g_nWordsIndex].eType)//��ǰ����������
	{
	case IDENTIFIER://��ǰ�����Ǳ�ʶ��(����ֵ����),Ӧ����"��ֵ���"����
		//���ұ���ֵ���������������ֱ��еĵ�ַ
		nNameTableIndexOfAssignedVariable = LookUpNameTable(g_Words[g_nWordsIndex].szName);
		if (nNameTableIndexOfAssignedVariable != 0)
		{//������ҵ�,������ֵ��������������
			PrintInGenerate(g_nWordsIndex, nIndentNum, "IDENTIFIER");//��ӡ������Ϣ

			g_nWordsIndex++;//ȡ��һ������
			if (g_Words[g_nWordsIndex].eType == ASSIGN)//��ʶ������Ӧ�Ǹ�ֵ�ŵ���':='
			{
				PrintInGenerate(g_nWordsIndex, nIndentNum, "ASSIGN");//��ӡ������Ϣ

				g_nWordsIndex++;//ȡ��һ������
				PrintInGenerate(g_nWordsIndex, nIndentNum, "Expression");//��ӡ������Ϣ
				ExpressionGenerate(nLevel, nIndentNum + 1);//':='����Ӧ�Ǳ��ʽ

				//����STORE_INSTRUCTָ��,��ջ���б��ʽ��ֵ�浽����ֵ�������ڴ���ȥ
				GenerateOneInstruction(STORE_INSTRUCT, nLevel - g_NameTable[nNameTableIndexOfAssignedVariable].nLevel, g_NameTable[nNameTableIndexOfAssignedVariable].nAddress);

				return OK;
			}
		}
		return ERROR;//û�м�⵽':='����
		break;

	case IF://�����ǰ������"if",��"�������"����
	/*	PrintInGenerate(g_nWordsIndex, nIndentNum, "IF");//��ӡ������Ϣ

		g_nWordsIndex++;//ȡ��һ������

		PrintInGenerate(g_nWordsIndex, nIndentNum, "Condition");//��ӡ������Ϣ
		ConditionGenerate(nLevel, nIndentNum + 1);//"if"����"����"Condition

		if (g_Words[g_nWordsIndex].eType == THEN)//"����"��Ӧ��"then"
		{
			PrintInGenerate(g_nWordsIndex, nIndentNum, "THEN");//��ӡ������Ϣ

			g_nWordsIndex++;//ȡ��һ������

			//���浱ǰָ���ַ,��"THEN"�ļٳ��ڵ�ַ,�Ȼ���ʱ��
			nInstructIndexCopy1 = g_nInstructsIndex;
			//����������תָ��JPC_INSTRUCT,��"THEN"�ļٳ���,��ת��ַ�ȴ�����
			GenerateOneInstruction(JPC_INSTRUCT, 0, 0);

			PrintInGenerate(g_nWordsIndex, nIndentNum, "Statement");//��ӡ������Ϣ
			StatementGenerate(nLevel, nIndentNum + 1);//"then"��Ӧ��"���"

			//����ǰָ���ַ����"THEN"�ļٳ��ڵ�ַ,�������תָ��JPC_INSTRUCT�еĵ�ַ
			g_Instructs[nInstructIndexCopy1].nOperand = g_nInstructsIndex;

			return OK;
		}
		else
			return ERROR;//ȱ��then

		break;
	*/
		PrintInGenerate(g_nWordsIndex, nIndentNum, (char*)"IF");

		g_nWordsIndex++;
		if (g_Words[g_nWordsIndex].eType == LEFT_PARENTHESIS)    //  if + ������'('
		{
			PrintInGenerate(g_nWordsIndex, nIndentNum, (char*)"LEFT_PARENTHESIS");

			g_nWordsIndex++;
			PrintInGenerate(g_nWordsIndex, nIndentNum, (char*)"Condition");
			if (ConditionGenerate(nLevel, nIndentNum + 1) == -1) return ERROR;     //  if + '(' + ���� Condition

			if (g_Words[g_nWordsIndex].eType == RIGHT_PARENTHESIS)   //  + ������')'�������е���������
			{
				PrintInGenerate(g_nWordsIndex, nIndentNum, (char*)"RIGHT_PARENTHESIS");
				g_nWordsIndex++;
			}
			else
			{
				printf("if��������С���������ȱ�������š�)����");
				return ERROR;
			}

			//  ���浱ǰָ���ַ���� if �ļٳ��ڵ�ַ���Ȼ���ʱ��
			nInstructIndexWhenFalse = g_nInstructsIndex;
			//  ����������תָ�� JPC_INSTRUCT���� if �ļٳ��ڣ���ת��ַ�ȴ�����
			GenerateOneInstruction(JPC_INSTRUCT, 0, 0);


			PrintInGenerate(g_nWordsIndex, nIndentNum, (char*)"Statement");
			StatementGenerate(nLevel, nIndentNum + 1);     //  ')'�����Ժ� + ��䣨��ԭ�Ƚ���then�������䣩


			//  �� �������� ���ִ����ɺ� Ӧ����ȥ��������ȥ�ĵ�һ���ڵ�ַ���ڲ�֪������Ҫ����
			//  ����Ҫ���浱ǰָ���ַ���� if �ĵ�һ���ڵ�ַ���ȴ�����
			nInstructIndexCopy1 = g_nInstructsIndex;    //  �������ĵ�ַ
			//  ����ֱ����תָ�� JMP_INSTRUCT���������ִ������Ժ����ת��ȥ
			GenerateOneInstruction(JMP_INSTRUCT, 0, 0);


			//  ����ǰָ���ַ���� if �ļٳ��ڵ�ַ���������תָ�� JPC_INSTRUCT �еĵ�ַ
			g_Instructs[nInstructIndexWhenFalse].nOperand = g_nInstructsIndex;

			if (g_Words[g_nWordsIndex].eType == ELSE)        //  ���Ϊ if...else...���
			{
				PrintInGenerate(g_nWordsIndex, nIndentNum, (char*)"ELSE");
				g_nWordsIndex++;

				PrintInGenerate(g_nWordsIndex, nIndentNum, (char*)"Statement");
				StatementGenerate(nLevel, nIndentNum + 1);     //  else �����Ժ� + ��һ����֧���
			}

			//  ����ǰָ���ַ���� if �ĵ�һ���ڵ�ַ���������תָ�� JMP_INSTRUCT �еĵ�ַ
			g_Instructs[nInstructIndexCopy1].nOperand = g_nInstructsIndex;

			return OK;
		}
		else
		{
			printf("if��������С�������ǰȱ�������š�(����");
			return ERROR;
		}
		break;
	case FOR:
		PrintInGenerate(g_nWordsIndex, nIndentNum, (char*)"FOR");
		g_nWordsIndex++;
		if (g_Words[g_nWordsIndex].eType == LEFT_PARENTHESIS) // for + ������'('
		{
			PrintInGenerate(g_nWordsIndex, nIndentNum, (char*)"LEFT_PARENTHESIS");
			g_nWordsIndex++;
			nNameTableIndexOfAssignedVariable = LookUpNameTable(g_Words[g_nWordsIndex].szName);
			if (nNameTableIndexOfAssignedVariable != 0)
			{	//  <��ֵ���> (��ʶ�� := ���ʽ)����ʡ��
				PrintInGenerate(g_nWordsIndex, nIndentNum, (char*)"IDENTIFIER");
				g_nWordsIndex++;
				if (g_Words[g_nWordsIndex].eType == ASSIGN)  //  + ":="
				{
					PrintInGenerate(g_nWordsIndex, nIndentNum, (char*)"ASSIGN");
					g_nWordsIndex++;
					PrintInGenerate(g_nWordsIndex, nIndentNum, (char*)"Expression");
					ExpressionGenerate(nLevel, nIndentNum + 1); // ��ֵ�� + ���ʽ

					//  ���� STORE_INSTRUCT ָ���ջ���б��ʽ��ֵ�浽����ֵ�������ڴ���ȥ  	
					// GenerateOneInstruction(STORE_INSTRUCT,nLevel-g_NameTable[nNameTableIndexOfAssignedVariable].nLevel,
					// g_NameTable[nNameTableIndexOfAssignedVariable].nAddress);
				}
				else
				{
					printf("û�и�ֵ����':='��ֵ���Ų���ȷ��");
					return ERROR;
				}
			}
			else
			{
				printf("�ñ�ʶ�������ڣ�����û����ǰ������");
				return ERROR;
			}

			if (g_Words[g_nWordsIndex].eType == SEMICOLON) // + �ֺ�';'����ֵ����
			{
				PrintInGenerate(g_nWordsIndex, nIndentNum, (char*)";");
				g_nWordsIndex++;
			}
			else
			{
				printf("forѭ���е�һ����ֵ����βȱ�ٷֺ�';'��");
				return ERROR;
			}


			// ����for����ʼ��ַ��Ϊfor��������ת����JMP_INSTRUCT��׼��
			nInstructIndexCopy1 = g_nInstructsIndex;

			g_nWordsIndex++;
			PrintInGenerate(g_nWordsIndex, nIndentNum, (char*)"Condition");
			ConditionGenerate(nLevel, nIndentNum + 1);		//  <�������>

			if (g_Words[g_nWordsIndex].eType == SEMICOLON) // +�ֺ�';'����������
			{
				PrintInGenerate(g_nWordsIndex, nIndentNum, (char*)";");
				g_nWordsIndex++;
			}
			else
			{
				printf("forѭ�����������Ľ�βȱ�ٷֺ�';'��");
				return ERROR;
			}

			//  ������������ʱӦ����ȥ���������ļٳ��ڵ�ַ���ڲ�֪����Ҫ����
			//  ����Ҫ���浱ǰָ���ַ���� for �ļٳ��ڵ�ַ���ȴ�����
			nInstructIndexWhenFalse = g_nInstructsIndex;    //  �������ĵ�ַ
			//  ����������תָ�� JPC_INSTRUCT������ ���� ������ʱӦ����ȥ
			GenerateOneInstruction(JPC_INSTRUCT, 0, 0);

			nNameTableIndexOfAssignedVariable =
				LookUpNameTable(g_Words[g_nWordsIndex].szName);
			if (nNameTableIndexOfAssignedVariable != 0)
			{	//  <��ֵ���> (��ʶ�� := ���ʽ)����ʡ��
				PrintInGenerate(g_nWordsIndex, nIndentNum, (char*)"IDENTIFIER");
				g_nWordsIndex++;
				if (g_Words[g_nWordsIndex].eType == ASSIGN)  //  + ":="
				{
					PrintInGenerate(g_nWordsIndex, nIndentNum, (char*)"ASSIGN");
					g_nWordsIndex++;

					PrintInGenerate(g_nWordsIndex, nIndentNum, (char*)"Expression");
					ExpressionGenerate(nLevel, nIndentNum + 1);  // ��ֵ��+ ���ʽ

					//  ���� STORE_INSTRUCT ָ���ջ���б��ʽ��ֵ�浽����ֵ�������ڴ���ȥ   	
					// GenerateOneInstruction(STORE_INSTRUCT,nLevel-g_NameTable[nNameTableIndexOfAssignedVariable].nLevel,
					// g_NameTable[nNameTableIndexOfAssignedVariable].nAddress);
				}
				else
				{
					printf("û�и�ֵ����':='��ֵ���Ų���ȷ��");
					return ERROR;
				}
			}
			else
			{
				printf("�ñ�ʶ�������ڣ�����û����ǰ������");
				return ERROR;
			}

			if (g_Words[g_nWordsIndex].eType == RIGHT_PARENTHESIS)
			{	//  + ')'�������е�����������
				PrintInGenerate(g_nWordsIndex, nIndentNum, (char*)"RIGHT_PARENTHESIS");
				g_nWordsIndex++;
			}
			else
			{
				printf("forѭ���и�ֵ-����-��ֵ����ȱ��������')'��");
				return ERROR;
			}
			PrintInGenerate(g_nWordsIndex, nIndentNum, (char*)"Statement");
			StatementGenerate(nLevel, nIndentNum + 1); 	//  for(;;)������ + ���

			//  for ������Ӧ���� JMP_INSTRUCT ���ص� for ���ĳ�ʼ��ַ
			GenerateOneInstruction(JMP_INSTRUCT, 0, nInstructIndexCopy1);

			//  ����һ��ָ���ַ���� for �ļٳ��ڵ�ַ
			//  ������ for ����Ϊ�ٵ� JPC_INSTRUCT ָ��ĵ�ַ
			g_Instructs[nInstructIndexWhenFalse].nOperand = g_nInstructsIndex;
			return OK;
		}
		else
		{
			printf("forѭ���и�ֵ-����-��ֵ����ȱ��������'('��");
			return ERROR;
		}
		break;
	case WHILE://�����ǰ������"while",׼������"ѭ�����"����
		PrintInGenerate(g_nWordsIndex, nIndentNum, "WHILE");//��ӡ������Ϣ

		//����"while"���ĳ�ʼ��ַ,Ϊwhile��������ת����JMP_INSTRUCT�����׼��
		nInstructIndexCopy1 = g_nInstructsIndex;

		g_nWordsIndex++;//ȡ��һ������
		PrintInGenerate(g_nWordsIndex, nIndentNum, "Condition");//��ӡ������Ϣ
		ConditionGenerate(nLevel, nIndentNum + 1);//"while"����Ӧ��"����"

		//��"����"������ʱӦ����ȥ,������ȥ�ļٳ��ڵ�ַ���ڲ�֪��,��Ҫ����
		//����Ҫ���浱ǰָ���ַ,��"while"�ļٳ��ڵ�ַ,�ȴ�����
		nInstructIndexWhenFalse = g_nInstructsIndex;//�������ĵ�ַ
		//����������תָ��JPC_INSTRUCT,����"����"������ʱӦ����ȥ
		GenerateOneInstruction(JPC_INSTRUCT, 0, 0);

		if (g_Words[g_nWordsIndex].eType == DO)//"����"����Ӧ��"do"
		{
			PrintInGenerate(g_nWordsIndex, nIndentNum, "DO");//��ӡ������Ϣ

			g_nWordsIndex++;//ȡ��һ������
			PrintInGenerate(g_nWordsIndex, nIndentNum, "Statement");//��ӡ������Ϣ
			StatementGenerate(nLevel, nIndentNum + 1);//"do"����Ӧ��"һ�����"

			//while������Ӧ����JMP_INSTRUCT���ص�while���ĳ�ʼ��ַ
			GenerateOneInstruction(JMP_INSTRUCT, 0, nInstructIndexCopy1);

			//����һ��ָ���ַ����"while"�ļٳ��ڵ�ַ
			//������"while"����Ϊ�ٵ�JPC_INSTRUCTָ��ĵ�ַ
			g_Instructs[nInstructIndexWhenFalse].nOperand = g_nInstructsIndex;

			return OK;
		}
		else
			return ERROR;//ȱ��do

		break;

	case BEGIN://�����ǰ������"begin",׼������"�������"����
		PrintInGenerate(g_nWordsIndex, nIndentNum, "BEGIN");//��ӡ������Ϣ

		g_nWordsIndex++;//ȡ��һ������
		PrintInGenerate(g_nWordsIndex, nIndentNum, "Statement");//��ӡ������Ϣ
		StatementGenerate(nLevel, nIndentNum + 1);//"begin"����Ӧ��һ�����

		while (g_Words[g_nWordsIndex].eType == SEMICOLON)//��������滹��';'
		{
			PrintInGenerate(g_nWordsIndex, nIndentNum, ";");//��ӡ������Ϣ

			g_nWordsIndex++;//ȡ��һ������
			PrintInGenerate(g_nWordsIndex, nIndentNum, "Statement");//��ӡ������Ϣ
			StatementGenerate(nLevel, nIndentNum + 1);//��";"����Ӧ��"һ�����"
		}

		if (g_Words[g_nWordsIndex].eType == END)//���������������"end"
		{
			PrintInGenerate(g_nWordsIndex, nIndentNum, "END");//��ӡ������Ϣ

			g_nWordsIndex++;//ȡ��һ������
			return OK;
		}
		else
			return ERROR;//ȱ��end��ֺ�

		break;

	case READ://�����ǰ������"read",׼������"�����"����
		PrintInGenerate(g_nWordsIndex, nIndentNum, "READ");//��ӡ������Ϣ

		g_nWordsIndex++;//ȡ��һ������
		if (g_Words[g_nWordsIndex].eType == LEFT_PARENTHESIS)//"read"����Ӧ��������'('
		{
			PrintInGenerate(g_nWordsIndex, nIndentNum, "LEFT_PARENTHESIS");//��ӡ������Ϣ

			do {//һ��"�����"Ӧ������һ��������ʶ��
				g_nWordsIndex++;//ȡ��һ������

				if (g_Words[g_nWordsIndex].eType == IDENTIFIER)//����Ӧ��һ����ʶ��
				{
					PrintInGenerate(g_nWordsIndex, nIndentNum, "IDENTIFIER");//��ӡ������Ϣ

					nNameTableIndex = LookUpNameTable(g_Words[g_nWordsIndex].szName);//����Ҫ���ı����Ƿ��Ѿ������ֱ���
					if (nNameTableIndex > 0)
					{//����ñ������������ı�����
						GenerateOneInstruction(IN_INSTRUCT, 0, 0);//��������ָ��,��ȡ����ֵ��ջ��
						//����STORE_INSTRUCTָ��,��ջ�����ݴ浽ĳ����̵���Ե�ַΪ���������ڴ���
						GenerateOneInstruction(STORE_INSTRUCT, nLevel - g_NameTable[nNameTableIndex].nLevel, g_NameTable[nNameTableIndex].nAddress);
					}
					else
					{
						return ERROR;
					}

					g_nWordsIndex++;//ȡ��һ������
				}
				else
					return ERROR;//��ʽ����,

				if (g_Words[g_nWordsIndex].eType == COMMA)//��ӡ������Ϣ
					PrintInGenerate(g_nWordsIndex, nIndentNum, "COMMA");
			} while (g_Words[g_nWordsIndex].eType == COMMA);//�����ʶ��������һ������','

			if (g_Words[g_nWordsIndex].eType == RIGHT_PARENTHESIS)//���Ӧ��������')'
			{
				PrintInGenerate(g_nWordsIndex, nIndentNum, ")");//��ӡ������Ϣ

				g_nWordsIndex++;//ȡ��һ������
				return OK;
			}
			else
				return ERROR;//��ʽ����,Ӧ��������
		}
		else
			return ERROR;//��ʽ����,Ӧ��������

		break;

	case WRITE://�����ǰ������"write",׼������"д���"����
		PrintInGenerate(g_nWordsIndex, nIndentNum, "WRITE");

		g_nWordsIndex++;//ȡ��һ������
		if (g_Words[g_nWordsIndex].eType == LEFT_PARENTHESIS)//"write"����Ӧ��������'('
		{
			PrintInGenerate(g_nWordsIndex, nIndentNum, "(");

			do {//һ��write����д�������
				g_nWordsIndex++;//ȡ��һ������

				PrintInGenerate(g_nWordsIndex, nIndentNum, "Expression");//��ӡ������Ϣ
				ExpressionGenerate(nLevel, nIndentNum + 1);//����"���ʽ"ָ��

				//�������ָ��OUT_INSTRUCT,���ջ������
				GenerateOneInstruction(OUT_INSTRUCT, 0, 0);

				if (g_Words[g_nWordsIndex].eType == COMMA)
					PrintInGenerate(g_nWordsIndex, nIndentNum, "COMMA");
			} while (g_Words[g_nWordsIndex].eType == COMMA);//�����ʶ��������һ������','

			if (g_Words[g_nWordsIndex].eType == RIGHT_PARENTHESIS)//���Ӧ��������')'
			{
				PrintInGenerate(g_nWordsIndex, nIndentNum, ")");

				g_nWordsIndex++;//ȡ��һ������
				return OK;
			}
			else
				return ERROR;//��ʽ����,Ӧ��������
		}
		else
			return ERROR;//��ʽ����,Ӧ��������

		break;

	case CALL://�����ǰ������"call",׼������"���ú������"����
		PrintInGenerate(g_nWordsIndex, nIndentNum, "CALL");

		g_nWordsIndex++;//ȡ��һ������
		if (g_Words[g_nWordsIndex].eType == IDENTIFIER)//"call"����Ӧ��һ����ʶ��,������
		{
			PrintInGenerate(g_nWordsIndex, nIndentNum, "IDENTIFIER");

			nNameTableIndex = LookUpNameTable(g_Words[g_nWordsIndex].szName);//�����ֱ��в��Ҹù�����
			if (nNameTableIndex > 0)
			{
				if (g_NameTable[nNameTableIndex].eType == PROCEDURE_TYPE)//����ù��������������Ĺ�����
					//���ɵ��ù���ָ��CALL_INSTRUCT,���ص�ַѹջ
					GenerateOneInstruction(CALL_INSTRUCT, nLevel - g_NameTable[nNameTableIndex].nLevel, g_NameTable[nNameTableIndex].nAddress);
				else
					return ERROR;
			}
			else
				return ERROR;

			g_nWordsIndex++;//ȡ��һ������
			return OK;
		}
		else
			return ERROR;//call��ӦΪ��ʶ��
		break;
	case SL_COMMENT://�����ǰ������"call",׼������"���ú������"����
		PrintInGenerate(g_nWordsIndex, nIndentNum, "SL_COMMENT");
		g_nWordsIndex++;//ȡ��һ������
		break;
	default:	return OK;
	}

	return ERROR;
}
//"����"�﷨������������
int ConditionGenerate(int nLevel, int nIndentNum)//nLevel�Ƿֳ������ڵĲ��,nIndentNum�Ǵ�ӡʱҪ�����Ŀո���
{
	enum	WORD_TYPE_ENUM	ePreRelationOperator;

	if (g_Words[g_nWordsIndex].eType == ODD)//�����"odd"����
	{
		PrintInGenerate(g_nWordsIndex, nIndentNum, "ODD");//��ӡ������Ϣ

		g_nWordsIndex++;//ȡ��һ������

		PrintInGenerate(g_nWordsIndex, nIndentNum, "Expression");//��ӡ������Ϣ
		ExpressionGenerate(nLevel, nIndentNum + 1);//"odd"������һ��"���ʽ"

		//�����ж�����ָ��ODD_INSTRUCT,�ж�ջ�������Ƿ�Ϊ����.�����,��ջ������Ϊ1,����Ϊ0
		GenerateOneInstruction(ODD_INSTRUCT, 0, 0);
	}
	else
	{//���û��"odd"����,��"����"��һ��"���ʽ"
		PrintInGenerate(g_nWordsIndex, nIndentNum, "Expression");//��ӡ������Ϣ
		ExpressionGenerate(nLevel, nIndentNum + 1);//"����"��һ��"���ʽ"

		if (g_Words[g_nWordsIndex].eType == EQL		//����������߼������
			|| g_Words[g_nWordsIndex].eType == NEQ
			|| g_Words[g_nWordsIndex].eType == LES
			|| g_Words[g_nWordsIndex].eType == LEQ
			|| g_Words[g_nWordsIndex].eType == GTR
			|| g_Words[g_nWordsIndex].eType == GEQ)
		{
			PrintInGenerate(g_nWordsIndex, nIndentNum, "LOGICAL");//��ӡ������Ϣ

			ePreRelationOperator = g_Words[g_nWordsIndex].eType;//���浱ǰ���߼������

			g_nWordsIndex++;//ȡ��һ������

			PrintInGenerate(g_nWordsIndex, nIndentNum, "Expression");//��ӡ������Ϣ
			ExpressionGenerate(nLevel, nIndentNum + 1);//�����������ĵڶ���"���ʽ"

			switch (ePreRelationOperator)//����ǰ�汣����߼������,������Ӧ��ָ��
			{
			case EQL://ȡ�����ж�ջ�����ݺʹ�ջ�������Ƿ���ͬ.�����ͬ,��ջ������Ϊ1,����Ϊ0
				GenerateOneInstruction(EQL_INSTRUCT, 0, 0);
				break;
			case NEQ://ȡ�����ж�ջ�����ݺʹ�ջ�������Ƿ���ͬ.�����ͬ,��ջ������Ϊ0,����Ϊ1
				GenerateOneInstruction(NEQ_INSTRUCT, 0, 0);
				break;
			case LES://ȡ�����жϴ�ջ�������Ƿ�С��ջ������.�����,��ջ������Ϊ1,����Ϊ0
				GenerateOneInstruction(LES_INSTRUCT, 0, 0);
				break;
			case GEQ://ȡ�����жϴ�ջ�������Ƿ���ڵ���ջ������.�����,��ջ������Ϊ1,����Ϊ0��
				GenerateOneInstruction(GEQ_INSTRUCT, 0, 0);
				break;
			case GTR://ȡ�����жϴ�ջ�������Ƿ����ջ������.�����,��ջ������Ϊ1,����Ϊ0
				GenerateOneInstruction(GTR_INSTRUCT, 0, 0);
				break;
			case LEQ://ȡ�����жϴ�ջ�������Ƿ�С�ڵ���ջ������.�����,��ջ������Ϊ1,����Ϊ0
				GenerateOneInstruction(LEQ_INSTRUCT, 0, 0);
				break;
			}
		}
		else
			return ERROR;//ȱ��������
	}
	return OK;
}
//"���ʽ"�﷨������������
int ExpressionGenerate(int nLevel, int nIndentNum)//nLevel�Ƿֳ������ڵĲ��,nIndentNum�Ǵ�ӡʱҪ�����Ŀո���
{
	enum	WORD_TYPE_ENUM	eMathOperator = PLUS;

	if (g_Words[g_nWordsIndex].eType == PLUS || g_Words[g_nWordsIndex].eType == MINUS)
	{//������ʽ��ͷ��������,���ʱ���ʽӦ������һ�����Ļ򸺵���
		if (g_Words[g_nWordsIndex].eType == PLUS)//�����ͷ����������,�����
			PrintInGenerate(g_nWordsIndex, nIndentNum, "PLUS");//��ӡ������Ϣ
		if (g_Words[g_nWordsIndex].eType == MINUS)//�����ͷ�����Ǹ���
		{
			PrintInGenerate(g_nWordsIndex, nIndentNum, "MINUS");//��ӡ������Ϣ
			eMathOperator = MINUS;//���浱ǰ�ĸ���
		}

		g_nWordsIndex++;//ȡ��һ������
	}

	PrintInGenerate(g_nWordsIndex, nIndentNum, "Term");//��ӡ������Ϣ
	TermGenerate(nLevel, nIndentNum + 1);//���ʽ������һ��"��"

	if (eMathOperator == MINUS)//�����ͷ�����Ǹ���,������ȡ��ָ��NEGATIVE_INSTRUCT
		GenerateOneInstruction(NEGATIVE_INSTRUCT, 0, 0);//ȡ������,��ջ������ȡ�����Է���ջ��

	while (g_Words[g_nWordsIndex].eType == PLUS || g_Words[g_nWordsIndex].eType == MINUS)
	{//���"��"���滹��'+'��'-'
		if (g_Words[g_nWordsIndex].eType == PLUS)
		{//"��"������'+'
			PrintInGenerate(g_nWordsIndex, nIndentNum, "PLUS");//��ӡ������Ϣ
			eMathOperator = PLUS;//�����������
		}
		if (g_Words[g_nWordsIndex].eType == MINUS)
		{//"��"������'-'
			PrintInGenerate(g_nWordsIndex, nIndentNum, "MINUS");//��ӡ������Ϣ
			eMathOperator = MINUS;//�����������
		}

		g_nWordsIndex++;//ȡ��һ������

		PrintInGenerate(g_nWordsIndex, nIndentNum, "Term");//��ӡ������Ϣ
		TermGenerate(nLevel, nIndentNum + 1);//'+'��'-'���滹��"��"

		if (eMathOperator == PLUS)//���ǰ�汣������������'+'
			GenerateOneInstruction(ADD_INSTRUCT, 0, 0);//���ɼӷ�ָ��ADD_INSTRUCT,ȡ��ջ�����ݺʹ�ջ�����ݵĺ��ٷŵ�ջ��
		if (eMathOperator == MINUS)//���ǰ�汣������������'-'
			GenerateOneInstruction(SUB_INSTRUCT, 0, 0);//���ɼ���ָ��SUB_INSTRUCT,ȡ��ջ�����ݺʹ�ջ�����ݵĲ��ٷŵ�ջ��
	}
	return OK;
}
//"��"�﷨������������
int TermGenerate(int nLevel, int nIndentNum)//nLevel�Ƿֳ������ڵĲ��,nIndentNum�Ǵ�ӡʱҪ�����Ŀո���
{
	enum	WORD_TYPE_ENUM	eMathOperator = PLUS;

	PrintInGenerate(g_nWordsIndex, nIndentNum, "Factor");//��ӡ������Ϣ
	FactorGenerate(nLevel, nIndentNum + 1);//"��"������һ��"����"

	while (g_Words[g_nWordsIndex].eType == MULTIPLY || g_Words[g_nWordsIndex].eType == DIVIDE)
	{//���"����"���滹��'*'��'/'
		PrintInGenerate(g_nWordsIndex, nIndentNum, "*/");//��ӡ������Ϣ

		eMathOperator = g_Words[g_nWordsIndex].eType;//�ȱ����������

		g_nWordsIndex++;//ȡ��һ������

		PrintInGenerate(g_nWordsIndex, nIndentNum, "Factor");//��ӡ������Ϣ
		FactorGenerate(nLevel, nIndentNum + 1);//'*'��'/'���滹Ӧ��"����"

		if (eMathOperator == MULTIPLY)//���ǰ�汣������������'*'
			GenerateOneInstruction(MULTI_INSTRUCT, 0, 0);//���ɳ˷�ָ��MULTI_INSTRUCT,ȡ��ջ�����ݺʹ�ջ�����ݵĻ��ٷŵ�ջ��
		if (eMathOperator == DIVIDE)//���ǰ�汣������������'/'
			GenerateOneInstruction(DIVID_INSTRUCT, 0, 0);//���ɳ���ָ��DIVID_INSTRUCT,ȡ��ջ�����ݺʹ�ջ�����ݵ����ٷŵ�ջ��
	}
	return OK;
}
//"����"�﷨������������
int FactorGenerate(int nLevel, int nIndentNum)//nLevel�Ƿֳ������ڵĲ��,nIndentNum�Ǵ�ӡʱҪ�����Ŀո���
{
	int		nNameTableIndex;

	switch (g_Words[g_nWordsIndex].eType)
	{
	case IDENTIFIER://���ӿ�����һ�����������
		PrintInGenerate(g_nWordsIndex, nIndentNum, "IDENTIFIER");//��ӡ������Ϣ

		nNameTableIndex = LookUpNameTable(g_Words[g_nWordsIndex].szName);//�����ֱ��в��Ҹó����������
		if (nNameTableIndex > 0)
		{
			switch (g_NameTable[nNameTableIndex].eType)
			{
			case CONSTANT_TYPE://����Ϊ����
				//����INSTANT_INSTRUCTָ��,ֱ�ӽ����ֱ��еĲ�������ֵѹ��ջ��
				GenerateOneInstruction(INSTANT_INSTRUCT, 0, g_NameTable[nNameTableIndex].nVal);
				break;
			case VARIABLE_TYPE://����Ϊ����
				//����LOAD_INSTRUCTָ��,�ҵ�������ַ������ֵѹ��ջ��
				GenerateOneInstruction(LOAD_INSTRUCT, nLevel - g_NameTable[nNameTableIndex].nLevel, g_NameTable[nNameTableIndex].nAddress);
				break;
			default: return ERROR;
			}
		}
		else
			return ERROR;//��ʶ��δ��������

		g_nWordsIndex++;//ȡ��һ������
		return OK;

	case NUMBER:	//���ӿ�����һ����
		PrintInGenerate(g_nWordsIndex, nIndentNum, "NUMBER");//��ӡ������Ϣ
		//����INSTANT_INSTRUCTָ��,ֱ�Ӱ�����ֵѹ��ջ
		GenerateOneInstruction(INSTANT_INSTRUCT, 0, g_Words[g_nWordsIndex].nNumberValue);

		g_nWordsIndex++;//ȡ��һ������
		return OK;

	case LEFT_PARENTHESIS:	//�������������'('
		PrintInGenerate(g_nWordsIndex, nIndentNum, "(");

		g_nWordsIndex++;//ȡ��һ������

		PrintInGenerate(g_nWordsIndex, nIndentNum, "Expression");
		ExpressionGenerate(nLevel, nIndentNum + 1);//������'('����Ӧ��"���ʽ"

		if (g_Words[g_nWordsIndex].eType == RIGHT_PARENTHESIS)//"���ʽ"����Ӧ��������')'
		{
			PrintInGenerate(g_nWordsIndex, nIndentNum, ")");

			g_nWordsIndex++;//ȡ��һ������
			return OK;
		}
		else
			return ERROR;//ȱ��������
		break;

	default:		return ERROR;
	}
	return OK;
}
//��ö�����͵�ָ��ת�����ַ���
int InstructFromEnumToString(enum INSTRUCT_ENUM eInstruct, char* szString)
{
	switch (eInstruct)
	{
	case INSTANT_INSTRUCT:
		strcpy(szString, "INSTANT");
		break;
	case LOAD_INSTRUCT:
		strcpy(szString, "LOAD");
		break;
	case STORE_INSTRUCT:
		strcpy(szString, "STORE");
		break;
	case CALL_INSTRUCT:
		strcpy(szString, "CALL");
		break;
	case ENDCALL_INSTRUCT:
		strcpy(szString, "ENDCALL");
		break;
	case ALLOCATE_INSTRUCT:
		strcpy(szString, "ALLOCATE");
		break;
	case JMP_INSTRUCT:
		strcpy(szString, "JMP");
		break;
	case JPC_INSTRUCT:
		strcpy(szString, "JPC");
		break;
	case NEGATIVE_INSTRUCT:
		strcpy(szString, "NEG");
		break;
	case ADD_INSTRUCT:
		strcpy(szString, "ADD");
		break;
	case SUB_INSTRUCT:
		strcpy(szString, "SUB");
		break;
	case MULTI_INSTRUCT:
		strcpy(szString, "MULTI");
		break;
	case DIVID_INSTRUCT:
		strcpy(szString, "DIVID");
		break;
	case ODD_INSTRUCT:
		strcpy(szString, "ODD");
		break;
	case EQL_INSTRUCT:
		strcpy(szString, "EQL");
		break;
	case NEQ_INSTRUCT:
		strcpy(szString, "NEQ");
		break;
	case LES_INSTRUCT:
		strcpy(szString, "LES");
		break;
	case GEQ_INSTRUCT:
		strcpy(szString, "GEQ");
		break;
	case GTR_INSTRUCT:
		strcpy(szString, "GTR");
		break;
	case LEQ_INSTRUCT:
		strcpy(szString, "LEQ");
		break;
	case OUT_INSTRUCT:
		strcpy(szString, "OUT");
		break;
	case IN_INSTRUCT:
		strcpy(szString, "IN");
		break;
	}
	return OK;
}

void PrintInGenerate(int nWordsIndex, int nIndentNum, char* pString)//��ӡ������Ϣ
{
	int		i;
	char	strText[100];

	printf("\n%-4d%-4d%-12s", nWordsIndex + 1, g_Words[nWordsIndex].nLineNo, g_Words[nWordsIndex].szName);
	printf("%-1s", "|");
	for (i = 0; i < nIndentNum; i++)
		printf(" ");
	printf("%-1s", " ");

	sprintf(strText, "(%d)%s", nIndentNum, pString);
	printf("%-15s", strText);

	for (i = 0; i < 10 - nIndentNum; i++)
		printf(" ");
	printf("|");
}
//��ָ�����g_Instructs�ṹ����������һ������ָ��
int GenerateOneInstruction(INSTRUCT_ENUM eInstruct, int nLevel, int nOperand)//eInstruct������ָ��Ĳ�����,nLevel������ָ����������ò���������Ĳ�β�,nOperand������ָ�������
{
	char		szText[100];

	if (g_nInstructsIndex >= MAX_NUMBER_INSTRUCTS)
	{
		printf("GenerateOneInstruction()--Program too long");//�������,�޷��������
		return	-1;
	}
	g_Instructs[g_nInstructsIndex].eInstruct = eInstruct;//�������ָ�������
	g_Instructs[g_nInstructsIndex].nLevel = nLevel;//�������ָ����������ò���������Ĳ�β�
	g_Instructs[g_nInstructsIndex].nOperand = nOperand;//�������ָ�������

	//��ӡ������Ϣ
	InstructFromEnumToString(g_Instructs[g_nInstructsIndex].eInstruct, szText);
	printf("\n\t\t\t\t\t         %-4d%-10s%-4d%-3d", g_nInstructsIndex, szText, g_Instructs[g_nInstructsIndex].nLevel, g_Instructs[g_nInstructsIndex].nOperand);

	g_nInstructsIndex++;//��һ��ָ���ŵ�λ���±��һ

	return 0;
}

void PrintAllInstructions()//����ӡ�������ɵ�ָ��
{
	char		szText[100];

	for (int i = 0; i < g_nInstructsIndex; i++)
	{
		InstructFromEnumToString(g_Instructs[i].eInstruct, szText);
		printf("\n%-5d%-15s%-5d%-5d", i, szText, g_Instructs[i].nLevel, g_Instructs[i].nOperand);
	}
}

void PrintAVariable(int nNameTableIndex)
{
	printf("\n\t\t\t\t\t       --Table[%d] %s Level=%d Addr=%d", nNameTableIndex, g_NameTable[nNameTableIndex].szName, g_NameTable[nNameTableIndex].nLevel, g_NameTable[nNameTableIndex].nAddress);
}

