#include "Postfix.h"
#include "Exception.h"

Postfix::TypeSymbol Postfix::checksymbol(char temp) {
    if ((temp == '*') || (temp == '/') || (temp == '+') || (temp == '-'))
        return TypeSymbol::operation;
    if (temp == ')')
        return TypeSymbol::closingBracket;
    if (temp == '(')
        return TypeSymbol::openingBracket;
    if (isalpha(temp))
        return TypeSymbol::operand;
    if (temp == ' ')
        return TypeSymbol::space;
    else
        return TypeSymbol::invalid;
}

bool Postfix::checkExpression(const std::string expression) {
    size_t size = expression.size();
    size_t openingbracket = 0, closingbracket = 0;
    Postfix::TypeSymbol type, two_symbol = TypeSymbol::invalid;
    for (size_t i = 0; i < size; i++) {
        type = checksymbol(expression[i]);
        if (type == TypeSymbol::space)
            continue;
        if (((type == TypeSymbol::operation) && ((i == 0) || (two_symbol == TypeSymbol::operation))) ||
            ((type == TypeSymbol::operand) && (two_symbol == TypeSymbol::operand)))
            return false;
        else if ((two_symbol == TypeSymbol::operand) && (type == TypeSymbol::openingBracket) ||
                 (two_symbol == TypeSymbol::openingBracket) && (type == TypeSymbol::closingBracket))
            return false;
        else if ((two_symbol == TypeSymbol::operation) && (type == TypeSymbol::closingBracket))
            return false;
        else if ((two_symbol == TypeSymbol::openingBracket) && (type == TypeSymbol::operation))
            return false;
        else if ((two_symbol == TypeSymbol::closingBracket) && (type == TypeSymbol::operand))
            return false;
        if (type == TypeSymbol::invalid)
            return false;
        else if (type == TypeSymbol::closingBracket)
            closingbracket++;
        else if (type == TypeSymbol::openingBracket)
            openingbracket++;
        else if (openingbracket < closingbracket)
            return false;
        two_symbol = type;
    }
    if ((closingbracket != openingbracket) || (two_symbol == TypeSymbol::operation))
        return false;
    return true;
}

std::string Postfix::operandToString(const std::string expression) {
    size_t size = expression.size();
    std::string result;
    Postfix::TypeSymbol type;
    for (std::string::const_iterator i = expression.begin(); i != expression.end(); i++) {
        size_t flag = 0;
        for (std::string::const_iterator j = result.begin(); j != result.end(); j++)
            if (*i == *j) {
                flag = 1;
                break;
            }
        if (flag == 1)
            continue;
        type = checksymbol(*i);
        if (type == TypeSymbol::operand)
            result += *i;
    }
    return result;
}

int Postfix::priorityOperations(const char symbol) {
    if ((symbol == '*') || symbol == '/')
        return 3;
    if ((symbol == '+') || symbol == '-')
        return 2;
    if (symbol == ')')
        return 1;
    else
        return 0;
}

Postfix::Variable Postfix::findVariable(const Variables variables, const char name) {
    for (size_t i = 0; i < variables.size; i++) {
        const Variable& variable = variables.variables[i];
        if (variable.symbol == name)
            return Variable(variable);
    }
    return Variable();
}

std::string Postfix::PostfixForm(std::string expression) {
    if (!checkExpression(expression))
        throw invalidExpression();
    size_t sizeString = expression.size();
    TStack<char> first(sizeString), second(sizeString);
    TypeSymbol type;
    for (size_t i = 0; i < sizeString; i++) {
        type = checksymbol(expression[i]);
        if (type == TypeSymbol::space)
            continue;
        if (type == TypeSymbol::operand)
            second.Put(expression[i]);
        else if (type == TypeSymbol::openingBracket)
            first.Put(expression[i]);
        else if (type == TypeSymbol::closingBracket) {
            while (first.Check() != '(') {
                second.Put(first.Check());
                first.Get();
            }
            if (!first.IsEmpty())
                first.Get();
        } else if ((first.IsEmpty()) || (priorityOperations(expression[i]) > priorityOperations(first.Check())))
            first.Put(expression[i]);
        else {
            while ((!first.IsEmpty()) && (priorityOperations(expression[i]) <= priorityOperations(first.Check()))) {
                second.Put(first.Check());
                first.Get();
            }
            first.Put(expression[i]);
        }
    }
    while (!first.IsEmpty()) {
        second.Put(first.Check());
        first.Get();
    }
    std::string result;
    while (!second.IsEmpty()) {
        result += second.Check();
        second.Get();
    }
    std::reverse(result.rbegin(), result.rend());
    return result;
}

double Postfix::Calculate(std::string postfixForm, const Variables variables) {
    size_t sizeForm = postfixForm.size();
    TStack<double> counting(sizeForm);
    for (size_t i = 0; i < sizeForm; i++) {
        TypeSymbol type = checksymbol(postfixForm[i]);
        if (type == TypeSymbol::operand) {
            Variable variable = findVariable(variables, postfixForm[i]);
            if (!variable.symbol)
                throw symbolNotFound();
            counting.Put(variable.value);
        } else if (type == TypeSymbol::operation) {
            double first, second;
            try {
                first = counting.Check();
                counting.Get();
                second = counting.Check();
                counting.Get();
            } catch (Empty) {
                throw invalidExpression();
            }
            switch (postfixForm[i]) {
            case '+':
                counting.Put(second + first);
                break;
            case '-':
                counting.Put(second - first);
                break;
            case '*':
                counting.Put(second * first);
                break;
            case '/':
                if (first == 0)
                    throw DivisionByZero();
                counting.Put(second / first);
                break;
            default:
                throw invalidOperation();
                break;
            }
        }
    }
    double result = 0.0;
    try {
        result = counting.Check();
        counting.Get();
    } catch (Empty) {
        throw invalidExpression();
    }
    if (counting.IsEmpty())
        return result;
    else
        throw invalidExpression();
}
