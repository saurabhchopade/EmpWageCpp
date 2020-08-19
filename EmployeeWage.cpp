#include <iostream>
#include <bits/stdc++.h> 
#include <fstream>
using namespace std;

struct empInfo{
	string empName;
	string month;
	int monthlyWage;
};

void saveWage(int wage,int month, string name) {
	fstream fileStream;
	fileStream.open("WageRecords.txt", ios::out | ios::app);
   if(fileStream.is_open()) {
      fileStream << wage << " " << month << " " << name << endl;
      fileStream.close();
  	}
}

int  wageCalculator(string name,int month) {
	struct empInfo emp;
	emp.empName = name;
	emp.month = month;
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
		emp.monthlyWage =totalWage;

		if(totalWorkHours == 100) {
         cout << "\nWage for month = " << totalWage;
      	saveWage(totalWage, month, name);
         return 0;
      }
	}
	return 0;
}


int calculateWages(string line , string name, int monthNum) {
	string words[3];
	int counter =0;
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
      	totalWages += calculateWages(line,name,monthNum);
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
 	wageCalculator("ram", 2);
	wageCalculator("ram", 4);

	int option;
	cout << "-------------------OPTION-------------------------";
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
				cout<<"\n Do want to calculate another month press (Y)";
				cin >> check;
			}
			while(check == 'y');
			cout <<"totalWages = " <<totalWages;
			break;
		}
		default :{
			cout << "Enter Valid optiom";
		}
	}
}
