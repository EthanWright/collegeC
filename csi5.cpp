#include <iostream>
#include <string>
using namespace std;

void advance(int* j) {
     (*j)++;
}

void backtrack(int filler[], int* j) {
     filler[*j]++;
     while (filler[*j]>5) {
        filler[*j]=0;
        (*j)--;
        filler[*j]++;
     }
}

int test(int j, int filler[], string words[]) {
    for (int count=0; count<j; count++) {
        if (filler[count]==filler[j]) return 0;
        }
    if (j<3) return 1;
    if(words[filler[0]].at(j-3)==words[filler[j]].at(0) && 
    words[filler[1]].at(j-3)==words[filler[j]].at(1) && 
    words[filler[2]].at(j-3)==words[filler[j]].at(2)) return 1;
    return 0;
}

int main() {
    string words[6]={"tou","hmo","you","why","emo","wet"};
    int filler[6]={0,0,0,0,0,0}; // says which word it has
    int j=0; //the column/row
    
    do {
        if (test(j, filler, words)==1)
         advance(&j);
        else 
         backtrack(filler, &j);
    } while(j<6 && j>0);
    
    for (int count=0; count<3; count++)
    cout << words[filler[count]] << endl;
    
    system("PAUSE");
    return 0;
    
}
