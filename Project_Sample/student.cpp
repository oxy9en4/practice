// student.cpp
#include "student.h"

Student::Student()
    : id(0), name(""), koreanScore(0), englishScore(0), mathScore(0) {}
Student::Student(int id, std::string name, int koreanScore, int englishScore, int mathScore)
    : id(id), name(name), koreanScore(koreanScore), englishScore(englishScore), mathScore(mathScore) {}

int Student::getId() const { return id; }
std::string Student::getName() const { return name; }
int Student::getKoreanScore() const { return koreanScore; }
int Student::getEnglishScore() const { return englishScore; }
int Student::getMathScore() const { return mathScore; }

void Student::setId(int id) { this->id = id; }
void Student::setName(std::string name) { this->name = name; }
void Student::setKoreanScore(int koreanScore) { this->koreanScore = koreanScore; }
void Student::setEnglishScore(int englishScore) { this->englishScore = englishScore; }
void Student::setMathScore(int mathScore) { this->mathScore = mathScore; }
