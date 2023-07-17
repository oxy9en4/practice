#include "stdafx.h"
#include "StudentManager.h"
#include "FileIO.h"
#include <limits>

enum {
    PRINT = 0,
    SAVE = 1,
    LOAD = 2,
    RESET = 3,
    ADD = 4,
    DELETE = 5,
    SEARCH = 6,
    SORT = 7,
    EXIT = 8
};

LinkedList<Student> StudentManager::slist;

void StudentManager::gen_students() {
	srand(time(0));
	
	for (int i = 0; i < 10; ++i) {
		int id = i + 1;
		int kor = rand() % 101;
		int eng = rand() % 101;
		int math = rand() % 101;
		std::string name = "";
        for (int j = 0; j < 3; ++j) {
			name += 'A' + rand() % 26;
		}
		Student* s = new Student(name, id, kor, eng, math);
		slist.Push_Back(s);
	}
}

void StudentManager::Run() {

    gen_students();
    int op;

    while (1) {
        string test;
        int test_value=0;
        while (1) {
            cout << "\n���(0), ����(1), �ε�(2), �ʱ�ȭ(3), �߰�(4), ����(5), �˻�(6), ����(7), ����(8) : ";
            cin >> test;

            try {
                test_value = stoi(test);
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (test_value >= 0 && test_value < 10) {
                    op = test_value;
                    
                    break;
                }
                else {
                    cout << "�Է��� �߸��Ǿ����ϴ�. �ٽ� �Է����ּ���." << endl;
                }
            }
            catch (const std::invalid_argument& e) {
                cout << "���ڸ� �Է� �����մϴ�." << endl;
            }
            
            
        }


        

        if (op == PRINT) {
            slist.print();
            cout << "�� �л� �� : " << slist.size << "��" << endl;
        }
        else if (op == SAVE) {
            FileIO<Student>::save(slist);
        }
        else if (op == LOAD) {
            FileIO<Student>::load(slist);
        }
        else if (op == RESET) {
            slist.clear();
            cout << "����Ʈ�� �ʱ�ȭ�߽��ϴ�." << endl;
        }
        else if (op == ADD) {
            string name;
            int id, kor, eng, math;
            while (1) {
                cout << "�̸�, ID, ����, ����, ���� ������ �������� �����Ͽ� �Է��ϼ���: ";
                cin >> name >> id >> kor >> eng >> math;
                // �Է� ��ȿ�� �˻�
                if (cin.fail() || kor < 0 || kor > 100 || eng < 0 || eng > 100 || math < 0 || math > 100) {
                    // �̸�, ���̵� �Ǵ� ���� �� �߸��� ���� �ԷµǾ��ٸ� ���� �޽����� ����ϰ� �ٽ� �Է��� �޽��ϴ�.
                    cout << "�Է��� �߸��Ǿ����ϴ�. �ٽ� �Է����ּ���." << endl;
                    cin.clear(); // ���� �÷��� �ʱ�ȭ
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �Է� ���� ����
                }
                else {
                    break;
                }
            }
            Student* s = new Student(name, id, kor, eng, math);
            slist.Push_Back(s);
        }
        else if (op == 5) {
            int type;
            cout << "�̸����� �˻�(1) �Ǵ� ID�� �˻�(2): ";
            cin >> type;

            if (type == 1) {
                string name;
                cout << "������ �л��� �̸��� �Է��ϼ���: ";
                cin >> name;
                Student* s = slist.searchByName(name);
                if (s) {
                    s->print();
                    cout << "�� �л��� �����Ͻðڽ��ϱ�? (��: 1, �ƴϿ�: 0): ";
                    int yes;
                    cin >> yes;
                    if (yes == 1) {
                        if (slist.removeByID(s->id)) {
                            cout << "�л��� ���������� �����Ǿ����ϴ�." << endl;
                        }
                        else {
                            cout << "���� �������� ������ �߻��߽��ϴ�." << endl;
                        }
                    }
                }
                else {
                    cout << "ã�� �л��� �����ϴ�." << endl;
                }
            }
            else if (type == 2)
            {
                int id;
                cout << "������ �л��� ID�� �Է��ϼ���: ";
                cin >> id;
                Student* s = slist.searchByID(id);
                if (s) {
                    s->print();
                    cout << "�� �л��� �����Ͻðڽ��ϱ�? (��: 1, �ƴϿ�: 0): ";
                    int yes;
                    cin >> yes;
                    if (yes == 1) {
                        if (slist.removeByID(id)) {
                            cout << "�л��� ���������� �����Ǿ����ϴ�." << endl;
                        }
                        else {
                            cout << "���� �������� ������ �߻��߽��ϴ�." << endl;
                        }
                    }
                }
                else {
                    cout << "ã�� �л��� �����ϴ�." << endl;
                }
            }
            else {
                cout << "�Է��� �߸��Ǿ����ϴ�.";
            }
        }
        else if (op == 6) {
            int type;
            cout << "�̸����� �˻�(1) �Ǵ� ID�� �˻�(2): ";
            cin >> type;

            if (type == 1) {
                string name;
                cout << "�̸��� �Է��ϼ���: ";
                cin >> name;
                Student* s = slist.searchByName(name);
                if (s) {
                    s->print();
                }
                else {
                    cout << "ã�� �л��� �����ϴ�." << endl;
                }
            }
            else {
                int id;
                cout << "ID�� �Է��ϼ���: ";
                cin >> id;
                Student* s = slist.searchByID(id);
                if (s) {
                    s->print();
                }
                else {
                    cout << "ã�� �л��� �����ϴ�." << endl;
                }
            }
        }
        else if (op == 7) {
            int type;
            cout << "�̸� ��(1), ID ��(2), ���� ��(3): ";
            cin >> type;

            switch (type) {
            case 1:
                slist.sortByName();
                slist.print();
                break;
            case 2:
                slist.sortByID();
                slist.print();
                break;
            case 3:
                slist.sortByScore();
                slist.print();
                break;
            default:
                cout << "�߸��� �Է��Դϴ�." << endl;
            }
        }
        else if (op == 8) {
            cout << "����" << endl;
            break;
        }
        else {
            cout << "�߸��� �Է��Դϴ�." << endl;
        }
    }

    
}