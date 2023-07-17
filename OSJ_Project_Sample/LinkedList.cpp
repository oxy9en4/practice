// LinkedList.cpp
#include "LinkedList.h"
#include <iostream>
#include <algorithm>

Node::Node(const Student& data, Node* next)
    : data(data), next(next) {}

LinkedList::LinkedList() : head(nullptr) {}
LinkedList::~LinkedList() {
    Node* tmp;
    while (head != nullptr) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}

void LinkedList::add(const Student& data) {
    if (head == nullptr) {
        head = new Node(data, nullptr);
    }
    else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new Node(data, nullptr);
    }
}

bool LinkedList::remove(int id) {
    if (head == nullptr) {
        return false;
    }

    if (head->data.getId() == id) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
        return true;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->data.getId() != id) {
        current = current->next;
    }

    if (current->next != nullptr) {
        Node* tmp = current->next;
        current->next = tmp->next;
        delete tmp;
        return true;
    }

    return false;
}

Node* LinkedList::findByScore(int score) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.getKoreanScore() == score ||
            current->data.getEnglishScore() == score ||
            current->data.getMathScore() == score) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

Node* LinkedList::findStudentByName(const std::string& name) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.getName() == name) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

Node* LinkedList::findStudentById(int id) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.getId() == id) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void LinkedList::sortById() {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    Node* current = head;
    Node* nextNode;
    Student temp;

    while (current != nullptr) {
        nextNode = current->next;
        while (nextNode != nullptr) {
            if (current->data.getId() > nextNode->data.getId()) {
                temp = current->data;
                current->data = nextNode->data;
                nextNode->data = temp;
            }
            nextNode = nextNode->next;
        }
        current = current->next;
    }
}

void LinkedList::printList() {
    Node* current = head;
    while (current != nullptr) {
        std::cout << "ID: " << current->data.getId()
            << ", 이름: " << current->data.getName()
            << ", 국어: " << current->data.getKoreanScore()
            << ", 영어: " << current->data.getEnglishScore()
            << ", 수학: " << current->data.getMathScore()
            << "\n";
        current = current->next;
    }
}
