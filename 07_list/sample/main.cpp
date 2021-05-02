#include <iostream>
#include "TList.h"

int main()
{
    TList<int> list;

    list.InsFirst(2);
    list.InsFirst(1);
    list.InsLast(5);
    list.InsLast(6);
    list.InsAfter(list.GetFirst()->next, 3);
    list.InsBefore(list.GetLast()->prev, 4);
    list.InsBefore(list.GetFirst(), 0);
    list.InsAfter(list.GetLast(), 7);
    list.InsLast(8);
    std::cout << list << '\n';
    // 0 1 2 3 4 5 6 7 8

    TList<int> list2 = list;
    std::cout << list2 << '\n';

    list.DelFirst();
    list.DelLast();
    list.DelLast();
    list.DelFirst();
    list.Del(list.GetFirst());
    list.Del(list.GetLast());
    list.Del(list.GetFirst()->next);
    list.Del(list.GetLast()->prev);
    std::cout << list << '\n';
    // 5
}
