
#ifndef RUN_PL0_INTERPRET_H
#define RUN_PL0_INTERPRET_H
#include "block.h"
#include <stack>
//codeEle currentCode;    //ָ��Ĵ���
int paranum = 0;        //��������
int pcReg;              //��һ��Ŀ��ָ���ַ
int spReg;              //ջ���Ĵ�����top
int bpReg;              //����ַ�Ĵ�����sp
//vector<int> runningStack;//����ջ
vector<float> runningStack;//����ջ

//���ֱ���var��valueû�����ã��ڽ���ִ�е�ʱ��ֵ

void Interpret()
{
    cout << "��ʼִ��" << endl;
    bool code_end = false;
    int cIndex = 0;     //������������
    //��ʼ������ջ������Ӿ�̬������̬�������ص�ַ
    runningStack.clear();
    runningStack.push_back(0);   //��̬����ջ��ֱ�����
    runningStack.push_back(0);   //��̬����ջ����sp
    runningStack.push_back(0);   //���ص�ַ��ջ
    spReg = -1;
    pcReg = 0;
    bpReg = 0;
    while (cIndex < codes.size() && !code_end) {
        pcReg++;
        if (codes[cIndex].func == "lit") {
            spReg++;
            runningStack.push_back(codes[cIndex].offset);
        }
        else if (codes[cIndex].func == "lod") {//�����
            spReg++;
            int tmpBpReg = bpReg;
            for (int i = 0; i < codes[cIndex].level_d; ++i)
                tmpBpReg = runningStack[tmpBpReg];        //���ݵ�ǰ���̵ľ�̬�����Ҳ�����0�Ļ���ַ
            runningStack.push_back(runningStack[tmpBpReg + (int)codes[cIndex].offset]);
        }
        else if (codes[cIndex].func == "sto") {
            int tmpBpReg = bpReg;
            for (int i = 0; i < codes[cIndex].level_d; ++i)
                tmpBpReg = runningStack[tmpBpReg];        //���ݵ�ǰ���̵ľ�̬�����Ҳ�����0�Ļ���ַ
            runningStack[tmpBpReg + (int)codes[cIndex].offset] = runningStack.back();
            runningStack.pop_back();
            spReg--;
        }
        else if (codes[cIndex].func == "cal") {
            int tmpBpReg = bpReg;
            for (int i = 0; i < codes[cIndex].level_d; ++i)
                tmpBpReg = runningStack[tmpBpReg];        //���ݵ�ǰ���̵ľ�̬�����ҵ������ľ�̬���
            //runningStack.push_back(tmpBpReg);      //��̬��
            //runningStack.push_back(bpReg);  //��̬������sp
            //runningStack.push_back(pcReg);  //���ص�ַ
            //pasָ���Ѿ������˿ռ�
            runningStack[spReg + 1] = tmpBpReg;      //��̬��
            runningStack[spReg + 2] = bpReg;  //��̬������sp
            runningStack[spReg + 3] = pcReg; //���ص�ַ
            bpReg = spReg + 1;              //�޸Ļ���ַ�Ĵ���
            pcReg = codes[cIndex].offset;   //�޸�pcֵ
        }
        else if (codes[cIndex].func == "int") {//Ϊ�������ٿռ�
            int tmpSpace = (int)codes[cIndex].offset - 3;
            runningStack.resize(runningStack.size()+tmpSpace);
            spReg = spReg + codes[cIndex].offset + paranum;//��ջ��ָ���Ƶ����һ��������
        }
        else if (codes[cIndex].func == "jmp") {
            pcReg = codes[cIndex].offset;
        }
        else if (codes[cIndex].func == "jpc") {
            if (runningStack[spReg] == 0) {
                pcReg = codes[cIndex].offset;
            }
            spReg--;
            runningStack.pop_back();
        }
        else if (codes[cIndex].func == "pas") {
            paranum = (int)codes[cIndex].offset;//�����ù��̵�ʵ�θ���
            runningStack.resize(runningStack.size() + 3);//֮��ʵ������������3����Ԫ
            for (int k = paranum; k > 0; k--) {
                runningStack[spReg + 3] = runningStack[spReg];
                spReg--;//���ջ��ָ��ص��ˣ������ù��̵ľ�̬��ǰһ����λ
            }
        }
        else if (codes[cIndex].func == "opr") {
            switch ((int)codes[cIndex].offset) {
                case ReturnOpr: {
                    if (pcReg == codes.size()) {
                        code_end = true;
                        cout << "�������" << endl;
                    }
                    int count = (int)runningStack.size() - bpReg;
                    spReg = bpReg - 1;
                    bpReg = runningStack[spReg+2];      //��̬�����ݣ��޸Ļ���ַ�Ĵ���
                    pcReg = runningStack[spReg+3];      //�޸�pc�Ĵ������˴�ջλ���Ƿ��ص�ַ
                    //��ջ
                    runningStack.resize(runningStack.size()-count);
                    break;
                }
                case MinusOpr: {
                    runningStack[spReg] = -runningStack[spReg];
                    break;
                }
                case AddOpr: {
                    spReg--;
                    runningStack[spReg] += runningStack[spReg+1];
                    runningStack.pop_back();
                    break;
                }
                case SubOpr: {
                    spReg--;
                    runningStack[spReg] -= runningStack[spReg+1];
                    runningStack.pop_back();
                    break;
                }
                case MulOpr: {
                    spReg--;
                    runningStack[spReg] *= runningStack[spReg+1];
                    runningStack.pop_back();
                    break;
                }
                case DivOpr: {
                    spReg--;
                    runningStack[spReg] = (int)(runningStack[spReg] / runningStack[spReg+1]);
                    runningStack.pop_back();
                    break;
                }
                case OddOpr: {
                    runningStack[spReg] = (int)runningStack[spReg] % 2;
                    break;
                }
                case ModOpr: {
                    spReg--;
                    runningStack[spReg] = (int)runningStack[spReg] % (int)runningStack[spReg + 1];
                    runningStack.pop_back();
                    break;
                }
                case EquOpr: {
                    spReg--;
                    runningStack[spReg] = (runningStack[spReg] == runningStack[spReg+1]);
                    runningStack.pop_back();
                    break;
                }
                case NeqOpr: {
                    spReg--;
                    runningStack[spReg] = (runningStack[spReg] != runningStack[spReg+1]);
                    runningStack.pop_back();
                    break;
                }
                case LessOpr: {
                    spReg--;
                    runningStack[spReg] = (runningStack[spReg] < runningStack[spReg+1]);
                    runningStack.pop_back();
                    break;
                }
                case EgreOpr: {
                    spReg--;
                    runningStack[spReg] = (runningStack[spReg] >= runningStack[spReg+1]);
                    runningStack.pop_back();
                    break;
                }
                case GreOpr: {
                    spReg--;
                    runningStack[spReg] = (runningStack[spReg] > runningStack[spReg+1]);
                    runningStack.pop_back();
                    break;
                }
                case ElessOpr: {
                    spReg--;
                    runningStack[spReg] = (runningStack[spReg] <= runningStack[spReg+1]);
                    runningStack.pop_back();
                    break;
                }
                case WriteOpr: {
                    cout << "����Ļ�����" << runningStack.back();
                    spReg--;
                    runningStack.pop_back();
                    break;
                }
                case ChaLineOpr: {
                    cout << endl;
                    break;
                }
                case ReadOpr: {
                    spReg++;
                    int cinTmp;
                    cout << "�Ӽ��̶��룺";
                    cin >> cinTmp;
                    getchar();
                    runningStack.push_back(cinTmp);
                    //cout << "�������" << endl;
                    break;
                }
                case AndOpr: {
                    spReg--;
                    runningStack[spReg] = (runningStack[spReg] && runningStack[spReg + 1]);
                    runningStack.pop_back();
                    break;
                }
                case OrOpr: {
                    spReg--;
                    runningStack[spReg] = (runningStack[spReg] || runningStack[spReg + 1]);
                    runningStack.pop_back();
                    break;
                }
                case AntiOpr: {
                    runningStack[spReg] = !runningStack[spReg];
                    break;
                }
                case RDivOpr: {
                    spReg--;
                    runningStack[spReg] = runningStack[spReg] / runningStack[spReg + 1];
                    runningStack.pop_back();
                    break;
                }
                default: {
                    break;
                }
            }
        }
        cIndex = pcReg;
    }
}

#endif //RUN_PL0_INTERPRET_H
