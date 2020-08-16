#include <iostream>
using namespace std;

int main() {
	const int WAGE_PER_HOUR = 20;
	const int IS_FULL_TIME = 1;
	const int IS_PART_TIME = 2;
	int hour, status,empWage;
	srand(time(NULL));
	status = ((1 + rand() % 3));

	if(status == IS_FULL_TIME) {
		hour = 8;
	}
	else if(status == IS_PART_TIME) {
		hour = 4;
	}
	else {
		hour = 0;
	}

	empWage = hour * WAGE_PER_HOUR;
	cout << "\nEmployee Wage = " << empWage;
}
