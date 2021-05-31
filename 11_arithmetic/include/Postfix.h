#pragma once

#include "TStack.h"
#include <iostream>
#include <string>

class Postfix {
  public:
    struct Variable {
        char symbol;
        double value;
    };

    struct Variables {
        Variable* variables;
        size_t size;
    };

  private:
    static int priorityOperations(const char);
    enum class TypeSymbol { operation, operand, space, invalid, closingBracket, openingBracket };
    static TypeSymbol checksymbol(const char);
    static bool checkExpression(const std::string);
    static Variable findVariable(const Variables, const char);

  public:
    static std::string PostfixForm(std::string);
    static double Calculate(std::string, const Variables);
    static std::string operandToString(const std::string);
};
