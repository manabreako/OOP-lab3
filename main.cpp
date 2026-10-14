#include <iostream>
#include <numeric>
#include <stdexcept>
#include <cstdlib>
#include <string>
#include <clocale>

using namespace std;

class Fraction
{
private:
    int numerator;
    int denominator;
    mutable int accessCount;
    static int objectCount;

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
    Fraction() : numerator(0), denominator(1), accessCount(0)
    {
        objectCount++;
    }

    explicit Fraction(int n) : numerator(n), denominator(1), accessCount(0)
    {
        objectCount++;
    }

    Fraction(int n, int d) : numerator(n), denominator(d), accessCount(0)
    {
        reduce();
        objectCount++;
    }

    Fraction(const Fraction& other)
        : numerator(other.numerator),
          denominator(other.denominator),
          accessCount(0)
    {
        objectCount++;
    }

    ~Fraction()
    {
        objectCount--;
    }

    string getValue() const
    {
        accessCount++;
        return to_string(numerator) + "/" + to_string(denominator);
    }

    int getAccessCount() const
    {
        return accessCount;
    }

    static int getObjectCount()
    {
        return objectCount;
    }

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

    friend Fraction operator+(Fraction a, const Fraction& b) { return a += b; }
    friend Fraction operator-(Fraction a, const Fraction& b) { return a -= b; }
    friend Fraction operator*(Fraction a, const Fraction& b) { return a *= b; }
    friend Fraction operator/(Fraction a, const Fraction& b) { return a /= b; }

    friend bool operator==(const Fraction& a, const Fraction& b)
    {
        return a.numerator == b.numerator &&
               a.denominator == b.denominator;
    }

    friend bool operator!=(const Fraction& a, const Fraction& b) { return !(a == b); }

    friend bool operator<(const Fraction& a, const Fraction& b)
    {
        return 1LL * a.numerator * b.denominator <
               1LL * b.numerator * a.denominator;
    }

    friend bool operator>(const Fraction& a, const Fraction& b) { return b < a; }
    friend bool operator<=(const Fraction& a, const Fraction& b) { return !(a > b); }
    friend bool operator>=(const Fraction& a, const Fraction& b) { return !(a < b); }

    friend ostream& operator<<(ostream& out, const Fraction& f)
    {
        out << f.numerator << "/" << f.denominator;
        return out;
    }
};

int Fraction::objectCount = 0;

int main()
{
    setlocale(LC_ALL, "");

    const Fraction a(2, 5);

    cout << "Дробь: " << a.getValue() << '\n';
    cout << "Повторно: " << a.getValue() << '\n';
    cout << "Количество обращений: " << a.getAccessCount() << '\n';
    cout << "Количество объектов: " << Fraction::getObjectCount() << '\n';

    return 0;
}