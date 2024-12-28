#include "calculator.h"
  
bool ReadNumber(Number& result) {

    if (!(cin >> result)) {
        cerr << "Error: Numeric operand expected" << endl;
        return false;
    }
        return true;

}

bool RunCalculatorCycle() {
    
    Number current_value = 0.0;
    Number memory_value = 0.0;
    bool is_memory_set = false; 
    Number inf = std::numeric_limits<Number>::infinity();
    string command;

    
    if (!ReadNumber(current_value)) {
        return false;
    }

    for (;;) {
        cin >> command;

        if (command == "q") {
            break; 
        }

        Number result;

        // Проверка на валидность операции
        if (command == "+" || command == "-" || command == "*" || command == "/" || command == "**") {
            if (!ReadNumber(result)) {
                return false; 
            }
        }

        if (command == "+") {
            current_value += result;
        } else if (command == "-") {
            current_value -= result;
        } else if (command == "*") {
            current_value *= result;
        } else if (command == "/") {
            if (result == 0) {
                current_value = inf; // Деление на ноль
            } else {
                current_value /= result;
            }
        } else if (command == "**") {
            current_value = pow(current_value, result);
        } else if (command == "=") {
            cout << current_value << endl; 
        } else if (command == ":") {
            if (!ReadNumber(current_value)) {
                return false; 
            }
        } else if (command == "c") {
            current_value = 0.0; 
        } else if (command == "s") { 
            memory_value = current_value;
            is_memory_set = true; 
        } else if (command == "l") { 
            if (!is_memory_set) { 
                cerr << "Error: Memory is empty" << endl;
                return false; 
            }
            current_value = memory_value;
        } else {
            cerr << "Error: Unknown token " << command << endl; 
            return false; 
        }
    }

    return false;
}