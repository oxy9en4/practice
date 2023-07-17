#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

enum Sex {
	man,
	woman,
	unknown
};

class Person {
public:
	Person(const std::string name, const int id);
	Person(const std::string name, const int id, const bool sex, const int age);
	int Id_get() const { return this->_id; };
	void print() const { std::cout << "name: " << this->_name << " id: " << this->_id << std::endl; };
private:
	std::string _name;
	int _id;
	int _sex;
	int _age;
};

Person::Person(const std::string name, const int id)
	: _name(name), _id(id)
{
	this->_age = -1;
	this->_sex = unknown;
}
Person::Person(const std::string name, const int id, const bool sex, const int age)
	: _name(name), _id(id), _sex(sex), _age(age) {}

bool operator==(const Person& lhs, const Person& rhs) {
	return lhs.Id_get() == rhs.Id_get();
}

struct  MyHash
{
	std::size_t operator()(Person const& s) const noexcept {
		std::size_t h1 = std::hash<std::int32_t>{}(s.Id_get());
		std::size_t h2 = std::hash<std::int32_t>{}(s.Id_get());
		return h1 ^ (h2 << 1);
	}
};


int main() {

	std::unordered_set<Person, MyHash> PersonHash;

	PersonHash.emplace(Person("檜團輿", 123));
	PersonHash.emplace(Person("彌團衝", 763));
	PersonHash.emplace(Person("譆辦營", 59));

	for (auto it = PersonHash.begin(); it != PersonHash.end(); ++it) {
		(*it).print();
	}



	/*std::unordered_set<int> us;
	std::vector<int> nsum = { 1, 2, 3, 4, 1 };

	for (int i = 0; i < nsum.size(); ++i) {
		us.insert(nsum[i]);
	}*/


	return 0;
}