#include <iostream>
#include <string>
using namespace std;


bool isShuffle_nonrecursive(string y, string x, string z) {
int n = x.length();
int m = y.length();
int r = z.length();
if (r != n + m)
return false; // obvious case

bool S[n+1][m+1];

for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
        S[i][j]=0;
    }
}

S[0][0] = true;
for (int i = 1; i <= n; i++)
    S[i][0] = S[i-1][0] && (z[i-1] == x[i-1]);

for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
        cout << S[i][j] << " ";
    }
    cout << endl;
}
cout << endl;

for (int j = 1; j <= m; j++) 
    S[0][j] = S[0][j-1] && (z[j-1] == y[j-1]);


for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
        cout << S[i][j] << " ";
    }
    cout << endl;
}
cout << endl;

for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        S[i][j] = ( (z[i+j-1] == x[i-1]) && S[i-1][j] )|| ( (z[i+j-1] == y[j-1]) && S[i][j-1]);
    }
}

for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
        cout << S[i][j] << " ";
    }
    cout << endl;
}
cout << endl;


return S[n][m];
}

int main() {
 
    cout << isShuffle_nonrecursive("more", "mess", "momerses") << endl;
    system("PAUSE");
    return 0;
}
