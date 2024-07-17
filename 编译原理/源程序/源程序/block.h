#ifndef RUN_PL0_BLOCK_H
#define RUN_PL0_BLOCK_H
#include "getsym.h"

//��������ö��
enum OPR_TYPE {//���㽫1��Ϊջ��
    ReturnOpr, // return�����������ù��̣����ص��õ㲢��ջ
    /*
    (sp <- bp - 1;
    bp <- stack[sp + 2];
    pc <- stack[sp + 3];)
    */
    MinusOpr, //ȡ��
    /*
    (- stack[sp] )
    */
    AddOpr, //��
    /*
    (sp <- sp �C 1 ;
    stack[sp] <- stack[sp] + stack[sp + 1])
    */
    SubOpr, //��
    /*
    (sp <- sp �C 1 ;
    stack[sp] <- stack[sp] - stack[sp + 1])
    */
    MulOpr, //��
    /*
    (sp <- sp �C 1 ;
    stack[sp] <- stack[sp] * stack[sp + 1])
    */
    DivOpr, //������div
    /*
    sp <- sp �C 1 ;
    stack[sp] <- (int)(stack[sp] / stack[sp + 1])
    */
    OddOpr, // odd����2ȡģ��
    /*
    (stack[sp] <- stack % 2)
    */
    ModOpr, //ȡģ
    /*
    (sp <- sp �C 1 ;
    stack[sp] <- stack[sp] % stack[sp + 1])
    */
    EquOpr, //����
    /*
    (sp <- sp �C 1 ;
    stack[sp] <- stack[sp] == stack[sp + 1])
    */
    NeqOpr, //������
    /*
    (sp <- sp �C 1 ;
    stack[sp] <- stack[sp] != stack[sp + 1])
    */
    LessOpr, //С��
    /*
    (sp <- sp �C 1 ;
    stack[sp] <- stack[sp] < stack[sp + 1])
    */
    EgreOpr, //���ڵ���
    /*
    (sp <- sp �C 1 ;
    stack[sp] <- stack[sp] >= stack[sp + 1])
    */
    GreOpr, //����
    /*
    (sp <- sp �C 1 ;
    stack[sp] <- stack[sp] > stack[sp + 1])
    */
    ElessOpr, //С�ڵ���
    /*
    (sp <- sp �C 1 ;
    stack[sp] <- stack[sp] <= stack[sp + 1])
    */
    WriteOpr, // write(���ջ��)
    /*
    print (stack[sp]);
    sp <- sp �C 1;
    */
    ChaLineOpr, //�������
    /*
    print ('\n');
    */
    ReadOpr, //����ջ��
    /*
    scan(stack[sp]);
    sp <- sp + 1;
    */
    AndOpr,//������
    /*
    (sp <- sp �C 1 ;
    stack[sp] <- stack[sp] && stack[sp + 1]) 
    */
    OrOpr,//������
    /*
    (sp <- sp �C 1 ;
    stack[sp] <- stack[sp] || stack[sp + 1])
    */
    AntiOpr,//������
    /*
    stack[sp] <- !stack[sp] 
    */
    RDivOpr, //ʵ����'/'
    /*
    (sp <- sp �C 1 ;
    stack[sp] <- stack[sp] / stack[sp + 1])
    */
};

//�﷨��������
enum ERROR_GRAMMAR {
    const_state_end_wrong,//��������β����
    number_wrong,//������
    const_assign_wrong,//�����������
    identifier_wrong, //���Ǳ�ʶ��
    var_state_end_wrong,//����˵���Ľ�������
    var_no_type_wrong,//����������
    var_type_wrong,//�������ʹ���
    procedure_state_end_wrong,//��������������
    procedure_name_redefined,//�����������������ظ�
    procedure_head_wrong,//�����ײ�������
    not_procedure_name,//���ǹ�����
    var_assign_wrong,//���Ǳ�����ֵ
    Boolean_assign_wrong,//Bollean������ֵ����
    integer_assign_wrong,//integer������ֵ����
    expression_in_factor_wrong,//�����а����ı��ʽ�Ĵ������
    factor_wrong,//�������Ӵ���
    if_then_wrong,//if������
    condition_wrong, //������ȷ�ıȽ������
    while_do_wrong,//while������
    exit_wrong,//exit������
    exit_IsNotIn_while,//exit��䲻��ѭ����
    read_end_wrong,//read��������
    read_wrong,//read����
    read_var_wrong,//������Ĳ��Ǳ���
    read_Boolean_wrong,//Boolean���ͱ����޷�������
    write_end_wrong,//write����������
    write_wrong,//write������
    complex_end_wrong,//������ȷ�����������������м����ȱ�ٷֺ�
    wrong_program_end,//����Ĺ��̽���
    var_undefined,//δ����
    var_wrong,//���Ǳ���
    var_redefined,//�����ض���
    const_redefined,//�����ض���,
    call_end_wrong,//���̵��ý�������
    real_para_wrong,//�β���ʵ�θ�������
};

string rightType = "Boolean";  //��ֵ����ұߵ����ͣ�ȫ�֣�realû�и�ֵ���ƣ�integer���ܸ�real�ͣ�Booleanֻ�ܸ�Boolean��
int paraCount = 0;   //��¼�������ʱ������������
int exitCount = 0;      //��¼exit�˳�ѭ�����δ��������
int GLoopLevel = 0;     //��¼ѭ��������ȫ��
int procedureLevel = 0; //��¼������ȫ��
int tx = 0;             //���ֱ�������ȫ��
int dx = 3;             //ÿ��ľֲ���Ե�ַ��ȫ��
int cx = 0;             //���뼯�ϵ�������ָ����һ����ַ��ȫ��

//�˳�ѭ��exitList�ṹ��
struct ExitList{
    int cx;//���ڴ洢ִ��exit�󣬲�����תָ��ĵ�ַ����ѭ�����������ݴ˵�ַ����
    int LoopLevel;//��¼ѭ���Ĳ�����ֻ���ǰ��ε�ѭ��
};

//�﷨�����
struct treeNode {
    string element;
    vector<treeNode *> child;
    explicit treeNode(string e) {//��ֹ�๹�캯������ʽ�Զ�ת��
        element = e; // NOLINT
        for (auto &it : child)
            it = nullptr;
    }
};

//�﷨�������ֱ�Ԫ��
struct tableEle {
    string name;//������(����)�������
    string kind;//�������ࣺconst��var��procedure
    string type;//�������ͣ�integer��real��Boolean
    float value;//��ʾ������ֵ
    int level;//Ƕ�ײ��
    int addr;//(ƫ��)���������Ƕ�׹��̻���ַ�ĵ�ַ��procedure��¼���Ǹù��̵ĵ�һ��ָ���ַ
    int paranum;//���ڱ�����̵Ĳ�������
    tableEle() {//Ĭ��ֵ
        name = "";
        kind = "";
        type = "";
        value = -1;
        level = -1;
        addr = -1;
        paranum = -1;
    }
};

vector<ExitList> exitList; //�˳�ѭ���б�
vector<tableEle> tables; //�﷨�������ֱ�

