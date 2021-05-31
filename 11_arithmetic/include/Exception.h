#pragma once

#include <exception>
#include <string>

class Full : public std::exception {
    const std::string what_Str = "Stack is full.\n";

  public:
    const char* what() const {
        return what_Str.c_str();
    }
};

class Empty : public std::exception {
    const std::string what_Str = "Stack is empty.\n";

  public:
    const char* what() const {
        return what_Str.c_str();
    }
};

class invalidSymbol : public std::exception {
    const std::string what_Str = "Invalid symbol.\n";

  public:
    const char* what() const {
        return what_Str.c_str();
    }
};

class symbolNotFound : public std::exception {
    const std::string what_Str = "Symbol not found.\n";

  public:
    const char* what() const {
        return what_Str.c_str();
    }
};

class DivisionByZero : public std::exception {
    const std::string what_Str = "Division by zero.\n";

  public:
    const char* what() const {
        return what_Str.c_str();
    }
};

class invalidOperation : public std::exception {
    const std::string what_Str = "Invalid operation.\n";

  public:
    const char* what() const {
        return what_Str.c_str();
    }
};

class invalidExpression : public std::exception {
    const std::string what_Str = "The wrong expression.\n";

  public:
    const char* what() const {
        return what_Str.c_str();
    }
};
