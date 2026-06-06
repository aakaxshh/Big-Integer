#ifndef BIGINT_H  // ifdef stands for if not defined (prevents multiple inclusion, it checks if BigINT.h has not been defined earlier)
#define BIGINT_H   // it defines the identifier

#include <iostream>
#include <string>
using namespace std;

class BigInt {
    string digits;    //private data member that stores actual digit

public:
    BigInt(string s = "0");   //constructor declaration, it allows to create BigInt object eg BigInt a("12345")
    BigInt(long long n);   //another constructor, only acceps long long

    friend ostream& operator<<(ostream&, const BigInt&);  // friend is used to access pvt class
    friend istream& operator>>(istream&, BigInt&);

    bool operator<(const BigInt&) const;
    bool operator==(const BigInt&) const;

    BigInt operator+(const BigInt&) const;
    BigInt operator-(const BigInt&) const;
    BigInt operator*(const BigInt&) const;

private:
    void removeLeadingZeros();
};

#endif
