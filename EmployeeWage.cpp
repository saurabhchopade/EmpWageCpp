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
   fileStream.open("DailyAndTotal.csv", ios::out | ios::app);

   if(fileStream.is_open()) {
      fileStream << wage << "," << totalWage << "," << month << "," << name << "," << company << endl;
      fileStream.close();
   }
}

void saveWage(int wage, int month, string name, string company,int dailyWage,int wageRate) {
	fstream fileStream;
	fileStream.open("WageRecords.csv", ios::out | ios::app);

   if(fileStream.is_open()) {
      fileStream << wage << "," << month << "," << name << "," << company << "," << dailyWage << ","<< wageRate << endl;
		cout <<" \n \n " << " WAGE = " <<wage << " MONTH = " << month << " NAME = " << name << " Company = "<< company << " DailyWage = "
		 << dailyWage << " WageRate = " << wageRate;
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
      	saveWage(totalWage, emp.month, emp.empName, emp.companyName, dailyWage, emp.wage);
         return 0;
      }
	}

	return 0;
}

int calculateWages(string line , string name, int monthNum, string companyName) {
	string words[6];
	int counter = 0;
	string word = "";

   for (auto x : line)
   {
       if (x == ',')
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
	else if(companyName == words[3] && monthNum == 0){
		return stoi(words[0]);
	}
	return 0;
}

int getDataForSort(string line ,map<string, int> &map1) {
   string words[6];
   int counter = 0;
   string word = "";

   for (auto x : line)
   {
       if (x == ',')
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
   map1.insert( { words[2], stoi(words[0]) });
   return 0;
}

int getDataForDailyWageSort(string line ,int month,map<string, int> &map1) {
   string words[6];
   int counter = 0;
   string word = "";

   for (auto x : line)
   {
       if (x == ',')
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
	string str = to_string(month);
   if(str == words[1]) {
         map1.insert( { words[2], stoi(words[4]) });
   }
   return 0;
}

int getDataOnWageRateSort(string line , int wageRate, map<string, int> &map1) {
   string words[6];
   int counter = 0;
   string word = "";

   for (auto x : line)
   {
       if (x == ',')
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

   string str = to_string(wageRate);
   if(str == words[5]) {
         map1.insert( { words[2], stoi(words[4]) });
   }
   return 0;
}

bool cmp(pair<string, int>& a,pair<string, int>& b)  {
    return a.second < b.second;
}

int sort(map<string, int>& M)
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
	return 0;
}

int readLineData(string name, int monthNum, string companyName, int funNo, int wageRate) {
	string line;
   int totalWages = 0;
   map<string, int> map;
   fstream fileStream("WageRecords.csv", ios::in);

   if(fileStream.is_open()) {

    	while ( getline (fileStream, line) ) {

		switch(funNo){
			case 1:
				totalWages += calculateWages(line, name, monthNum, companyName);
				break;
			case 2:
				getDataForSort(line, map);
				break;
			case 3:
				getDataForDailyWageSort(line, monthNum, map);
				break;
			case 4:
				getDataOnWageRateSort(line, wageRate, map);
				break;
		}

      }
      fileStream.close();
   }

  	if(funNo == 2|| funNo == 3 || funNo == 4) {
		sort(map);
		return 0;
  	}
	return totalWages;
}

int calcMonthlyWage(string name, int monthNum, string companyName) {
	return readLineData(name, monthNum, companyName,1,0);
}

void sortByMonthlyWage() {
	  readLineData("0", 0, "0",2, 0);
}

void sortByDailyWage(int month){
		readLineData("0", month, "0", 3, 0);
}

void  getEmpByWageRate(int wageRate) {
		readLineData("0", 0, "0", 4, wageRate);
}

int main() {
	remove("DailyAndTotal.csv");
	remove("WageRecords.csv");

	struct CompanyEmpWage emp[5];
	//EmployeeName--month--company--Wage--WorkingDays--MonthlyHours
	emp[0] = {"alice", 2, "Dmart", 20, 60, 48};
	emp[1] = {"alice", 3, "Dmart", 30, 80, 80};
	emp[2] = {"alia", 4, "Kmart", 20, 65, 64};
	emp[3] = {"akash", 4, "Walmart", 15, 65, 64};
	emp[4] = {"robin", 4, "Walmart", 10, 65, 32};

	empWageBuilder(emp[0]);
	empWageBuilder(emp[1]);
	empWageBuilder(emp[2]);
	empWageBuilder(emp[3]);
   empWageBuilder(emp[4]);


	int option;
	cout<< "\n\n\n";
	cout << "\n-------------------OPTION-------------------------";
	cout << "\n| 1) get wage for selected Month =                 |";
	cout << "\n| 2) get total wage                                |";
	cout << "\n| 3) Sort By monthly Wage                          |";
	cout << "\n| 4) Sort By dailyWage                             |";
   cout << "\n| 5) Find Employees based on Wage rate             |";
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
			int month1 = 0;
			string empName;
			int totalWages = 0;

			cout << "\n Enter companyName = ";
			cin >> companyName;
			totalWages += calcMonthlyWage(empName, month1,companyName);
			cout << "\n COMPANY NAME = " << companyName << "\n TotalWage = " << totalWages << "\n";
			break;
		}
		case 3:{
			sortByMonthlyWage();
			break;
		}
		case 4:{
			int month;

			cout<<"\n Enter Month Number = ";
			cin >> month;

			sortByDailyWage(month);
			break;
		}
		case 5 :{
			int wageRate;

			cout << "Enter Wage Rate = ";
			cin >> wageRate;

			 getEmpByWageRate(wageRate);
			 break;
		}
		default :{
			cout << "Enter Valid option";
			break;
		}
	}
}
