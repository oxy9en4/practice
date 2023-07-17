#include <iostream>
#include <string>

class Employee {
protected:
	std::string name;
	int age;

	std::string position; //직책
	int rank; // 순위

public:
	Employee(std::string _name, int _age, std::string _position, int _rank)
		: name(_name), age(_age), position(_position), rank(_rank) {}
	Employee(const Employee& emp) {
		name = emp.name;
		age = emp.age;
		position = emp.position;
		rank = emp.rank;
	}
	Employee() = default;

	virtual void print_info() {
		std::cout << name << " (" << position << " , " << age << ") ==> "
			<< calculate_pay() << "만원" << std::endl;
	}

	virtual int calculate_pay() { return 200 + rank * 50; }
};

class Manager : public Employee {
	int year_of_service;

public:
	Manager(std::string name, int age, std::string position, int rank,
		int year_of_service)
		: year_of_service(year_of_service), Employee(name, age, position, rank) {}

	int calculate_pay() override { return 200 + rank * 50 + 5 * year_of_service; }
	void print_info() override {
		std::cout << name << " (" << position << " , " << age << ", "
			<< year_of_service << "년차) ==> " << calculate_pay() << "만원"
			<< std::endl;
	}
};

class EmployeeList {
	int alloc_memory;
	int current_employee;
	Employee** employeelist;

public:
	EmployeeList(int alloc_memory): alloc_memory(alloc_memory) {
		employeelist = new Employee * [alloc_memory];
		current_employee = 0;
	}
	void add_employee(Employee* emp) {
		employeelist[current_employee] = emp;
		++current_employee;
	}
	int current_employee_num() { return current_employee; }

	void print_employee_info() {
		int total_pay = 0;
		for (int i = 0; i < current_employee; ++i) {
			employeelist[i]->print_info();
			total_pay += employeelist[i]->calculate_pay();
		}
		std::cout << "총 비용 : " << total_pay << "만원 " << std::endl;
	}
	~EmployeeList() {
		for (int i = 0; i < current_employee; ++i) {
			delete employeelist[i];
		}
		delete[] employeelist;
	}

};

int main() {
	EmployeeList emp_list(10);
	emp_list.add_employee(new Employee("노홍철", 34, "평사원", 1));
	emp_list.add_employee(new Employee("하하", 34, "평사원", 1));

	emp_list.add_employee(new Manager("유재석", 41, "부장", 7, 12));
	emp_list.add_employee(new Manager("정준하", 43, "과장", 4, 15));
	emp_list.add_employee(new Manager("박명수", 43, "차장", 5, 13));
	emp_list.add_employee(new Employee("정형돈", 36, "대리", 2));
	emp_list.add_employee(new Employee("길", 36, "인턴", -2));
	emp_list.print_employee_info();
	return 0;
}