// FileIO.cpp
#include "FileIO.h"
#include "LinkedList.h"
#include <fstream>
#include <sstream>
#include <string>

bool FileIO::save(const std::string& filename, LinkedList& list) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    Node* current = list.getHead();
    while (current != nullptr) {
        const Student& student = current->data;
        file << student.getId() << ","
            << student.getName() << ","
            << student.getKoreanScore() << ","
            << student.getEnglishScore() << ","
            << student.getMathScore() << "\n";
        current = current->next;
    }

    file.close();
    return true;
}

bool FileIO::load(const std::string& filename, LinkedList& list) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);

        int id, koreanScore, englishScore, mathScore;
        char delimiter;
        std::string name;

        if (!(iss >> id >> delimiter
            && std::getline(iss, name, ',')
            && iss >> koreanScore >> delimiter
            >> englishScore >> delimiter
            >> mathScore)) {
            break;
        }

        Student student(id, name, koreanScore, englishScore, mathScore);
        list.add(student);
    }

    file.close();
    return true;
}
