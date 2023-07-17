#include "FileIO.h"
#include "LinkedList.cpp"
#include "Student.h"

// "\n출력(0), 저장(1), 로드(2), 초기화(3), 추가(4), 삭제(5), 검색(6), 정렬(7), 종료(8)"
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


