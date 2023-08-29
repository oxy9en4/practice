// StudentManager.h
#pragma once
#include "student.h"
#include "LinkedList.h"
#include <functional>

class StudentManager {
private:
    LinkedList studentList;

public:
    StudentManager();

    int getStudentCount() const;

    void addStudent(const Student& student);
    Student* searchStudent(int id);
    bool removeStudent(int id);
    void printStudents();
    const LinkedList& getStudentList() const;
    void setStudentList(const LinkedList& newList);
};
