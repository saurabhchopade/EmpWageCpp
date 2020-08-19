#include <iostream>
#include <fstream>
using namespace std;

void saveWage(int day, int wage) {
	fstream fileStream;
   fileStream.open("WageRecords.txt", ios::out | ios::app);
   if(fileStream.is_open()) {
      fileStream << day <<" " << wage << endl;
      fileStream.close();
  	}
}

int main() {
	const int WAGE_PER_HOUR = 20;
	const int IS_FULL_TIME = 1;
	const int IS_PART_TIME = 2;
	const int WORKING_DAYS = 100;
	int hour, status, totalWage = 0,totalWorkHours = 0,dailyWage = 0;
	srand(time(NULL));

	for(int day = 1; day <= WORKING_DAYS; day++) {
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
		dailyWage = hour * WAGE_PER_HOUR;
		totalWage += dailyWage;
		totalWorkHours += hour;
		saveWage(day,dailyWage);

		if(totalWorkHours == 100) {
         cout << "\nWage for month = " << totalWage;
         return 0;
      }
	}
}
