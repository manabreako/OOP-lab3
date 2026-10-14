#include <iostream>
#include <numeric>
#include <stdexcept>
#include <cstdlib>
#include <clocale>

using namespace std;

class Fraction
{
private:
    int numerator;
    int denominator;

    void reduce()
    {
        if (denominator == 0)
            throw invalid_argument("Знаменатель не может быть равен нулю!");

        if (denominator < 0)
        {
            numerator = -numerator;
            denominator = -denominator;
        }

        int divisor = gcd(abs(numerator), denominator);
        numerator /= divisor;
        denominator /= divisor;
    }

public:
    Fraction() : numerator(0), denominator(1) {}
    explicit Fraction(int n) : numerator(n), denominator(1) {}

    Fraction(int n, int d) : numerator(n), denominator(d)
    {
        reduce();
    }

    Fraction(const Fraction& other)
        : numerator(other.numerator), denominator(other.denominator) {}

    Fraction& operator++()
    {
        numerator += denominator;
        reduce();
        return *this;
    }

    Fraction operator++(int)
    {
        Fraction old(*this);
        ++(*this);
        return old;
    }

    Fraction& operator--()
    {
        numerator -= denominator;
        reduce();
        return *this;
    }

    Fraction operator--(int)
    {
        Fraction old(*this);
        --(*this);
        return old;
    }

    Fraction& operator+=(const Fraction& other)
    {
        numerator = numerator * other.denominator
                  + other.numerator * denominator;
        denominator *= other.denominator;
        reduce();
        return *this;
    }

    Fraction& operator-=(const Fraction& other)
    {
        numerator = numerator * other.denominator
                  - other.numerator * denominator;
        denominator *= other.denominator;
        reduce();
        return *this;
    }

    Fraction& operator*=(const Fraction& other)
    {
        numerator *= other.numerator;
        denominator *= other.denominator;
        reduce();
        return *this;
    }

    Fraction& operator/=(const Fraction& other)
    {
        if (other.numerator == 0)
            throw invalid_argument("Деление на ноль!");

        numerator *= other.denominator;
        denominator *= other.numerator;
        reduce();
        return *this;
    }

    friend ostream& operator<<(ostream& out, const Fraction& f)
    {
        out << f.numerator << "/" << f.denominator;
        return out;
    }
};

int main()
{
    setlocale(LC_ALL, "");

    Fraction b(1, 3);
    Fraction c(1, 2);

    c += b;
    cout << "После += : " << c << '\n';

    c = Fraction(1, 2);
    c -= b;
    cout << "После -= : " << c << '\n';

    c = Fraction(1, 2);
    c *= b;
    cout << "После *= : " << c << '\n';

    c = Fraction(1, 2);
    c /= b;
    cout << "После /= : " << c << '\n';

    return 0;
}