#pragma once

#include "TPlex.h"

class TCanvas {
protected:
	std::vector<TBase*> objects;

public:
	TCanvas(){}

	void Print();
	void AddObj(TBase* a);
};