//�ҵ����������ֱ��λ�ã�û�ҵ�����-1����ʾû���ض��壬��δ����
int findAddrInTable(string &s) {
    for (int i = (int)tables.size() - 1; i >= 0; --i)
        if (s == tables[i].name && tables[i].level <= procedureLevel)
            return i;
    return -1;
}

void printTables() {
    cout << "���ֱ�" << endl;
    for (int i = 0; i < tables.size(); ++i) {
        if(tables[i].kind=="const")
            cout << i << ": " << tables[i].name << " " << tables[i].kind << " " << tables[i].type << " " <<tables[i].value << endl;
        if(tables[i].kind=="var")
            cout << i << ": " << tables[i].name << " " << tables[i].kind << " " << tables[i].type << " " << tables[i].level << " " << tables[i].addr << endl;
        if(tables[i].kind=="procedure")
            cout << i << ": " << tables[i].name << " " << tables[i].kind << " " << tables[i].type << " " << tables[i].level << " " << tables[i].addr << " " << tables[i].paranum <<endl;
    }
}

struct codeEle {//Ŀ�Ĵ���Ԫ��
    string func;//������
    int level_d;//��β� ����ʶ�����ò��ȥ����㣩����Ҫ���ž�̬���ߵĴ���
    float offset;//��ͬ�������岻ͬ
};
vector<codeEle> codes; //Ŀ�Ĵ����

void addCode(string str, int lev, float off) {
    codeEle coe;
    coe.func = str;
    coe.level_d = lev;
    coe.offset = off;
    codes.push_back(coe);
    cx++;//�м��������1
}

void printCodes() {
    cout << "Ŀ���������" << endl;
    for (int i = 0; i < codes.size(); ++i)
        cout << i << ": " << codes[i].func << " " << codes[i].level_d << " " << codes[i].offset << endl;
}

void printTreeNode(treeNode *root, int level) {
    if (root != nullptr) {
        for (int i = 0; i < level; ++i)
            cout << " |";
        cout << " *" << root->element << endl;
        for (auto &it : root->child)//ȡ�����к���
            printTreeNode(it, level + 1);//�ݹ�
    }
}

string sym;//ȫ�ֵ��ʱ�������

bool error_grammar = false;

void error_exc(int error_grammar_type); //������
void BLOCK(treeNode *tn);               //�﷨������ڳ���
void subBlock(treeNode *tn);            //�ֳ���
void const_BLOCK(treeNode *tn);         //����˵��
void const_def(treeNode *tn);           //��������
int var_BLOCK(treeNode *tn);            //����˵��
void procedure_BLOCK(treeNode *tn);     //����˵��
void procedure_head(treeNode *tn);      //�����ײ�
void sen_BLOCK(treeNode *tn);           //���
void assi_sen(treeNode *tn);            //��ֵ���
void condition_sen(treeNode *tn);       //�������
void do_while_sen(treeNode *tn);        //����ѭ�����
void exit_sen(treeNode* tn);            //�˳�ѭ�����
void proc_call_sen(treeNode *tn);       //���̵������
void read_sen(treeNode *tn);            //�����
void write_sen(treeNode *tn);           //д���
void complex_sen(treeNode *tn);         //�������
void rel_expression(treeNode *tn);      //��ϵ���ʽ
void expression(treeNode *tn);          //���ʽ
//void condition(treeNode *tn);           //����
void item(treeNode *tn);                //��
void factor(treeNode *tn);              //����

