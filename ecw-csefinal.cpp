//ethan wright final c++ project
/*
start a loop where a mnu screen is printed.
have them input a letter, then choose the correct response.
Bubblesortis used to order the employees either by id or salary
if a q is entered, the loop terminates.
p will print the current sorting of the array.
*/

#include <iostream>
#include <fstream>
const int NUM=10;
using namespace std;
struct employee {
       int number;
       int id;
       float hourlyWage;
};
void bubblesortWage(employee arr[], int n);
void bubblesortID(employee arr[], int n);

int main() {
    char input;
    float sum=0.0;
    int die=0;
    int max=0, id;
    employee empArray [NUM];
    ifstream myInputFile("test.txt"); 
    for (int count=0;count<NUM;count++) {
        myInputFile >> empArray[count].id >> empArray[count].hourlyWage;
        empArray[count].number=count;
    }
    myInputFile.close();
    while (1) {
    cout << "Enter one of the following commands: "<<endl
    << "(s) Sort from lowest to highest id" <<endl
    << "(t) Sort from lowest to highest salary" <<endl
    << "(p) Print file to screen" <<endl
    << "(f) Enter an id to see their hourly salary" <<endl
    << "(h) See id and salary of employee with the highest salary" <<endl
    << "(a) Prints average salary of all employees" <<endl
    << "(q) Quit" <<endl;

    cin >> input;
    switch (input) {
       case 's':
            bubblesortID(empArray,NUM);     
            break;  
       case 't':
            bubblesortWage(empArray,NUM);     
            break; 
       case 'p':{
            for (int count=0;count<NUM;count++) {
                cout << empArray[count].id << " " << empArray[count].hourlyWage << endl;
            }
            ofstream myOutFile("myOut.txt");
            for (int count=0;count<NUM;count++) {
                myOutFile << empArray[count].id << " " << empArray[count].hourlyWage << endl;
            }
            myOutFile.close();
            break;
       }
       case 'f': {
            cout << "Enter an id to see their salary"<<endl;
            cin >> id;
            for(int count=0;count<NUM;count++) {
                    cout << empArray[count].id << endl;
                 if (empArray[count].id==id)
                    cout << "The person with id " << id << " has hourly salary " 
                         << empArray[count].hourlyWage<<endl;
                 else {
                      cout << "There is no person with id " << id << endl;
                      break;
                 }
            }
            break;
       }
       case 'h': {
            for(int count=0;count<NUM;count++)
                 if (empArray[count].hourlyWage>empArray[max].hourlyWage)
                     max=count;
            cout << "The person with the highest salary has id " << empArray[max].id << 
                     " and has a salary of " << empArray[max].hourlyWage << endl;
                     max=0;
            break;
       }
       case 'a': {          
            for(int count=0;count<NUM;count++) {
                 sum+=empArray[count].hourlyWage;
            }
            cout << "The average salary is " << sum/NUM << endl;
            sum=0;
            break;
       }
       case 'q': {
            die=1;
            break;
        }
    }
    if (die==1) {
       die=0;
       break;
    }  
    }
system("PAUSE"); 
}
void bubblesortID(employee arr[], int n) {
	int numComps = n-1, sorted;
	do 
	{
		sorted = 1;
		for (int i = 0; i < numComps; i++)
			if (arr[i].id > arr[i + 1].id)
			{
				employee temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				sorted = 0;
			}
		numComps--;
	}
	while (sorted == 0);
}

void bubblesortWage(employee arr[], int n) {
	int numComps = n-1, sorted;
	do 
	{
		sorted = 1;
		for (int i = 0; i < numComps; i++)
			if (arr[i].hourlyWage > arr[i + 1].hourlyWage)
			{
				employee temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				sorted = 0;
			}
			else if (arr[i].hourlyWage == arr[i + 1].hourlyWage && arr[i].id > arr[i + 1].id) {
                employee temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				sorted = 0;     
            }       
		numComps--;
	}
	while (sorted == 0);
}
