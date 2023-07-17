#pragma once


class Student
{
public:
	string name;
	int id, kor, eng, math, total;
	float average;
	Student(string name, int id, int kor, int eng, int math);
	void print();
};