//������
void error_exc(int error_grammar_type) {
    error_grammar = true;
    int temp_line = lineSum + 1;
    switch (error_grammar_type) {
    case const_state_end_wrong:
        cout << "����˵���������� in line " << temp_line << endl;
        break;
    case number_wrong:
        cout << "�޷���������ʵ������ in line " << temp_line << endl;
        break;
    case const_assign_wrong:
        cout << "������ֵ���� in line " << temp_line << endl;
        break;
    case identifier_wrong:
        cout << "��ʶ������ in line " << temp_line << endl;
        break;
    case var_state_end_wrong:
        cout << "����˵���������� in line " << temp_line << endl;
        break;
    case var_no_type_wrong:
        cout << "���������� in line " << temp_line << endl;
        break;
    case var_type_wrong:
        cout << "�������ʹ��� in line " << temp_line << endl;
        break;
    case procedure_state_end_wrong:
        cout << "����˵���������� in line " << temp_line << endl;
        break;
    case procedure_name_redefined:
        cout << "�������������������ظ� in line " << temp_line << endl;
        break;
    case procedure_head_wrong:
        cout << "�����ײ����� in line " << temp_line << endl;
        break;
    case not_procedure_name:
        cout << "���÷ǹ����� in line " << temp_line << endl;
        break;

    case var_assign_wrong:
        cout << "������ֵ���� in line " << temp_line << endl;
        break;
    case Boolean_assign_wrong:
        cout << "Boolean�������ܸ�������ʵ�� in line " << temp_line << endl;
        break;
   case integer_assign_wrong:
        cout << "integer�������ܸ�ʵ�� in line " << temp_line << endl;
        break;
    case expression_in_factor_wrong:
        cout << "�����еı��ʽ���� in line " << temp_line << endl;
        break;
    case factor_wrong:
        cout << "�����д��� in line " << temp_line << endl;
        break;
    case if_then_wrong:
        cout << "if_then������ in line " << temp_line << endl;
        break;
    case condition_wrong:
        cout << "�Ƚ�������� in line " << temp_line << endl;
        break;
    case while_do_wrong:
        cout << "while_do������ in line " << temp_line << endl;
        break;
    case exit_wrong:
        cout << "exit�˳�ѭ�������� in line " << temp_line << endl;
        break;
    case exit_IsNotIn_while:
        cout << "exit�˳�ѭ����䲻��ѭ���� in line " << temp_line << endl;
        break;
    case read_end_wrong:
        cout << "read���������� in line " << temp_line << endl;
        break;
    case read_wrong:
        cout << "read������ in line " << temp_line << endl;
        break;
    case read_var_wrong:
        cout << "������Ĳ��Ǳ��� in line " << temp_line << endl;
        break;
    case read_Boolean_wrong:
        cout << "Boolean���ͱ����޷������� in line " << temp_line << endl;
        break;

    case write_end_wrong:
        cout << "write���������� in line " << temp_line << endl;
        break;
    case write_wrong:
        cout << "write������ in line " << temp_line << endl;
        break;
    case complex_end_wrong:
        cout << "������ȷ�����������������м����ȱ�ٷֺ� in line " << temp_line << endl;
        break;
    case wrong_program_end:
        cout << "wrong program end in line " << temp_line << endl;
        break;
    case var_undefined:
        cout << "��δ����ı��� in line " << temp_line << endl;
        break;
    case var_wrong:
        cout << "����ֵ�Ĳ��Ǳ��� in line " << temp_line << endl;
        break;
    case var_redefined:
        cout << "�ظ�����ı��� in line " << temp_line << endl;
        break;
    case const_redefined:
        cout << "�ظ�����ĳ��� in line " << temp_line << endl;
        break;
    case call_end_wrong:
        cout << "���̵��ý������� in line " << temp_line << endl;
        break;
    case real_para_wrong:
        cout << "�β���ʵ�θ������� in line " << temp_line << endl;
        break;
    default:
        break;
    }
    exit(0);
}
//�﷨������ڳ���
void BLOCK(treeNode *tn) {
    sym = GETSYM();
    auto *subBlockt = new treeNode("�ֳ���");
    tn->child.push_back(subBlockt);//ѹ��һ������
    subBlock(subBlockt);//ת��ֳ�����
    if (sym == ".") {
        tn->child.push_back(new treeNode("."));
        sym = GETSYM();
        //��Ӵ���
        addCode("opr", 0, ReturnOpr);//���������ù��̣����ص��õ㲢��ջ
        //
        cout << "Grammar analysis complete" << endl;
        // cout << "the chart of integer has " << integerArray.size() << " items." << endl;
        // cout << "the chart of identifier has " << identifierArray.size() << " items" << endl;
    } 
    else
        error_exc(wrong_program_end);
}
//�ֳ���
void subBlock(treeNode *tn) {
    addCode("jmp", 0, -1); //��ת����䲿�֣�-1��ʾ�ȴ�����
    int tmpCodeAddr = cx - 1;
    int varcount = 0;
    if (sym == "const") {//����Ϊconst
        auto *const_BLOCKt = new treeNode("����˵������");
        tn->child.push_back(const_BLOCKt);//ѹ��Ϊ�ֳ�����
        const_BLOCK(const_BLOCKt); //����˵��
    }
    if (sym == "var") {
        auto *var_BLOCKt = new treeNode("����˵������");
        tn->child.push_back(var_BLOCKt);//ѹ��Ϊ�ֳ�����
        varcount = var_BLOCK(var_BLOCKt); //����˵��
    }    if (sym == "procedure") {
        auto *procedure_BLOCKt = new treeNode("����˵������");
        tn->child.push_back(procedure_BLOCKt);//ѹ��Ϊ�ֳ�����
        procedure_BLOCK(procedure_BLOCKt); //����˵��
    }
    auto *sen_BLOCKt = new treeNode("���");
    tn->child.push_back(sen_BLOCKt);
    //��Ӵ���
    addCode("int", 0, varcount + 3);
    codes[tmpCodeAddr].offset = cx - 1;//ָ����һ��
    //
    sen_BLOCK(sen_BLOCKt); //���
}
//����˵��
void const_BLOCK(treeNode *tn) {
    if (sym == "const") {
        tn->child.push_back(new treeNode("const"));//��constѹ�볣��˵��
        sym = GETSYM();//��ȡ��һ�����ʣ�Ϊ��һ���ж���׼��
        auto *const_deft = new treeNode("��������");//��������������
        tn->child.push_back(const_deft);
        const_def(const_deft);//���볣�����岿�֣����ó��������㴫��
        while (sym == ",") {
            tn->child.push_back(new treeNode(","));
            sym = GETSYM();
            auto *const_defts = new treeNode("��������");
            tn->child.push_back(const_defts);
            const_def(const_defts);
        }
        if (sym == ";") {
            tn->child.push_back(new treeNode(";"));
            sym = GETSYM();
        } else
            error_exc(const_state_end_wrong); //����˵���Ĵ������
    } 
    else
        return;//û��ֱ�ӷ���
}
//��������
void const_def(treeNode *tn) {
    if (sym == "identifier") {
        auto *idt = new treeNode(debugId);//��ʶ�����ƽ��
        tn->child.push_back(new treeNode("��ʶ��"));
        tn->child.back()->child.push_back(idt);
        //������ֱ�
        int labelAddr = findAddrInTable(debugId);//�鿴�Ƿ��ض���
        if (labelAddr != -1)
            error_exc(const_redefined);
        tableEle tabe;
        tabe.name = debugId;
        tabe.kind = "const";
        //
        sym = GETSYM();
        if (sym == "=") {
            tn->child.push_back(new treeNode("="));
            sym = GETSYM();
            if (sym == "int_number") {
                auto *numt = new treeNode(Int_debugNum);
                tn->child.push_back(new treeNode("�޷�������"));
                tn->child.back()->child.push_back(numt);
                //������ֱ�
                tabe.value = Int_debugNumber;
                tabe.type = "integer";
                tables.push_back(tabe);
                tx++;//���ֱ�������1
                
                sym = GETSYM();
            }
            else if (sym=="real_number") {
                auto* numt2 = new treeNode(Real_debugNum);
                tn->child.push_back(new treeNode("ʵ��"));
                tn->child.back()->child.push_back(numt2);
                //������ֱ�
                tabe.value = Real_debugNumber;
                tabe.type = "real";
                tables.push_back(tabe);
                tx++;//���ֱ�������1

                sym = GETSYM();//��סȡ��һ����������
            }
            else
                error_exc(number_wrong); //��������
        } 
        else
            error_exc(const_assign_wrong); //���ǳ�����ֵ
    } 
    else
        error_exc(identifier_wrong); //���Ǳ�ʶ��
}
//����˵������:���������
int var_BLOCK(treeNode *tn) {
    if (sym == "var") {
        int varNumber = 0;//������Ŀ
        tn->child.push_back(new treeNode("var"));
        sym = GETSYM();
        int temp_tx = tx;//��¼�����ʼ���±�
        tableEle tabe;//�������ֱ���
        if (sym == "identifier") {
            auto *idt = new treeNode(debugId);
            tn->child.push_back(new treeNode("��ʶ��"));
            tn->child.back()->child.push_back(idt);//ѹ���ʶ���ĺ��ӣ���ʶ������
            //������ֱ�
            int labelAddr = findAddrInTable(debugId);
            if (labelAddr != -1)
                error_exc(var_redefined);
            tabe.name = debugId;
            tabe.kind = "var";
            tabe.addr = dx++;
            tabe.level = procedureLevel;
            tables.push_back(tabe);
            tx++;
            varNumber++;
            //
            sym = GETSYM();
        } 
        else
            error_exc(identifier_wrong); //���Ǳ�ʶ��
        while (sym == ",") {
            tn->child.push_back(new treeNode("��"));
            sym = GETSYM();
            if (sym == "identifier") {
                auto *idt = new treeNode(debugId);
                tn->child.push_back(new treeNode("��ʶ��"));
                tn->child.back()->child.push_back(idt);
                //������ֱ�
                int labelAddr = findAddrInTable(debugId);
                if (labelAddr != -1)
                    error_exc(var_redefined);//�ض���
                tabe.name = debugId;
                tabe.kind = "var";
                tabe.addr = dx++;
                tabe.level = procedureLevel;
                tables.push_back(tabe);
                tx++;
                varNumber++;
                //
                sym = GETSYM();//ȡ��һ����������
            } 
            else
                error_exc(identifier_wrong); //���Ǳ�ʶ��
        }
        if (sym == ":") {//�������:�����������������
            tn->child.push_back(new treeNode("��"));//�﷨��
            sym = GETSYM();
            if (sym == "integer" || sym == "real" || sym == "Boolean") {
                tn->child.push_back(new treeNode("����"));
                tn->child.back()->child.push_back(new treeNode(sym));
                for (int j = temp_tx; j < tx; j++) {//���temp_tx����tx-1�±������type
                    tables[j].type = sym;
                }
                sym = GETSYM();//ȡ��һ����������
            }
            else
                error_exc(var_type_wrong);//���ʹ���
        }
        else
            error_exc(var_no_type_wrong);//������
        if (sym == ";") {
            tn->child.push_back(new treeNode(";"));
            sym = GETSYM();//ȡ��һ���������ͣ��ж��Ƿ��ǹؼ���
        } 
        else
            error_exc(var_state_end_wrong); //����˵���Ľ�������

        while (!IsKey) {//��һ�����ʲ��ǹؼ�����������壬�ⲿ���ظ���������˵��
            temp_tx = tx;//��¼�����ʼ���±�
            tableEle tabe;//�������ֱ���
            if (sym == "identifier") {
                auto* idt = new treeNode(debugId);
                tn->child.push_back(new treeNode("��ʶ��"));
                tn->child.back()->child.push_back(idt);//ѹ���ʶ���ĺ��ӣ���ʶ������
                //������ֱ�
                int labelAddr = findAddrInTable(debugId);
                if (labelAddr != -1)
                    error_exc(var_redefined);
                tabe.name = debugId;
                tabe.kind = "var";
                tabe.addr = dx++;
                tabe.level = procedureLevel;
                tables.push_back(tabe);
                tx++;
                varNumber++;
                //
                sym = GETSYM();
            }
            else
                error_exc(identifier_wrong); //���Ǳ�ʶ��
            while (sym == ",") {
                tn->child.push_back(new treeNode("��"));
                sym = GETSYM();
                if (sym == "identifier") {
                    auto* idt = new treeNode(debugId);
                    tn->child.push_back(new treeNode("��ʶ��"));
                    tn->child.back()->child.push_back(idt);
                    //������ֱ�
                    int labelAddr = findAddrInTable(debugId);
                    if (labelAddr != -1)
                        error_exc(var_redefined);//�ض���
                    tabe.name = debugId;
                    tabe.kind = "var";
                    tabe.addr = dx++;
                    tabe.level = procedureLevel;
                    tables.push_back(tabe);
                    tx++;
                    varNumber++;
                    //
                    sym = GETSYM();//ȡ��һ����������
                }
                else
                    error_exc(identifier_wrong); //���Ǳ�ʶ��
            }
            if (sym == ":") {//�������:�����������������
                tn->child.push_back(new treeNode("��"));//�﷨��
                sym = GETSYM();
                if (sym == "integer" || sym == "real" || sym == "Boolean") {
                    tn->child.push_back(new treeNode("����"));
                    tn->child.back()->child.push_back(new treeNode(sym));
                    for (int j = temp_tx; j < tx; j++) {//���temp_tx����tx-1�±������type
                        tables[j].type = sym;
                    }
                    sym = GETSYM();//ȡ��һ����������
                }
                else
                    error_exc(var_type_wrong);//���ʹ���
            }
            else
                error_exc(var_no_type_wrong);//������
            if (sym == ";") {
                tn->child.push_back(new treeNode(";"));
                sym = GETSYM();//ȡ��һ���������ͣ��ж��Ƿ��ǹؼ���
            }
            else
                error_exc(var_state_end_wrong); //����˵���Ľ�������
        }
        return varNumber;
    } 
    else
        return -1;
}
//����˵��
void procedure_BLOCK(treeNode *tn) {
    if (sym == "procedure") {
        //����һ�����̣����Ӳ������ֲ���Ե�ַ�ָ�Ϊ3
        procedureLevel++;
        dx = 3;
        auto *procedure_headt = new treeNode("�����ײ�");
        tn->child.push_back(procedure_headt);
        procedure_head(procedure_headt);
        auto *subBlockt = new treeNode("�ֳ���");
        tn->child.push_back(subBlockt);
        subBlock(subBlockt);
        if (sym == ";") {
            tn->child.push_back(new treeNode(";"));
            //��Ӵ���
            addCode("opr", 0, ReturnOpr);
            procedureLevel--; //���̽��������Ͳ���
            
            sym = GETSYM();
            while (sym == "procedure") {
                auto *procedure_BLOCKt = new treeNode("����˵������");
                tn->child.push_back(procedure_BLOCKt);
                procedure_BLOCK(procedure_BLOCKt);
            }
        } 
        else
            error_exc(procedure_state_end_wrong); //����˵���Ľ�������
    } 
    else
        return;
}
//�����ײ�
void procedure_head(treeNode *tn) {
    if (sym == "procedure") {
        int temp_pro_tx = 0;//������������±�
        paraCount = 0;//�βα�����Ŀ��ÿ�ι��̶���ʱ���ó�ֵ0
        tn->child.push_back(new treeNode("procedure"));
        sym = GETSYM();
        if (sym == "identifier") {
            auto *idt = new treeNode(debugId);
            tn->child.push_back(new treeNode("��ʶ��"));
            tn->child.back()->child.push_back(idt);//ѹ��Ϊ��ʶ���ĺ���
            //������ֱ�
            int labelAddr = findAddrInTable(debugId);
            if (labelAddr != -1)
                error_exc(procedure_name_redefined);
            tableEle tabe;
            tabe.name = debugId;
            tabe.kind = "procedure";
            tabe.addr = cx;//ָ���ֳ�������
            tabe.level = procedureLevel - 1; //���̵Ĳ���Ӧ�������ڹ��̵���һ�㣬0�㶨��Ĺ���������0��
            tables.push_back(tabe);
            temp_pro_tx = tx;//������������±�
            tx++;
            //
            sym = GETSYM();
            if (sym == "(") {
                tn->child.push_back(new treeNode("("));
                sym = GETSYM();
                int temp_tx = tx;//��¼�����ʼ���±�
                tableEle tabe;//�������ֱ���
                if (sym == "identifier") {
                    auto* idt = new treeNode(debugId);
                    tn->child.push_back(new treeNode("��ʶ��"));
                    tn->child.back()->child.push_back(idt);//ѹ���ʶ���ĺ��ӣ���ʶ������
                    //������ֱ�
                    int labelAddr = findAddrInTable(debugId);
                    if (labelAddr != -1)
                        error_exc(var_redefined);
                    tabe.name = debugId;
                    tabe.kind = "var";
                    tabe.addr = dx++;
                    tabe.level = procedureLevel;
                    tables.push_back(tabe);
                    tx++;
                    paraCount++;
                    //
                    sym = GETSYM();
                }
                else
                    error_exc(identifier_wrong); //���Ǳ�ʶ��
                while (sym == ",") {
                    tn->child.push_back(new treeNode("��"));
                    sym = GETSYM();
                    if (sym == "identifier") {
                        auto* idt = new treeNode(debugId);
                        tn->child.push_back(new treeNode("��ʶ��"));
                        tn->child.back()->child.push_back(idt);
                        //������ֱ�
                        int labelAddr = findAddrInTable(debugId);
                        if (labelAddr != -1)
                            error_exc(var_redefined);//�ض���
                        tabe.name = debugId;
                        tabe.kind = "var";
                        tabe.addr = dx++;
                        tabe.level = procedureLevel;
                        tables.push_back(tabe);
                        tx++;
                        paraCount++;
                        //
                        sym = GETSYM();//ȡ��һ����������
                    }
                    else
                        error_exc(identifier_wrong); //���Ǳ�ʶ��
                }
                if (sym == ":") {//�������:�����������������
                    tn->child.push_back(new treeNode("��"));//�﷨��
                    sym = GETSYM();
                    if (sym == "integer" || sym == "real" || sym == "Boolean") {
                        tn->child.push_back(new treeNode("����"));
                        tn->child.back()->child.push_back(new treeNode(sym));
                        for (int j = temp_tx; j < tx; j++) {//���temp_tx����tx-1�±������type
                            tables[j].type = sym;
                        }
                        sym = GETSYM();//ȡ��һ����������
                    }
                    else
                        error_exc(var_type_wrong);//���ʹ���
                }
                else
                    error_exc(var_no_type_wrong);//������
                //������;�����������βΣ��ظ���������
                while (sym == ";") {
                    tn->child.push_back(new treeNode("��"));
                    sym = GETSYM();
                    int temp_tx = tx;//��¼�����ʼ���±�
                    tableEle tabe;//�������ֱ���
                    if (sym == "identifier") {
                        auto* idt = new treeNode(debugId);
                        tn->child.push_back(new treeNode("��ʶ��"));
                        tn->child.back()->child.push_back(idt);//ѹ���ʶ���ĺ��ӣ���ʶ������
                        //������ֱ�
                        int labelAddr = findAddrInTable(debugId);
                        if (labelAddr != -1)
                            error_exc(var_redefined);
                        tabe.name = debugId;
                        tabe.kind = "var";
                        tabe.addr = dx++;
                        tabe.level = procedureLevel;
                        tables.push_back(tabe);
                        tx++;
                        paraCount++;
                        //
                        sym = GETSYM();
                    }
                    else
                        error_exc(identifier_wrong); //���Ǳ�ʶ��
                    while (sym == ",") {
                        tn->child.push_back(new treeNode("��"));
                        sym = GETSYM();
                        if (sym == "identifier") {
                            auto* idt = new treeNode(debugId);
                            tn->child.push_back(new treeNode("��ʶ��"));
                            tn->child.back()->child.push_back(idt);
                            //������ֱ�
                            int labelAddr = findAddrInTable(debugId);
                            if (labelAddr != -1)
                                error_exc(var_redefined);//�ض���
                            tabe.name = debugId;
                            tabe.kind = "var";
                            tabe.addr = dx++;
                            tabe.level = procedureLevel;
                            tables.push_back(tabe);
                            tx++;
                            paraCount++;
                            //
                            sym = GETSYM();//ȡ��һ����������
                        }
                        else
                            error_exc(identifier_wrong); //���Ǳ�ʶ��
                    }
                    if (sym == ":") {//�������:�����������������
                        tn->child.push_back(new treeNode("��"));//�﷨��
                        sym = GETSYM();
                        if (sym == "integer" || sym == "real" || sym == "Boolean") {
                            tn->child.push_back(new treeNode("����"));
                            tn->child.back()->child.push_back(new treeNode(sym));
                            for (int j = temp_tx; j < tx; j++) {//���temp_tx����tx-1�±������type
                                tables[j].type = sym;
                            }
                            sym = GETSYM();//ȡ��һ����������
                        }
                        else
                            error_exc(var_type_wrong);//���ʹ���
                    }
                    else
                        error_exc(var_no_type_wrong);//������

                }
                if (sym == ")") {
                    tn->child.push_back(new treeNode(")"));
                    sym = GETSYM();
                }
                else {
                    error_exc(procedure_head_wrong);//�����ײ�����
                }
            }
            if (sym == ";") {//�����ײ��ԷֺŽ���
                tn->child.push_back(new treeNode(";"));
                sym = GETSYM();
                //�����������
                tables[temp_pro_tx].paranum = paraCount;
            } else
                error_exc(procedure_head_wrong); //�����ײ��������
        } else
            error_exc(identifier_wrong); //���Ǳ�ʶ��
    } else
        return;
}
//�ֳ�������
void sen_BLOCK(treeNode *tn) {
    if (sym == "identifier") {
        auto *assi_sent = new treeNode("��ֵ���");
        tn->child.push_back(assi_sent);//ѹ��Ϊ���ĺ���
        assi_sen(assi_sent);
    } 
    else if (sym == "if") {
        auto *condition_sent = new treeNode("�������");
        tn->child.push_back(condition_sent);
        condition_sen(condition_sent);
    } 
    else if (sym == "while") {
        auto *do_while_sent = new treeNode("����ѭ�����");
        tn->child.push_back(do_while_sent);
        do_while_sen(do_while_sent);
    } 
    else if (sym == "exit") {
        auto *exit_sent = new treeNode("�˳�ѭ�����");
        tn->child.push_back(exit_sent);
        exit_sen(exit_sent);
    } 

    else if (sym == "call") {
        auto *proc_call_sent = new treeNode("���̵������");
        tn->child.push_back(proc_call_sent);
        proc_call_sen(proc_call_sent);
    } 
    else if (sym == "read") {
        auto *read_sent = new treeNode("�����");
        tn->child.push_back(read_sent);
        read_sen(read_sent);
    } 
    else if (sym == "write") {
        auto *write_sent = new treeNode("д���");
        tn->child.push_back(write_sent);
        write_sen(write_sent);
    } 
    else if (sym == "begin") {
        auto *complex_sent = new treeNode("�������");
        tn->child.push_back(complex_sent);
        complex_sen(complex_sent);
    }
}
//��ֵ���
void assi_sen(treeNode *tn) {
    if (sym == "identifier") {
        auto *idt = new treeNode(debugId);
        tn->child.push_back(new treeNode("��ʶ��"));
        tn->child.back()->child.push_back(idt);
        string tmp = debugId; //�������ֵ�ı���
        int labelAddr = findAddrInTable(tmp);
        if (labelAddr == -1)
            error_exc(var_undefined);
        if(tables[labelAddr].kind!="var")
            error_exc(var_wrong);//����ֵ�Ĳ��Ǳ���
        rightType = "Boolean";//ÿ��ִ�и�ֵ��䣬��Ҫ���Ҳ���������ΪBoolean
        string leftType = tables[labelAddr].type;//���汻��ֵ��ʶ��������
        sym = GETSYM();
        if (sym == ":=") {
            tn->child.push_back(new treeNode(":="));
            sym = GETSYM();
            auto * rel_expressiont = new treeNode("�Ƚϱ��ʽ");
            tn->child.push_back(rel_expressiont);
            rel_expression(rel_expressiont);
            //��Ӵ���
            int level_diff = abs(tables[labelAddr].level - procedureLevel);//��¼������ʱ��̬����ʹ��
            addCode("sto", level_diff, tables[labelAddr].addr);//��ջ����ֵ������Ϊlevel_diff��ƫ����Ϊtables[labelAddr].addr�ĵ�Ԫ
            //
            if (leftType == "Boolean" && rightType!="Boolean") {
                error_exc(Boolean_assign_wrong);//Boolean��ֵ����
            }
            else if (leftType == "integer" && rightType == "real") {
                error_exc(integer_assign_wrong);//integer��ֵ����
            }
        } 
        else
            error_exc(var_assign_wrong); //���Ǳ�����ֵ
    } else
        return;
}

 //��ϵ���ʽ
