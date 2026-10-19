#include <iostream>
using namespace std;

int main() {
    int n, k;
    cout << "Enter n and k: ";
    cin >> n >> k;

    int C[50][50];

    for (int i = 0; i <= n; i++) {
        cout << "\nRow " << i << ":\n";
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i) {
                C[i][j] = 1;
                cout << "  C(" << i << "," << j << ") = 1\n";
            } else {
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
                cout << "  C(" << i << "," << j << ") = C(" << i - 1 << "," << j - 1 << ") + C(" << i - 1 << "," << j << ") = "
                     << C[i - 1][j - 1] << " + " << C[i - 1][j] << " = " << C[i][j] << endl;
            }
        }
        cout << "  Row " << i << ": ";
        for (int j = 0; j <= i; j++)
            cout << C[i][j] << " ";
        cout << endl;
    }

    cout << "\nC(" << n << "," << k << ") = " << C[n][k] << endl;
    return 0;
}
