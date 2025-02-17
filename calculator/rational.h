#pragma once
#include <iostream>
#include <numeric>
#include <cassert>
#include <QDebug>

class Rational {
public:
    
    Rational() : numerator_(0), denominator_(1) { Reduction(); }
    Rational(int numerator) : numerator_(numerator), denominator_(1) { Reduction(); }
    Rational(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {
        assert(denominator != 0);
        Reduction();
    }
    Rational(const Rational& other) : numerator_(other.numerator_), denominator_(other.denominator_) {}

    
    int GetNumerator() const { return numerator_; }
    int GetDenominator() const { return denominator_; }

    // Унарные операции
    Rational operator+() const { return *this; }
    Rational operator-() const { return Rational(-numerator_, denominator_); }

    // Присваивающие операции
    Rational& operator+=(const Rational& r) {
        numerator_ = numerator_ * r.denominator_ + r.numerator_ * denominator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator-=(const Rational& r) {
        numerator_ = numerator_ * r.denominator_ - r.numerator_ * denominator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator*=(const Rational& r) {
        numerator_ *= r.numerator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator/=(const Rational& r) {
        assert(r.numerator_ != 0); 
        numerator_ *= r.denominator_;
        denominator_ *= r.numerator_;
        Reduction();
        return *this;
    }

    // Операция присваивания
    Rational& operator=(const Rational& other) = default;

    // Метод Inv
    Rational Inv() const {
        assert(numerator_ != 0); 
        return Rational(denominator_, numerator_);
    }

    // Оператор сравнения
    bool operator==(const Rational& r) const = default;

    // Трёхстороннее сравнение
    auto operator<=>(const Rational& r) const {
        return (numerator_ * r.denominator_) <=> (r.numerator_ * denominator_);
    }

private:
    int numerator_;
    int denominator_;

    // Метод для приведения дроби к несократимому виду
    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }
};

// Бинарные арифметические операции
inline Rational operator+(const Rational& r1, const Rational& r2) {
    Rational result{r1};
    result += r2;
    return result;
}

inline Rational operator-(const Rational& r1, const Rational& r2) {
    Rational result{r1};
    result -= r2;
    return result;
}

inline Rational operator*(const Rational& r1, const Rational& r2) {
    Rational result{r1};
    result *= r2;
    return result;
}

inline Rational operator/(const Rational& r1, const Rational& r2) {
    Rational result{r1};
    result /= r2;
    return result;
}

// Ввод и вывод
inline std::ostream& operator<<(std::ostream& os, const Rational& r) {
    if (r.GetDenominator() == 1) {
        os << r.GetNumerator();
    } else {
        os << r.GetNumerator() << " / " << r.GetDenominator();
    }
    return os;
}

inline std::istream& operator>>(std::istream& is, Rational& r) {
    int numerator = 0, denominator = 1;
    char div;
    if (!(is >> numerator)) {
        return is;
    }
    if (!(is >> std::ws >> div)) {
        r = Rational(numerator,1);
        is.clear();
        return is;
    }
    if (div != '/') {
        r = Rational(numerator,1);
        is.unget();
        return is;
    }
    if (!(is >> denominator) || (denominator == 0)) {
        is.setstate(std::ios::failbit);
        return is;
    }


    r = Rational(numerator, denominator);
    return is;
}

//Дебаг
inline QDebug operator<<(QDebug debug, const Rational& r) {
    QDebugStateSaver saver(debug);
    if (r.GetDenominator() == 1) {
        debug << r.GetNumerator();
    } else {
        debug << r.GetNumerator() << "/" << r.GetDenominator();
    }
    return debug;
}