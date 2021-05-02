#ifndef _TARRAYLIST_H_
#define _TARRAYLIST_H_

#include <iostream>

template<typename T>
class TArrayList
{
    int size;
    int count;
    int* links; // -1 last elem, -2 empty elem
    T* data;
    int head;
public:
	TArrayList(int size_ = 1);
	TArrayList(TArrayList<T>& other);
	~TArrayList();

	int GetSize();
	int GetCount();
	bool IsEmpty();
	bool IsFull();
	T& operator[](int index);

	void InsFirst(const T& d);
	void InsLast(const T& d);
	void InsBefore(const T& d, int index);
	T& GetFirst();
	T& GetLast();
	void DelLast();
	void DelFirst();
	void Del(int index);

	friend std::ostream& operator<<(std::ostream& s, TArrayList<T>& l)
	{
		for (int i = 0; i < l.count; i++)
			s << l[i] << ' ';
		return s;
	}
};

template<typename T>
TArrayList<T>::TArrayList(int size_)
{
	size = size_;
	count = 0;
	links = new int[s];
	data = new T[s];
	for (int i = 0; i < s; i++)
	{
		links[i] = -2;
		data[i] = 0;
	}
	head = -1;
}

template<typename T>
TArrayList<T>::TArrayList(TArrayList<T>& other)
{
	size = other.size;
	count = other.count;
	links = new int[size];
	data = new T[size];
	for (int i = 0; i < size; i++)
	{
		links[i] = other.links[i];
		data[i] = other.data[i];
	}
	head = other.head;
}

template<typename T>
TArrayList<T>::~TArrayList()
{
	for (int i = 0; i < count; i++)
	{
		links[i] = -2;
		data[i] = 0;
	}
	head = -1;
	count = 0;

	delete[] links;
	delete[] data;
	size = 0;
}

template<typename T>
int TArrayList<T>::GetSize()
{
	return size;
}

template<typename T>
int TArrayList<T>::GetCount()
{
	return count;
}

template<typename T>
bool TArrayList<T>::IsEmpty()
{
	return head == -1;
}

template<typename T>
bool TArrayList<T>::IsFull()
{
	return count == size;
}

template<typename T>
T& TArrayList<T>::operator[](int index)
{
	if (index < 0 || index >= count)
		throw "Incorrect index";
	int counter = 0;
	int current = head;
	while (current != -1)
	{
		if (counter == index)
			break;
		current = links[current];
		counter++;
	}
	return data[current];
}

template<typename T>
void TArrayList<T>::InsLast(const T& d)
{
	if (IsFull())
		throw "List full";
	if (IsEmpty())
	{
		head = 0;
		data[0] = d;
		links[0] = -1;
	}
	else
	{
		int last = head;
		for (int i = 0; i < count; i++)
			if (links[last] != -1)
				last = links[last];
			else
				break;
		int current = 0;
		for (int i = 0; i < size; i++)
			if (links[i] == -2)
			{
				current = i;
				break;
			}
		data[current] = d;
		links[last] = current;
		links[current] = -1;
	};
	count++;
}

template<typename T>
void TArrayList<T>::DelLast()
{
	if (IsEmpty())
		throw "List empty";
	if (links[head] == -1)
	{
		links[head] = -2;
		head = -1;
	}
	else
	{
		int last = head;
		int previous = 0;
		for (int i = 0; i < count; i++)
			if (links[last] != -1)
			{
				previous = last;
				last = links[last];
			}
			else
			{
				links[last] = -2;
				links[previous] = -1;
			}
	}
	count--;
}

template<typename T>
void TArrayList<T>::DelFirst()
{
	if (IsEmpty())
		throw "List empty";
	if (links[head] == -1)
	{
		links[head] = -2;
		head = -1;
	}
	else
	{
		int first = links[head];
		links[head] = -2;
		head = first;
	}
	count--;
}

template<typename T>
void TArrayList<T>::InsFirst(const T& d)
{
	if (IsFull())
		throw "List full";
	if (IsEmpty())
	{
		head = 0;
		data[0] = d;
		links[0] = -1;
	}
	else
	{
		int current = 0;
		while (links[current] != -2)
			current++;
		data[current] = d;
		links[current] = head;
		head = current;
	}
	count++;
}

template<typename T>
void TArrayList<T>::InsBefore(const T& d, int index)
{
	if (index < 0 || index > count)
		throw "Incorrect index";
	if (IsFull())
		throw "Full list";
	if (index == 0)
		InsFirst(d);
	else
	{
		int current = 0;
		while (links[current] != -2)
			current++;
		int previous = head;
		int counter = 0;
		while (counter != index - 1)
		{
			if (links[previous] == -1)
				break;
			previous = links[previous];
			counter++;
		}
		data[current] = d;
		links[current] = links[previous];
		links[previous] = current;
		count++;
	}
}

template<typename T>
T& TArrayList<T>::GetFirst()
{
	return operator[](0);
}

template<typename T>
T& TArrayList<T>::GetLast()
{
	return operator[](count - 1);
}

template<typename T>
void TArrayList<T>::Del(int index)
{
	if (index < 0 || index >= count)
		throw "Incorrect index";
	if (index == 0)
		DelFirst();
	else
	{
		int toDelete = head;
		int previous = 0;
		int counter = 0;

		while (counter != index)
		{
			if (counter == index - 1)
				previous = toDelete;
			toDelete = links[toDelete];
			counter++;
		}

		links[previous] = links[toDelete];
		links[toDelete] = -2;
		count--;
	}
}

#endif
