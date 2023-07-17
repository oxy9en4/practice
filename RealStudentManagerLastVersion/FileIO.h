#pragma once

template <class T>
class FileIO
{
public:
	static void save(const LinkedList<T>& slist) {
		ofstream outfile("students.txt");
		for (Node<T>* curr = slist.pHead; curr; curr = curr->pNext) {
			T* s = curr->pData;
			outfile << s->name << ' ' << s->id << ' ' << s->kor << ' ' << s->eng << ' ' << s->math << '\n';
		}
		outfile.close();
		cout << "저장했습니다." << endl;
	}
	static void load(LinkedList<T>& slist) {
		ifstream infile("students.txt");
		slist.clear();
		string  name;
		int id, kor, eng, math;
		while (infile >> name >> id >> kor >> eng >> math) {
			T* s = new T(name, id, kor, eng, math);
			slist.Push_Back(s);
		}
		infile.close();
		cout << "파일을 불러왔습니다." << endl;
		
	}
	
};

