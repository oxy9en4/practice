#pragma once

#include "Student.h"
#include "LinkedList.cpp"

class StudentManager {
public:
	static LinkedList<Student> slist;
	

	static void gen_students();
	static void Run();
};