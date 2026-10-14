#include <iostream>
#include <clocale>

using namespace std;

class Fraction
{
private:
    int numerator;
    int denominator;

public:
    Fraction(int num, int den)
        : numerator(num), denominator(den)
    {
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

    Fraction a(1, 2);
    Fraction b(1, 3);

    cout << "a = " << a << '\n';
    cout << "b = " << b << '\n';

    return 0;
}