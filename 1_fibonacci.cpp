#include <iostream>
using namespace std;

int steps = 0;

int fibRecursive(int n) {
    steps++;
    if (n <= 1) return n;
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    cout << "\nIterative Fibonacci\n";
    int a = 0, b = 1, c;
    int count = 0;
    cout << "Initially: a = " << a << ", b = " << b << endl;

    if (n <= 1) {
        cout << "n is 0 or 1, so Fib(" << n << ") = " << n << endl;
        c = n;
    } else {
        for (int i = 2; i <= n; i++) {
            c = a + b;
            count++;
            cout << "Step " << count << " (i = " << i << "): c = a + b = " << a << " + " << b << " = " << c << endl;
            a = b;
            b = c;
            cout << "         update: a = " << a << ", b = " << b << endl;
        }
    }
    cout << "Iterative: Fib(" << n << ") = " << c << ", steps = " << count << endl;

    steps = 0;
    int r = fibRecursive(n);
    cout << "\nRecursive: Fib(" << n << ") = " << r << ", steps = " << steps << endl;
    return 0;
}
