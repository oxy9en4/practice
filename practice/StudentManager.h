#include "FileIO.h"
#include "LinkedList.cpp"
#include "Student.h"

// "\n���(0), ����(1), �ε�(2), �ʱ�ȭ(3), �߰�(4), ����(5), �˻�(6), ����(7), ����(8)"
enum work {Print, Save, Load, Init, Add, Remove, Find, Sort, Exit};

template <typename T>
class StudentManager {
public:
	static int sm_size;
	LinkedList<T> m_LinkedList;

	void AddRandomly();
	void Print();
	void Save();
	void Load();
	Student* NewStudent();

};


