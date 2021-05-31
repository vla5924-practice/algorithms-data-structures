#include "TCanvas.h"

void TCanvas::Print()
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Print();
		std::cout << "\n\n";
	}
}

void TCanvas::AddObj(TBase* a)
{
	objects.push_back(a);
}
