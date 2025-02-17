
#pragma once

#include <string>
#include <optional>
#include <cmath>
#include "rational.h"
#include "pow.h"
#include <QDebug>

using Error = std::string;

// Реализация шаблонного калькулятора.

template<typename Number>
class Calculator {
public:
    
void Set (Number number) {
    qDebug() << "Set:" << number;
    number_ = number;
}

Number GetNumber() const {
    qDebug() << "GetNumber:" << number_;
    return number_;
}

std::optional<Error> Add(Number other) {
    qDebug() << "Add:" << number_ << "+" << other;
    number_ += other;
    qDebug() << "Result:" << number_;
    return std::nullopt;
}

std::optional<Error> Sub(Number other) {
    qDebug() << "Sub:" << number_ << "-" << other;
    number_ -= other;
    qDebug() << "Result:" << number_;
    return std::nullopt;
}

std::optional<Error> Mul(Number other) {
    qDebug() << "Mul:" << number_ << "*" << other;
    number_ *= other;
    qDebug() << "Result:" << number_;
    return std::nullopt;
}

std::optional<Error> Div(Number other) {
    qDebug() << "Div:" << number_ << "/" << other;
    if constexpr (std::is_integral_v<Number> || std::is_same_v<Number, Rational>) {
        if (other == 0) {
            qDebug() << "Error: Division by zero";
            return "Division by zero";
        }
    }
    number_ /= other;
    qDebug() << "Result:" << number_;
    return std::nullopt;
}

std::optional<Error> Pow(Number other) {
    if constexpr (std::is_integral_v<Number> || std::is_same_v<Number, Rational>) {
        qDebug() << "Pow:" << number_ << "^" << other;
        if (number_ == 0 && other == 0) {
            qDebug() << "Error: Zero power to zero";
            return "Zero power to zero";
        }          
    }

    if constexpr (std::is_same_v<Number, Rational>) {
        if (other.GetDenominator() != 1) {
            qDebug() << "Error: Fractional power is not supported";
            return "Fractional power is not supported";
        } else {
            number_ = ::Pow(number_, other);
            qDebug() << "Result:" << number_;
            return std::nullopt;
        }            
    }

    if constexpr (std::is_integral_v<Number>) {
        if (other < 0) {
            return "Integer negative power";
        } else {
            number_ = ::IntegerPow(number_, other);
            return std::nullopt;
        }            
    }

    if constexpr(std::is_same_v<Number, double> || std::is_same_v<Number, float>) {
        number_ = pow(number_, other);
    }

    return std::nullopt;
}

void Save() {
    qDebug() << "Save:" << number_;
    mem_ = number_;
}

bool GetHasMem() const {
    qDebug() << "GetHasMem:" << mem_.has_value();
    return mem_.has_value();
}

Number Load() {
    qDebug() << "Load:" << (mem_.has_value() ? mem_.value() : Number{});
    return number_ = mem_.value_or(Number{});
}


private:
    Number number_ = 0;
    std::optional<Number> mem_;
};