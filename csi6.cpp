#include <iostream>
#include <string>
using namespace std;

void advance(int* j) {
     (*j)++;
}

void backtrack(int queens[], int* j) {
     queens[*j]++;
      while (queens[*j]>7) {
        queens[*j]=0;
        (*j)--;
        queens[*j]++;
     }
     
}

int test(int* j, int queens[]) {
    for (int count=((*j)-1); count>=0; count--) {
        if (queens[count]==queens[*j]) return 0; //horizontal
        if ((queens[count]+((*j)-count))==queens[*j]) return 0; // diag
        if ((queens[count]-((*j)-count))==queens[*j]) return 0; //diag
    }
    return 1;
}

int main() {
    int queens[8]={0,0,0,0,0,0,0,0};
    int j=0;

    do {
        if (test(&j, queens)==1)
         advance(&j);
        else 
         backtrack(queens, &j);
    } while(j<=8);
    
    //print
    for (int count=0; count<8; count++)
        cout << queens[count] << " ";
    cout << endl;   
    cout << "_ _ _ _ _ _ _ _" << endl;
    for (int go=7; go>=0; go--) {
        for (int test=0; test<8; test++) {
            if (queens[test]==go) {
               for (int spaces=0; spaces<test; spaces++) cout << "_|";
               cout << "q|";
               for (int spaces2=test; spaces2<7; spaces2++) cout << "_|";
               cout << endl;
            }
        }
    }
  
    system("PAUSE");
    return 0;    
}
