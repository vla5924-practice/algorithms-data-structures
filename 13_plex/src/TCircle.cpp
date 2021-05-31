#include "TCircle.h"

TCircle::TCircle(double _x0, double _x1, double _radius) {
	x0 = _x0;
	x1 = _x1;
	radius = _radius;
}

TCircle::TCircle(const TCircle& p) {
	x0 = p.x0;
	x1 = p.x1;
	radius = p.radius;
}

void TCircle::Print() {
	std::cout << "Circle: X0: " << x0 << " " << " X1: " << x1 << " radius: " << radius;
}

double TCircle::GetVal(int i) {
	if (i < 0 || i > 1)
		throw - 1;
	if (i == 0)
		return x0;
	return x1;
}

void TCircle::SetVal(double val, int i) {
	if (i < 0 || i > 1)
		throw - 1;
	if (i == 0)
		x0 = val;
	if (i == 1)
		x1 = val;
}

double& TCircle::operator[](char* name) {
	if (name[1] == 0)
		return x0;
	if (name[1] == 1)
		return x1;
	throw - 1;
}

double& TCircle::operator[](int i) {
	if (i < 0 || i > 1)
		throw - 1;
	if (i == 0)
		return x0;
	return x1;
}

TBase* TCircle::GetChild(int i) {
	return 0;
}
void TCircle::SetChild(TBase* c, int i) {
}

double TCircle::GetX0() {
	return x0;
}

double TCircle::GetX1() {
	return x1;
}

double TCircle::GetRadius()
{
	return radius;
}

void TCircle::SetX0(double x) {
	x0 = x;
}

void TCircle::SetX1(double x) {
	x1 = x;
}

void TCircle::SetRadius(double r)
{
	if (r < 0)
		throw - 1;
	radius = r;
}

TBase* TCircle::Clone()
{
	return new TCircle(*this);
}

std::ostream& operator<<(std::ostream& out, const TCircle& cir)
{
	out << cir.x0 << " " << cir.x1 << " " << cir.radius;
	return out;
}
