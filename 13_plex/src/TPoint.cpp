#include "TPoint.h"

TPoint::TPoint(double _x0, double _x1) {
	x0 = _x0;
	x1 = _x1;
}

TPoint::TPoint(const TPoint& p) {
	x0 = p.x0;
	x1 = p.x1;
}

void TPoint::Print() {
	std::cout << "Point: " << x0 << " " << x1 << "\n";
}

double TPoint::GetVal(int i) {
	if (i < 0 || i > 1)
		throw - 1;
	if (i == 0)
		return x0;
	return x1;
}

void TPoint::SetVal(double val, int i) {
	if (i < 0 || i > 1)
		throw - 1;
	if (i == 0)
		x0 = val;
	if (i == 1)
		x1 = val;
}

double& TPoint::operator[](char* name) {
	if (name == "X0")
		return x0;
	else {
		if (name == "X1")
			return x1;
		else
			throw - 1;
	}
}

double& TPoint::operator[](int i) {
	if (i < 0 || i > 1)
		throw - 1;
	if (i == 0)
		return x0;
	return x1;
}

TBase* TPoint::GetChild(int i) {
	return 0;
}
void TPoint::SetChild(TBase* c, int i) {
}

double TPoint::GetX0() {
	return x0;
}

double TPoint::GetX1() {
	return x1;
}

void TPoint::SetX0(double x) {
	x0 = x;
}

void TPoint::SetX1(double x) {
	x1 = x;
}

TBase* TPoint::Clone()
{
	return new TPoint(*this);
}
