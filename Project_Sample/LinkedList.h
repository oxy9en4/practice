// LinkedList.h
#pragma once
#include "student.h"

class Node {
public:
    Student data;
    Node* next;

    Node(const Student& data, Node* next);
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList();
    ~LinkedList();

    void add(const Student& data);
    bool remove(int id);

    Node* findByScore(int score);
    Node* findStudentByName(const std::string& name);
    Node* findStudentById(int id);
    Node* getHead() { return head; }

    void sortById();
    void printList();
};
