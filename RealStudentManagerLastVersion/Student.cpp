#include "stdafx.h"
#include "Student.h"


#include <iomanip>

void Student::print() {
    std::cout << std::left << std::setw(7) << "�л�: " << std::setw(7) << name
        << std::setw(5) << "ID: " << std::setw(5) << id
        << std::setw(5) << "����: " << std::setw(5) << kor
        << std::setw(5) << "����: " << std::setw(5) << eng
        << std::setw(5) << "����: " << std::setw(5) << math
        << std::setw(5) << "����: " << std::setw(5) << total
        << std::setw(5) << "���: " << std::setw(5) << std::fixed << std::setprecision(1) << average
        << std::endl;
}


Student::Student(string name, int id, int kor, int eng, int math)
	: name(name), id(id), kor(kor), eng(eng), math(math) {
	total = kor + eng + math;
	average = float(total) / 3;
}