void rel_expression(treeNode* tn) {
    auto* expressiont0 = new treeNode("���ʽ");//�������
    tn->child.push_back(expressiont0);
    expression(expressiont0);
    if (sym == "=" || sym == "<>" || sym == "<" || sym == "<=" || sym == ">" || sym == ">=") {
        string opr = sym;
        auto* idt = new treeNode(sym);
        tn->child.push_back(new treeNode("���������"));
        tn->child.back()->child.push_back(idt);
        sym = GETSYM();
        auto* expressiont1 = new treeNode("���ʽ");//�����ұ�
        tn->child.push_back(expressiont1);
        expression(expressiont1);
        //��Ӵ���
        if (opr == "=")
            addCode("opr", 0, EquOpr); //=����
        else if (opr == "<>")
            addCode("opr", 0, NeqOpr); //<>����
        else if (opr == "<")
            addCode("opr", 0, LessOpr); //<����
        else if (opr == "<=")
            addCode("opr", 0, ElessOpr); //<=����
        else if (opr == ">")
            addCode("opr", 0, GreOpr); //>����
        else if (opr == ">=")
            addCode("opr", 0, EgreOpr); //>=����

    }

}

//���ʽ
void expression(treeNode *tn) {
    if (sym == "+" || sym == "-") {
        tn->child.push_back(new treeNode(sym));
        string opr = sym;
        sym = GETSYM();
        //��Ӵ���
        if (opr == "-")
            addCode("opr", 0, MinusOpr); //ȡ������
        //
    }
    auto *itemt = new treeNode("��");
    tn->child.push_back(itemt);
    item(itemt);
    while (sym == "+" || sym == "-" || sym == "or") {//����or
        auto *idt = new treeNode(sym);
        tn->child.push_back(new treeNode("�Ӽ��������"));
        tn->child.back()->child.push_back(idt);
        string opr = sym; //�ݴ������
        sym = GETSYM();
        auto *itemts = new treeNode("��");
        tn->child.push_back(itemts);
        item(itemts);
        //��Ӵ���
        if (opr == "+")
            addCode("opr", 0, AddOpr); //+����
        else if (opr == "-")
            addCode("opr", 0, SubOpr); //-����
        else if (opr == "or")
            addCode("opr", 0, OrOpr);//or����
        //
    }
}
//��
void item(treeNode *tn) {
    auto factort = new treeNode("����");
    tn->child.push_back(factort);
    factor(factort);
    while (sym == "*" || sym == "/" || sym == "mod" || sym == "and" || sym == "div" || sym == "%") {
        string opr = sym;//�ݴ������
        auto *idt = new treeNode(sym);
        tn->child.push_back(new treeNode("�˳�ȡ���������"));
        tn->child.back()->child.push_back(idt);
        sym = GETSYM();
        auto factorts = new treeNode("����");
        tn->child.push_back(factorts);
        factor(factorts);
        //��Ӵ��룬���������2�����Ӵ������֮���
        if (opr == "*")
            addCode("opr", 0, MulOpr); //*����
        else if (opr == "/")
            addCode("opr", 0, RDivOpr); // ʵ��/����
        else if (opr == "div")
            addCode("opr", 0, DivOpr); // ����div����
        else if (opr == "mod" || sym == "%")
            addCode("opr", 0, ModOpr); // mod����
        else if (opr == "and")
            addCode("opr", 0, AndOpr); // and����
        
    }
}

