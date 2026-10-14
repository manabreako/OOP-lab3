#include <iostream>
#include <vector>
#include <string>
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
    Fraction() : numerator(0), denominator(1), accessCount(0) { objectCount++; }

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

    ~Fraction() { objectCount--; }

    string getValue() const
    {
        accessCount++;
        return to_string(numerator) + "/" + to_string(denominator);
    }

    int getAccessCount() const { return accessCount; }
    static int getObjectCount() { return objectCount; }

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
        return a.numerator == b.numerator && a.denominator == b.denominator;
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

    vector<string> history;

    try
    {
        Fraction a(1, 2);
        Fraction b(1, 3);

        cout << "=== КАЛЬКУЛЯТОР ДРОБЕЙ ===\n\n";
        cout << "a = " << a << ", b = " << b << "\n\n";

        cout << "=== АРИФМЕТИКА ===\n";

        Fraction result = a + b;
        cout << a << " + " << b << " = " << result << '\n';
        history.push_back("1/2 + 1/3 = " + result.getValue());

        result = a - b;
        cout << a << " - " << b << " = " << result << '\n';
        history.push_back("1/2 - 1/3 = " + result.getValue());

        result = a * b;
        cout << a << " * " << b << " = " << result << '\n';
        history.push_back("1/2 * 1/3 = " + result.getValue());

        result = a / b;
        cout << a << " / " << b << " = " << result << '\n';
        history.push_back("1/2 / 1/3 = " + result.getValue());

        cout << "\n=== ОПЕРАТОРЫ ПРИСВАИВАНИЯ ===\n";

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

        cout << "\n=== ИНКРЕМЕНТ И ДЕКРЕМЕНТ ===\n";

        Fraction d(3, 4);
        cout << "Исходная дробь: " << d << '\n';
        cout << "Префиксный ++d: " << ++d << '\n';
        cout << "Постфиксный d++: " << d++ << '\n';
        cout << "После d++: " << d << '\n';
        cout << "Префиксный --d: " << --d << '\n';
        cout << "Постфиксный d--: " << d-- << '\n';
        cout << "После d--: " << d << '\n';

        cout << "\n=== СРАВНЕНИЯ ===\n";

        cout << boolalpha;
        cout << "a == b: " << (a == b) << '\n';
        cout << "a != b: " << (a != b) << '\n';
        cout << "a < b:  " << (a < b) << '\n';
        cout << "a > b:  " << (a > b) << '\n';
        cout << "a <= b: " << (a <= b) << '\n';
        cout << "a >= b: " << (a >= b) << '\n';

        cout << "\n=== EXPLICIT ===\n";

        Fraction whole(5);
        cout << "Целое число: " << whole << '\n';
        cout << "a + 2 = " << a + Fraction(2) << '\n';

        cout << "\n=== MUTABLE И CONST ===\n";

        const Fraction constant(2, 5);
        cout << "Дробь: " << constant.getValue() << '\n';
        cout << "Дробь повторно: " << constant.getValue() << '\n';
        cout << "Количество обращений: " << constant.getAccessCount() << '\n';

        cout << "\n=== ИСТОРИЯ ОПЕРАЦИЙ ===\n";

        for (int i = 0; i < static_cast<int>(history.size()); i++)
            cout << i + 1 << ". " << history[i] << '\n';

        cout << "\nКоличество объектов: "
             << Fraction::getObjectCount() << '\n';
    }
    catch (const exception& e)
    {
        cout << "Ошибка: " << e.what() << '\n';
    }

    return 0;
}