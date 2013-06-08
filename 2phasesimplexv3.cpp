#include <iostream>
#include <stdio.h>

using namespace std;

//x=rows of a, y=columns of a=rows of b, z=columns of b
void mult(float *m, float *a, float *b, int x, int y, int z)
{
    for(int j=0; j<x; j++) {
        for(int k=0; k<z; k++) {
            for(int i=0; i<y; i++) {
                m[(j*z)+k]+=a[(j*x)+i]*b[(i*z)+k];
            }
        }    
    }
    return;
}

float* inverse(float *matrix)
{
     return matrix;
}


//is first z row just - initial? yes
//no negative xa? 
//is cb just 11111?
//is cn 0000?


//inverse
//MRT
//eliminate
//infeasible
//alternative solutions
//strict formatting

int main() {
    const int SIZE=100;
    int m=0,n=0,e=0; //dimensions of A, n=rows m=columns e=extra
    int found=0, count=0, sign=1, elements=0, c=0;
    float calc=0;
    
//read N from file
    int temp[SIZE];
    FILE *data1 = fopen("A.txt", "r");
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

//Create N
    float *N = (float *)malloc(n*m* sizeof(float));    
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

//create b
    float *b = (float *)malloc(n*sizeof(float));
    elements=0;
    FILE *data2 = fopen("b.txt", "r");
    while((c = fgetc(data2)) != EOF) {
        temp[elements]=c;
        elements++;
    }
    fclose(data2);
    
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

//create cn
    float *cn = (float *)malloc(m*sizeof(float));
    elements=0;
    FILE *data3 = fopen("cn.txt", "r");
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
    float *B = (float *)malloc(n*n*sizeof(float));
    
    for (int i=0; i<n*n; i++){
        if(i%(n+1)==0) {
            B[i]=1;
        } else {
            B[i]=0;
        }
    }
//create cb
    float *cb = (float *)malloc(n*sizeof(float));
    for (int i=0; i<n; i++)
        cb[i]=1;

//create initial
    float *initial = (float *)malloc((m+n+2)* sizeof(float)); //for top z row     
    for(int i=0; i<(m-n); i++) 
        initial[i]=(-1)*cn[i];
    for(int i=(m-n); i<(m+n+2); i++) 
        initial[i]=0;   

    for (int i=0; i<m; i++)
        cn[i]=0; 

//Set up the matricies
//B-1 * b
    float *Binverseb = (float *)malloc(n*1*sizeof(float));
    mult(Binverseb, inverse(B), b,n,n,1);

//B-1 * N
    float *BinverseN = (float *)malloc(n*m*sizeof(float));
    //mult(BinverseN, inverse(B), N, n,n,m);
    BinverseN=N;
    
//cb * B-1 * b
    float *cbBinverseb = (float *)malloc(1*sizeof(float));
    mult(cbBinverseb, cb, Binverseb, 1, n, 1);

//cb * B-1 * N
    float *cbBinverseN = (float *)malloc(1*m*sizeof(float));
    mult(cbBinverseN, cb, BinverseN, 1, n, m); 
    
//cb * B-1 *N - cn
    float *cbBinverseNcn = (float *)malloc(m*sizeof(float));
    for (int i=0; i<m; i++) 
        cbBinverseNcn[i] = cbBinverseN[i] - cn[i];

//make z
    float *z = (float *)malloc((n+2)*(m+n+2)*sizeof(float));
    for (int i=1; i<n+1; i++)
        z[i*(m+n+2)]=0;  
    z[0]=1;
    z[m+n+2]=1;
    for (int i=0; i<m; i++) 
        z[i+m+n+3]=cbBinverseNcn[i];
    for (int i=m; i<(m+n); i++) 
        z[i+m+n+3]=0;
  
    z[2*(m+n+2)-1]=cbBinverseb[0];
    
    for (int i=0; i<m+n; i++) 
        z[i+1]=initial[i];

    for (int i=0; i<n; i++) { //row
        for (int j=0; j<m; j++) { //column
            z[(i+2)*(m+n+2)+(j+1)]=BinverseN[i*m+j];
        }
    }
    
    for (int i=0; i<n; i++)
        z[((m+n+2)*(i+3))-1]=Binverseb[i];
   
    for (int i=0; i<n; i++) { //row
        for (int j=0; j<n; j++) { //column
            z[(i+2)*(m+n+2)+(j+m+1)]=B[i*n+j];
        }
    }

    for(int i=0;i<(m+n+2)*(n+2);i++){
        if (i%(m+n+2)==0) cout<<endl;
        if (z[i]<.000001) cout << 0 << " ";
        else
        cout << z[i] << " ";
    }
      
//basis stores the values of the variables in the basis
    float *basis = (float *)malloc(n*sizeof(float));
    for(int i=0;i<n; i++)
        basis[i]=n+m+i+1;
        
//----------------------------------------------------------repeat  
//while any basis > n+m+1
//find var to enter and calc MRT
    int enter;
    float min=214000000;
    for(int i=m+n+3; i<(2*m+n+3); i++) {
        if(z[i]<0) {
            enter=i-(m+n+2);
            break;
        }
    }
    for(int i=2; i<(n+2); i++) {
        if (z[i*(m+n+2)+enter] != 0)
            if(z[(i+1)*(m+n+2)-1]/z[i*(m+n+2) + enter] < min && z[(i+1)*(m+n+2)-1]/z[i*(m+n+2) + enter] >0)
                min=z[(i+1)*(m+n+2)-1]/z[i*(m+n+2) + enter];
    }
    cout <<endl<<enter<<" " << min;
    
    
//eliminate

    free(N);
    free(B);
    free(cb);
    free(cn);
    free(b);
    free(initial);
    free(Binverseb);
    free(BinverseN);
    free(cbBinverseb);
    free(cbBinverseN);
    free(cbBinverseNcn);
    free(z);

  
    system("PAUSE");
    return 0;
}
