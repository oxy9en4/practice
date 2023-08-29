// student_manager.cpp
#include "student_manager.h"
#include <iostream>

StudentManager::StudentManager()
    : students(new Student[10]), studentCount(3), maxStudentCount(10) {
    students[0] = Student(1, "학생 A", 92, 78, 85);
    students[1] = Student(2, "학생 B", 88, 90, 70);
    students[2] = Student(3, "학생 C", 82, 84, 92);
}

int StudentManager::getStudentCount() const { return studentCount; }
const Student& StudentManager::getStudent(int index) const { return students[index]; }

void StudentManager::addStudent(const Student& participant) {
    if (studentCount < maxStudentCount) {
        students[studentCount] = participant;
        studentCount++;
    }
}

int StudentManager::findStudentByName(const std::string& name) {
    for (int i = 0; i < studentCount; ++i) {
        if (students[i].getName() == name) {
            return i;
        }
    }
    return -1;
}

int StudentManager::findStudentById(int id) {
    for (int i = 0; i < studentCount; ++i) {
        if (students[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

void StudentManager::findByScore(int score) {
    bool found = false;
    for (int i = 0; i < studentCount; i) {
        if (students[i].getKoreanScore() == score || students[i].getEnglishScore() == score || students[i].getMathScore() == score) {
            std::cout << "ID: " << students[i].getId() << ", 이름: " << students[i].getName() << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "성적이 " << score << "인 학생은 없습니다." << std::endl;
    }
}
