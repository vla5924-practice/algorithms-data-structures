#include <iostream>
#include "TTreeTable.h"

int main()
{
	TTreeTable<int, int> table;
	table.Insert(1, 2);
	table.Insert(3, 4);
	table.Remove(3);
}
