#include <iostream>
using namespace std;

int main() {
	srand(time(NULL));
	int status = ((1 + rand() % 2));

	(status == 1) ? cout << "Employee is Present": cout << "Employee is absent";
}
