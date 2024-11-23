#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include <filesystem>
#include <fstream>
#include <string>

using namespace std;
namespace fs = std::filesystem;

// ��ȡ����ľ���·��
fs::path desktopPath = fs::path(getenv("USERPROFILE")) / "Desktop";
fs::path NoSQLPath;             //�ǹ�ϵ�����ݿ����ϵͳ�洢·��
fs::path userPath;              //�û�����·��
fs::path databasePath;          //��ǰ���ݿ�·��
fs::path newPath;               //��ʱ·��

//�ĵ���
class Document {
public:
    string document_name ;
    string content;

    Document() {}
    Document(string name,string s) {
        document_name = name;
        content = s;
    }

    //չʾ�ĵ�
    void showDocument() {
        cout << "�ĵ�����:" << document_name << endl;
        cout << "�ĵ�����:" << content << endl;
    }
};

//������
class Collection {
public:
    string collection_name ;
    vector<Document> documents;
    Collection() {}
    Collection(string name) {
        collection_name = name;
    }

    // �����ĵ�
    void insertDocument(Document& document) {
        if (findDocument(document.document_name)==nullptr) {
            newPath = databasePath / collection_name / document.document_name;
            ofstream outputFile(newPath);
            if (outputFile.is_open()) {
                outputFile << document.content << endl;
                outputFile.close();
            }
            else {
                std::cerr << "Error creating document." << std::endl;
            }
            documents.push_back(document);
            cout << "�ĵ�����ɹ�" << endl;
        }
        else {
            cout << "�ĵ��Ѵ���" << endl;
        }
    }

    // ��ѯ�ĵ�
    Document* findDocument(string document_name) {
        auto it = find_if(documents.begin(), documents.end(),
            [document_name](Document& doc) {
                return doc.document_name == document_name;
            });

        if (it != documents.end()) {
            cout << "�ĵ���ѯ�ɹ�" << endl;
            return addressof(*it);
        }
        else {
            cout << "�ĵ���ѯʧ��" << endl;
            return nullptr;
        }
    }

    // �����ĵ�
    void updateDocument(string document_name, string s) {
        if (findDocument(document_name) != nullptr) {
            findDocument(document_name)->content = s;
            newPath = databasePath / collection_name / document_name;
            ofstream outputFile(newPath, ios::trunc);
            if (outputFile.is_open()) {
                outputFile << s << endl;
                outputFile.close();
                cout << "�ĵ��޸ĳɹ�" << endl;
            }
            else {
                std::cerr << "�ĵ���ʧ��" << std::endl;
            }
        }
        else {
            cout << "�ĵ��޸�ʧ��" << endl;
        }
    }

    // ɾ���ĵ�
    void deleteDocument(string document_name) {
        if (findDocument(document_name) != nullptr) {
            newPath = databasePath / collection_name / document_name;
            fs::remove_all(newPath);
            documents.erase(std::remove_if(documents.begin(), documents.end(),
                [document_name](Document& doc) {
                    return doc.document_name == document_name;
                }),
                documents.end());
            cout << "�ĵ�ɾ���ɹ�" << endl;
        }
        else {
            cout << "�ĵ�ɾ��ʧ��" << endl;
        }
    }

    //չʾ����
    void showCollection() {
        cout << "��������:" << collection_name << endl;
        for (int i = 0; i < documents.size(); i++)
            documents[i].showDocument();
    }
};

//���ݿ���
class Database {
public:
    string database_name ;
    vector<Collection> collections;
    Database() {}
    Database(string name) {
        database_name = name;
    }

    // ���뼯��
    void insertCollection(string collection_name) {
        if (findCollection(collection_name) == nullptr) {
            newPath = userPath / database_name / collection_name;
            fs::create_directory(newPath);
            collections.push_back(Collection(collection_name));
            cout << "���ϲ���ɹ�" << endl;
        }
        else {
            cout << "�����Ѵ���" << endl;
        }
    }

    // ��ѯ����
    Collection* findCollection(string collection_name) {
        auto it = find_if(collections.begin(), collections.end(),
            [collection_name](Collection& col) {
                return col.collection_name == collection_name;
            });

        if (it != collections.end()) {
            cout << "���ϲ�ѯ�ɹ�" << endl;
            return addressof(*it);
        }
        else {
            cout << "���ϲ�ѯʧ��"<<endl;
            return nullptr;
        }
    }

