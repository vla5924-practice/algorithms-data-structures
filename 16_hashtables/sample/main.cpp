#include <iostream>
#include "THashTable.h"
#include "TArrayHashTable.h"

int main()
{
	THashTable<int, int> table;
	table.Insert(1, 2);
	table.Insert(3, 4);
	table.Remove(3);
	table.Find(1);

	TArrayHashTable<int, int> arrtable(100, 3);
	arrtable.Insert(1, 2);
	arrtable.Insert(3, 4);
	arrtable.Remove(3);
	arrtable.Find(1);
}
