
#pragma once

#include <string>
#include <optional>
#include <cmath>
#include "rational.h"
#include "pow.h"


using Error = std::string;

// Реализация шаблонного калькулятора.

template<typename Number>
class Calculator {
public:
    
void Set (Number number) {
    number_ = number;
}

Number GetNumber() const {
    return number_;
}

std::optional<Error> Add(Number other) {
    number_ += other;
    return std::nullopt;
}

std::optional<Error> Sub(Number other) {
    number_ -= other;
    return std::nullopt;
}

std::optional<Error> Mul(Number other) {
    number_ *= other;
    return std::nullopt;
}

std::optional<Error> Div(Number other) {
    if constexpr (std::is_integral_v<Number> || std::is_same_v<Number, Rational>) {
        if (other == 0) {
            return "Division by zero";
        }
    }
    number_ /= other;
    return std::nullopt;
}

std::optional<Error> Pow(Number other) {
    if constexpr (std::is_integral_v<Number> || std::is_same_v<Number, Rational>) {
        if (number_ == 0 && other == 0) {
            return "Zero power to zero";
        }          
    }

    if constexpr (std::is_same_v<Number, Rational>) {
        if (other.GetDenominator() != 1) {
            return "Fractional power is not supported";
        } else {
            number_ = ::Pow(number_, other);
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
    mem_ = number_;
}

bool GetHasMem() const {
    return mem_.has_value();
}

Number Load() {
    return number_ = mem_.value_or(Number{});
}


private:
    Number number_ = 0;
    std::optional<Number> mem_;
};