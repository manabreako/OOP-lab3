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

    explicit Fraction(int number)
        : numerator(number), denominator(1) {}

    Fraction(int num, int den)
        : numerator(num), denominator(den)
    {
        reduce();
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

    Fraction a(2, 4);
    Fraction b(3, -6);

    cout << "a = " << a << '\n';
    cout << "b = " << b << '\n';

    return 0;
}