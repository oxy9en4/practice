#include <iostream>
using namespace std;

class Calculator {
public:
	int add(int a, int b) { return a + b; }
	int substract(int a, int b) { return a - b; }
	int multiply(int a, int b) { return a * b; }
	double divide(int a, int b) {
		if (b == 0) {
			cout << "Error: Division by zero!" << endl;
			return 0;
		}
		return (double)a / (double)b;
	}
	
};

int main()
{
	Calculator calc;
	cout << "1 + 2 = " << calc.add(1, 2) << endl;
	cout << "3 - 4 = " << calc.substract(3, 4) << endl;
	cout << "5 * 6 = " << calc.multiply(5, 6) << endl;
	cout << "9 / 0 = " << calc.divide(9, 0) << endl;
}