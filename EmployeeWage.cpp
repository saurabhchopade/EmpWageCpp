#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

struct CompanyEmpWage{
	string empName;
	int month;
	string companyName;
	int wage;
	int workDays;
	int monthlyHrs;
};

void saveDailyWage(int wage, int totalWage, int month, string name, string company) {
   fstream fileStream;
   fileStream.open("DailyAndTotal.txt", ios::out | ios::app);

   if(fileStream.is_open()) {
      fileStream << wage << " " << totalWage << " " << month << " " << name << " " << company << endl;
      fileStream.close();
   }
}

void saveWage(int wage, int month, string name, string company) {
	fstream fileStream;
	fileStream.open("WageRecords.txt", ios::out | ios::app);

   if(fileStream.is_open()) {
      fileStream << wage << " " << month << " " << name << " " << company << endl;
      fileStream.close();
  	}
}

int  empWageBuilder(CompanyEmpWage emp) {

	int WAGE_PER_HOUR = emp.wage;
	const int IS_FULL_TIME = 1;
	const int IS_PART_TIME = 2;
	int WORKING_DAYS = emp.workDays;
	int totalMonthHrs = emp.monthlyHrs;
	int hour, status, totalWage = 0, totalWorkHours = 0, dailyWage = 0;
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
		saveDailyWage(dailyWage, totalWage, emp.month, emp.empName, emp.companyName);

		if(totalWorkHours == totalMonthHrs) {
      	saveWage(totalWage, emp.month, emp.empName, emp.companyName);
         return 0;
      }
	}

	return 0;
}

int calculateWages(string line , string name, int monthNum, string companyName) {
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

	if(name == words[2] && monthNum == stoi(words[1]) && companyName == words[3]) {
		return stoi(words[0]);
	}
	return 0;
}

int getDataForSort(string line ,string companyName,  map<string, int> &map1) {
   string words[4];
   int counter = 0;
   string comp = companyName;
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

   if(companyName == words[3]) {
      	map1.insert( { words[2], stoi(words[0]) });
   }
   return 0;
}


bool cmp(pair<string, int>& a,pair<string, int>& b)  {
    return a.second < b.second;
}

void sort(map<string, int>& M)
{
    vector<pair<string, int> > A;

    for (auto& it : M) {
        A.push_back(it);
    }

    sort(A.begin(), A.end(), cmp);

    for (auto& it : A) {

        cout << it.first << ' '
             << it.second << endl;
    }
}

int readLineData(string name, int monthNum, string companyName,int funNo) {
	string line;
   int totalWages = 0;
   map<string, int> map;
   fstream fileStream("WageRecords.txt", ios::in);

   if(fileStream.is_open()) {

    	while ( getline (fileStream, line) ) {
    		if(funNo == 1) {
      		totalWages += calculateWages(line, name, monthNum, companyName);
			}
			else if(funNo == 2) {
				getDataForSort(line, companyName, map);
			}
      }
      fileStream.close();
  	}
  	if(funNo == 2) {
		sort(map);
		return 0;
  	}
	return totalWages;
}


int calcMonthlyWage(string name, int monthNum, string companyName) {
	return readLineData(name, monthNum, companyName,1);
}

void sortByMonthlyWage(string companyName) {
	  readLineData("dummy", 0, companyName,2);
}

int main() {
	remove("DailyAndTotal.txt");
	remove("WageRecords.txt");
	struct CompanyEmpWage emp[4];

	emp[0] = {"bob", 2, "Dmart", 20, 60, 48};
	emp[1] = {"alice", 3, "Dmart", 20, 80, 80};
	emp[2] = {"alia", 4, "Kmart", 20, 65, 64};
	emp[3] = {"shantanu", 4, "Walmart", 20, 65, 64};

	empWageBuilder(emp[0]);
	empWageBuilder(emp[1]);
	empWageBuilder(emp[2]);

	int option;
	cout << "\n-------------------OPTION-------------------------";
	cout << "\n| 1) get wage for selected Month =                 |";
	cout << "\n| 2) get total wage                                |";
	cout << "\n| 3) Sort By monthly Wage                          |";
	cout << "\n| 4) Sort By dailyWage                             |";
   cout << "\n| 5) Find Employees based on Wage                  |";
	cout << "\n--------------------------------------------------";
	cout << "\n\n\n Enter Option = ";
	cin >> option;
	switch(option) {

		case 1:{
			char check;
			string name;
			string companyName;
			cout << "\n Enter Employee Name = ";
         cin >> name;
         cout << "\n Enter CompanyName = ";
			cin >> companyName;
			int totalWages = 0;
			do {
				int monthNum;
				cout << "\n Enter Month Number = ";
				cin >> monthNum;
				totalWages += calcMonthlyWage(name, monthNum,companyName);
				cout << "\n PRESS (Y/N)";
				cin >> check;
			}

			while(check == 'y');
			cout << " \n TOTAL WAGE = " << totalWages << "\n";
			break;
		}

		case 2:{
			string companyName;
			string empName;
			int totalWages = 0;

			cout << "\n Enter companyName = ";
			cin >> companyName;
			cout << "\n Enter Employee Name = ";
			cin >> empName;

			for(int month = 0; month< 12; month++){
				totalWages += calcMonthlyWage(empName, month, companyName);
			}
			cout << "\n EMPLYEE NAME = "<< empName << "\n COMPANY NAME = " << companyName << "\n TotalWage = " << totalWages << "\n";
			break;
		}
		case 3:{
			string companyName;

         cout << "\n Enter companyName = ";
         cin >> companyName;

			sortByMonthlyWage(companyName);
			break;
		}
		default :{
			cout << "Enter Valid option";
		}
	}
}
