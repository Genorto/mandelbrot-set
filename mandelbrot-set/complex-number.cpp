#include "complex-number.h"

ComplexNumber::ComplexNumber() : a_(0), b_(0) {}

ComplexNumber::ComplexNumber(double a, double b) : a_(a), b_(b) {}

ComplexNumber::ComplexNumber(const ComplexNumber& other) : a_(other.a_), b_(other.b_) {}

ComplexNumber ComplexNumber::operator=(const ComplexNumber& other) {
    ComplexNumber buffer = other;
    Swap(buffer);
    return *this;
}

ComplexNumber::ComplexNumber(ComplexNumber&& other) : a_(std::move(other.a_)), b_(std::move(other.b_)) {}

ComplexNumber ComplexNumber::operator=(const ComplexNumber&& other) {
    ComplexNumber buffer = other;
    Swap(buffer);
    return *this;
}

ComplexNumber operator+(const ComplexNumber& lhs, const ComplexNumber& rhs) {
    ComplexNumber res;
    res.a_ = lhs.a_ + rhs.a_;
    res.b_ = lhs.b_ + rhs.b_;
    return res;
}

ComplexNumber& operator+=(ComplexNumber& lhs, const ComplexNumber& rhs) {
    lhs = lhs + rhs;
    return lhs;
}

ComplexNumber operator-(const ComplexNumber& lhs, const ComplexNumber& rhs) {
    ComplexNumber res;
    res.a_ = lhs.a_ - rhs.a_;
    res.b_ = lhs.b_ - rhs.b_;
    return res;
}

ComplexNumber& operator-=(ComplexNumber& lhs, const ComplexNumber& rhs) {
    lhs = lhs - rhs;
    return lhs;
}

ComplexNumber operator*(const ComplexNumber& lhs, const ComplexNumber& rhs) {
    ComplexNumber res;
    res.a_ = lhs.a_ * rhs.a_ - lhs.b_ * rhs.b_;
    res.b_ = lhs.a_ * rhs.b_ + rhs.a_ * lhs.b_;
    return res;
}

ComplexNumber& operator*=(ComplexNumber& lhs, const ComplexNumber& rhs) {
    lhs = lhs * rhs;
    return lhs;
}

ComplexNumber operator/(const ComplexNumber& lhs, const ComplexNumber& rhs) {
    ComplexNumber res;
    res.a_ = (lhs.a_ * rhs.a_ + lhs.b_ * rhs.b_) / (rhs.a_ * rhs.a_ + rhs.b_ * rhs.b_);
    res.b_ = (lhs.b_ * rhs.a_ - lhs.a_ * rhs.b_) / (rhs.a_ * rhs.a_ + rhs.b_ * rhs.b_);
    return res;
}

ComplexNumber& operator/=(ComplexNumber& lhs, const ComplexNumber& rhs) {
    lhs = lhs / rhs;
    return lhs;
}
