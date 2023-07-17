#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


const int NUM_SUBJECTS = 3;
const std::string FILENAME = "students.txt";

struct Node;

struct Student {
    std::string name;
    int school_number;
    int grades[NUM_SUBJECTS];  // 국어, 영어, 수학
};

struct Node {
    Student data;
    Node* prev;
    Node* next;
};

class StudentList {
public:
    StudentList() : head(nullptr), tail(nullptr) {}
    ~StudentList();
    void add_student(const std::string& name, int school_number, int grade_korean, int grade_english, int grade_math);
    void remove_student(int school_number);
    void display_list();
    Node* find_student_by_name(const std::string& name);
    Node* find_student_by_school_number(int school_number);
    void sort_by_name();
    void sort_by_grade();
    void sort_by_school_number();
    bool save_to_file();
    bool load_from_file();

private:
    Node* head;
    Node* tail;

    // Helper functions
    void insert_sorted(Node* newNode, bool byName, bool byGrade);
    static bool compare_nodes_name(Node* a, Node* b);
    static bool compare_nodes_grade(Node* a, Node* b);
    static bool compare_nodes_school_number(Node* a, Node* b);
};

// 소멸자 구현
StudentList::~StudentList() {
    Node* current = head;
    while (current) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

// 학생 추가 함수 구현
void StudentList::add_student(const std::string& name, int school_number, int grade_korean, int grade_english, int grade_math) {
    Student new_student{ name, school_number, {grade_korean, grade_english, grade_math} };
    Node* newNode = new Node{ new_student, nullptr, nullptr };

    if (!head) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void StudentList::remove_student(int school_number) {
    Node* current = head;
    while (current) {
        if (current->data.school_number == school_number) {
            if (current->prev) current->prev->next = current->next;
            if (current->next) current->next->prev = current->prev;
            if (current == head) head = current->next;
            if (current == tail) tail = current->prev;
            delete current;
            return;
        }
        current = current->next;
    }
}

void StudentList::display_list() {
    Node* current = head;
    while (current) {
        std::cout << "이름: " << current->data.name
            << ", 학번: " << current->data.school_number
            << ", 성적: 국어(" << current->data.grades[0]
            << "), 영어(" << current->data.grades[1]
            << "), 수학(" << current->data.grades[2] << ")\n";
        current = current->next;
    }
}

Node* StudentList::find_student_by_name(const std::string& name) {
    Node* current = head;
    while (current) {
        if (current->data.name == name) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

Node* StudentList::find_student_by_school_number(int school_number) {
    Node* current = head;
    while (current) {
        if (current->data.school_number == school_number) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void StudentList::sort_by_name() {
    Node* newHead = nullptr;
    Node* current = head;
    while (current) {
        Node* next_node = current->next;
        current->prev = current->next = nullptr;
        insert_sorted(current, true, false);
        current = next_node;
    }
    head = newHead;
}

void StudentList::sort_by_grade() {
    Node* newHead = nullptr;
    Node* current = head;
    while (current) {
        Node* next_node = current->next;
        current->prev = current->next = nullptr;
        insert_sorted(current, false, true);
        current = next_node;
    }
    head = newHead;
}

void StudentList::sort_by_school_number() {
    Node* newHead = nullptr;
    Node* current = head;
    while (current) {
        Node* next_node = current->next;
        current->prev = current->next = nullptr;
        insert_sorted(current, false, false);
        current = next_node;
    }
    head = newHead;
}

bool StudentList::save_to_file() {
    std::ofstream file(FILENAME);
    if (!file.is_open()) {
        return false;
    }
    Node* current = head;
    while (current) {
        file << current->data.name << ","
            << current->data.school_number << ","
            << current->data.grades[0] << ","
            << current->data.grades[1] << ","
            << current->data.grades[2] << std::endl;
        current = current->next;
    }
    file.close();
    return true;
}

bool StudentList::load_from_file() {
    std::ifstream file(FILENAME);
    if (!file.is_open()) {
        return false;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string name, str_school_number, str_grade_korean, str_grade_english, str_grade_math;
        std::getline(ss, name, ',');
        std::getline(ss, str_school_number, ',');
        std::getline(ss, str_grade_korean, ',');
        std::getline(ss, str_grade_english, ',');
        std::getline(ss, str_grade_math);
        add_student(name, std::stoi(str_school_number), std::stoi(str_grade_korean), std::stoi(str_grade_english), std::stoi(str_grade_math));
    }
    file.close();
    return true;
}

void StudentList::insert_sorted(Node* newNode, bool byName, bool byGrade) {
    if (!head) {
        head = tail = newNode;
        return;
    }
    Node* curr = head;
    while (curr) {
        bool shouldInsert = byName ? compare_nodes_name(newNode, curr) : (byGrade ? compare_nodes_grade(newNode, curr) : compare_nodes_school_number(newNode, curr));
        if (shouldInsert) {
            newNode->prev = curr->prev;
            newNode->next = curr;
            if (curr->prev) {
                curr->prev->next = newNode;
            }
            else {
                head = newNode;
            }
            curr->prev = newNode;
            return;
        }
        if (!curr->next) {
            curr->next = newNode;
            newNode->prev = curr;
            tail = newNode;
            return;
        }
        curr = curr->next;
    }
}

bool StudentList::compare_nodes_name(Node* a, Node* b) {
    return a->data.name < b->data.name;
}

bool StudentList::compare_nodes_grade(Node* a, Node* b) {
    int a_total = a->data.grades[0] + a->data.grades[1] + a->data.grades[2];
    int b_total = b->data.grades[0] + b->data.grades[1] + b->data.grades[2];
    return a_total > b_total;
}

bool StudentList::compare_nodes_school_number(Node* a, Node* b) {
    return a->data.school_number < b->data.school_number;
}

int main() {
    StudentList student_list;
    bool is_running = true;

    student_list.add_student("홍길동", 20230001, 90, 80, 95);
    student_list.add_student("김철수", 20230002, 60, 90, 90);
    student_list.add_student("장보고", 20230003, 87, 65, 95);

    while (is_running) {
        std::cout << "\n1. 학생 추가\n2. 학생 삭제\n3. 검색\n4. 정렬\n5. 전체 목록 출력\n6. 파일 저장\n7. 파일 로드\n8. 종료\n선택하세요: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: {
            std::cout << "이름 입력: ";
            std::string name;
            std::getline(std::cin, name);

            std::cout << "학번 입력: ";
            int school_number;
            std::cin >> school_number;

            int grades[NUM_SUBJECTS];
            std::cout << "국어 성적 입력: ";
            std::cin >> grades[0];
            std::cout << "영어 성적 입력: ";
            std::cin >> grades[1];
            std::cout << "수학 성적 입력: ";
            std::cin >> grades[2];
            std::cin.ignore();

            student_list.add_student(name, school_number, grades[0], grades[1], grades[2]);
            break;
        }
        case 2: {
            std::cout << "삭제할 학생의 학번 입력: ";
            int school_number;
            std::cin >> school_number;
            std::cin.ignore();
            student_list.remove_student(school_number);
            break;
        }
        case 3: {
            std::cout << "1. 이름으로 검색\n2. 학번으로 검색\n선택하세요: ";
            int search_choice;
            std::cin >> search_choice;
            std::cin.ignore();
            if (search_choice == 1) {
                std::cout << "이름 입력: ";
                std::string name;
                std::getline(std::cin, name);
                Node* result = student_list.find_student_by_name(name);
                if (result) {
                    std::cout << "학생 정보:\n이름: " << result->data.name << ", 학번: " << result->data.school_number << ", 성적: 국어(" << result->data.grades[0] << "), 영어(" << result->data.grades[1] << "), 수학(" << result->data.grades[2] << ")\n";
                }
                else {
                    std::cout << "찾는 학생이 없습니다.\n";
                }
            }
            else {
                std::cout << "학번 입력: ";
                int school_number;
                std::cin >> school_number;
                std::cin.ignore();
                Node* result = student_list.find_student_by_school_number(school_number);
                if (result) {
                    std::cout << "학생 정보:\n이름: " << result->data.name << ", 학번: " << result->data.school_number << ", 성적: 국어(" << result->data.grades[0] << "), 영어(" << result->data.grades[1] << "), 수학(" << result->data.grades[2] << ")\n";
                }
                else {
                    std::cout << "찾는 학생이 없습니다.\n";
                }
            }
            break;
        }
        case 4: {
            std::cout << "1. 이름 순 정렬\n2. 성적 순 정렬\n3. 학번 순 정렬\n선택하세요: ";
            int sort_choice;
            std::cin >> sort_choice;
            std::cin.ignore();
            if (sort_choice == 1) {
                student_list.sort_by_name();
            }
            else if (sort_choice == 2) {
                student_list.sort_by_grade();
            }
            else {
                student_list.sort_by_school_number();
            }
            break;
        }
        case 5: {
            student_list.display_list();
            break;
        }
        case 6: {
            if (student_list.save_to_file()) {
                std::cout << "파일 저장 성공\n";
            }
            else {
                std::cout << "파일 저장 실패\n";
            }
            break;
        }
        case 7: {
            if (student_list.load_from_file()) {
                std::cout << "파일 로드 성공\n";
            }
            else {
                std::cout << "파일 로드 실패\n";
            }
            break;
        }
        case 8: {
            is_running = false;
            break;
        }
        default: {
            std::cout << "잘못된 입력입니다.\n";
            break;
        }
        }
    }

    return 0;
}
