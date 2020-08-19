#include <iostream>
#include <bits/stdc++.h> 
#include <fstream>
using namespace std;

struct empInfo{
	string empName;
	string month;
	string companyName;
	int monthlyWage;
};

void saveWage(int wage,int month, string name, string company) {
	fstream fileStream;
	fileStream.open("WageRecords.txt", ios::out | ios::app);

   if(fileStream.is_open()) {
      fileStream << wage << " " << month << " " << name << " " << company << endl;
      fileStream.close();
  	}
}

int  wageCalculator(string name, int month, string companyName, int wage, int workDays, int monthlyHrs) {
	struct empInfo emp;

	emp.empName = name;
	emp.month = month;
	emp.companyName = companyName;

	int WAGE_PER_HOUR = wage;
	const int IS_FULL_TIME = 1;
	const int IS_PART_TIME = 2;
	int WORKING_DAYS = workDays;
	int totalMonthHrs = monthlyHrs;
	int hour, status, totalWage = 0,totalWorkHours = 0,dailyWage = 0;
	srand(time(NULL));

	for(int day = 1; day <= WORKING_DAYS; day++) {
		status = ((1 + rand() % 3));
		switch(status) {
			case IS_FULL_TIME :
				hour = 8;
				break;
			case IS_PART_TIME :
				hour = 8;
				break;
			default :
				hour = 0;
				break;
		}

		dailyWage = hour * WAGE_PER_HOUR;
		totalWage += dailyWage;
		totalWorkHours += hour;
		emp.monthlyWage = totalWage;

		if(totalWorkHours == totalMonthHrs) {
      	saveWage(totalWage, month, name, companyName);
         return 0;
      }
	}

	return 0;
}


int calculateWages(string line , string name, int monthNum) {
	string words[4];
	int counter = 0;
	string word = "";

   for (auto x : line)
   {
       if (x == ' ')
       {
         words[counter] = word;
         counter++;
           word = "";
       }
       else
       {
           word = word + x;
       }
   }

   words[counter] = word;

	if(name == words[2] && monthNum == stoi(words[1])) {
		return stoi(words[0]);
	}
	return 0;
}


int readLineData(string name, int monthNum) {
	string line;
   int totalWages = 0;
   fstream fileStream("WageRecords.txt", ios::in);

   if(fileStream.is_open()) {
   	cout << "File is opened for reading" << endl;

    	while ( getline (fileStream, line) ) {
      	totalWages += calculateWages(line, name, monthNum);
      }
      fileStream.close();
  	}

  	return totalWages;
}


int calcMonthlyWage(string name, int monthNum) {
	return readLineData(name, monthNum);
}


int main() {
	remove("WageRecords.txt");
 	wageCalculator("ram", 2, "Dmart", 20, 60, 48);
	wageCalculator("rahul", 4,"Kmart", 20, 65, 64);
	wageCalculator("rahul", 4,"kl", 20, 65, 64);

	int option;
	cout << "\n-------------------OPTION-------------------------";
	cout << "\n 1) Calculate wage for m = ";
	cout << "\n Enter Option = ";
	cin >> option;

	switch(option) {
		case 1:{
			char check;
			int totalWages = 0;
			do {
				int monthNum;
				string name;
				cout << "\n Enter empName = ";
         	cin >> name;
				cout << "\n Enter Month Number = ";
				cin >> monthNum;
				totalWages += calcMonthlyWage(name, monthNum);
				cout << "\n Do want to calculate another month press (Y)";
				cin >> check;
			}

			while(check == 'y');
			cout << " \n totalWages = " << totalWages;
			break;
		}
		default :{
			cout << "Enter Valid optiom";
		}
	}
}
