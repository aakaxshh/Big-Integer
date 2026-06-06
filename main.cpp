#include "BigInt.h"
#include <iostream>
using namespace std;

int main() {
    BigInt a, b;
    cout << "Enter first big integer: ";
    cin >> a;
    cout << "Enter second big integer: ";
    cin >> b;

    cout << "\nAddition: " << (a + b);
    if (!(a < b))
        cout << "\nSubtraction: " << (a - b);
    else
        cout << "\nSubtraction: Not possible (negative result)";

    cout << "\nMultiplication: " << (a * b) << endl;
    return 0;
}