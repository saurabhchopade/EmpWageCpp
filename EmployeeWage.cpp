#include <iostream>
using namespace std;

int main() {
	const int WAGE_PER_HOUR = 20;
	const int IS_FULL_TIME = 1;
	const int IS_PART_TIME = 2;
	const int DAYS_IN_MONTH = 20;
	int hour, status, totalWage = 0;
	srand(time(NULL));

	for(int day = 1; day <= DAYS_IN_MONTH; day++) {
		status = ((1 + rand() % 3));
		switch(status) {
			case IS_FULL_TIME :
				hour = 8;
				break;
			case IS_PART_TIME :
				hour = 4;
				break;
			default :
				hour = 0;
				break;
		}
		totalWage += hour * WAGE_PER_HOUR;
	}
	cout << "\nWage for month = " << totalWage;
}
