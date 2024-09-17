#pragma once
#include <algorithm>

class ComplexNumber {
public:
    ComplexNumber();
    ComplexNumber(double, double);
    ComplexNumber(const ComplexNumber& other);
    ComplexNumber operator=(const ComplexNumber& other);
    ComplexNumber(ComplexNumber&& other);
    ComplexNumber operator=(const ComplexNumber&& other);
    friend ComplexNumber operator+(const ComplexNumber& lhs, const ComplexNumber& rhs);
    friend ComplexNumber& operator+=(ComplexNumber& lhs, const ComplexNumber& rhs);
    friend ComplexNumber operator-(const ComplexNumber& lhs, const ComplexNumber& rhs);
    friend ComplexNumber& operator-=(ComplexNumber& lhs, const ComplexNumber& rhs);
    friend ComplexNumber operator*(const ComplexNumber& lhs, const ComplexNumber& rhs);
    friend ComplexNumber& operator*=(ComplexNumber& lhs, const ComplexNumber& rhs);
    friend ComplexNumber operator/(const ComplexNumber& lhs, const ComplexNumber& rhs);
    friend ComplexNumber& operator/=(ComplexNumber& lhs, const ComplexNumber& rhs);
    double get_length() {
        return a_ * a_ + b_ * b_;
    }

private:
    double a_, b_;
    void Swap(ComplexNumber& rhs) {
        std::swap(a_, rhs.a_);
        std::swap(b_, rhs.b_);
    }
};
