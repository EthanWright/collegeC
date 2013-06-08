#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

//x=rows of a, y=columns of a=rows of b, z=columns of b
void mult(float *m, float *a, float *b, int x, int y, int z)
{
//for each row of A and column of B, multiply each cell together and add them
    for(int j=0; j<x; j++) {
        for(int k=0; k<z; k++) {
            for(int i=0; i<y; i++) {
                m[(j*z)+k]+=a[(j*x)+i]*b[(i*z)+k];
            }
        }    
    }
    return;
}

void inverse(float *matrix, int n)
{
//setup matrix + identity matrix
    float *temp = (float *)malloc(n*n*2*sizeof(float));
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++)
            temp[(i*2*n)+j]=matrix[(i*n)+j];
        for (int j=n;j<n*2;j++) {
            if(j-n==i)
                temp[(i*2*n)+j]=1;
            else
                temp[(i*2*n)+j]=0;
        }
    }
//Gauss Jordan elimination, algorithm in book          
    float mod;
    for (int i=0;i<n;i++) {
        mod=1/temp[0];
        for (int j=0;j<n*2;j++)
            temp[i]*=mod;
        
        for(int k=0; k<n;k++) {
            if(k!=i) {
                for(int l=0; l<2*n;l++) {
                    temp[k*n*2+l]+=(-1*temp[k*n*2+l]/temp[i*n*2+i])*temp[i*n*2+l];
                }
            }
        }
    }
//Take back just the inverted matrix
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++)
            matrix[(i*n)+j]=temp[(i*2*n)+j];
    }
    return;   
}

void eliminate(float *matrix, int col, int row, int n, int m) {
//makes every cell in the column 0, except the one at n,m, which becomes 1.
    float mod;
    mod=1/matrix[row*m+col];
    for(int i=0;i<m;i++)
        matrix[row*m+i]=(mod)*matrix[row*m+i];
    for(int i=0;i<n;i++) {
        if(i != row) {
            mod=matrix[i*m+col]/matrix[row*m+col];
            for(int j=0;j<m;j++)
                matrix[i*m+j]-=matrix[row*m+j]*mod;    
        }
    }
}

//inverse
//infeasible


