#include <iostream>
#include <string>

using namespace std;

bool isCenterOpen(int &Z, int &Y, int &X)
{
    if (board[2][2][2] == ' ') 
    {
        X=Y=Z=2;               
    }
}

bool isCornerOpen() {
     if (board[0][0][0] == ' ') {
        return true;
        X=Y=Z=0;
     }
     if (board[0][0][4] == ' ') {
        return true;
        X=Y=0;
        Z=4;
     }
     if (board[0][4][0] == ' ') {
        return true;
        X=Z=0;
        Y=4;
     }
     if (board[0][4][4] == ' ') {
        return true;
        Z=Y=4;
        X=0;
     }
     if (board[4][0][0] == ' ') {
        return true;
        Z=Y=0;
        X=4;
     }
     if (board[4][0][4] == ' ') {
        return true;
        X=Z=4;
        Y=0;
     }
     if (board[4][4][0] == ' ') {
        return true;
        X=Y=4;
        Z=0;
     }
     if (board[4][4][4] == ' ') {
        return true;
        X=Y=Z=4;
     }
}

bool isFourInARow(char player, int &Z, int &Y, int &X)
{
    int totalX;
    int totalY;
    int totalZ;
    int totalX1;
    int totalY1;
    int totalZ1;
    int totalX2;
    int totalY2;
    int totalZ2;
    int diag1=0;
    int diag2=0;
    int diag3=0;
    int diag4=0;
    
    //lines first, 75 of em
    for (int a=0;a < 5;a++) {
        for (int b=0;b < 5;b++) {
            totalX=0;
            totalY=0;
            totalZ=0;
            for (int c=0;c<5;c++) {
                if (board[a][b][c] == player) totalX++;
                if (board[a][c][b] == player) totalY++;
                if (board[c][b][a] == player) totalZ++;    
            }
    
            if (totalX==4) {
               for (int i=0;i<5;i++) {
                   if (board[a][b][i]== ' ') cout << a << " " << b <<" "<< i <<endl;
               }
            }
            if (totalY==4) {
               for (int i=0;i<5;i++) {
                   if (board[a][i][b]== ' ') cout << a << " " << i <<" "<< b <<endl;
               }
            }
            if (totalZ==4) {
               for (int i=0;i<5;i++) {
                   if (board[i][b][a]== ' ') cout << i << " " << b <<" "<< a <<endl;
               }
            }
        }
    }   

    //diagonals, 30 of them
    for (int a=0;a < 5;a++) {
        totalX1=0;
        totalX2=0;
        totalY1=0;
        totalY2=0;
        totalZ1=0;
        totalZ2=0;                        
        for (int b=0;b<5;b++) {
            if (board [a][b][b] == player) totalX1++;
            if (board [a][4-b][b] == player) totalX2++;
            if (board [b][b][a] == player) totalY1++;
            if (board [b][4-b][a] == player) totalY2++;
            if (board [b][a][b] == player) totalZ1++;
            if (board [4-b][a][b] == player) totalZ2++;
            
        }
        if (totalX1==4) {
           for (int i=0;i<5;i++) {
               if (board[a][i][i]== ' ') cout << a << " " << i << " " << i << endl;
           }
        }
        if (totalX2==4) {
           for (int i=0;i<5;i++) {
               if (board[a][4-i][i]== ' ') cout << a << " " << 4-i << " " << i << endl;
           }
        }  
        if (totalY1==4) {
           for (int i=0;i<5;i++) {
               if (board[i][i][a]== ' ') cout << i << " " << i << " " << a << endl;
           }
        }
        if (totalY2==4) {
           for (int i=0;i<5;i++) {
               if (board[i][4-i][a]== ' ') cout << i << " " << 4-i << " " << a << endl;
           }
        }
        if (totalZ1==4) {
           for (int i=0;i<5;i++) {
               if (board[i][a][i]== ' ') cout << i << " " << a << " " << i << endl;
           }
        }               
        if (totalZ2==4) {
           for (int i=0;i<5;i++) {
               if (board[i][a][4-i]== ' ') cout << i << " " << a << " " << 4-i << endl;
           }
        }
    }

    //the 4 super diagonals      
    for (int a=0;a<5;a++) {
        if (board[a][a][a] == player) diag1++;
        if (board[4-a][a][a] == player) diag2++;
        if (board[a][4-a][a] == player) diag3++;
        if (board[a][a][4-a] == player) diag4++;
    }        
    if (diag1==4) {
       for (int i=0;i<5;i++) {
           if (board[i][i][i]== ' ') cout << i << " " << i << " " << i << endl;
       }
    }
    if (diag2==4) {
       for (int i=0;i<5;i++) {
           if (board[4-i][i][i]== ' ') cout << 4-i << " " << i << " " << i << endl;
       }
    } 
    if (diag3==4) {
       for (int i=0;i<5;i++) {
           if (board[i][4-i][i]== ' ') cout << i << " " << 4-i << " " << i << endl;
       }
    }  
    if (diag4==4) {
       for (int i=0;i<5;i++) {
           if (board[i][i][4-i]== ' ') cout << i << " " << i << " " << 4-i << endl;
       }
    } 
}
