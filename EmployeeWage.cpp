#include <iostream>
using namespace std;

int main() {
	const int WAGE_PER_HOUR = 20;
	int hour, status,empWage;
	srand(time(NULL));
	status = ((1 + rand() % 2));

	if( status == 1 ) {
		cout << "Employee is present";
		hour = 8;
	}
	else {
		cout << "Employee is absent";
		hour = 0;
	}

	empWage = hour * WAGE_PER_HOUR;
	cout << "\nEmployee Wage = " << empWage;
}