//����
void factor(treeNode *tn) {
    if (sym == "identifier" || sym == "int_number" || sym == "real_number" || sym == "true" || sym == "false") {
        string tmp;
        treeNode *idt;
        if (sym == "identifier") {
            tmp = "��ʶ��";
            idt = new treeNode(debugId);
            //��Ӵ���
            int labelAddr = findAddrInTable(debugId);
            if (labelAddr == -1)
                error_exc(var_undefined);
            if (tables[labelAddr].kind == "const") {
                addCode("lit", 0, tables[labelAddr].value);
                if (tables[labelAddr].type == "integer" && rightType == "Boolean") {//��Boolean���͸�Ϊinteger
                    rightType = "integer";
                }
                else if (tables[labelAddr].type == "real" && rightType != "real") {//����real���͸�Ϊreal����
                    rightType = "real";
                }
            }
            else if (tables[labelAddr].kind == "var") {
                int level_diff = abs(tables[labelAddr].level - procedureLevel);//��¼������ʱ��̬����ʹ��
                addCode("lod", level_diff, tables[labelAddr].addr);
                if (tables[labelAddr].type == "integer" && rightType == "Boolean") {//��Boolean���͸�Ϊinteger
                    rightType = "integer";
                }
                else if (tables[labelAddr].type == "real" && rightType != "real") {//����real���͸�Ϊreal����
                    rightType = "real";
                }
            }   
            
        } 
        else if(sym == "int_number"){
            tmp = "�޷�������";
            idt = new treeNode(Int_debugNum);
            //��Ӵ���
            addCode("lit", 0, Int_debugNumber);
            if (rightType=="Boolean") {
                rightType = "integer";
            }
        }
        else if(sym == "real_number"){
            tmp = "ʵ��";
            idt = new treeNode(Real_debugNum);
            //��Ӵ���
            addCode("lit", 0, Real_debugNumber);
            if (rightType == "Boolean" || rightType == "integer") {
                rightType = "real";
            }
        }
        else if(sym == "true"){
            tmp = "����ֵ";
            idt = new treeNode("true");
            //��Ӵ���
            addCode("lit", 0, 1);
        }
        else if(sym == "false"){
            tmp = "����ֵ";
            idt = new treeNode("false");
            //��Ӵ���
            addCode("lit", 0, 0);
        }
        tn->child.push_back(new treeNode(tmp));
        tn->child.back()->child.push_back(idt);
        sym = GETSYM();
    } 
    else if (sym == "not") {//ȡ��
        tn->child.push_back(new treeNode("not"));//�����﷨��
        auto* factort = new treeNode("����");
        tn->child.push_back(factort);
        sym = GETSYM();
        factor(factort);

        //��Ӵ���
        addCode("opr", 0, AntiOpr); // not����
    }
    else if (sym == "odd") {//����Ϊ1��ż��Ϊ0
        tn->child.push_back(new treeNode("odd"));//�����﷨��
        sym = GETSYM();
        if (sym == "(") {
            tn->child.push_back(new treeNode("("));
            sym = GETSYM();
            auto* expressiont = new treeNode("���ʽ");
            tn->child.push_back(expressiont);
            expression(expressiont);
            if (sym == ")") {
                tn->child.push_back(new treeNode(")"));
                sym = GETSYM();
            }
            else
                error_exc(expression_in_factor_wrong); //�����а����ı��ʽ�Ĵ������
        }
        else
            error_exc(factor_wrong);

        //��Ӵ���
        addCode("opr", 0, OddOpr); // odd����
    }
    else if (sym == "(") {
        tn->child.push_back(new treeNode("("));
        sym = GETSYM();
        auto * rel_expressiont = new treeNode("�Ƚϱ��ʽ");
        tn->child.push_back(rel_expressiont);
        rel_expression(rel_expressiont);
        if (sym == ")") {
            tn->child.push_back(new treeNode(")"));
            sym = GETSYM();
        } 
        else
            error_exc(expression_in_factor_wrong); //�����а����ı��ʽ�Ĵ������
    }
    else
        error_exc(factor_wrong);
}
//�������
void condition_sen(treeNode *tn) {
    if (sym == "if") {
        tn->child.push_back(new treeNode("if"));
        sym = GETSYM();
        auto *rel_expressiont = new treeNode("�Ƚϱ��ʽ");
        tn->child.push_back(rel_expressiont);
        rel_expression(rel_expressiont);
        if (sym == "then") {
            tn->child.push_back(new treeNode("then"));
            sym = GETSYM();
            auto *sen_BLOCKt = new treeNode("���");
            tn->child.push_back(sen_BLOCKt);
            //��Ӵ���
            addCode("jpc", 0, -1); //��ַ�ȴ�����
            int tmp = cx - 1;//tmpָ�����jpcָ��ĵ�ַ
            //
            sen_BLOCK(sen_BLOCKt);

            addCode("jmp", 0, -1);//����������else֮�󣬻������һ��
            int tmp2 = cx - 1;
            //������֮�����
            codes[tmp].offset = cx; //������ת�ĵ�ַ��ʵ��if����Ϊ����ת�ĵ�ַ
            if (sym == "else") {
                tn->child.push_back(new treeNode("else"));
                auto* sen_BLOCKt2 = new treeNode("���");
                tn->child.push_back(sen_BLOCKt2);

                sym = GETSYM();
                sen_BLOCK(sen_BLOCKt2);
            }
            codes[tmp2].offset = cx;//����else�����Ŀ�����������ĺ�һ��ָ��ĵ�ַ
            //
        }
        //if()
        else
            error_exc(if_then_wrong); //������ȷ��if���
    } else
        return;
}
//����
//void condition(treeNode *tn) {
//    if (sym != "odd") {
//        auto * expressiont0 = new treeNode("���ʽ");//�������
//        tn->child.push_back(expressiont0);
//        expression(expressiont0);
//        if (sym == "=" || sym == "<>" || sym == "<" || sym == "<=" || sym == ">" || sym == ">=") {
//            string opr = sym;
//            auto *idt = new treeNode(sym);
//            tn->child.push_back(new treeNode("���������"));
//            tn->child.back()->child.push_back(idt);
//            sym = GETSYM();
//            auto* expressiont1 = new treeNode("���ʽ");//�����ұ�
//            tn->child.push_back(expressiont1);
//            expression(expressiont1);
//            //��Ӵ���
//            if (opr == "=")
//                addCode("opr", 0, EquOpr); //=����
//            else if (opr == "<>")
//                addCode("opr", 0, NeqOpr); //<>����
//            else if (opr == "<")
//                addCode("opr", 0, LessOpr); //<����
//            else if (opr == "<=")
//                addCode("opr", 0, ElessOpr); //<=����
//            else if (opr == ">")
//                addCode("opr", 0, GreOpr); //>����
//            else if (opr == ">=")
//                addCode("opr", 0, EgreOpr); //>=����
//
//            //
//        } 
//        else
//            error_exc(condition_wrong); //������ȷ�ıȽ������
//    } 
//    else {
//        string opr = sym;
//        tn->child.push_back(new treeNode("odd"));
//        sym = GETSYM();
//        auto *expressiont2 = new treeNode("���ʽ");
//        tn->child.push_back(expressiont2);
//        expression(expressiont2);
//        //��Ӵ���
//        addCode("opr", 0, OddOpr); // odd����
//        //
//    }
//}
//���̵������
void proc_call_sen(treeNode *tn) {
    if (sym == "call") {
        tn->child.push_back(new treeNode("call"));
        sym = GETSYM();
        if (sym == "identifier") {
            int real_paranum = 0;//��¼ʵ�εĸ���
            auto *idt = new treeNode(debugId);
            tn->child.push_back(new treeNode("��ʶ��"));
            tn->child.back()->child.push_back(idt);
            //��Ӵ���
            int labelAddr = findAddrInTable(debugId);//�ҵ������������ֱ��е�λ��
            if (labelAddr == -1)
                error_exc(var_undefined);
            if (tables[labelAddr].kind != "procedure") {
                error_exc(not_procedure_name);//�����õĲ��ǹ���
            }
            sym = GETSYM();
            if (sym == "(") {//�������û�в��������ü�����
                tn->child.push_back(new treeNode("("));
                sym = GETSYM();
                auto* rel_expressiont = new treeNode("�Ƚϱ��ʽ");
                tn->child.push_back(rel_expressiont);
                rel_expression(rel_expressiont);
                real_paranum++;//ʵ�θ�����1
                while (sym == ",") {
                    tn->child.push_back(new treeNode(","));
                    sym = GETSYM();
                    auto* rel_expressionts = new treeNode("�Ƚϱ��ʽ");
                    tn->child.push_back(rel_expressionts);
                    rel_expression(rel_expressionts);
                    real_paranum++;//ʵ�θ�����1
                }
                if (sym == ")") {
                    tn->child.push_back(new treeNode(")"));
                    sym = GETSYM();
                }
                else
                    error_exc(call_end_wrong); //������ȷ��call������
            }
            //�ж�ʵ�����βθ����Ƿ����
            if(real_paranum!= tables[labelAddr].paranum)
                error_exc(real_para_wrong);//ʵ�����βθ�������
            //���pasָ�ʵ������3����λ
            addCode("pas", 0, real_paranum);
            float entryCode = codes[tables[labelAddr].addr].offset;
            //float entryCode = tables[labelAddr].addr;//�����Ͷ�һ��jmp��ת
            addCode("cal", abs(tables[labelAddr].level - procedureLevel), entryCode);
            //
            //sym = GETSYM();
        } else
            error_exc(identifier_wrong); //���Ǳ�ʶ��
    } 
    else
        return;
}
//����ѭ�����
void do_while_sen(treeNode *tn) {
    if (sym == "while") {
        GLoopLevel++;//����ѭ����ѭ������+1
        tn->child.push_back(new treeNode("while"));
        int tmpCodeAddr = cx;//��ʱcxָ����һ��ѭ����Ҫ���ɵ�ָ��
        auto * rel_expressiont = new treeNode("����");
        tn->child.push_back(rel_expressiont);

        sym = GETSYM();
        rel_expression(rel_expressiont);
        if (sym == "do") {
            tn->child.push_back(new treeNode("do"));
            sym = GETSYM();
            auto *sen_BLOCKt = new treeNode("���");
            tn->child.push_back(sen_BLOCKt);
            //��Ӵ���
            addCode("jpc", 0, -1); // while����������ת
            int tmpCodeId = cx - 1;
            //
            sen_BLOCK(sen_BLOCKt);
            //��Ӵ���
            addCode("jmp", 0, tmpCodeAddr); //��ת��while
            //���������ת
            codes[tmpCodeId].offset = cx;
            //
            while (exitCount) {//����exit���
                if (exitList[exitCount - 1].LoopLevel == GLoopLevel) {//���ѭ����exit���ȼ���
                    codes[exitList[exitCount - 1].cx].offset = cx;//exit������ɵ�ָ����ת��ַ����
                    exitCount--;
                    exitList.pop_back();
                }
                else
                    break;
            }

            GLoopLevel--;//�˳�ѭ����ѭ������-1��
        } 
        else
            error_exc(while_do_wrong); //������ȷ��while_do���
    } 
    else
        return;
}

