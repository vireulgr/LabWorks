#include "RationalNumbers.h"
#include <exception>

// TODO
RationalNumbers::RationalNumbers(int a, unsigned int b) 
    : m_numerator(1), m_denominator(1)
{
    normalize();
}

// TODO
void RationalNumbers::normalize() {
}

// TODO
int RationalNumbers::floor() {
    return m_numerator / m_denominator;
}

// TODO
double RationalNumbers::toDouble() {
    return (double)m_numerator / m_denominator;
}

// TODO
RationalNumbers RationalNumbers::reciprocal() {
    return RationalNumbers(m_denominator, m_numerator);
}

// TODO
int RationalNumbers::euclidGcd(int a, int b) {
    return a;
}

// TODO
RationalNumbers RationalNumbers::operator + (RationalNumbers const & right) {
    return *this;
}
// TODO
RationalNumbers RationalNumbers::operator - (RationalNumbers const & right) {
    return *this;
}

// TODO
RationalNumbers RationalNumbers::operator * (RationalNumbers const & right) {
    return *this;
}
// TODO
RationalNumbers RationalNumbers::operator / (RationalNumbers const & right) {
    return *this;
}

// TODO
bool RationalNumbers::operator == (RationalNumbers const & right) {
    return false;
}

// TODO
bool RationalNumbers::operator != (RationalNumbers const & right) {
    return false;
}

// TODO
bool RationalNumbers::operator < (RationalNumbers const & right) {
    return false;
}

// TODO
bool RationalNumbers::operator > (RationalNumbers const & right) {
    return false;
}

// TODO
bool RationalNumbers::operator <= (RationalNumbers const & right) {
    return false;
}

// TODO
bool RationalNumbers::operator >= (RationalNumbers const & right) {
    return false;
}

// TODO
RationalNumbers RationalNumbers::operator ++ () {
    return *this;
}

// TODO
RationalNumbers RationalNumbers::operator ++ (int) {
    return *this;
}

// TODO
RationalNumbers RationalNumbers::operator -- () {
    return *this;
}

// TODO
RationalNumbers RationalNumbers::operator -- (int) {
    return *this;
}

