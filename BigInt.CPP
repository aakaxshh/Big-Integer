#include "BigInt.h"
#include <algorithm>
#include <stdexcept>

using namespace std;

// Constructors
BigInt::BigInt(string s) {        
    if (!all_of(s.begin(), s.end(), ::isdigit))
        throw invalid_argument("Invalid number!");
    reverse(s.begin(), s.end());
    digits = s;
    removeLeadingZeros();
}

BigInt::BigInt(long long n) {
    if (n == 0) digits = "0";
    else {
        while (n > 0) {
            digits.push_back(n % 10 + '0');
            n /= 10;
        }
    }
}

// Helper
void BigInt::removeLeadingZeros() {
    while (digits.size() > 1 && digits.back() == '0')
        digits.pop_back();
}

// Print
ostream& operator<<(ostream& out, const BigInt& a) {
    for (int i = a.digits.size() - 1; i >= 0; i--)
        out << a.digits[i];
    return out;
}

// Read
istream& operator>>(istream& in, BigInt& a) {
    string s;
    in >> s;
    a = BigInt(s);
    return in;
}

// Comparison
bool BigInt::operator<(const BigInt& b) const {
    if (digits.size() != b.digits.size())
        return digits.size() < b.digits.size();
    for (int i = digits.size() - 1; i >= 0; i--)
        if (digits[i] != b.digits[i])
            return digits[i] < b.digits[i];
    return false;
}

bool BigInt::operator==(const BigInt& b) const {
    return digits == b.digits;
}

// Addition
BigInt BigInt::operator+(const BigInt& b) const {
    string result = "";
    int carry = 0;
    int n = max(digits.size(), b.digits.size());

    for (int i = 0; i < n; i++) {
        int sum = carry;
        if (i < digits.size()) sum += digits[i] - '0';
        if (i < b.digits.size()) sum += b.digits[i] - '0';
        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
    if (carry) result.push_back(carry + '0');

    BigInt res;
    res.digits = result;
    res.removeLeadingZeros();
    return res;
}

// Subtraction (assumes *this >= b)
BigInt BigInt::operator-(const BigInt& b) const {
    if (*this < b)
        throw invalid_argument("Negative result not supported!");

    string result = "";
    int borrow = 0;

    for (size_t i = 0; i < digits.size(); i++) {
        int diff = (digits[i] - '0') - borrow;
        if (i < b.digits.size())
            diff -= (b.digits[i] - '0');

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else
            borrow = 0;

        result.push_back(diff + '0');
    }

    BigInt res;
    res.digits = result;
    res.removeLeadingZeros();
    return res;
}

// Multiplication
BigInt BigInt::operator*(const BigInt& b) const {
    BigInt res("0");
    res.digits = string(digits.size() + b.digits.size(), '0');

    for (size_t i = 0; i < digits.size(); i++) {
        int carry = 0;
        for (size_t j = 0; j < b.digits.size() || carry; j++) {
            long long cur = res.digits[i + j] - '0' +
                (digits[i] - '0') * (j < b.digits.size() ? (b.digits[j] - '0') : 0) +
                carry;
            res.digits[i + j] = (cur % 10) + '0';
            carry = cur / 10;
        }
    }

    res.removeLeadingZeros();
    return res;
}