//�˳�ѭ�����
void exit_sen(treeNode* tn) {
    if (sym == "exit") {
        tn->child.push_back(new treeNode("exit"));
        sym = GETSYM();
        if (sym == "(") {
            tn->child.push_back(new treeNode("("));
            sym = GETSYM();
            if (sym == ")") {
                tn->child.push_back(new treeNode(")"));
                sym = GETSYM();
                if (GLoopLevel) {
                    ExitList eexit;//�ṹ��Ԫ��
                    addCode("jmp", 0, -1);//�ȴ�ѭ����������

                    eexit.cx = cx - 1;//cx-1��ʾָ������ɵ���תָ��ĵ�ַ
                    eexit.LoopLevel = GLoopLevel;//��¼ѭ������
                    exitCount++;
                    exitList.push_back(eexit);
                }
                else
                    error_exc(exit_IsNotIn_while); //exit��䲻��ѭ����
            }
            else
                error_exc(exit_wrong); //������ȷ��exit���
        }
        else
            error_exc(exit_wrong); //������ȷ��exit���
    }
}

//�����
void read_sen(treeNode *tn) {
    if (sym == "read") {
        tn->child.push_back(new treeNode("read"));
        //��Ӵ���
        addCode("opr", 0, ReadOpr); // read����
        //
        sym = GETSYM();
        if (sym == "(") {
            tn->child.push_back(new treeNode("("));
            sym = GETSYM();
            if (sym == "identifier") {
                auto *idt = new treeNode(debugId);
                tn->child.push_back(new treeNode("��ʶ��"));
                tn->child.back()->child.push_back(idt);
                //��Ӵ���
                int labelAddr = findAddrInTable(debugId);
                if (labelAddr == -1)
                    error_exc(var_undefined);
                if (tables[labelAddr].kind != "var")
                    error_exc(read_var_wrong);//������Ĳ��Ǳ���
                if(tables[labelAddr].type=="Boolean")
                    error_exc(read_Boolean_wrong);//Boolean���ͱ����޷�������
                addCode("sto", abs(tables[labelAddr].level - procedureLevel), tables[labelAddr].addr);//ÿ����һ���ʹ��ڱ�����Ӧ��λ��
                //
                sym = GETSYM();
            } else
                error_exc(identifier_wrong); //���Ǳ�ʶ��
            while (sym == ",") {
                tn->child.push_back(new treeNode(","));
                //��Ӵ���
                addCode("opr", 0, ReadOpr); // read����
                //
                sym = GETSYM();
                if (sym == "identifier") {
                    auto *idt = new treeNode(debugId);
                    tn->child.push_back(new treeNode("��ʶ��"));
                    tn->child.back()->child.push_back(idt);
                    //��Ӵ���
                    int labelAddr = findAddrInTable(debugId);
                    if (labelAddr == -1)
                        error_exc(var_undefined);
                    if (tables[labelAddr].kind != "var")
                        error_exc(read_var_wrong);//������Ĳ��Ǳ���
                    if (tables[labelAddr].type == "Boolean")
                        error_exc(read_Boolean_wrong);//Boolean���ͱ����޷�������
                    addCode("sto", abs(tables[labelAddr].level - procedureLevel), tables[labelAddr].addr);
                    //
                    sym = GETSYM();
                }
            }
            if (sym == ")") {
                tn->child.push_back(new treeNode(")"));
                sym = GETSYM();
            } else
                error_exc(read_end_wrong); //������ȷ��read������
        } else
            error_exc(read_wrong); //������ȷ��read���
    } else
        return;
}
//д���
void write_sen(treeNode *tn) {
    if (sym == "write") {
        tn->child.push_back(new treeNode("write"));
        sym = GETSYM();
        if (sym == "(") {
            tn->child.push_back(new treeNode("("));
            sym = GETSYM();
            auto *rel_expressiont = new treeNode("�Ƚϱ��ʽ");
            tn->child.push_back(rel_expressiont);
            rel_expression(rel_expressiont);
            //��Ӵ���
            addCode("opr", 0, WriteOpr); // write����
            addCode("opr", 0, ChaLineOpr);
            //
            while (sym == ",") {
                tn->child.push_back(new treeNode(","));
                sym = GETSYM();
                auto * rel_expressionts = new treeNode("�Ƚϱ��ʽ");
                tn->child.push_back(rel_expressionts);
                rel_expression(rel_expressionts);
                //��Ӵ���
                addCode("opr", 0, WriteOpr); // write����
                addCode("opr", 0, ChaLineOpr);
                //
            }
            if (sym == ")") {
                tn->child.push_back(new treeNode(")"));
                sym = GETSYM();
            } else
                error_exc(write_end_wrong); //������ȷ��write������
        } else
            error_exc(write_wrong); //������ȷ��write���
    } else
        return;
}
//������䣬����
void complex_sen(treeNode *tn) {
    if (sym == "begin") {
        tn->child.push_back(new treeNode("begin"));
        sym = GETSYM();
        auto *sen_BLOCKt = new treeNode("���");
        tn->child.push_back(sen_BLOCKt);
        sen_BLOCK(sen_BLOCKt);
        while (sym == ";") {
            tn->child.push_back(new treeNode(";"));
            sym = GETSYM();
            auto *sen_BLOCKts = new treeNode("���");
            tn->child.push_back(sen_BLOCKts);
            sen_BLOCK(sen_BLOCKts);
        }
        if (sym == "end") {
            tn->child.push_back(new treeNode("end"));
            sym = GETSYM();
        } 
        else
            error_exc(complex_end_wrong); //������ȷ�ĸ���������
    } 
    else
        return;
}
#endif // RUN_PL0_BLOCK_H