int main() {
//Declarations
    char Nfile[]="N.txt";
    char bfile[]="b.txt";
    char cnfile[]="cn.txt";
    const int SIZE=100;
    int m=0,n=0,e=0, xamount; //dimensions of A, n=rows m=columns e=extra
    int found=0, count=0, sign=1, elements=0, c=0;
    float calc=0;
    
//read N from file
    int temp[SIZE];
    FILE *data1 = fopen(Nfile, "r");
    while((c = fgetc(data1)) != EOF) {
        temp[elements]=c;
        elements++;
    }
    fclose(data1);
//find m and n    
    for (int i=0; i<=elements; i++) {
        if (temp[i] == ' ' && n==0)
            m++;
        if (temp[i] == '\n')
            n++;
    }
    m++;
    if(temp[elements-1]!='\n')n++;

//Create N from data read
    float N [100];
    for (int i=0; i<=elements; i++) {
      if (temp[i] == ' ' || temp[i] == '\n') {
          N[count]=calc;
          calc=0;
          count++;
          sign=1;
      } else {
          if (temp[i]==45) {
              sign=-1;
          } else {
              calc=calc*10+(sign*(temp[i]-48));
          }
      }
    }
    sign=1;
//read and create b
    float b [100];
    elements=0;
    FILE *data2 = fopen(bfile, "r");
    while((c = fgetc(data2)) != EOF) {
        temp[elements]=c;
        elements++;
    }
    fclose(data2);
    sign=1;
    count=0;
    calc=0;
    for (int i=0; i<=elements; i++) {
      if (temp[i] == '\n' && count < n) {
          b[count]=calc;
          calc=0;
          count++;
          sign=1;
      } else {
          if (temp[i]==45) {
              sign=-1;
          } else {
              calc=calc*10+(sign*(temp[i]-48));
          }
      }
    }
    sign=1;
//read and create cn
    float cn [100];
    elements=0;
    FILE *data3 = fopen(cnfile, "r");
    while((c = fgetc(data3)) != EOF) {
        temp[elements]=c;
        elements++;
    }
    fclose(data3);
    
    count=0;
    calc=0;
    for (int i=0; i<=elements; i++) {
      if (temp[i] == '\n' && count < m) {
          cn[count]=calc;
          calc=0;
          count++;
          sign=1;
      } else {
          if (temp[i]==45) {
              sign=-1;
          } else {
              calc=calc*10+(sign*(temp[i]-48));
          }
      }
    }
   
//Create B
    //float *B = (float *)malloc(n*n*sizeof(float));
    float B [100];
    for (int i=0; i<n*n; i++){
        if(i%(n+1)==0) {
            B[i]=1;
        } else {
            B[i]=0;
        }
    }
//create cb
    float cb [100];
    for (int i=0; i<n; i++)
        cb[i]=1;

//create initial
    float initial [100]; //for top z row
    for(int i=0; i<(m-n); i++) {
        initial[i]=(-1)*cn[i];cout << cn[i] << " ";}
        
    for(int i=(m-n); i<(m+n+2); i++) 
        initial[i]=0;   

    for (int i=0; i<m; i++)
        cn[i]=0; //cn all 0s

//Set up the matricies
//invert B
    inverse(B, n);
//B-1 * b
    float Binverseb [100];
    mult(Binverseb, B, b,n,n,1);

//B-1 * N
    float BinverseN [100];
    mult(BinverseN, B, N, n,n,m);
 
//cb * B-1 * b
    float cbBinverseb [100];
    mult(cbBinverseb, cb, Binverseb, 1, n, 1);

//cb * B-1 * N
    float cbBinverseN [100];
    mult(cbBinverseN, cb, BinverseN, 1, n, m);
    
//cb * B-1 *N - cn
    float cbBinverseNcn [100];
    for (int i=0; i<m; i++) 
        cbBinverseNcn[i] = cbBinverseN[i] - cn[i];


//make z
    int cols=m+n+2;
    int rows=n+2;

    float z [100];
        for (int i=0; i<(rows)*(cols); i++)z[i]=0;
//set up z according to the tableau format on page 79 in the book    
    for (int i=2; i<n+2; i++)
        z[i*(cols)]=0; 
    z[0]=1;
    z[cols]=1;
    for (int i=0; i<m; i++) 
        z[i+cols+1]=cbBinverseNcn[i];
    for (int i=m; i<(m+n); i++) 
        z[i+cols+1]=0;
  
    z[2*(cols)-1]=cbBinverseb[0];
    
    for (int i=0; i<cols-1; i++) 
        z[i+1]=initial[i];

    for (int i=0; i<n; i++) { //row
        for (int j=0; j<m; j++) { //column
            z[((i+2)*(cols))+(j+1)]=BinverseN[i*m+j];
        }
    }
    
    for (int i=0; i<n; i++)
        z[((cols)*(i+3))-1]=Binverseb[i];
   
    for (int i=0; i<n; i++) { //row
        for (int j=0; j<n; j++) { //column
            z[(i+2)*(cols)+(j+m+1)]=B[i*n+j];
        }
    }



//basis stores the values of the variables in the basis
    float basis [100];
    for(int i=0;i<n; i++)
        basis[i]=m+i+1;
    xamount=m-n;
    
//FIRST PHASE of the simplex algorithm
    int allGone=0, iter=0;
    do
    {
    iter++;
    if(iter>xamount*xamount) {
        cout << "ifeasible"<<endl;
        return 0;
    }
    //output all the information
        for(int i=0;i<((cols)*(rows));i++){
            if (i%(cols)==0) {
                cout<<endl;
                if (i/cols > 1) {
                    if(basis[i/cols-2] < xamount) cout << "x" << basis[i/cols-2]+1 << " ";
                    else if(basis[i/cols-2] < m) cout << "s" << basis[i/cols-2]-(xamount-1)<<" ";  
                    else if(basis[i/cols-2] <= m+n) cout <<"xa" << basis[i/cols -2]-(m+n-3) << " ";
                    else cout <<basis[i/cols-2];
                } else
                    cout << "   ";
            }
            if (z[i]<.000001 && z[i] > -.000001) 
                cout << 0 << " ";
            else
                cout << z[i] << " ";
        }
        allGone=1;
        for(int i=0; i<n; i++){
            if(basis[i]>m) allGone=0;
        }
        if (allGone==0){
//find var to enter
        int col=0,row=0;
        float min=214000000;
        for(int i=m+n+3; i<(2*m+n+3); i++) {
            if(z[i]>0) { // min
                col=i-(m+n+2);
                break;
            }
        }
//calc MRT for the var, RHS col/col
        for(int i=2; i<(n+2); i++) {
            if (z[i*(m+n+2)+col] != 0) {
                if(z[(i+1)*(m+n+2)-1]/z[i*(m+n+2) + col] < min && z[(i+1)*(m+n+2)-1]/z[i*(m+n+2) + col] >0){
                    min=z[(i+1)*(m+n+2)-1]/z[i*(m+n+2) + col];
                    row=i;
                }
            }
        }
        if (col!=0) {
            cout <<endl<<"col: "<<col<<" row: " << row << " MRT: " << min<<endl;
            eliminate(z, col, row, n+2, m+n+2);
            basis[row-2]=col-1; //update basis
        }
        }
    } while (allGone==0);
      
    cout << endl<<"Phase 1 complete" <<endl<<endl;

//create phase 2 matrix by removing the n xa columns and the z row
    float z2 [100]; //n+1 by m+2
    for (int i=0; i<(n+1)*(m+2); i++)z2[i]=0;

    for(int i=0; i<m+1; i++)
        z2[i]=z[i];

    for(int i=2; i<n+2; i++)
        z2[(m+2)*i-1]=z[(m+n+2)*(i+1)-1];

    z2[m+1]=z[m+n+1];

    for(int i=1; i<n+1; i++)
        for(int j=0; j<m+1; j++)
            z2[i*(m+2)+j]=z[(i+1)*(2+m+n)+j];
            
//PHASE 2 of the simplex algorithm. Run until optimal solution is found
//meaning there are no negative values in the z row
    int fail=0;
    rows--;
    cols-=n;
    do
    {
    //output everything for each iteration
        for(int i=0;i<((cols)*(rows));i++){
            if (i%(cols)==0) {
                cout<<endl;
                if (i/cols > 0) {
                    if(basis[i/cols-1] < xamount) cout << "x" << basis[i/cols-1]+1 << " ";
                    else if(basis[i/cols-1] < m) cout << "s" << basis[i/cols-1]-(xamount-1)<<" ";  
                    else cout <<"Bad";
                } else
                    cout << "   ";
            }
            if (z2[i]<.000001 && z2[i] > -.000001) 
                cout << 0 << " ";
            else
                cout << z2[i] << " ";
        }
//find var to enter
        int col=0,row=0;
        float min=214000000;
        for(int i=1; i<=m+n; i++) {
            if(z2[i]<0) { //max
                col=i;
                break;
            }
        }
        if (col==0) {
            fail=1;
            break;
        }
//calc MRT for the var found
        for(int i=1; i<(n+1); i++) {
            if (z2[i*(m+2)+col] != 0) {
                if(z2[(i+1)*(m+2)-1]/z2[i*(m+2) + col] < min && z2[(i+1)*(m+2)-1]/z2[i*(m+2) + col] >0){
                    min=z2[(i+1)*(m+2)-1]/z2[i*(m+2) + col];
                    row=i;
                }
            }
        }
        if(min==214000000) fail=1;//nothing found
        else{
            cout <<endl<<col<<" " << row << " " << min<<endl;
            basis[row-1]=col-1;
            eliminate(z2, col, row, n+1, m+2);
        }
    } while (fail==0);
    
//output the final answer
    cout << endl <<endl  <<"Solution: "<< endl;
    for(int i=0; i<n; i++) {
        if(basis[i] < xamount) cout << "x" << basis[i]+1 << " ";
        else if(basis[i] < m) cout << "s" << basis[i]-(xamount-1) << " ";  
            if (z2[(i+2)*(m+2)-1]<.000001 && z2[(i+2)*(m+2)] > -.000001)//float inaccuracies 
                cout << 0 <<endl;
            else
                cout << z2[(i+2)*(m+2)-1] <<endl;
    }
    
    system("PAUSE");
    return 0;
}
