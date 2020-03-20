#ifndef __RATIONAL_NUMBERS_H__
#define __RATIONAL_NUMBERS_H__
class RationalNumbers {
    int m_numerator;
    unsigned int m_denominator;

    int euclidGcd(int a, int b);
    void normalize();
public:
    RationalNumbers(int a = 0, unsigned int b = 1);

    int floor();
    double toDouble();
    RationalNumbers reciprocal();

    RationalNumbers operator + (RationalNumbers const & right);
    RationalNumbers operator - (RationalNumbers const & right);

    RationalNumbers operator * (RationalNumbers const & right);
    RationalNumbers operator / (RationalNumbers const & right);

    bool operator == (RationalNumbers const & right);
    bool operator != (RationalNumbers const & right);

    bool operator < (RationalNumbers const & right);
    bool operator > (RationalNumbers const & right);
    bool operator <= (RationalNumbers const & right);
    bool operator >= (RationalNumbers const & right);

    RationalNumbers operator ++ ();
    RationalNumbers operator ++ (int);

    RationalNumbers operator -- ();
    RationalNumbers operator -- (int);
};
#endif
