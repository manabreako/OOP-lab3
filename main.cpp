#include <iostream>
#include <clocale>

using namespace std;

class Fraction
{
private:
    int numerator;
    int denominator;

public:
    Fraction() : numerator(0), denominator(1) {}

    explicit Fraction(int number)
        : numerator(number), denominator(1) {}

    Fraction(int num, int den)
        : numerator(num), denominator(den) {}

    friend ostream& operator<<(ostream& out, const Fraction& f)
    {
        out << f.numerator << "/" << f.denominator;
        return out;
    }
};

int main()
{
    setlocale(LC_ALL, "");

    Fraction a;
    Fraction b(5);
    Fraction c(1, 2);

    cout << "a = " << a << '\n';
    cout << "b = " << b << '\n';
    cout << "c = " << c << '\n';

    return 0;
}