#include <iostream>
#include "TPlex.h"

int main()
{
	TPoint a(1, 2);
	TPoint b(3, 4);
	TPoint c(5, 6);

	TPlex p(&a, &b);
	p.AddLine(&b, &c);
	p.Print();
}
