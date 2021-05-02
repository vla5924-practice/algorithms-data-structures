#include <iostream>
#include "TStack.h"

int main()
{
    TStack<int> s;
    s.Put(1);
    s.Put(2);
    s.Put(3);
    std::cout << s.Get();
    std::cout << s.Get();
    std::cout << s.Get();
    std::cout << ' ' << s.IsEmpty();
}
