#pragma once
#include <string>

using Number = double;
class Calculator
{
private:
    Number current_number_ = 0.0;

public:
    //Заменяет текущий результат на число n    
    void Set(Number n);
    //Возвращает текущий результат вычислений калькулятора.
    //В только что сконструированном калькуляторе этот метод возвращает 0.
    Number GetNumber() const;
    //Прибавляет число n к текущему результату внутри калькулятора.
    void Add(Number n);
    //Вычитает число n из текущего результата.
    void Sub(Number n);
    //Делит текущий результат на n.
    void Div(Number n);
    //Умножает текущий результат на n.
    void Mul(Number n);
    //Возводит текущий результат в степень n.
    void Pow(Number n);
    
};


