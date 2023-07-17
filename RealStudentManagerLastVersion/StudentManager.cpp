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
            cout << "\n출력(0), 저장(1), 로드(2), 초기화(3), 추가(4), 삭제(5), 검색(6), 정렬(7), 종료(8) : ";
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
                    cout << "입력이 잘못되었습니다. 다시 입력해주세요." << endl;
                }
            }
            catch (const std::invalid_argument& e) {
                cout << "숫자만 입력 가능합니다." << endl;
            }
            
            
        }


        

        if (op == PRINT) {
            slist.print();
            cout << "총 학생 수 : " << slist.size << "명" << endl;
        }
        else if (op == SAVE) {
            FileIO<Student>::save(slist);
        }
        else if (op == LOAD) {
            FileIO<Student>::load(slist);
        }
        else if (op == RESET) {
            slist.clear();
            cout << "리스트를 초기화했습니다." << endl;
        }
        else if (op == ADD) {
            string name;
            int id, kor, eng, math;
            while (1) {
                cout << "이름, ID, 국어, 영어, 수학 점수를 공백으로 구분하여 입력하세요: ";
                cin >> name >> id >> kor >> eng >> math;
                // 입력 유효성 검사
                if (cin.fail() || kor < 0 || kor > 100 || eng < 0 || eng > 100 || math < 0 || math > 100) {
                    // 이름, 아이디 또는 점수 중 잘못된 값이 입력되었다면 오류 메시지를 출력하고 다시 입력을 받습니다.
                    cout << "입력이 잘못되었습니다. 다시 입력해주세요." << endl;
                    cin.clear(); // 에러 플래그 초기화
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 입력 버퍼 비우기
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
            cout << "이름으로 검색(1) 또는 ID로 검색(2): ";
            cin >> type;

            if (type == 1) {
                string name;
                cout << "삭제할 학생의 이름을 입력하세요: ";
                cin >> name;
                Student* s = slist.searchByName(name);
                if (s) {
                    s->print();
                    cout << "위 학생을 삭제하시겠습니까? (예: 1, 아니오: 0): ";
                    int yes;
                    cin >> yes;
                    if (yes == 1) {
                        if (slist.removeByID(s->id)) {
                            cout << "학생이 성공적으로 삭제되었습니다." << endl;
                        }
                        else {
                            cout << "삭제 과정에서 문제가 발생했습니다." << endl;
                        }
                    }
                }
                else {
                    cout << "찾는 학생이 없습니다." << endl;
                }
            }
            else if (type == 2)
            {
                int id;
                cout << "삭제할 학생의 ID를 입력하세요: ";
                cin >> id;
                Student* s = slist.searchByID(id);
                if (s) {
                    s->print();
                    cout << "위 학생을 삭제하시겠습니까? (예: 1, 아니오: 0): ";
                    int yes;
                    cin >> yes;
                    if (yes == 1) {
                        if (slist.removeByID(id)) {
                            cout << "학생이 성공적으로 삭제되었습니다." << endl;
                        }
                        else {
                            cout << "삭제 과정에서 문제가 발생했습니다." << endl;
                        }
                    }
                }
                else {
                    cout << "찾는 학생이 없습니다." << endl;
                }
            }
            else {
                cout << "입력이 잘못되었습니다.";
            }
        }
        else if (op == 6) {
            int type;
            cout << "이름으로 검색(1) 또는 ID로 검색(2): ";
            cin >> type;

            if (type == 1) {
                string name;
                cout << "이름을 입력하세요: ";
                cin >> name;
                Student* s = slist.searchByName(name);
                if (s) {
                    s->print();
                }
                else {
                    cout << "찾는 학생이 없습니다." << endl;
                }
            }
            else {
                int id;
                cout << "ID를 입력하세요: ";
                cin >> id;
                Student* s = slist.searchByID(id);
                if (s) {
                    s->print();
                }
                else {
                    cout << "찾는 학생이 없습니다." << endl;
                }
            }
        }
        else if (op == 7) {
            int type;
            cout << "이름 순(1), ID 순(2), 성적 순(3): ";
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
                cout << "잘못된 입력입니다." << endl;
            }
        }
        else if (op == 8) {
            cout << "종료" << endl;
            break;
        }
        else {
            cout << "잘못된 입력입니다." << endl;
        }
    }

    
}