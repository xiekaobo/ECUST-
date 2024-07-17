#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <cstring>

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
	enum INSTRUCT_ENUM		eInstruct;		//�����ָ��
	int											nLevel;			//���ò���������Ĳ�β�
	int											nOperand;	//������,���ݲ�ָͬ�����ͬ
};

#define		MAX_NUMBER_INSTRUCTS					200		//���������ָ����
#define		STACK_SIZE												500

extern		INSTRUCT_STRUCT			g_Instructs[MAX_NUMBER_INSTRUCTS];

int GetBase(int nNum, int* pStack, int nStackCurrentBase);
void PrintInInterprete(int nNo, int Stack[], int nStackTop, enum INSTRUCT_ENUM CurrentInstruct);
int InstructFromEnumToString(enum INSTRUCT_ENUM eInstruct, char* szString);
void InitializeInterpret(int Stack[]);

//���ͳ���
void Interpreter()
{
	INSTRUCT_STRUCT		CurrentInstruct;//ָ��Ĵ�����ŵ�ǰ����ָ��

	int	nNo = 1;
	int	nInstructsIndex;//�����ַ�Ĵ���
	int	nStackBase;
	int	nStackTop;//��ַ�Ĵ���
	int	nLevel;
	int	nBase, nAddress;
	int	Stack[STACK_SIZE];//���ݴ洢��,����ջ

	InitializeInterpret(Stack);//��ʼ������ջ

	printf("\nInterpret Start\n");

	nStackTop = 0;//����ջ��Ϊ��
	nStackBase = 0;
	nInstructsIndex = 0;
	Stack[0] = Stack[1] = Stack[2] = 0;

	do {
		CurrentInstruct = g_Instructs[nInstructsIndex];//����ǰָ�ָ��Ĵ���CurrentInstruct
		nInstructsIndex++;//׼����һ��ָ��

		PrintInInterprete(nNo, Stack, nStackTop, CurrentInstruct.eInstruct);//��ӡ����ջ
		nNo++;

		switch (CurrentInstruct.eInstruct)//���ݵ�ǰָ�������
		{
		case JMP_INSTRUCT://ֱ����ת����ַΪ��������ָ��
			nInstructsIndex = CurrentInstruct.nOperand;
			break;
		case JPC_INSTRUCT://������ת.���ջ�����ݵ�����,����תִ�е�ַΪ��������ָ��,����ִ����һ��ָ��
			nStackTop--;
			if (Stack[nStackTop] == 0)
				nInstructsIndex = CurrentInstruct.nOperand;
			break;
		case INSTANT_INSTRUCT://ֱ�ӽ���������ֵѹ��ջ��
			Stack[nStackTop] = CurrentInstruct.nOperand;
			nStackTop++;
			break;
		case LOAD_INSTRUCT://ȡĳ����̵���Ե�ַΪ���������ڴ��ֵ��ջ��
			nLevel = CurrentInstruct.nLevel;
			nBase = GetBase(nLevel, Stack, nStackBase);
			nAddress = nBase + CurrentInstruct.nOperand;
			Stack[nStackTop] = Stack[nAddress];
			nStackTop++;
			break;
		case STORE_INSTRUCT://��ջ�����ݴ浽ĳ����̵���Ե�ַΪ���������ڴ���
			nStackTop--;
			nLevel = CurrentInstruct.nLevel;
			nBase = GetBase(nLevel, Stack, nStackBase);
			nAddress = nBase + CurrentInstruct.nOperand;
			Stack[nAddress] = Stack[nStackTop];
			break;
		case CALL_INSTRUCT:	//���ù���,���ص�ַѹջ
			Stack[nStackTop] = GetBase(CurrentInstruct.nLevel, Stack, nStackBase);//�������̻���ַѹ��ջ
			Stack[nStackTop + 1] = nStackBase;//�����̻���ַ��ջ,����������GetBase����
			Stack[nStackTop + 2] = nInstructsIndex;//����ǰָ��ָ����ջ
			nStackBase = nStackTop;//�ı����ַָ��ֵΪ�¹��̵Ļ���ַ
			nInstructsIndex = CurrentInstruct.nOperand;//��ת
			break;
		case ENDCALL_INSTRUCT:	//��������,��ջ,���ص�ԭ���ù��̴�
			nStackTop = nStackBase;
			nInstructsIndex = Stack[nStackTop + 2];
			nStackBase = Stack[nStackTop + 1];
			break;
		case ALLOCATE_INSTRUCT://�����ڴ�,ջ��ָ�����Ӳ�����
			nStackTop += CurrentInstruct.nOperand;
			break;
		case NEGATIVE_INSTRUCT://ȡ������,��ջ������ȡ�����Է���ջ��
			Stack[nStackTop - 1] = -Stack[nStackTop - 1];
			break;
		case ADD_INSTRUCT://�ӷ�ָ��,ȡ��ջ�����ݺʹ�ջ�����ݵĺ��ٷŵ�ջ��
			nStackTop--;
			Stack[nStackTop - 1] = Stack[nStackTop - 1] + Stack[nStackTop];
			break;
		case SUB_INSTRUCT://����ָ��,ȡ��ջ�����ݺʹ�ջ�����ݵĲ��ٷŵ�ջ��
			nStackTop--;
			Stack[nStackTop - 1] = Stack[nStackTop - 1] - Stack[nStackTop];
			break;
		case MULTI_INSTRUCT://���ָ��,ȡ��ջ�����ݺʹ�ջ�����ݵĻ��ٷŵ�ջ��
			nStackTop--;
			Stack[nStackTop - 1] = Stack[nStackTop - 1] * Stack[nStackTop];
			break;
		case DIVID_INSTRUCT://���ָ��,ȡ��ջ�����ݺʹ�ջ�����ݵ����ٷŵ�ջ��
			nStackTop--;
			Stack[nStackTop - 1] = Stack[nStackTop - 1] / Stack[nStackTop];//����������ԭnStackTop-2��
			break;
		case ODD_INSTRUCT://�ж�ջ�������Ƿ�Ϊ����.�����,��ջ������Ϊ1,����Ϊ0
			Stack[nStackTop - 1] = Stack[nStackTop - 1] % 2;
			break;
		case EQL_INSTRUCT://ȡ�����ж�ջ�����ݺʹ�ջ�������Ƿ���ͬ.�����ͬ,��ջ������Ϊ1,����Ϊ0
			nStackTop--;
			Stack[nStackTop - 1] = (Stack[nStackTop - 1] == Stack[nStackTop]);
			break;
		case NEQ_INSTRUCT://ȡ�����ж�ջ�����ݺʹ�ջ�������Ƿ���ͬ.�����ͬ,��ջ������Ϊ0,����Ϊ1
			nStackTop--;
			Stack[nStackTop - 1] = (Stack[nStackTop - 1] != Stack[nStackTop]);
			break;
		case LES_INSTRUCT://ȡ�����жϴ�ջ�������Ƿ�С��ջ������.�����,��ջ������Ϊ1,����Ϊ0
			nStackTop--;
			Stack[nStackTop - 1] = (Stack[nStackTop - 1] < Stack[nStackTop]);
			break;
		case LEQ_INSTRUCT://ȡ�����жϴ�ջ�������Ƿ�С�ڵ���ջ������.�����,��ջ������Ϊ1,����Ϊ0
			nStackTop--;
			Stack[nStackTop - 1] = (Stack[nStackTop - 1] <= Stack[nStackTop]);
			break;
		case GTR_INSTRUCT://ȡ�����жϴ�ջ�������Ƿ����ջ������.�����,��ջ������Ϊ1,����Ϊ0
			nStackTop--;
			Stack[nStackTop - 1] = (Stack[nStackTop - 1] > Stack[nStackTop]);
			break;
		case GEQ_INSTRUCT://ȡ�����жϴ�ջ�������Ƿ���ڵ���ջ������.�����,��ջ������Ϊ1,����Ϊ0��
			nStackTop--;
			Stack[nStackTop - 1] = (Stack[nStackTop - 1] >= Stack[nStackTop]);
			break;
		case OUT_INSTRUCT://�������ָ��,���ջ������
			printf("OUT_INSTRUCT=%d\n", Stack[nStackTop - 1]);
			nStackTop--;
			break;
		case IN_INSTRUCT://��������ָ��,��ȡ���ݵ�ջ��
			printf("IN_INSTRUCT=");
			scanf("%d", &Stack[nStackTop]);
			nStackTop++;
			break;
		}
	} while (nInstructsIndex != 0);
}
//ͨ�����̻�ַ����һ����̵Ļ�ַ
int GetBase(int nNum, int* pStack, int nStackCurrentBase)
{
	int nStackIndex;

	nStackIndex = nStackCurrentBase;
	while (nNum > 0)
	{
		nStackIndex = pStack[nStackIndex];
		nNum--;
	}
	return nStackIndex;
}

void InitializeInterpret(int Stack[])//��ʼ������ջ
{
	int	i;

	for (i = 0; i < STACK_SIZE; Stack[i++] = -1);
}

void PrintInInterprete(int nNo, int Stack[], int nStackTop, enum INSTRUCT_ENUM eInstruct)//��ӡ����ջ
{
	int		i;
	char		strInstruct[100];

	InstructFromEnumToString(eInstruct, strInstruct);
	printf("%-4d", nNo);
	for (i = 0; i <= nStackTop; i++)
		printf("%-3d", Stack[i]);
	printf("%-20s\n", strInstruct);
}
