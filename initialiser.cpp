namespace init{
	void file1() {
   	std :: fstream f;
   	f.open("DailyAndTotal.csv", std::ios::out | std::ios::app);

   	if(f.is_open()) {
      	f << "WAGE" << "," << "TOTALWAGE" << "," << "MONTH" << "," << "EMPNAME" << "," << "COMPANY" << std::endl;
      	f.close();
   	}
	}

	void file2() {
   	std :: fstream f;
   	f.open("WageRecords.csv", std::ios::out | std::ios::app);

   	if(f.is_open()) {
      	f << "WAGE" << "," << "MONTH" << "," << "EMPNAME" << "," << "COMPANY" << "," << "DAILYWAGE" << ","<< "WAGERATE" << std :: endl;
      	f.close();
   	}
	}
}
