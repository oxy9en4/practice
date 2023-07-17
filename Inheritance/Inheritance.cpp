#include <iostream>
#include <string>

class Employee {
protected:
	std::string name;
	int age;

	std::string position; //��å
	int rank; // ����

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
			<< calculate_pay() << "����" << std::endl;
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
			<< year_of_service << "����) ==> " << calculate_pay() << "����"
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
		std::cout << "�� ��� : " << total_pay << "���� " << std::endl;
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
	emp_list.add_employee(new Employee("��ȫö", 34, "����", 1));
	emp_list.add_employee(new Employee("����", 34, "����", 1));

	emp_list.add_employee(new Manager("���缮", 41, "����", 7, 12));
	emp_list.add_employee(new Manager("������", 43, "����", 4, 15));
	emp_list.add_employee(new Manager("�ڸ��", 43, "����", 5, 13));
	emp_list.add_employee(new Employee("������", 36, "�븮", 2));
	emp_list.add_employee(new Employee("��", 36, "����", -2));
	emp_list.print_employee_info();
	return 0;
}