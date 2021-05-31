#include "Postfix.h"
#include <iostream>

int main() {
    std::string expression, operandNames, postfixForm;
    std::cout << "Enter your expression: ";
    getline(std::cin, expression);
    try {
        postfixForm = Postfix::PostfixForm(expression);
        std::cout << "Postfix form: " << postfixForm << std::endl;
        operandNames = Postfix::operandToString(expression);
    } catch (std::exception& e) {
        std::cout << e.what();
        return 1;
    }
    Postfix::Variables variables;
    variables.size = operandNames.size();
    variables.variables = new Postfix::Variable[variables.size];
    size_t i = 0;
    for (std::string::iterator j = operandNames.begin(); j != operandNames.end(); j++) {
        variables.variables[i].symbol = *j;
        std::cout << "Enter |" << *j << "| value: ";
        std::cin >> variables.variables[i].value;
        i++;
    }
    try {
        double result = Postfix::Calculate(postfixForm, variables);
        std::cout << "Expression result: " << result << std::endl;
    } catch (DivisionByZero& e) {
        std::cout << e.what();
        return 2;
    } catch (std::exception& e) {
        std::cout << e.what();
        return 3;
    }
}
