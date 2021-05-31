#include "TPlex.h"

TPlex::TPlex()
{
	left = new TPoint();
	right = new TPoint();
}

TPlex::TPlex(char* s)
{
	int count = 1;
	int cc = 0;
	int i = 0;
	int j = 0;


	while (s[i] != '\0')
	{
		if (s[i] == ' ')
			count++;
		i++;
		cc++;
	}


	if (count % 2 != 0 && count < 4)
	{
		throw "Error";
	}

	std::vector<double> obj(count);

	std::string temp = "";


	i = 0;
	for (int q = 0; q < cc; q++)
	{
		if (s[q] != ' ' && s[q] != ',')
			temp += s[q];
		else if (temp != "")
		{
			obj[j] = atoi(temp.c_str());
			j++;
			temp = "";
		}
	}
	obj[j] = atoi(temp.c_str());

	TPoint* a = new TPoint(obj[0], obj[1]);
	TPoint* b = new TPoint(obj[2], obj[3]);

	left = a;
	right = b;

	for (int q = 4; q < count; q++)
	{
		TPoint* temp_left = new TPoint(obj[q - 2], obj[q - 1]);
		TPoint* temp_right = new TPoint(obj[q], obj[q + 1]);

		this->AddLine(temp_left, temp_right);
		q++;
	}
}

TPlex::TPlex(TPoint* a, TPoint* b) : left(nullptr), right(nullptr)
{
	if (a != nullptr)
		left = a;

	if (b != nullptr)
		right = b;
}

TPlex::TPlex(const TPlex& p)
{
	left = p.left->Clone();
	right = p.right->Clone();
}

void TPlex::Print()
{
	PrintAll();
};

TBase* TPlex::PrintAll()
{
	std::cout << *this << "\n";
	return 0;
}

double TPlex::GetVal(int i) {
	throw - 1;
}

void TPlex::SetVal(double val, int i) {
	throw - 1;
}

double& TPlex::operator[](char* name) {
	throw - 1;
}

double& TPlex::operator[](int i) {
	throw - 1;
}

TBase* TPlex::GetChild(int i) {
	if (i == 0)
		return left;
	else if (i == 1)
		return right;
	else
		throw - 1;
}

void TPlex::SetChild(TBase* c, int i)
{
	if (i == 0)
		left = c;
	else if (i == 1)
		right = c;
	else
		throw - 1;
}

TBase* TPlex::GetLeft()
{
	return left;
}
TBase* TPlex::GetRight()
{
	return right;
}

TPlex* TPlex::GetLeftPlex()
{
	return dynamic_cast<TPlex*>(left);
}
TPlex* TPlex::GetRightPlex()
{
	return dynamic_cast<TPlex*>(right);
}

void TPlex::SetLeft(TBase* x)
{
	left = x;
}
void TPlex::SetRight(TBase* x)
{
	right = x;
}
bool TPlex::AddLine(TPoint* a, TPoint* b)
{
	TStack<TBase*> stack(200);
	stack.Put(this);
	bool result = false;

	while (!stack.IsEmpty())
	{

		TBase* top_base = stack.Get();
		TBase* right_base = top_base->GetChild(0);
		TBase* left_base = top_base->GetChild(1);


		if (right_base->GetChildCount() != 0)
		{
			stack.Put(right_base);
		}
		else if (right_base == a)
		{

			TPlex* new_plex = new TPlex(a, b);
			top_base->SetChild(new_plex, 0);
			result = true;
			break;
		}


		if (left_base->GetChildCount() != 0)
		{
			stack.Put(left_base);
		}
		else if (left_base == b)
		{

			TPlex* new_plex = new TPlex(b, a);
			top_base->SetChild(new_plex, 1);
			result = true;
			break;
		}
	}
	return result;
}

TBase* TPlex::Clone()
{
	return new TPlex(*this);
}

std::ostream& operator<<(std::ostream& out, const TPlex& _plex)
{
	TBase* base = const_cast<TPlex*>(&_plex);
	TPoint* point_first = nullptr;
	TPoint* point_second = nullptr;


	TStack<TBase*> stack(200);
	stack.Put(base);

	while (!stack.IsEmpty())
	{

		base = stack.Get();

		while (point_first == nullptr)
		{

			TBase* left_base = base->GetChild(0);
			TPlex* plex = dynamic_cast<TPlex*>(left_base);
			if (plex == nullptr)
			{

				point_first = dynamic_cast<TPoint*>(left_base);
			}
			else
			{

				stack.Put(base);
				base = left_base;
			}
		}

		while (point_second == nullptr)
		{

			TBase* right_base = base->GetChild(1);
			TPlex* plex = dynamic_cast<TPlex*>(right_base);

			if (plex == nullptr)
			{

				point_second = dynamic_cast<TPoint*>(right_base);
			}
			else
			{

				stack.Put(base);
				base = right_base;
			}
		}


		if (point_first != nullptr && point_second != nullptr)
		{

			out << "Point left: " << *point_first << "\n";
			out << "Point right: " << *point_second << "\n\n";
			TBase* tmp_base = point_second;


			if (!stack.IsEmpty())
			{

				base = stack.Get();

				TBase* base_left = base->GetChild(0);
				TBase* base_right = base->GetChild(1);


				TPlex* plex_left = dynamic_cast<TPlex*>(base_left);
				TPlex* plex_right = dynamic_cast<TPlex*>(base_right);


				if (plex_left != nullptr && plex_right != nullptr)
				{

					TPlex* plex_new = new TPlex(point_second, 0);

					plex_new->SetChild(base_right, 1);

					stack.Put(plex_new);

					point_second = nullptr;
					point_first = nullptr;
				}
				else
				{
					if (plex_left != nullptr)
					{
						point_first = dynamic_cast<TPoint*>(tmp_base);
						point_second = nullptr;
					}
					else
					{
						point_second = dynamic_cast<TPoint*>(tmp_base);
						point_first = nullptr;
					}

					stack.Put(base);
				}
			}
		}
	}
	return out;
}
