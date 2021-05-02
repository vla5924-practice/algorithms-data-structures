#include <iostream>
#include "TQueue.h"

int main()
{
  TQueue<int> s(3);
  s.Put(1);
  s.Put(2);
  s.Put(3);
  std::cout << s.IsFull() << ' ';
  std::cout << s.Get();
  std::cout << s.Get();
  std::cout << s.Get();
  std::cout << ' ' << s.IsEmpty();
}
