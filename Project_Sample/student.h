// student.h
#pragma once
#include <string>

class Student {
private:
    int id;
    std::string name;
    int koreanScore, englishScore, mathScore;

public:
    Student();
    Student(int id, std::string name, int koreanScore, int englishScore, int mathScore);

    int getId() const;
    std::string getName() const;
    int getKoreanScore() const;
    int getEnglishScore() const;
    int getMathScore() const;

    void setId(int id);
    void setName(std::string name);
    void setKoreanScore(int koreanScore);
    void setEnglishScore(int englishScore);
    void setMathScore(int mathScore);
};