    // ɾ������
    void deleteCollection(string collection_name) {
        if (findCollection(collection_name) != nullptr) {
            newPath = userPath / database_name / collection_name;
            fs::remove_all(newPath);
            collections.erase(remove_if(collections.begin(), collections.end(),
                [collection_name](Collection& col) {
                    return col.collection_name == collection_name;
                }),
                collections.end());
            cout << "����ɾ���ɹ�" << endl;
        }
        else {
            cout << "����ɾ��ʧ��" << endl;
        }
    }

    //չʾ���ݿ�
    void showDatabase() {
        cout << "���ݿ�����:" << database_name << endl;
        for (int i = 0; i < collections.size(); i++)
            collections[i].showCollection();
    }
};

class User {
public:
    string userName;
    vector<Database> databases;
    User() {}
    User(string name) {
        userName = name;
    }

    // �������ݿ�
    void insertDatabase(string database_name) {
        if (findDatabase(database_name) == nullptr) {
            newPath = userPath / database_name;
            fs::create_directory(newPath);
            databases.push_back(Database(database_name));
            cout << "���ݿ����ɹ�" << endl;
        }
        else {
            cout << "���ݿ��Ѵ���" << endl;
        }
    }

    // ��ѯ���ݿ�
    Database* findDatabase(string database_name) {
        auto it = find_if(databases.begin(), databases.end(),
            [database_name](Database& dat) {
                return dat.database_name == database_name;
            });

        if (it != databases.end()) {
            cout << "���ݿ��ѯ�ɹ�" << endl;
            return addressof(*it);
        }
        else {
            cout << "���ݿ��ѯʧ��" << endl;
            return nullptr;
        }
    }

    // ɾ�����ݿ�
    void deleteDatabase(string database_name) {
        if (findDatabase(database_name) != nullptr) {
            newPath = userPath / database_name;
            fs::remove_all(newPath);
            databases.erase(remove_if(databases.begin(), databases.end(),
                [database_name](Database& dat) {
                    return dat.database_name == database_name;
                }),
                databases.end());
            cout << "���ݿ�ɾ���ɹ�" << endl;
        }
        else {
            cout << "���ݿ�ɾ��ʧ��" << endl;
        }
    }
};

User user_now = User();

void Initial(string username) {
    // �������Ŀ¼�Ƿ��ȡ
    if (fs::exists(desktopPath)) {
        std::cout << "����·���ѻ�ȡ" << std::endl;

        //�����ǹ�ϵ�����ݿ����ϵͳ�洢Ŀ¼
        NoSQLPath = desktopPath / "NoSQL_store";
        if (!fs::exists(NoSQLPath)) {
            fs::create_directory(NoSQLPath);
            std::cout << "�ǹ�ϵ�����ݿ�Ŀ¼�����ɹ� " << std::endl;
        }
        else {
            cout << "�ǹ�ϵ�����ݿ�Ŀ¼�Ѵ���" << std::endl;
        }

        //�����û�Ŀ¼
        userPath = NoSQLPath / username;
        databasePath = userPath;
        if (!fs::exists(userPath)) {
            fs::create_directory(userPath);
            std::cout << "��¼�û���һ��ʹ�÷ǹ�ϵ�����ݿ����ϵͳ���ѳ�ʼ����� " << std::endl;
        }
        else {
            try {
                //��ȡ�û�������������������ڴ�
                for (auto& entry1 : fs::directory_iterator(userPath)) {//�����û�Ŀ¼
                    if (fs::is_directory(entry1.status())) {
                        user_now.databases.push_back(Database(entry1.path().filename().string()));
                        for (auto& entry2 : fs::directory_iterator(entry1.path())) {//�������ݿ�Ŀ¼
                            if (fs::is_directory(entry2.status())) {
                                user_now.databases.back().collections.push_back(Collection(entry2.path().filename().string()));
                                for (auto& entry3 : fs::directory_iterator(entry2.path())) {//��������Ŀ¼
                                    if (fs::is_regular_file(entry3.status())) {//��ȡ�ĵ�����
                                        Document tempDoc;
                                        tempDoc.document_name = entry3.path().filename().string();
                                        ifstream inputFile(entry3.path());
                                        if (inputFile.is_open()) {
                                            string content;
                                            while (getline(inputFile, content)) {
                                                tempDoc.content += content + '\n';
                                            }
                                            inputFile.close();
                                            user_now.databases.back().collections.back().documents.push_back(tempDoc);
                                        }
                                        else {
                                            std::cerr << "Error opening file." << std::endl;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            catch (const fs::filesystem_error& e) {
                std::cerr << "Error accessing the folder: " << e.what() << std::endl;
            }
            cout << "�ǹ�ϵ�����ݿ����ϵͳ�Ѽ������" << std::endl;
        }
    }
    else {
        cerr << "����·��δ�ҵ�" << std::endl;
    }
}